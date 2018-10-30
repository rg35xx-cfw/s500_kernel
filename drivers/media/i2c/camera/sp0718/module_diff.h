/*
 * module different macro
 *
 * Copyright (C) 2008 Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __MODULE_DIFF_H__
#define __MODULE_DIFF_H__

#include "./../module_comm/module_comm.h"


#define CAMERA_MODULE_NAME 		"sp0718"
#define CAMERA_MODULE_PID		0x71
#define VERSION(pid, ver) 		((pid<<8)|(ver&0xFF))

#define MODULE_I2C_REAL_ADDRESS  (0x42>>1)
#define MODULE_I2C_REG_ADDRESS		(0x21)

#define I2C_REGS_WIDTH			1
#define I2C_DATA_WIDTH			1

#define DEFAULT_VSYNC_ACTIVE_LEVEL		V4L2_MBUS_VSYNC_ACTIVE_HIGH
#define DEFAULT_PCLK_SAMPLE_EDGE      V4L2_MBUS_PCLK_SAMPLE_RISING

#define DEFAULT_POWER_LINE_FREQUENCY	V4L2_CID_POWER_LINE_FREQUENCY_50HZ



#define PID						0x02 /* Product ID Number */


#define OUTTO_SENSO_CLOCK 		24000000


#define MODULE_DEFAULT_WIDTH	WIDTH_VGA
#define MODULE_DEFAULT_HEIGHT	HEIGHT_VGA
#define MODULE_MAX_WIDTH		WIDTH_VGA
#define MODULE_MAX_HEIGHT		HEIGHT_VGA

#define AHEAD_LINE_NUM			15    //10行 = 50次循环
#define DROP_NUM_CAPTURE		3
#define DROP_NUM_PREVIEW		2
static unsigned int frame_rate_vga[]   = {30,};
/*
 * register setting for window size
 */
#define SP0718_NORMAL_Y0ffset  0x20
#define SP0718_LOWLIGHT_Y0ffset  0x25
//AE target
#define  SP0718_P1_0xeb  0x78
#define  SP0718_P1_0xec  0x6c
//HEQ
#define  SP0718_P1_0x10  0x00//outdoor
#define  SP0718_P1_0x14  0x20
#define  SP0718_P1_0x11  0x00//nr
#define  SP0718_P1_0x15  0x18
#define  SP0718_P1_0x12  0x00//dummy
#define  SP0718_P1_0x16  0x10
#define  SP0718_P1_0x13  0x00//low
#define  SP0718_P1_0x17  0x00



