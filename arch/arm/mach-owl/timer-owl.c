/*
 * arch/arm/mach-owl/timer.c
 *
 * time0 use as clocksource
 * timer1 for time tick at boot stage
 *
 * Copyright 2012 Actions Semi Inc.
 * Author: Actions Semi, Inc.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/time.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/clockchips.h>
#include <linux/clocksource.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/cpu.h>
#include <asm/sched_clock.h>

#include <mach/hardware.h>

/*
 * clocksource
 */
static cycle_t owl_read_timer(struct clocksource *cs)
{
	return (cycle_t)act_readl(T0_VAL);
}

static struct clocksource owl_clksrc = {
	.name		= "timer0",
	.rating		= 200,
	.read		= owl_read_timer,
	.mask		= CLOCKSOURCE_MASK(32),
	.shift		= 20,
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

/*
 * Using this local implementation sched_clock which uses timer0
 * to get some better resolution when scheduling the kernel.
 */
static u32 notrace owl_read_sched_clock(void)
{
	return act_readl(T0_VAL);
}

/* Clockevent device: use one-shot mode */
static void owl_clkevt_mode(enum clock_event_mode mode,
				 struct clock_event_device *dev)
{
	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		pr_err("%s: periodic mode not supported\n", __func__);
		break;
	case CLOCK_EVT_MODE_ONESHOT:
		act_writel(0, T1_CTL);
		act_writel(0, T1_VAL);
		act_writel(0, T1_CMP);
		break;
	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_UNUSED:
		/* disable irq */
		act_writel(0, T1_CTL);
		break;
	case CLOCK_EVT_MODE_RESUME:
		break;
	}
}

static int owl_clkevt_next(unsigned long evt, struct clock_event_device *ev)
{
	/* disable timer */
	act_writel(0x0, T1_CTL);

	/* writing the value has immediate effect */
	act_writel(0, T1_VAL);
	act_writel(evt, T1_CMP);

	/* enable timer & IRQ */
	act_writel(0x6, T1_CTL);

	return 0;
}

static struct clock_event_device owl_clkevt = {
	.name		= "timer1",
	.features	= CLOCK_EVT_FEAT_ONESHOT,
	.rating	 = 200,
	.set_mode	= owl_clkevt_mode,
	.set_next_event	= owl_clkevt_next,
};

/*
 * IRQ Handler for timer 1 of the MTU block.
 */
static irqreturn_t owl_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *evdev = dev_id;

	act_writel(1 << 0, T1_CTL); /* Interrupt clear reg */
	evdev->event_handler(evdev);

	return IRQ_HANDLED;
}

static struct irqaction owl_timer_irq = {
	.name		= "timer1_tick",
	.flags		= IRQF_DISABLED | IRQF_TIMER,
	.handler	= owl_timer_interrupt,
	.dev_id		= &owl_clkevt,
};

static void owl_check_and_reset_time0_in_cpu0_idle(unsigned long flag)
{
	static unsigned int val = 0;
	
	if(smp_processor_id() != 0 || (act_readl(T0_CTL) & 0x4) == 0)
		return;
	
	if(flag == IDLE_START)
		val = act_readl(T0_VAL);
	else if(flag == IDLE_END && act_readl(T0_VAL) == val)
	{
		pr_err("time0 crashed, now reset it.\n");
		act_writel(0, T0_CTL);
		while(act_readl(T0_CTL) & 0x4) 
		{
			//do nothing here, just wait
		}
		act_writel(val, T0_VAL);
		act_writel(0x4, T0_CTL);
		pr_err("time0 reset successed.\n");
	}
}

static int owl_idle_notifier(struct notifier_block *nb,
					     unsigned long val,
					     void *data)
{
	owl_check_and_reset_time0_in_cpu0_idle(val);
    return 0;
}

static struct notifier_block owl_idle_nb = {
    .notifier_call = owl_idle_notifier,
};

static void owl_register_idle_notifier(void)
{
	idle_notifier_register(&owl_idle_nb);
}

void __init owl_gp_timer_init(void)
{
	unsigned long rate;

	/* enable the clock of timer */
	act_setl(1 << 27, CMU_DEVCLKEN1);

	rate = 24000000;

	/* Timer 0 is the free running clocksource */
	act_writel(0, T0_CTL);
	act_writel(0, T0_VAL);
	act_writel(0, T0_CMP);
	act_writel(4, T0_CTL);

	setup_sched_clock(owl_read_sched_clock, 32, rate);
	clocksource_register_hz(&owl_clksrc, rate);
	owl_register_idle_notifier();
	
	/* Timer 1 is used for events, fix according to rate */
	act_writel(0, T1_CTL);
	act_writel(0, T1_VAL);
	act_writel(0, T1_CMP);

	setup_irq(OWL_IRQ_TIMER1, &owl_timer_irq);
	owl_clkevt.cpumask = cpumask_of(0);
	clockevents_config_and_register(&owl_clkevt, rate,
					0xf, 0xffffffff);
}

