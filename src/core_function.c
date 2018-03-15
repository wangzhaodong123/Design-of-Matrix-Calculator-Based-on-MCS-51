/*************************************************************************
	工程名：Matrix_Calculator
	作者: 王召东
	联系方式：yuanliudongdong@163.com
	当前文件: includsrc/lcd_code.c
	当前文件描述：整个系统的核心功能函数定义
 ************************************************************************/
#include "../include/core_function.h"

//初始化函数
extern void LCD_Init();
extern void LCD_Clear();
extern void LCD_Delay(unsigned int t);
extern void LCD_Show(unsigned char page,unsigned char cols, unsigned char *code_table,int chinese);
extern void KeyBoard_Init();
extern unsigned char KeyBoard_Scan();

//字符码声明
extern __code unsigned char code_gong[];
extern __code unsigned char code_neng[];
extern __code unsigned char code_xuan[];
extern __code unsigned char code_ze[];
extern __code unsigned char code_maohao[];
extern __code unsigned char code_xiang[];
extern __code unsigned char code_jia[];
extern __code unsigned char code_cheng[];
extern __code unsigned char code_qiu[];
extern __code unsigned char code_ni[];
extern __code unsigned char code_mo[];
extern __code unsigned char code_ban[];
extern __code unsigned char code_sui[];
extern __code unsigned char code_right[];
extern __code unsigned char code_blank[];
extern __code unsigned char code_number[][16];
extern __code unsigned char code_abc[][16];

//定义三个函数处理所需的矩阵
int MatrixA[3][3];
int MatrixB[3][3];
int MatrixC[3][3];

//系统初始化函数
//将各个设备进行初始化
void SystemInit()
{
  //P3口初始化为0
  P3 = 0x00;
  //LCD初始化函数
  LCD_Init();
  //键盘初始化函数
  KeyBoard_Init();
}

//功能显示界面函数
void FunctionMenu()
{
  LCD_LEFT = 0;
  LCD_RIGHT = 1;
  //左屏 功能选择
  LCD_Show(0,0,code_gong,1);
  LCD_Show(0,16,code_neng,1);
  LCD_Show(0,32,code_xuan,1);
  LCD_Show(0,48,code_ze,1);
  //→相加
  LCD_Show(2,0,code_right,1);
  LCD_Show(2,16,code_xiang,1);
  LCD_Show(2,32,code_jia,1);
  LCD_Show(2,48,code_blank,1);
  // 求逆
//   LCD_Show(4,0,code_blank,1);
//   LCD_Show(4,16,code_qiu,1);
//   LCD_Show(4,32,code_ni,1);
//   LCD_Show(4,48,code_blank,1);
  // 伴随
  LCD_Show(4,0,code_blank,1);
  LCD_Show(4,16,code_ban,1);
  LCD_Show(4,32,code_sui,1);
  LCD_Show(4,48,code_blank,1);
  
  LCD_LEFT = 1;
  LCD_RIGHT = 0;
  //右屏 
  LCD_Show(0,0,code_blank,1);
  LCD_Show(0,16,code_blank,1);
  LCD_Show(0,32,code_blank,1);
  LCD_Show(0,48,code_blank,1);
  //→相加
  LCD_Show(2,0,code_blank,1);
  LCD_Show(2,16,code_xiang,1);
  LCD_Show(2,32,code_cheng,1);
  LCD_Show(2,48,code_blank,1);
  // 求逆
  LCD_Show(4,0,code_blank,1);
  LCD_Show(4,16,code_qiu,1);
  LCD_Show(4,32,code_mo,1);
  LCD_Show(4,48,code_blank,1);
  // 伴随
  LCD_Show(6,0,code_blank,1);
  LCD_Show(6,16,code_blank,1);
  LCD_Show(6,32,code_blank,1);
  LCD_Show(6,48,code_blank,1);
  
}

//功能选择函数
unsigned char FunctionSelect()
{
  //局部功能选择变量
  unsigned char function=0;
  unsigned char key=0;
  unsigned char flag=0;
  //功能显示界面
  FunctionMenu();
  
  while(1)
  {
    //扫描键盘
    key = KeyBoard_Scan(); 
    LCD_Delay(100);
    switch (key)
    {
      //按下功能键时切换功能
      case 0xeb://11101011 11
	//功能变量加1
	function = (function+1) % 4;
	//清除上一次的箭头
	LCD_LEFT=0;
	LCD_RIGHT=1;
	LCD_Show(2,0,code_blank,1);
	LCD_Show(4,0,code_blank,1);
	LCD_Show(6,0,code_blank,1);
	LCD_LEFT=1;
	LCD_RIGHT=0;
	LCD_Show(2,0,code_blank,1);
	LCD_Show(4,0,code_blank,1);
	//根据function确定箭头位置
	switch ( function )
	{
	  //相加
	  case 0:
	    LCD_LEFT=0;
	    LCD_RIGHT=1;
	    LCD_Show(2,0,code_right,1);
	    break;
	  //求逆
// 	  case 1:
// 	    LCD_LEFT=0;
// 	    LCD_RIGHT=1;
// 	    LCD_Show(4,0,code_right,1);
// 	    break;
	  //伴随
	  case 1:
	    LCD_LEFT=0;
	    LCD_RIGHT=1;
	    LCD_Show(4,0,code_right,1);
	    break;
	  //相乘
	  case 2:
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(2,0,code_right,1);
	    break;
	  //求模
	  case 3:
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(4,0,code_right,1);
	    break;
	}
	break;
      //按下确定键时，标志位置1
      case 0xe7://11100111 15
	flag = 1;
	break; 
      default:
	break;
    }
    if( flag ==1 )
      break;
  }
  
  return function;
}

