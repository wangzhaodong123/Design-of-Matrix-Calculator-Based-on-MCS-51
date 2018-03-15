/*************************************************************************
	工程名：Matrix_Calculator
	作者: 王召东
	联系方式：yuanliudongdong@163.com
	当前文件: test/test_1.c
	当前文件描述：工程测试文件
 ***********************************************************************/
#include "../include/common_include.h"

extern void AddMatrix();
extern void MultiplyMatrix();
extern void InverseMatrix();
extern void ModuleMatrix();
extern void AdjointMatrix();
extern void SystemInit();
extern void InputMatrix( int (*matrix)[3][3], int number );
extern void ShowMatrix( int (*matrix)[3][3],int function);
extern unsigned char FunctionSelect();
extern unsigned char KeyBoard_Scan();
extern void LCD_Show(unsigned char page,unsigned char cols, unsigned char *code_table,int chinese);
extern void LCD_Clear();
extern __code unsigned char code_number[11][16];

int main( )
{ 
  //传递功能选项的变量
  unsigned char Function;
  unsigned char Key;
  //系统初始化
  SystemInit();
  //每运行完一个程序重新回到功能选择界面
   while(1)
   {
     //功能选择
     Function = FunctionSelect();
     //根据功能变量进入不同功能函数
     switch ( Function )
     {
       //相加
       case 0:
 	AddMatrix();
 	break;
       //求逆
//        case 1:
//  	InverseMatrix();
//  	break;
       //伴随
       case 1:
 	AdjointMatrix();
 	break;
       //相乘
       case 2:
 	MultiplyMatrix();
 	break;
       //求模
       case 3:
 	ModuleMatrix();
 	break;
     }
     //等待确定键按下，进入下一个功能
     do
     {
       Key = KeyBoard_Scan();
      }while( Key != 0xe7 );
     //清屏
     LCD_Clear();     
  }
  return 0;
}