static const struct regval_list module_init_regs[] =
{
	
	{0xfd,0x00},
	{0x1C,0x00},
	{0x31,0x10},
	{0x27,0xb3},//0xb3	//2x gain
	{0x1b,0x17},
	{0x26,0xaa},
	{0x37,0x02},
	{0x28,0x8f},
	{0x1a,0x73},
	{0x1e,0x1b},
	{0x21,0x06},  //blackout voltage
	{0x22,0x2a},  //colbias
	{0x0f,0x3f},
	{0x10,0x3e},
	{0x11,0x00},
	{0x12,0x01},
	{0x13,0x3f},
	{0x14,0x04},
	{0x15,0x30},
	{0x16,0x31},
	{0x17,0x01},
	{0x69,0x31},
	{0x6a,0x2a},
	{0x6b,0x33},
	{0x6c,0x1a},
	{0x6d,0x32},
	{0x6e,0x28},
	{0x6f,0x29},
	{0x70,0x34},
	{0x71,0x18},
	{0x36,0x00},//02 delete badframe
	{0xfd,0x01},
	{0x5d,0x51},//position
	{0xf2,0x19},

	//Blacklevel
	{0x1f,0x10},
	{0x20,0x1f},
	//pregain 
	{0xfd,0x02},
	{0x00,0x88},
	{0x01,0x88},
	//SI15_SP0718 24M 50Hz 15-8fps 
	//ae setting
	{0xfd,0x00},
	{0x03,0x01},
	{0x04,0xce},
	{0x06,0x00},
	{0x09,0x02},
	{0x0a,0xc4},
	{0xfd,0x01},
	{0xef,0x4d},
	{0xf0,0x00},
	{0x02,0x0c},
	{0x03,0x01},
	{0x06,0x47},
	{0x07,0x00},
	{0x08,0x01},
	{0x09,0x00},
	//Status   
	{0xfd,0x02},
	{0xbe,0x9c},
	{0xbf,0x03},
	{0xd0,0x9c},
	{0xd1,0x03},
	{0xfd,0x01},
	{0x5b,0x03},
	{0x5c,0x9c},

	//rpc
	{0xfd,0x01},
	{0xe0,0x40},////24//4c//48//4c//44//4c//3e//3c//3a//38//rpc_1base_max
	{0xe1,0x30},////24//3c//38//3c//36//3c//30//2e//2c//2a//rpc_2base_max
	{0xe2,0x2e},////24//34//30//34//2e//34//2a//28//26//26//rpc_3base_max
	{0xe3,0x2a},////24//2a//2e//2c//2e//2a//2e//26//24//22//rpc_4base_max
	{0xe4,0x2a},////24//2a//2e//2c//2e//2a//2e//26//24//22//rpc_5base_max
	{0xe5,0x28},////24//2c//2a//2c//28//2c//24//22//20//rpc_6base_max
	{0xe6,0x28},////24//2c//2a//2c//28//2c//24//22//20//rpc_7base_max
	{0xe7,0x26},////24//2a//28//2a//26//2a//22//20//20//1e//rpc_8base_max
	{0xe8,0x26},////24//2a//28//2a//26//2a//22//20//20//1e//rpc_9base_max
	{0xe9,0x26},////24//2a//28//2a//26//2a//22//20//20//1e//rpc_10base_max
	{0xea,0x26},////24//28//26//28//24//28//20//1f//1e//1d//rpc_11base_max
	{0xf3,0x26},////24//28//26//28//24//28//20//1f//1e//1d//rpc_12base_max
	{0xf4,0x26},////24//28//26//28//24//28//20//1f//1e//1d//rpc_13base_max
	//ae gain &status
	{0xfd,0x01},
	{0x04,0xe0},//rpc_max_indr
	{0x05,0x26},//1e//rpc_min_indr 
	{0x0a,0xa0},//rpc_max_outdr
	{0x0b,0x26},//rpc_min_outdr
	{0x5a,0x40},//dp rpc   
	{0xfd,0x02}, 
	{0xbc,0xa0},//rpc_heq_low
	{0xbd,0x80},//rpc_heq_dummy
	{0xb8,0x80},//mean_normal_dummy
	{0xb9,0x90},//mean_dummy_normal

	//ae target
	{0xfd,0x01}, 
	{0xeb,SP0718_P1_0xeb},//78 
	{0xec,SP0718_P1_0xec},//78
	{0xed,0x0a},	
	{0xee,0x10},

	//lsc		
	{0xfd,0x01},
	{0x26,0x30},
	{0x27,0x2c},
	{0x28,0x07},
	{0x29,0x08},
	{0x2a,0x40},
	{0x2b,0x03},
	{0x2c,0x00},
	{0x2d,0x00},
	  
	{0xa1,0x24},
	{0xa2,0x27},
	{0xa3,0x27},
	{0xa4,0x2b},
	{0xa5,0x1c},
	{0xa6,0x1a},
	{0xa7,0x1a},
	{0xa8,0x1a},
	{0xa9,0x18},
	{0xaa,0x1c},
	{0xab,0x17},
	{0xac,0x17},
	{0xad,0x08},
	{0xae,0x08},
	{0xaf,0x08},
	{0xb0,0x00},
	{0xb1,0x00},
	{0xb2,0x00},
	{0xb3,0x00},
	{0xb4,0x00},
	{0xb5,0x02},
	{0xb6,0x06},
	{0xb7,0x00},
	{0xb8,0x00},
	   
	   
	//DP	   
	{0xfd,0x01},
	{0x48,0x09},
	{0x49,0x99},
		
	//awb		
	{0xfd,0x01},
	{0x32,0x05},
	{0xfd,0x00},
	{0xe7,0x03},
	{0xfd,0x02},
	{0x26,0xc8},
	{0x27,0xb6},
	{0xfd,0x00},
	{0xe7,0x00},
	{0xfd,0x02},
	{0x1b,0x80},
	{0x1a,0x80},
	{0x18,0x26},
	{0x19,0x28},
	{0xfd,0x02},
	{0x2a,0x00},
	{0x2b,0x08},
	{0x28,0xef},//0xa0//f8
	{0x29,0x20},

	//d65 90  e2 93
	{0x66,0x42},//0x59//0x60////0x58//4e//0x48
	{0x67,0x62},//0x74//0x70//0x78//6b//0x69
	{0x68,0xee},//0xd6//0xe3//0xd5//cb//0xaa
	{0x69,0x18},//0xf4//0xf3//0xf8//ed
	{0x6a,0xa6},//0xa5
	//indoor 91
	{0x7c,0x3b},//0x45//30//41//0x2f//0x44
	{0x7d,0x5b},//0x70//60//55//0x4b//0x6f
	{0x7e,0x15},//0a//0xed
	{0x7f,0x39},//23//0x28
	{0x80,0xaa},//0xa6
	//cwf	92 
	{0x70,0x3e},//0x38//41//0x3b
	{0x71,0x59},//0x5b//5f//0x55
	{0x72,0x31},//0x30//22//0x28
	{0x73,0x4f},//0x54//44//0x45
	{0x74,0xaa},
	//tl84	93 
	{0x6b,0x1b},//0x18//11
	{0x6c,0x3a},//0x3c//25//0x2f
	{0x6d,0x3e},//0x3a//35
	{0x6e,0x59},//0x5c//46//0x52
	{0x6f,0xaa},
	//f    94
	{0x61,0xea},//0x03//0x00//f4//0xed
	{0x62,0x03},//0x1a//0x25//0f//0f
	{0x63,0x6a},//0x62//0x60//52//0x5d
	{0x64,0x8a},//0x7d//0x85//70//0x75//0x8f
	{0x65,0x6a},//0xaa//6a
	  
	{0x75,0x80},
	{0x76,0x20},
	{0x77,0x00},
	{0x24,0x25},

	//针对室内调偏不过灯箱测试使用//针对人脸调偏
	{0x20,0xd8},
	{0x21,0xa3},//82//a8偏暗照度还有调偏
	{0x22,0xd0},//e3//bc
	{0x23,0x86},

	//outdoor r\b range
	{0x78,0xc3},//d8
	{0x79,0xba},//82
	{0x7a,0xa6},//e3
	{0x7b,0x99},//86


	//skin 
	{0x08,0x15},//
	{0x09,0x04},//
	{0x0a,0x20},//
	{0x0b,0x12},//
	{0x0c,0x27},//
	{0x0d,0x06},//
	{0x0e,0x63},//

	//wt th
	{0x3b,0x10},
	//gw
	{0x31,0x60},
	{0x32,0x60},
	{0x33,0xc0},
	{0x35,0x6f},

	// sharp
	{0xfd,0x02},
	{0xde,0x0f},
	{0xd2,0x02},//6//控制黑白边；0-边粗，f-变细
	{0xd3,0x06},
	{0xd4,0x06},
	{0xd5,0x06},
	{0xd7,0x20},//10//2x根据增益判断轮廓阈值
	{0xd8,0x30},//24//1A//4x
	{0xd9,0x38},//28//8x
	{0xda,0x38},//16x
	{0xdb,0x08},//
	{0xe8,0x58},//48//轮廓强度
	{0xe9,0x48},
	{0xea,0x30},
	{0xeb,0x20},
	{0xec,0x48},//60//80
	{0xed,0x48},//50//60
	{0xee,0x30},
	{0xef,0x20},
	//平坦区域锐化力度
	{0xf3,0x50},
	{0xf4,0x10},
	{0xf5,0x10},
	{0xf6,0x10},
	//dns		
	{0xfd,0x01},
	{0x64,0x44},//沿方向边缘平滑力度  //0-最强，8-最弱
	{0x65,0x22},
	{0x6d,0x04},//8//强平滑（平坦）区域平滑阈值
	{0x6e,0x06},//8
	{0x6f,0x10},
	{0x70,0x10},
	{0x71,0x08},//0d//弱平滑（非平坦）区域平滑阈值	
	{0x72,0x12},//1b
	{0x73,0x1c},//20
	{0x74,0x24},
	{0x75,0x44},//[7:4]平坦区域强度，[3:0]非平坦区域强度；0-最强，8-最弱；
	{0x76,0x02},//46
	{0x77,0x02},//33
	{0x78,0x02},
	{0x81,0x10},//18//2x//根据增益判定区域阈值，低于这个做强平滑、大于这个做弱平滑；
	{0x82,0x20},//30//4x
	{0x83,0x30},//40//8x
	{0x84,0x48},//50//16x
	{0x85,0x0c},//12/8+reg0x81 第二阈值，在平坦和非平坦区域做连接
	{0xfd,0x02},
	{0xdc,0x0f},
	   
	//gamma    
	{0xfd,0x01},
	{0x8b,0x00},//00//00	 
	{0x8c,0x0a},//0c//09	 
	{0x8d,0x16},//19//17	 
	{0x8e,0x1f},//25//24	 
	{0x8f,0x2a},//30//33	 
	{0x90,0x3c},//44//47	 
	{0x91,0x4e},//54//58	 
	{0x92,0x5f},//61//64	 
	{0x93,0x6c},//6d//70	 
	{0x94,0x82},//80//81	 
	{0x95,0x94},//92//8f	 
	{0x96,0xa6},//a1//9b	 
	{0x97,0xb2},//ad//a5	 
	{0x98,0xbf},//ba//b0	 
	{0x99,0xc9},//c4//ba	 
	{0x9a,0xd1},//cf//c4	 
	{0x9b,0xd8},//d7//ce	 
	{0x9c,0xe0},//e0//d7	 
	{0x9d,0xe8},//e8//e1	 
	{0x9e,0xef},//ef//ea	 
	{0x9f,0xf8},//f7//f5	 
	{0xa0,0xff},//ff//ff	 
	//CCM	   
	{0xfd,0x02},
	{0x15,0xd0},//b>th
	{0x16,0x95},//r<th
	//gc镜头照人脸偏黄
	//!F		
	{0xa0,0x80},//80
	{0xa1,0x00},//00
	{0xa2,0x00},//00
	{0xa3,0x00},//06
	{0xa4,0x8c},//8c
	{0xa5,0xf4},//ed
	{0xa6,0x0c},//0c
	{0xa7,0xf4},//f4
	{0xa8,0x80},//80
	{0xa9,0x00},//00
	{0xaa,0x30},//30
	{0xab,0x0c},//0c 
	//F 	   
	{0xac,0x8c},
	{0xad,0xf4},
	{0xae,0x00},
	{0xaf,0xed},
	{0xb0,0x8c},
	{0xb1,0x06},
	{0xb2,0xf4},
	{0xb3,0xf4},
	{0xb4,0x99},
	{0xb5,0x0c},
	{0xb6,0x03},
	{0xb7,0x0f},
		
	//sat u 	
	{0xfd,0x01},
	{0xd3,0x9c},//0x88//50
	{0xd4,0x98},//0x88//50
	{0xd5,0x8c},//50
	{0xd6,0x84},//50
	//sat v   
	{0xd7,0x9c},//0x88//50
	{0xd8,0x98},//0x88//50
	{0xd9,0x8c},//50
	{0xda,0x84},//50
	//auto_sat	
	{0xdd,0x30},
	{0xde,0x10},
	{0xd2,0x01},//autosa_en
	{0xdf,0xff},//a0//y_mean_th
		
	//uv_th 	
	{0xfd,0x01},
	{0xc2,0xaa},
	{0xc3,0xaa},
	{0xc4,0x66},
	{0xc5,0x66}, 

	//heq
	{0xfd,0x01},
	{0x0f,0xff},
	{0x10,SP0718_P1_0x10}, //out
	{0x14,SP0718_P1_0x14}, 
	{0x11,SP0718_P1_0x11}, //nr
	{0x15,SP0718_P1_0x15},	
	{0x12,SP0718_P1_0x12}, //dummy
	{0x16,SP0718_P1_0x16}, 
	{0x13,SP0718_P1_0x13}, //low	
	{0x17,SP0718_P1_0x17},		

	{0xfd,0x01},
	{0xcd,0x20},
	{0xce,0x1f},
	{0xcf,0x20},
	{0xd0,0x55},  
	//auto 
	{0xfd,0x01},
	{0xfb,0x33},
	{0x32,0x15},
	{0x33,0xff},
	{0x34,0xe7},
	{0x35,0x00},	
	//vga
	{0xfd, 0x01},
	{0x4a, 0x00},
	{0x4b, 0x01},
	{0x4c, 0xe0},
	{0x4d, 0x00},
	{0x4e, 0x02},
	{0x4f, 0x80},

	{0xfd, 0x02},
	{0x0f, 0x00},	// 1/4 subsample disable

	{0xfd, 0x00},
	{0x30, 0x00},
    ENDMARKER,
};




