/*************************************************************************
	工程名：Matrix_Calculator
	作者: 王召东
	联系方式：yuanliudongdong@163.com
	当前文件: src/lcd_function.c
	当前文件描述：LCD的各种功能函数实现
 ************************************************************************/

#include "../include/lcd_function.h"

//延迟程序
void LCD_Delay(unsigned int t)
{
  unsigned int i,j;
	for(i=0;i<t;i++)
	    for(j=0;j<10;j++);
}

//状态检测程序
//当LCD不忙，可以读写数据时，函数才会返回
void LCD_CheckBusy()
{
  unsigned int count_loop = 0;
  while( 1 )
  {
    //RS=0,R/W=1,EN=0
    //准备为EN制造上升沿
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 0;
    //随便向数据口写入一个数据？
    LCD_DATA = 0xFF;
    //EN获得上升沿，状态字已经写到P0口（LCD_DATA）
    LCD_EN = 1;
    //如果最高位是0，那么LCD可以读写数据，跳出while循环
    if ( (LCD_DATA & LCD_BUSY) ==0 )
      break;
    //查询十次后，默认LCD可读写数据了，跳出循环
    count_loop++;
    if (count_loop==10)
      break;
  }
}

//写指令函数
void LCD_WriteCode(unsigned char cmdcode)
{
  //检测LCD是否忙
  LCD_CheckBusy();
  //写指令准备，准备一个上升沿
  LCD_RS=0;
  LCD_RW=0;
  LCD_EN=0;
  //将指令送入P0口
  LCD_DATA=cmdcode;
  LCD_Delay(1);
  //上升沿出现，P0口指令有效
  LCD_EN=1;
  LCD_Delay(1);
  //EN口重新清零
  LCD_EN=0;
}

//写数据函数
void LCD_WriteData(unsigned char cmddata)
{
  //检测LCD是否忙
  LCD_CheckBusy();
  //写指令准备，准备一个上升沿
  LCD_RS=1;
  LCD_RW=0;
  LCD_EN=0;
  //将数据送入P0口
  LCD_DATA=cmddata;
  LCD_Delay(1);
  //上升沿出现，P0口数据有效
  LCD_EN=1;
  LCD_Delay(1);
  //EN口重新清零
  LCD_EN=0;
}

//在page页，column列显示指定字符code，左后一个参数决定是全角还是半角
//page == (0,2,4,6)；
//cols == (0,16,32,48)汉字；cols == (0,8,16,24,32,40,48,56)汉字；
//unsigned char code_table[] = {};
//chinese == 1汉字；否则为半角
void LCD_Show(unsigned char page,unsigned char cols, unsigned char *code_table, int chinese)
{
  unsigned char j=0,i;
  //区分汉字和半角字母
  int class_data = 8;
  if (chinese == 1)
  {
    class_data = 16;
  }
  //根据页和列写入数据
  for(j=0;j<2;j++)
  {
    LCD_WriteCode(LCD_PAGE+page+j);
    LCD_WriteCode(LCD_COLS+cols);
    for(i=0;i<class_data;i++) 
      LCD_WriteData(code_table[class_data*j+i]);
  }
}

//通过向每个位置写零进行清屏
void LCD_Clear()
{
  unsigned char c=0,d=0;
  //左右两屏均打开
  LCD_LEFT=0;
  LCD_RIGHT=0;
  for( d=0 ;d<8;d++)//控制页数0-7，共8页
  {
    LCD_WriteCode(LCD_PAGE+d); //每页每页进行写
    for( c=0;c<64;c++)  //每页最多可写32个中文文字或64个ASCII字符
    {
      LCD_WriteCode(LCD_COLS+c);
      LCD_WriteData(0x00);//控制列数0-63，共64列，写点内容，列地址自动加1
    }
  }
}


//欢迎界面输出函数
/*初始化界欢迎面
 * 一一一一一一一一一一一一
 *|     WELCOME!       |
 *|    51矩阵计算器      |
 *|    作者：王召东      |
 *|      2018.3        |
 * 一一一一一一一一一一一一
 */
void LCD_Welcome()
{
  //左屏 WELC
  LCD_LEFT=0;
  LCD_RIGHT=1;
  LCD_Show(0,32,code_abc[22],0);
  LCD_Show(0,40,code_abc[4],0);
  LCD_Show(0,48,code_abc[11],0);
  LCD_Show(0,56,code_abc[2],0);
  //51矩阵
  LCD_Show(2,16,code_number[5],0);
  LCD_Show(2,24,code_number[1],0);
  LCD_Show(2,32,code_ju,1);
  LCD_Show(2,48,code_zhen,1);  
  //作者：
  LCD_Show(4,16,code_zuo,1);
  LCD_Show(4,32,code_zhe,1);
  LCD_Show(4,48,code_blank,1);
  LCD_Show(4,48,code_maohao,0);
  //201
  LCD_Show(6,40,code_number[2],0);
  LCD_Show(6,48,code_number[0],0);
  LCD_Show(6,56,code_number[1],0);
  
  //右屏 COME!
  LCD_LEFT=1;
  LCD_RIGHT=0;
  LCD_Show(0,0,code_abc[14],0);
  LCD_Show(0,8,code_abc[12],0);
  LCD_Show(0,16,code_abc[4],0);
  LCD_Show(0,24,code_gantanhao,0);
  //计算器  
  LCD_Show(2,0,code_ji,1);
  LCD_Show(2,16,code_suan,1);
  LCD_Show(2,32,code_qi,1);
  //王召东
  LCD_Show(4,0,code_wang,1);
  LCD_Show(4,16,code_zhao,1);
  LCD_Show(4,32,code_dong,1);
  //201
  LCD_Show(6,0,code_number[8],0);
  LCD_Show(6,8,code_point,0);
  LCD_Show(6,16,code_number[3],0);
  //眼石清屏
  LCD_Delay(1000);
  LCD_Delay(1000);
  LCD_Delay(1000);
  LCD_Delay(1000);
  LCD_Clear();
}

//初始化函数
void LCD_Init()
{
  LCD_Delay(10);
  //关闭两屏
  LCD_LEFT=1;
  LCD_RIGHT=1;
  LCD_Delay(10);
  //写初始化命令
  LCD_WriteCode(LCD_OFF);	 
  LCD_WriteCode(LCD_PAGE);
  LCD_WriteCode(LCD_Start_Line);
  LCD_WriteCode(LCD_COLS);
  LCD_WriteCode(LCD_OPEN);
  LCD_Delay(10);
  //打开两屏
  LCD_LEFT=0;
  LCD_RIGHT=0;
  LCD_Delay(10);
  //清屏
  LCD_Clear();
  LCD_Delay(10);
  //欢迎界面
  LCD_Welcome();
  LCD_Delay(500);
}
