/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 系列 T1扩展为外部下降沿中断举例--------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
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

//-----------------------------------------------

sfr AUXR = 0x8e;                    //辅助寄存器
sbit P10 = P1^0;

//-----------------------------------------------
//中断服务程序
void t1int() interrupt 3            //中断入口
{
    P10 = !P10;                     //将测试口取反
}

void main()
{
    AUXR = 0x40;                    //定时器1为1T模式
    TMOD = 0x40;                    //设置定时器1为16位自动重装载外部记数模式
    TH1 = TL1 = 0xff;               //设置定时器1初始值
    TR1 = 1;                        //定时器1开始工作
    ET1 = 1;                        //开定时器1中断

    EA = 1;

    while (1);
}

