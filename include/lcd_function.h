/*************************************************************************
	工程名：Matrix_Calculator
	作者: 王召东
	联系方式：yuanliudongdong@163.com
	当前文件: include/lcd_function.h
	当前文件描述：LCD的各种功能函数声明
 ************************************************************************/

#ifndef LCD_FUNCTION
#define LCD_FUNCTION

#include "../include/pin_define.h"
#include "../include/lcd_code.h"

//lcd的字符码声明
extern __code unsigned char code_ju[];
extern __code unsigned char code_ji[];
extern __code unsigned char code_suan[];
extern __code unsigned char code_qi[];
extern __code unsigned char code_zuo[];
extern __code unsigned char code_zhe[];
extern __code unsigned char code_wang[];
extern __code unsigned char code_zhao[];
extern __code unsigned char code_dong[];
extern __code unsigned char code_blank[];
extern __code unsigned char code_zhen[];
extern __code unsigned char code_gantanhao[];
extern __code unsigned char code_point[];
extern __code unsigned char code_number[][16];
extern __code unsigned char code_abc[][16];

//延迟程序
extern void LCD_Delay(unsigned int t);
//状态检测程序
extern void LCD_CheckBusy();
//写指令函数
extern void LCD_WriteCode(unsigned char cmdcode);
//写数据函数
extern void LCD_WriteData(unsigned char cmddata);
//在page页，column列显示指定字符code，左后一个参数决定是全角还是半角
extern void LCD_Show(unsigned char page,unsigned char cols, unsigned char *code_table,int chinese);
//清屏
extern void LCD_Clear();
//初始化界面
extern void LCD_Welcome();
//初始化函数
extern void LCD_Init();

#endif