//右下角当前数字显示函数
void CurrentNumber( int numb )
{
  int numb_low;
  int numb_high;
  LCD_LEFT=1;
  LCD_RIGHT=0;
  LCD_Show(6,48,code_blank,1);
  numb_high = numb / 10;
  LCD_Show(6,48,code_number[numb_high],0);
  numb_low = numb % 10;
  LCD_Show(6,56,code_number[numb_low],0);  
}

//箭头定位函数
void LocateArrow( int rows, int cols )
{
  LCD_LEFT=0;
  LCD_RIGHT=1;
  LCD_Show(6,24,code_blank,1);
  LCD_Show(6,48,code_blank,1);
  LCD_LEFT=1;
  LCD_RIGHT=0;
  LCD_Show(0,32,code_blank,1);
  LCD_Show(2,32,code_blank,1);
  LCD_Show(4,32,code_blank,1);
  LCD_Show(6,8,code_blank,1);
  switch (rows)
  {
    case 1:
      LCD_LEFT=1;
      LCD_RIGHT=0;
      LCD_Show(0,32,code_left,1);
      break;
    case 2:
      LCD_LEFT=1;
      LCD_RIGHT=0;
      LCD_Show(2,32,code_left,1);
      break;
    case 3:
      LCD_LEFT=1;
      LCD_RIGHT=0;
      LCD_Show(4,32,code_left,1);
      break;
  }
  switch (cols)
  {
    case 1:
      LCD_LEFT=0;
      LCD_RIGHT=1;
      LCD_Show(6,24,code_up,1);
      break;
    case 2:
      LCD_LEFT=0;
      LCD_RIGHT=1;
      LCD_Show(6,48,code_up,1);
      break;
    case 3:
      LCD_LEFT=1;
      LCD_RIGHT=0;
      LCD_Show(6,8,code_up,1);
      break;
  }
  
}

//将全局的矩阵变量清零
void ClearMatrix()
{
  unsigned char i=0,j=0;
  for ( ;i<3;i++ )
    for ( ;j<3;j++ )
    {
      MatrixA[i][j]=0;
      MatrixB[i][j]=0;
      MatrixC[i][j]=0;
    }
}

//矩阵输入函数
/*输入界面
 * 一一一一一一一一一一一一
 *| A =|** ** **|      |
 *|    |** ** **| ←    |
 *|    |** ** **|      |
 *|        ↑       **  |
 * 一一一一一一一一一一一一
 */
