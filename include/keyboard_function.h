/*************************************************************************
	工程名：Matrix_Calculator
	作者: 王召东
	联系方式：yuanliudongdong@163.com
	当前文件: include/keyboard_function.h
	当前文件描述：键盘的各种功能函数声明
 ***********************************************************************/

#ifndef KEYBOARD_FUNCTION
#define KEYBOARD_FUNCTION

#include "../include/pin_define.h"

//初始化函数
extern void KeyBoard_Init();
//延迟函数
extern void KeyBoard_Delay(unsigned int t);
//键盘扫描函，返回键值
extern unsigned char KeyBoard_Scan();

#endif