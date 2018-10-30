#include <linux/module.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <mach/hardware.h>

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/ioport.h>
//#include <mach/board.h>

//#include <mach/gpio.h>

#include <asm/gpio.h>
#include <mach/hardware.h>
#include <linux/of.h>
#include <linux/of_gpio.h>

int GPS_POWER_EN_PIN = -1;

static ssize_t show_UbloxState(struct device *dev, struct device_attribute *attr, char *buf, size_t count) 
{
	char * show_string;
		
	return sprintf(buf, "%d\n", 0); 
}

char *strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (*s++ == '\0')
			return NULL;
	return (char *)s;
}

static int power_switch(int state){
	if(state == 1) {
		gpio_direction_output(GPS_POWER_EN_PIN, 1);
	}else{
		gpio_direction_output(GPS_POWER_EN_PIN, 0);
	}
}


static ssize_t store_UbloxState(struct device *dev, struct device_attribute *attr,
		 const char *buf, size_t count)
{
	unsigned int status=0;
	int size = count;
	
	//printk("store_UbloxState count = %d \n",count);
	if(*buf == '0') {
		printk("close ublox power \n");
		power_switch(0);
	}else if(*buf == '1') {
		printk("open ublox power \n");
		power_switch(1);
	}	
	
	
    	return count;
}


static int get_gpio(){
	struct device_node *np;
	enum of_gpio_flags flags;
	int state;
	np = of_find_compatible_node(NULL, NULL, "gps,ublox,power,ctl");
	if (NULL == np) {
		printk( "No bluetooth node found in dts\n");
		return -1;
	}

	GPS_POWER_EN_PIN = of_get_named_gpio_flags(np, "gps_en_gpios", 0, &flags);
	
	if(GPS_POWER_EN_PIN < 0)
		return -1;
	
	state = gpio_request(GPS_POWER_EN_PIN,"gps_power_en");
	if(state < 0) {
		printk("request gpio fail %d  %d \n",GPS_POWER_EN_PIN,state);
		return -1;
	}
	
	printk("GPS_POWER_EN_PIN = %d\n",GPS_POWER_EN_PIN);
	return 0;
}




static DEVICE_ATTR(UbloxState, S_IRUGO|S_IWUSR|S_IWGRP|S_IWOTH,
       show_UbloxState, store_UbloxState);


static struct attribute *UbloxState_attributes[] = {
    &dev_attr_UbloxState.attr,
    NULL
};

static struct attribute_group UbloxState_attribute_group = {
    .attrs = UbloxState_attributes
};

static  int hc_led_probe(struct platform_device *pdev)
{
	int ret ;
	printk("hc_led_probe");
	ret = sysfs_create_group(&pdev->dev.kobj,&UbloxState_attribute_group);

	return 0;
}

static  int ublox_power_remove(struct platform_device *pdev)
{

	return 0;
}

static int ublox_power_suspend(struct platform_device *pdev, pm_message_t m)
{
	
	return 0;
}

static int ublox_power_resume(struct platform_device *pdev)
{
	return 0;
}

static void ublox_power_shutdown(struct platform_device *pdev)
{
	//printk("%s\n",__FUNCTION__);

	return;
}

static void ublox_power_release(struct device * dev)
{	
	return;
}



static struct platform_device ublox_power_device = {
	.name           = "ublox-power",
	.dev = {
		//if not add has waring "does not have a release() function, it is broken and must be fixed"
		.release = ublox_power_release,
	}
};

static struct platform_driver ublox_power_driver = {
	.probe      = hc_led_probe,
	.remove     = ublox_power_remove,
	.driver     = {
		.name = "ublox-power",
		.owner = THIS_MODULE,
	},

	.suspend    = ublox_power_suspend,
	.resume     = ublox_power_resume,
	.shutdown =  ublox_power_shutdown,
};

static int __init ublox_power_init(void)
{	
	printk("%s\n",__FUNCTION__);
	if(get_gpio() < 0)
		return -1;
	platform_device_register(&ublox_power_device);
	platform_driver_register(&ublox_power_driver);

	return 0;
}
module_init(ublox_power_init);

static void __exit ublox_power_exit(void)
{
	printk("%s\n",__FUNCTION__);
	platform_driver_unregister(&ublox_power_driver);    
	platform_device_unregister(&ublox_power_device);
}
module_exit(ublox_power_exit);
MODULE_AUTHOR("Actions Semi, Inc");
MODULE_DESCRIPTION("ublox_power driver interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:led driver interface");
MODULE_VERSION("1.0.0");
























