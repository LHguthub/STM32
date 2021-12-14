#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "HK_all_include.h"

void ExInt_Init(void);
interrupt void xint1_isr(void);

//###########################################################################
//外部中断，下降沿检测
//开启XINT1外部中断
//---------------------------------------------------------------------------------------------
void ExInt_Init(void)
{
	//初始化S100/GPIO27作为中断引脚
	EALLOW;
	EXINT_S100MUX = 0;
	EXINT_S100DIR = 0;
	EXINT_S100QSEL = 0;
	EDIS;

	EALLOW;
	GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = EXINT_S100NUM;  //定位到哪个引脚中断
	EDIS;

	//中断触发极性
	XIntruptRegs.XINT1CR.bit.POLARITY = 2;                 // 1为上升沿，0和2为下降沿，3为双边沿

	//中断配置步骤-----1,开启模块中断使能，
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;                   // Enable XINT1

	//中断配置步骤-----2，重映射中断服务函数
	EALLOW;
    PieVectTable.XINT1 = &xint1_isr;
	EDIS;
	//中断配置步骤-----3，连接CPU中断矩阵Y
	IER |= M_INT1;
	//中断配置步骤-----4，连接CPU中断矩阵X
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Gropu 1 INT4   //XINT1
}

//###########################################################################
//按下S100时CPU进入该中断函数
//D400 LED状态改变
//按键操作仅仅验证外部中断功能，不建议用外部中断实现按键的检测
//由于按键有机械抖动，故按下一次S100时，可能存在不止一次触发外部中断
//---------------------------------------------------------------------------------------------
interrupt void xint1_isr(void)
{
	D400TOGGLE(); //D400 LED状态翻转，以指示进入了外部中断
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;//清除中断Group1的标识位
}