void InputMatrix( int (*matrix)[3][3], int number )
{
  int count;
  unsigned char key;
  int value_temp=0;
  //矩阵初始化
  (*matrix)[0][0]=0;
  (*matrix)[0][1]=0;
  (*matrix)[0][2]=0;
  (*matrix)[1][0]=0;
  (*matrix)[1][1]=0;
  (*matrix)[1][2]=0;
  (*matrix)[2][0]=0;
  (*matrix)[2][1]=0;
  (*matrix)[2][2]=0;
  //输入界面
  //清屏
  LCD_Clear();
  //左屏
  LCD_LEFT=0;
  LCD_RIGHT=1;
  if ( number == 1 )
    LCD_Show(0,0,code_abc[0],0);
  else
    LCD_Show(0,0,code_abc[1],0);
  LCD_Show(0,8,code_number[11],0);
  LCD_Show(0,16,code_number[12],0);
  LCD_Show(2,16,code_number[12],0);
  LCD_Show(4,16,code_number[12],0);
  LCD_Show(6,24,code_up,1);
  LCD_LEFT=1;
  LCD_RIGHT=0;
  LCD_Show(0,24,code_number[12],0);
  LCD_Show(2,24,code_number[12],0);
  LCD_Show(4,24,code_number[12],0);
  LCD_Show(0,32,code_left,1);
  
  //输入9个数
  CurrentNumber(0);
  for (  count = 0; count<9; count++ )
  {
    value_temp=0;
    //不停扫描键值，直到确定键按下
    do
   {
    key=KeyBoard_Scan();
    switch (key)
    {
      case 0xde://11011110 2
	value_temp = value_temp * 10;
	value_temp = value_temp +3;
	value_temp = value_temp % 100;
	break;
      case 0xbe://10111110 1
	value_temp = value_temp * 10;
	value_temp = value_temp +2;
	value_temp = value_temp % 100;
	break;
      case 0x7e://01111110 0
	value_temp = value_temp * 10;
	value_temp = value_temp +1;
	value_temp = value_temp % 100;
	break;
      case 0xdd://11011101 6
	value_temp = value_temp * 10;
	value_temp = value_temp +6;
	value_temp = value_temp % 100;
	break;
      case 0xbd://10111101 5
	value_temp = value_temp * 10;
	value_temp = value_temp +5;
	value_temp = value_temp % 100;
	break;
      case 0x7d://01111101 4
	value_temp = value_temp * 10;
	value_temp = value_temp +4;
	value_temp = value_temp % 100;
	break;
      case 0xdb://11011011 10
	value_temp = value_temp * 10;
	value_temp = value_temp +9;
	value_temp = value_temp % 100;
	break;
      case 0xbb://10111011 9
	value_temp = value_temp * 10;
	value_temp = value_temp +8;
	value_temp = value_temp % 100;
	break;
      case 0x7b://01111011 8 
	value_temp = value_temp * 10;
	value_temp = value_temp +7;
	value_temp = value_temp % 100;
	break;
      case 0x77://01110111 12
	value_temp = value_temp * 10;
	value_temp = value_temp +0;
	value_temp = value_temp % 100;
	break;
      default:
	break;
    }
    CurrentNumber(value_temp);
   }while( key != 0xe7 );
   
   //将键值写入矩阵
   (*matrix)[count/3][count%3]=value_temp;
   CurrentNumber(0);
   
   //每次将数显示在屏幕上
   switch (count)
   {
     case 0:
       LCD_LEFT=0;
       LCD_RIGHT=1;
       LCD_Show(0,24,code_number[value_temp/10],0);
       LCD_Show(0,32,code_number[value_temp%10],0);
       LocateArrow(1,2);
       break;
     case 1:
       LCD_LEFT=0;
       LCD_RIGHT=1;
       LCD_Show(0,48,code_number[value_temp/10],0);
       LCD_Show(0,56,code_number[value_temp%10],0);
       LocateArrow(1,3);
       break;
     case 2:
       LCD_LEFT=1;
       LCD_RIGHT=0;
       LCD_Show(0,8,code_number[value_temp/10],0);
       LCD_Show(0,16,code_number[value_temp%10],0);
       LocateArrow(2,1);
       break;
     case 3:
       LCD_LEFT=0;
       LCD_RIGHT=1;
       LCD_Show(2,24,code_number[value_temp/10],0);
       LCD_Show(2,32,code_number[value_temp%10],0);
       LocateArrow(2,2);
       break;
     case 4:
       LCD_LEFT=0;
       LCD_RIGHT=1;
       LCD_Show(2,48,code_number[value_temp/10],0);
       LCD_Show(2,56,code_number[value_temp%10],0);
       LocateArrow(2,3);
       break;
     case 5:
       LCD_LEFT=1;
       LCD_RIGHT=0;
       LCD_Show(2,8,code_number[value_temp/10],0);
       LCD_Show(2,16,code_number[value_temp%10],0);
       LocateArrow(3,1);
       break;
     case 6:
       LCD_LEFT=0;
       LCD_RIGHT=1;
       LCD_Show(4,24,code_number[value_temp/10],0);
       LCD_Show(4,32,code_number[value_temp%10],0);
       LocateArrow(3,2);
       break;
     case 7:
       LCD_LEFT=0;
       LCD_RIGHT=1;
       LCD_Show(4,48,code_number[value_temp/10],0);
       LCD_Show(4,56,code_number[value_temp%10],0);
       LocateArrow(3,3);
       break;
     case 8: 
       LCD_LEFT=1;
       LCD_RIGHT=0;
       LCD_Show(4,8,code_number[value_temp/10],0);
       LCD_Show(4,16,code_number[value_temp%10],0);
       //LocateArrow(3,3);
       break;
     
  }
  }
}

//矩阵显示函数
/*输出显示界面
 * 一一一一一一一一一一一一
 *|A*B=               |
 *||**     **      **||
 *||**     **      **||
 *||**     **      **||
 * 一一一一一一一一一一一一
 */