/* 640*480: VGA */
static const struct regval_list module_vga_regs[] = 
{

	{0xfd, 0x01},
	{0x4a, 0x00},
	{0x4b, 0x01},
	{0x4c, 0xe0},
	{0x4d, 0x00},
	{0x4e, 0x02},
	{0x4f, 0x80},

	{0xfd, 0x02},
	{0x0f, 0x00},	// 1/4 subsample disable
		
	{0xfd, 0x00},
	{0x30, 0x00},
    ENDMARKER,
};


/* 640*480 */
static struct camera_module_win_size module_win_vga = {
	.name             = "VGA",
	.width            = WIDTH_VGA,
	.height           = HEIGHT_VGA,
	.win_regs         = module_vga_regs,
	.frame_rate_array = frame_rate_vga,
	.capture_only     = 0,
};

static struct camera_module_win_size *module_win_list[] = {
	&module_win_vga,
};

static struct regval_list module_whitebance_auto_regs[]=
{	
	{0xfd,0x02},                      
	{0x26,0xc8},		                  
	{0x27,0xb6},                      
	{0xfd,0x01}, 		
	{0x32,0x15},   
	{0xfd,0x00},  
	ENDMARKER,
};

/* Cloudy Colour Temperature : 6500K - 8000K  */
static struct regval_list module_whitebance_cloudy_regs[]=
{
	{0xfd,0x01}, 
	{0x32,0x05},                 
	{0xfd,0x02},                 
	{0x26,0xdc},		             
	{0x27,0xe5},		             
	{0xfd,0x00}, 
	ENDMARKER,
};

