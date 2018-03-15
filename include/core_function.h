/*************************************************************************
	工程名：Matrix_Calculator
	作者: 王召东
	联系方式：yuanliudongdong@163.com
	当前文件: includsrc/core_function.h
	当前文件描述：整个系统的核心功能函数声明
 ************************************************************************/

#ifndef CORE_FUNCTION
#define CORE_FUNCTION

#include "../include/pin_define.h"
#include "../include/lcd_function.h"

//三个函数处理所需的矩阵
extern int MatrixA[][3];
extern int MatrixB[][3];
extern int MatrixC[][3];
//系统初始化函数
extern void SystemInit();
//功能显示界面函数
extern void FunctionMenu();
//功能选择函数
extern unsigned char FunctionSelect();
//右下角当前数字显示函数
extern void CurrentNumber( int numb );
//清箭头函数
extern void LocateArrow( int rows, int cols );
//将全局的矩阵变量清零
extern void ClearMatrix();
//矩阵输入函数
extern void InputMatrix( int (*matrix)[3][3], int number );
//矩阵显示函数
extern void ShowMatrix( int (*matrix)[3][3],int function);
//矩阵相加
extern void AddMatrix();
//矩阵相乘
extern void MultiplyMatrix();
//矩阵求逆
extern void InverseMatrix();
//矩阵求模
extern void ModuleMatrix();
//矩阵求伴随
extern void AdjointMatrix();

#endif