void ShowMatrix( int (*matrix)[3][3],int function  )
{
  int count;
  int res_first=0;
  int res_second=0;
  int res_third=0;
  int res_foruth=0;
  
  LCD_LEFT=0;
  LCD_RIGHT=1;
  //显示运算
  switch (function)
  {
    //A+B=
    case 1:
      LCD_Show(0,0,code_abc[0],0);
      LCD_Show(0,8,code_number[15],0);
      LCD_Show(0,16,code_abc[1],0);
      LCD_Show(0,24,code_number[11],0);
      break;
    //A*B=
    case 2:
      LCD_Show(0,0,code_abc[0],0);
      LCD_Show(0,8,code_number[16],0);
      LCD_Show(0,16,code_abc[1],0);
      LCD_Show(0,24,code_number[11],0);
      break;
    //A-1=
    case 3:
      LCD_Show(0,0,code_abc[0],0);
      LCD_Show(0,8,code_number[14],0);
      LCD_Show(0,24,code_number[11],0);
      break;
    //|A|=
    case 4:
      LCD_Show(0,0,code_number[12],0);
      LCD_Show(0,8,code_abc[0],0);
      LCD_Show(0,16,code_number[12],0);
      LCD_Show(0,24,code_number[11],0);
      break;
    //A*=
    case 5:
      LCD_Show(0,0,code_abc[0],0);
      LCD_Show(0,8,code_number[13],0);
      LCD_Show(0,24,code_number[11],0);
      break;
      
      
  }
  
  //矩阵边缘
  LCD_LEFT=0;
  LCD_RIGHT=1;
  LCD_Show(2,0,code_number[12],0);
  LCD_Show(4,0,code_number[12],0);
  LCD_Show(6,0,code_number[12],0);
  LCD_LEFT=1;
  LCD_RIGHT=0;
  LCD_Show(2,56,code_number[12],0);
  LCD_Show(4,56,code_number[12],0);
  LCD_Show(6,56,code_number[12],0);
  
  //显示矩阵
  for (count=0;count<9;count++)
  {
    //个十百千位分离
    res_first=(*matrix)[count/3][count%3]/1000;
    res_second=(*matrix)[count/3][count%3]/100-res_first*10;
    res_third=(*matrix)[count/3][count%3]/10-res_first*100-res_second*10;
    res_foruth=(*matrix)[count/3][count%3]%10;
    
    //因为每个数只能表示四位，所以会有溢出现象：
    if ( ((*matrix)[count/3][count%3]) <-999 ||((*matrix)[count/3][count%3]) >9999 )
    {
      switch( count )
      {
	case 0:
	  LCD_LEFT=0;
	  LCD_RIGHT=1;
	  LCD_Show(2,8,code_abc[14],0);
	  LCD_Show(2,16,code_abc[21],0);
	  LCD_Show(2,24,code_abc[4],0);
	  LCD_Show(2,32,code_number[17],0);
	  break;
	case 1:
	  LCD_LEFT=0;
	  LCD_RIGHT=1;
	  LCD_Show(2,48,code_abc[14],0);
	  LCD_Show(2,56,code_abc[21],0);
	  LCD_LEFT=1;
	  LCD_RIGHT=0;
	  LCD_Show(2,0,code_abc[4],0);
	  LCD_Show(2,8,code_number[17],0);
	  break;
	case 2:
	  LCD_LEFT=1;
	  LCD_RIGHT=0;
	  LCD_Show(2,8,code_abc[14],0);
	  LCD_Show(2,16,code_abc[21],0);
	  LCD_Show(2,24,code_abc[4],0);
	  LCD_Show(2,32,code_number[17],0);
	  break;
	case 3:
	  LCD_LEFT=0;
	  LCD_RIGHT=1;
	  LCD_Show(2,24,code_abc[14],0);
	  LCD_Show(2,32,code_abc[21],0);
	  LCD_Show(2,40,code_abc[4],0);
	  LCD_Show(2,48,code_number[17],0);
	  break;
	case 4:
	  LCD_LEFT=0;
	  LCD_RIGHT=1;
	  LCD_Show(4,48,code_abc[14],0);
	  LCD_Show(4,56,code_abc[21],0);
	  LCD_LEFT=1;
	  LCD_RIGHT=0;
	  LCD_Show(4,0,code_abc[4],0);
	  LCD_Show(4,8,code_number[17],0);
	  break;
	case 5:
	  LCD_LEFT=1;
	  LCD_RIGHT=0;
	  LCD_Show(4,24,code_abc[14],0);
	  LCD_Show(4,32,code_abc[21],0);
	  LCD_Show(4,40,code_abc[4],0);
	  LCD_Show(4,48,code_number[17],0);
	  break;
	case 6:
	  LCD_LEFT=0;
	  LCD_RIGHT=1;
	  LCD_Show(6,8,code_abc[14],0);
	  LCD_Show(6,16,code_abc[21],0);
	  LCD_Show(6,24,code_abc[4],0);
	  LCD_Show(6,32,code_number[17],0);
	  break;
	case 7:
	  LCD_LEFT=0;
	  LCD_RIGHT=1;
	  LCD_Show(6,48,code_abc[14],0);
	  LCD_Show(6,56,code_abc[21],0);
	  LCD_LEFT=1;
	  LCD_RIGHT=0;
	  LCD_Show(6,0,code_abc[4],0);
	  LCD_Show(6,8,code_number[17],0);
	  break;
	case 8:
	  LCD_LEFT=1;
	  LCD_RIGHT=0;
	  LCD_Show(6,24,code_abc[14],0);
	  LCD_Show(6,32,code_abc[21],0);
	  LCD_Show(6,40,code_abc[4],0);
	  LCD_Show(6,48,code_number[17],0);
	  break;
      }
    
      continue;
    }
    
    //显示9个数
    switch (count)
    {
      case 0:
	LCD_LEFT=0;
	LCD_RIGHT=1;
	if (((*matrix)[count/3][count%3])>=0)
	{
	  if ( res_first!=0 )
	    LCD_Show(2,8,code_number[res_first],0);
	  if ( res_second!=0 || res_first!=0 )
	    LCD_Show(2,16,code_number[res_second],0);
	  if ( res_third!=0 || res_second!=0 || res_first!=0 )
	    LCD_Show(2,24,code_number[res_third],0);
	  LCD_Show(2,32,code_number[res_foruth],0);
	  break;
	}
	else 
	{
	  if ( res_second!=0 )
	  {
	    LCD_Show(2,8,code_number[10],0);
	    LCD_Show(2,16,code_number[-res_second],0);
	    LCD_Show(2,24,code_number[-res_third],0);
	  }
	  else
	  if ( res_third!=0 )
	  {
	    LCD_Show(2,16,code_number[10],0);
	    LCD_Show(2,24,code_number[-res_third],0);
	  }
	  else
	  if ( res_foruth!=0 )
	  {
	    LCD_Show(2,24,code_number[10],0);
	  }

	  LCD_Show(2,32,code_number[-res_foruth],0);
	  break;
	}
      case 1:
	if (((*matrix)[count/3][count%3])>=0)
	{
	  LCD_LEFT=0;
	  LCD_RIGHT=1;
	  if ( res_first!=0 )
	    LCD_Show(2,48,code_number[res_first],0);
	  if ( res_second!=0 || res_first!=0 )
	    LCD_Show(2,56,code_number[res_second],0);
	  LCD_LEFT=1;
	  LCD_RIGHT=0;
	  if ( res_third!=0 || res_second!=0 || res_first!=0 )
	    LCD_Show(2,0,code_number[res_third],0);
	  LCD_Show(2,8,code_number[res_foruth],0);
	  break;
	}
	else 
	{
	  if ( res_second!=0 )
	  {
	    LCD_LEFT=0;
	    LCD_RIGHT=1;
	    LCD_Show(2,48,code_number[10],0);
	    LCD_Show(2,56,code_number[-res_second],0);
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(2,24,code_number[-res_third],0);
	  }
	  else
	  if ( res_third!=0 )
	  {
	    LCD_LEFT=0;
	    LCD_RIGHT=1;
	    LCD_Show(2,56,code_number[10],0);
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(2,0,code_number[-res_third],0);
	  }
	  else
	  if ( res_foruth!=0 )
	  {
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(2,0,code_number[10],0);
	  }
	  LCD_Show(2,8,code_number[-res_foruth],0);
	  break;
	}
      case 2:
	LCD_LEFT=1;
	LCD_RIGHT=0;
	if (((*matrix)[count/3][count%3])>=0)
	{
	  if ( res_first!=0 )
	    LCD_Show(2,24,code_number[res_first],0);
	  if ( res_second!=0 || res_first!=0 )
	    LCD_Show(2,32,code_number[res_second],0);
	  if ( res_third!=0 || res_second!=0 || res_first!=0 )
	    LCD_Show(2,40,code_number[res_third],0);
	  LCD_Show(2,48,code_number[res_foruth],0);
	  break;
	}
	else 
	{
	  if ( res_second!=0 )
	  {
	    LCD_Show(2,24,code_number[10],0);
	    LCD_Show(2,32,code_number[-res_second],0);
	    LCD_Show(2,40,code_number[-res_third],0);
	  }
	  else
	  if ( res_third!=0 )
	  {
	    LCD_Show(2,32,code_number[10],0);
	    LCD_Show(2,40,code_number[-res_third],0);
	  }
	  else
	  if ( res_foruth!=0 )
	  {
	    LCD_Show(2,40,code_number[10],0);
	  }

	  LCD_Show(2,48,code_number[-res_foruth],0);
	  break;
	}
      case 3:
	LCD_LEFT=0;
	LCD_RIGHT=1;
	if (((*matrix)[count/3][count%3])>=0)
	{
	  if ( res_first!=0 )
	    LCD_Show(4,8,code_number[res_first],0);
	  if ( res_second!=0 || res_first!=0 )
	    LCD_Show(4,16,code_number[res_second],0);
	  if ( res_third!=0 || res_second!=0 || res_first!=0 )
	    LCD_Show(4,24,code_number[res_third],0);
	  LCD_Show(4,32,code_number[res_foruth],0);
	  break;
	}
	else 
	{
	  if ( res_second!=0 )
	  {
	    LCD_Show(4,8,code_number[10],0);
	    LCD_Show(4,16,code_number[-res_second],0);
	    LCD_Show(4,24,code_number[-res_third],0);
	  }
	  else
	  if ( res_third!=0 )
	  {
	    LCD_Show(4,16,code_number[10],0);
	    LCD_Show(4,24,code_number[-res_third],0);
	  }
	  else
	  if ( res_foruth!=0 )
	  {
	    LCD_Show(4,24,code_number[10],0);
	  }

	  LCD_Show(4,32,code_number[-res_foruth],0);
	  break;
	}
      case 4:
	if (((*matrix)[count/3][count%3])>=0)
	{
	  LCD_LEFT=0;
	  LCD_RIGHT=1;
	  if ( res_first!=0 )
	    LCD_Show(4,48,code_number[res_first],0);
	  if ( res_second!=0 || res_first!=0 )
	    LCD_Show(4,56,code_number[res_second],0);
	  LCD_LEFT=1;
	  LCD_RIGHT=0;
	  if ( res_third!=0 || res_second!=0 || res_first!=0 )
	    LCD_Show(4,0,code_number[res_third],0);
	  LCD_Show(4,8,code_number[res_foruth],0);
	  break;
	}
	else 
	{
	  if ( res_second!=0 )
	  {
	    LCD_LEFT=0;
	    LCD_RIGHT=1;
	    LCD_Show(4,48,code_number[10],0);
	    LCD_Show(4,56,code_number[-res_second],0);
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(4,24,code_number[-res_third],0);
	  }
	  else
	  if ( res_third!=0 )
	  {
	    LCD_LEFT=0;
	    LCD_RIGHT=1;
	    LCD_Show(4,56,code_number[10],0);
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(4,0,code_number[-res_third],0);
	  }
	  else
	  if ( res_foruth!=0 )
	  {
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(4,0,code_number[10],0);
	  }
	  LCD_Show(4,8,code_number[-res_foruth],0);
	  break;
	}
      case 5:
	LCD_LEFT=1;
	LCD_RIGHT=0;
	if (((*matrix)[count/3][count%3])>=0)
	{
	  if ( res_first!=0 )
	    LCD_Show(4,24,code_number[res_first],0);
	  if ( res_second!=0 || res_first!=0 )
	    LCD_Show(4,32,code_number[res_second],0);
	  if ( res_third!=0 || res_second!=0 || res_first!=0 )
	    LCD_Show(4,40,code_number[res_third],0);
	  LCD_Show(4,48,code_number[res_foruth],0);
	  break;
	}
	else 
	{
	  if ( res_second!=0 )
	  {
	    LCD_Show(4,24,code_number[10],0);
	    LCD_Show(4,32,code_number[-res_second],0);
	    LCD_Show(4,40,code_number[-res_third],0);
	  }
	  else
	  if ( res_third!=0 )
	  {
	    LCD_Show(4,32,code_number[10],0);
	    LCD_Show(4,40,code_number[-res_third],0);
	  }
	  else
	  if ( res_foruth!=0 )
	  {
	    LCD_Show(4,40,code_number[10],0);
	  }

	  LCD_Show(4,48,code_number[-res_foruth],0);
	  break;
	}
      case 6:
	LCD_LEFT=0;
	LCD_RIGHT=1;
	if (((*matrix)[count/3][count%3])>=0)
	{
	  if ( res_first!=0 )
	    LCD_Show(6,8,code_number[res_first],0);
	  if ( res_second!=0 || res_first!=0 )
	    LCD_Show(6,16,code_number[res_second],0);
	  if ( res_third!=0 || res_second!=0 || res_first!=0 )
	    LCD_Show(6,24,code_number[res_third],0);
	  LCD_Show(6,32,code_number[res_foruth],0);
	  break;
	}
	else 
	{
	  if ( res_second!=0 )
	  {
	    LCD_Show(6,8,code_number[10],0);
	    LCD_Show(6,16,code_number[-res_second],0);
	    LCD_Show(6,24,code_number[-res_third],0);
	  }
	  else
	  if ( res_third!=0 )
	  {
	    LCD_Show(6,16,code_number[10],0);
	    LCD_Show(6,24,code_number[-res_third],0);
	  }
	  else
	  if ( res_foruth!=0 )
	  {
	    LCD_Show(6,24,code_number[10],0);
	  }

	  LCD_Show(6,32,code_number[-res_foruth],0);
	  break;
	}
      case 7:
	if (((*matrix)[count/3][count%3])>=0)
	{
	  LCD_LEFT=0;
	  LCD_RIGHT=1;
	  if ( res_first!=0 )
	    LCD_Show(6,48,code_number[res_first],0);
	  if ( res_second!=0 || res_first!=0 )
	    LCD_Show(6,56,code_number[res_second],0);
	  LCD_LEFT=1;
	  LCD_RIGHT=0;
	  if ( res_third!=0 || res_second!=0 || res_first!=0 )
	    LCD_Show(6,0,code_number[res_third],0);
	  LCD_Show(6,8,code_number[res_foruth],0);
	  break;
	}
	else 
	{
	  if ( res_second!=0 )
	  {
	    LCD_LEFT=0;
	    LCD_RIGHT=1;
	    LCD_Show(6,48,code_number[10],0);
	    LCD_Show(6,56,code_number[-res_second],0);
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(6,24,code_number[-res_third],0);
	  }
	  else
	  if ( res_third!=0 )
	  {
	    LCD_LEFT=0;
	    LCD_RIGHT=1;
	    LCD_Show(6,56,code_number[10],0);
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(6,0,code_number[-res_third],0);
	  }
	  else
	  if ( res_foruth!=0 )
	  {
	    LCD_LEFT=1;
	    LCD_RIGHT=0;
	    LCD_Show(6,0,code_number[10],0);
	  }
	  LCD_Show(6,8,code_number[-res_foruth],0);
	  break;
	}
      case 8:
	LCD_LEFT=1;
	LCD_RIGHT=0;
	if (((*matrix)[count/3][count%3])>=0)
	{
	  if ( res_first!=0 )
	    LCD_Show(6,24,code_number[res_first],0);
	  if ( res_second!=0 || res_first!=0 )
	    LCD_Show(6,32,code_number[res_second],0);
	  if ( res_third!=0 || res_second!=0 || res_first!=0 )
	    LCD_Show(6,40,code_number[res_third],0);
	  LCD_Show(6,48,code_number[res_foruth],0);
	  break;
	}
	else 
	{
	  if ( res_second!=0 )
	  {
	    LCD_Show(6,24,code_number[10],0);
	    LCD_Show(6,32,code_number[-res_second],0);
	    LCD_Show(6,40,code_number[-res_third],0);
	  }
	  else
	  if ( res_third!=0 )
	  {
	    LCD_Show(6,32,code_number[10],0);
	    LCD_Show(6,40,code_number[-res_third],0);
	  }
	  else
	  if ( res_foruth!=0 )
	  {
	    LCD_Show(6,40,code_number[10],0);
	  }

	  LCD_Show(6,48,code_number[-res_foruth],0);
	  break;
	}
    }
  }
    
  
}

