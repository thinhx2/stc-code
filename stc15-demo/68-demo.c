/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 系列 定时器4可编程时钟分频输出举例-----------------*/
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

//-----------------------------------------------

sfr T4T3M 	= 0xD1;                 //定时器3和定时器4控制寄存器
sfr T4H     = 0xD2;                 //定时器4高8位
sfr T4L     = 0xD3;                 //定时器4低8位
sfr T3H     = 0xD4;                 //定时器3高8位
sfr T3L     = 0xD5;                 //定时器3低8位

sbit T3     = P0^7;                 //定时器3的外部引脚
sbit T4     = P0^5;                 //定时器4的外部引脚
sbit T3CLKO = P0^6;            	    //定时器3的时钟输出脚
sbit T4CLKO = P0^4;            	    //定时器4的时钟输出脚

#define F38_4KHz (65536-FOSC/2/38400)    //1T模式
//#define F38_4KHz (65536-FOSC/2/12/38400) //12T模式

//-----------------------------------------------

void main()
{
    T4T3M |= 0x20;                 	//定时器4为1T模式
//  T4T3M &= ~0x20;                	//定时器4为12T模式

    T4T3M &= ~0x40;                 //T4_C/T=0, 对内部时钟进行时钟输出
//  T4T3M |= 0x40;                  //T4_C/T=1, 对T4引脚的外部时钟进行时钟输出

    T4L = F38_4KHz;                 //初始化计时值
    T4H = F38_4KHz >> 8;
    
    T4T3M |= 0x80;                  //定时器4开始计时
    T4T3M |= 0x10;                  //使能定时器4的时钟输出功能

    while (1);                      //程序终止
}

