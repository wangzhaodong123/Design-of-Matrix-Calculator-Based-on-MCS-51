/*************************************************************************
	工程名：Matrix_Calculator
	作者: 王召东
	联系方式：yuanliudongdong@163.com
	当前文件: include/pin_define.h
	当前文件描述：根据功能将外部引脚进行命名
 ************************************************************************/

#ifndef PIN_DEFINE
#define PIN_DEFINE

#include </usr/share/sdcc/include/mcs51/8052.h>

//定义LCD一些关键的地址
#define LCD_OFF   	0x3e	//关显示器地址
#define LCD_OPEN    	0x3f	//开显示器地址
#define LCD_PAGE     	0xb8	//页地址
#define LCD_COLS     	0x40	//列地址
#define LCD_Start_Line  0xC0	//屏幕起始地址
#define LCD_BUSY	0x80	//LCD正忙标志

//定义引脚
#define LCD_LEFT 	P2_1	//左屏片选位
#define LCD_RIGHT 	P2_2	//右屏片选位
#define LCD_RES_ET 	P2_3	//复位信号
#define LCD_RS 		P2_4	//数据指令选择位
#define LCD_RW 		P2_5	//读写选择位
#define LCD_EN 		P2_6	//使能信号
#define LCD_DATA	P0	//数据传输接口

#endif