//矩阵相加
void AddMatrix()
{
  //输入矩阵
  LCD_Clear();
  InputMatrix( &MatrixA,1);
  LCD_Clear();
  InputMatrix( &MatrixB,0);
  LCD_Clear();
  //计算和
  MatrixC[0][0]=MatrixA[0][0]+MatrixB[0][0];
  MatrixC[0][1]=MatrixA[0][1]+MatrixB[0][1];
  MatrixC[0][2]=MatrixA[0][2]+MatrixB[0][2];
  MatrixC[1][0]=MatrixA[1][0]+MatrixB[1][0];
  MatrixC[1][1]=MatrixA[1][1]+MatrixB[1][1];
  MatrixC[1][2]=MatrixA[1][2]+MatrixB[1][2];
  MatrixC[2][0]=MatrixA[2][0]+MatrixB[2][0];
  MatrixC[2][1]=MatrixA[2][1]+MatrixB[2][1];
  MatrixC[2][2]=MatrixA[2][2]+MatrixB[2][2];
  //显示结果矩阵
  ShowMatrix(&MatrixC,1);
  //矩阵变量清零
  ClearMatrix();
}

//矩阵相乘
void MultiplyMatrix()
{
  //输入矩阵
  LCD_Clear();
  InputMatrix( &MatrixA,1);
  LCD_Clear();
  InputMatrix( &MatrixB,0);
  LCD_Clear(); 
  //计算乘积
  MatrixC[0][0] = MatrixA[0][0]*MatrixB[0][0] + MatrixA[0][1]*MatrixB[1][0] + MatrixA[0][2]*MatrixB[2][0];
  MatrixC[0][1] = MatrixA[0][0]*MatrixB[0][1] + MatrixA[0][1]*MatrixB[1][1] + MatrixA[0][2]*MatrixB[2][1];
  MatrixC[0][2] = MatrixA[0][0]*MatrixB[0][2] + MatrixA[0][1]*MatrixB[1][2] + MatrixA[0][2]*MatrixB[2][2];
  MatrixC[1][0] = MatrixA[1][0]*MatrixB[0][0] + MatrixA[1][1]*MatrixB[1][0] + MatrixA[1][2]*MatrixB[2][0];
  MatrixC[1][1] = MatrixA[1][0]*MatrixB[0][1] + MatrixA[1][1]*MatrixB[1][1] + MatrixA[1][2]*MatrixB[2][1];
  MatrixC[1][2] = MatrixA[1][0]*MatrixB[0][2] + MatrixA[1][1]*MatrixB[1][2] + MatrixA[1][2]*MatrixB[2][2];
  MatrixC[2][0] = MatrixA[2][0]*MatrixB[0][0] + MatrixA[2][1]*MatrixB[1][0] + MatrixA[2][2]*MatrixB[2][0];
  MatrixC[2][1] = MatrixA[2][0]*MatrixB[0][1] + MatrixA[2][1]*MatrixB[1][1] + MatrixA[2][2]*MatrixB[2][1];
  MatrixC[2][2] = MatrixA[2][0]*MatrixB[0][2] + MatrixA[2][1]*MatrixB[1][2] + MatrixA[2][2]*MatrixB[2][2];
  //显示结果矩阵
  ShowMatrix(&MatrixC,2);
  //矩阵变量清零
  ClearMatrix();
}