/* ClearDay Colour Temperature : 5000K - 6500K  */
static struct regval_list module_whitebance_sunny_regs[]=
{
	{0xfd,0x01}, 
	{0x32,0x05},                 
	{0xfd,0x02},                 
	{0x26,0xc8},		             
	{0x27,0x89},		             
	{0xfd,0x00}, 
    ENDMARKER,
};

/* Office Colour Temperature : 3500K - 5000K ,荧光灯 */
static struct regval_list module_whitebance_fluorescent_regs[]=
{	
	{0xfd,0x01}, 
	{0x32,0x05},                 
	{0xfd,0x02},                 
	{0x26,0x75},		             
	{0x27,0xe2},		             
	{0xfd,0x00}, 
    ENDMARKER,
};

/* Home Colour Temperature : 2500K - 3500K ，白炽灯 */
static struct regval_list module_whitebance_incandescent_regs[]=
{
	{0xfd,0x01}, 
	{0x32,0x05},                 
	{0xfd,0x02},                 
	{0x26,0x91},		             
	{0x27,0xc8},		             
	{0xfd,0x00}, 
	ENDMARKER,
};


static struct regval_list module_scene_auto_regs[] =
{
	ENDMARKER,
};

static struct v4l2_ctl_cmd_info v4l2_ctl_array[] =
{
	{   .id = V4L2_CID_EXPOSURE, 
		.min = 0, 
		.max = 975,
		.step = 1, 
		.def = 500,
	},
	{	.id = V4L2_CID_EXPOSURE_COMP, 
		.min = -4, 
		.max = 4, 
		.step = 1, 
		.def = 0,
	},	
	{	.id = V4L2_CID_GAIN, 
		.min = 10, 
		.max = 2048, 
		.step = 1, 
		.def = 30,
	},
	{
        .id = V4L2_CID_AUTO_WHITE_BALANCE,
        .min = 0,
        .max = 1,
        .step = 1,
        .def = 1,
    },
    {
        .id = V4L2_CID_WHITE_BALANCE_TEMPERATURE,
        .min = 0,
        .max = 3,
        .step = 1,
        .def = 0,
    },
     {	.id   = V4L2_CID_FLASH_STROBE, 
		.min  = 0, 
		.max  = 1, 
		.step = 1, 
		.def  = 0,
	},
	
