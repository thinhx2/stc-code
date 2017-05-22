/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 系列 用RxD2串行中断2唤醒掉电模式(停电模式)举例 ----*/
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
#include "intrins.h"

#define FOSC 18432000L          //系统频率
#define BAUD 115200             //串口波特率
#define TM   (65536 - (FOSC/4/BAUD))

//-----------------------------------------------

sfr AUXR  = 0x8e;               //辅助寄存器
sfr S2CON = 0x9a;               //UART2 控制寄存器
sfr S2BUF = 0x9b;               //UART2 数据寄存器
sfr T2H   = 0xd6;               //定时器2高8位
sfr T2L   = 0xd7;               //定时器2低8位
sfr IE2   = 0xaf;               //中断控制寄存器2

#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
#define S2RB8 0x04              //S2CON.2
#define S2TB8 0x08              //S2CON.3

sfr P_SW2   = 0xBA;             //外设功能切换寄存器2

#define S2_S0 0x01              //P_SW2.0

sbit P20 = P2^0;

//-----------------------------------------------

void main()
{
    P_SW2 &= ~S2_S0;            //S2_S0=0 (P1.0/RxD2, P1.1/TxD2)
//  P_SW2 |= S2_S0;             //S2_S0=1 (P4.6/RxD2_2, P4.7/TxD2_2)

    S2CON = 0x50;               //8位可变波特率
    T2L = TM;                   //设置波特率重装值
    T2H = TM>>8;
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2

    IE2 = 0x01;                 //使能串口2中断
    EA = 1;

    while (1)
    {
        PCON = 0x02;            //MCU进入掉电模式
        _nop_();                //掉电模式被唤醒后,直接从此语句开始向下执行,不进入中断服务程序
        _nop_();
        P20 = !P20;          	//将测试口取反
    }
}

/*----------------------------
UART2 中断服务程序
-----------------------------*/
void Uart2() interrupt 8 using 1
{
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;         //清除S2RI位
        P0 = S2BUF;             //P0显示串口数据
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;         //清除S2TI位
    }
}