//矩阵求逆
// void InverseMatrix()
// {
//   LCD_Clear();
//   LCD_Show(0,0,code_qiu,1);
//   LCD_Show(0,16,code_ni,1);
//   LCD_Delay(1000);
//   LCD_Delay(1000);
// }

//矩阵求模
void ModuleMatrix()
{
  //定义模值变量
  int Module;
  //输入矩阵
  LCD_Clear();
  InputMatrix( &MatrixA,1);
  LCD_Clear();
  //计算模
  Module =   ( MatrixA[0][0]*( MatrixA[1][1]*MatrixA[2][2] - MatrixA[2][1]*MatrixA[1][2] ) )
	  -  ( MatrixA[0][1]*( MatrixA[1][0]*MatrixA[2][2] - MatrixA[2][0]*MatrixA[1][2] ) )
	  +  ( MatrixA[0][2]*( MatrixA[1][0]*MatrixA[2][1] - MatrixA[2][0]*MatrixA[1][1] ) );
  //显示
  LCD_LEFT=0;
  LCD_RIGHT=1;
  LCD_Show(0,0,code_number[12],0);
  LCD_Show(0,8,code_abc[0],0);
  LCD_Show(0,16,code_number[12],0);
  LCD_Show(0,24,code_number[11],0);
  if ( (Module/1000)!=0 )
    LCD_Show(0,32,code_number[Module/1000],0);
  if ( (Module/1000)!=0 || (Module/100-(Module/1000)*10)!=0 )
    LCD_Show(0,40,code_number[Module/100-(Module/1000)*10],0);
  if ( (Module/1000)!=0 || (Module/100-(Module/1000)*10)!=0 || (Module/10-Module/1000*100-(Module/100-(Module/1000)*10)*10)!=0 )
    LCD_Show(0,48,code_number[(Module/10-Module/1000*100-(Module/100-(Module/1000)*10)*10)],0);
  LCD_Show(0,56,code_number[Module%10],0);
  //矩阵变量清零
  ClearMatrix();
}

