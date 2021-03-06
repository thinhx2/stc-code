/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 系列 INT3下降沿唤醒掉电模式举例--------------------*/
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

//-----------------------------------------------

sfr INT_CLKO = 0x8F;            //外部中断与时钟输出控制寄存器
sbit INT3 = P3^7;               //INT3引脚定义

sbit P10 = P1^0;

//-----------------------------------------
//中断服务程序
void exint3() interrupt 11
{
    P10 = !P10;                 //将测试口取反
    
//  INT_CLKO &= 0xDF;           //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
//  INT_CLKO |= 0x20;           //然后再开中断即可
}

//-----------------------------------------------

void main()
{
    INT_CLKO |= 0x20;      	    //(EX3 = 1)使能INT3下降沿中断
    EA = 1;

    while (1)
    {
        PCON = 0x02;            //MCU进入掉电模式
        _nop_();                //掉电模式被唤醒后,首先执行此语句,然后再进入中断服务程序
        _nop_();
    }
}