	{	.id   = V4L2_CID_FLASH_STROBE_STOP, 
		.min  = 0, 
		.max  = 1, 
		.step = 1, 
		.def  = 0,
	},

    {
        .id = V4L2_CID_HFLIP,
        .min = 0,
        .max = 1,
        .step = 1,
        .def = 0,
    },
    {
        .id = V4L2_CID_VFLIP,
        .min = 0,
        .max = 1,
        .step = 1,
        .def = 0,
    },
};

static struct v4l2_ctl_cmd_info_menu v4l2_ctl_array_menu[] =
{
	 {
        .id = V4L2_CID_COLORFX,
        .max = 3,
        .mask = 0x0,
        .def = 0,
    },
    {
        .id = V4L2_CID_EXPOSURE_AUTO,
        .max = 1,
        .mask = 0x0,
        .def = 1,
    },
	{  
		   .id = V4L2_CID_SCENE_MODE, 
		   .max = V4L2_SCENE_MODE_TEXT, 
		   .mask = 0x0, 
		   .def = 0,
	},

   	{	.id   = V4L2_CID_FLASH_LED_MODE, 
		.max  = 3,
		.mask = 0x0,
		.def  = 0,},
	{.id = V4L2_CID_POWER_LINE_FREQUENCY, 
	.max = V4L2_CID_POWER_LINE_FREQUENCY_AUTO, 
	.mask = 0x0,
	.def = V4L2_CID_POWER_LINE_FREQUENCY_AUTO,},
};


#endif /* __MODULE_DIFF_H__ */