//矩阵求伴随
void AdjointMatrix()
{
  //输入矩阵
  LCD_Clear();
  InputMatrix( &MatrixA,1);
  LCD_Clear();
  //计算伴随矩阵
  MatrixC[0][0] =  MatrixA[1][1]*MatrixA[2][2] - MatrixA[2][1]*MatrixA[1][2];
  MatrixC[1][0] =(-1)*(  MatrixA[1][0]*MatrixA[2][2] - MatrixA[2][0]*MatrixA[1][2] );
  MatrixC[2][0] =  MatrixA[1][0]*MatrixA[2][1] - MatrixA[2][0]*MatrixA[1][1];
  MatrixC[0][1] =(-1)*(  MatrixA[0][1]*MatrixA[2][2] - MatrixA[2][1]*MatrixA[0][2] );
  MatrixC[1][1] =  MatrixA[0][0]*MatrixA[2][2] - MatrixA[2][0]*MatrixA[0][2];
  MatrixC[2][1] =(-1)*(  MatrixA[0][0]*MatrixA[2][1] - MatrixA[2][0]*MatrixA[0][1] );
  MatrixC[0][2] =  MatrixA[0][1]*MatrixA[1][2] - MatrixA[1][1]*MatrixA[0][2];
  MatrixC[1][2] =(-1)*(  MatrixA[0][0]*MatrixA[1][2] - MatrixA[1][0]*MatrixA[0][2] );
  MatrixC[2][2] =  MatrixA[1][1]*MatrixA[0][0] - MatrixA[0][1]*MatrixA[1][0];
  //显示结果
  ShowMatrix(&MatrixC,5);
  //矩阵变量清零
  ClearMatrix();
}