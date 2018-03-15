/*************************************************************************
	工程名：Matrix_Calculator
	作者: 王召东
	联系方式：yuanliudongdong@163.com
	当前文件: src/keyboard_function.c
	当前文件描述：键盘的各种功能函数定义
 ***********************************************************************/

#include "../include/keyboard_function.h"

//初始化函数
void KeyBoard_Init()
{
  
}

//延迟程序
void KeyBoard_Delay(unsigned int t)
{
  unsigned int i,j;
	for(i=0;i<t;i++)
	    for(j=0;j<10;j++);
}

//键盘扫描函数，返回键值
//键值表：
/***************************
 * 0    1    2    3	P1_0
 * 4    5    6    7	P1_1
 * 8    9    10   11	P1_2
 * 12   13   14   15	P1_3
 * P1_7 P1_6 P1_5 P1_4
 ***************************/
unsigned char KeyBoard_Scan()
{
  unsigned char Key;
  unsigned char Key_High,Key_Low;
  //循环扫描直到有按键按下
  while(1)
  {
    //高四位置1，低四位置0
    P1 = 0xf0 ;  
    //读取P1端口值
    Key_Low = P1;
    //只关注高四位
    Key_Low = Key_Low&0xf0 ;
    //如果有按键按下，高四位必有一位被置0，从而确定被按键行数
    if ( Key_Low != 0xf0 )
    {
      P1 = 0xf0 ;
      //延迟去抖
      KeyBoard_Delay(100);  
      //重新判断
      if ( Key_Low != 0xf0 )  
      {
	//重新读取P1端口值
	Key_Low = P1&0xf0;
	//将低四位置1，高四位中被按键的那一行置0
	Key_Low = Key_Low|0x0f;
	P1 = Key_Low;
	//读取P1端口值
	Key_High=P1;
	//只关注低四位
	Key_High=Key_High&0x0f;
	//只关注高四位
	Key_Low=Key_Low&0xf0;
	//高低位相加，获得Key的值
	Key=Key_High+Key_Low;
	
	//等待按键松开
	do
	{
	  //高四位置1，低四位置0
	  P1 = 0xf0 ;  
	  //读取P1端口值
	  Key_Low = P1;
	  //只关注高四位
	  Key_Low = Key_Low&0xf0; 
	}while( Key_Low != 0xf0 );
	break;
      }  
     }
  }
  return Key;
}