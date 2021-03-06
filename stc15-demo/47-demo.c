/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 系列 INT3中断举例----------------------------------*/
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

sfr INT_CLKO = 0x8f;                //外部中断与时钟输出控制寄存器
sbit P10 = P1^0;

//-----------------------------------------------
//中断服务程序
void exint3() interrupt 11          //INT3中断入口
{
    P10 = !P10;                     //将测试口取反
    
//  INT_CLKO &= 0xDF;               //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
//  INT_CLKO |= 0x20;               //然后再开中断即可
}

void main()
{
    INT_CLKO |= 0x20;               //(EX3 = 1)使能INT3中断
    EA = 1;

    while (1);
}

