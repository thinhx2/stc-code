/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 系列 内部RC时钟输出举例----------------------------*/
/* --- Mobile: (86)13922805190 -------------- -------------------------*/
/* --- Fax: 86-755-82905966 -------------------------------------------*/
/* --- Tel: 86-755-82948412 -------------------------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了宏晶科技的资料及程序   */
/* 如果要在文章中应用此代码,请在文章中注明使用了宏晶科技的资料及程序   */
/*---------------------------------------------------------------------*/

//本示例在Keil开发环境下请选择Intel的8058芯片型号进行编译
//假定测试芯片的工作频率为18.432MHz

#include "reg51.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 18432000L

//-----------------------------------------

sfr CLK_DIV	=0x97;              //IRC时钟输出控制寄存器

//-----------------------------------------

void main()
{
    CLK_DIV = 0x40;             //0100,0000 P5.4输出频率为SYSclk
//  CLK_DIV = 0x80;             //1000,0000 P5.4输出频率为SYSclk/2
//  CLK_DIV = 0xc0;             //1100,0000 P5.4输出频率为SYSclk/4
    
    while (1);                  //程序终止
}

