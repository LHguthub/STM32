//###########################################################################
//--------M新动力----------原创例程------2017-09-08--------------------------------
//本例程操作说明请看 工程 栏目右侧的 Doc下的txt教程文档

//###########################################################################
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "HK_all_include.h"      //包含该工程所有使用到的（M新动力自定义外设的）头文件

extern Uint16 RamfuncsLoadSize;

void InitLED(void);
void InitKEY(void);
void InitBeep(void);

void main(void) 
{
//  Initialize System Control:b
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2803x_SysCtrl.c CAN_Node_IDfile.
   InitSysCtrl();

// Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2803x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2803x_DefaultIsr.c.
// This function is found in DSP2803x_PieVect.c.
   InitPieVectTable();

   // Copy time critical code and Flash setup code to RAM
   // The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
   // symbols are created by the linker. Refer to the F28035v1.cmd file.
   //实现在RAM中运行代码的搬运，例如使用官方的DELAY_US
   memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);

  //-----------------------------------以上是系统初始化用的，一般不动---------------
   //InitKEY();//S100按键的普通IO口功能未被初始化  本例程不做普通IO口使用，作为外部中断特殊引脚使用，故这里不再初始化
	InitLED();//LED初始化
	InitBeep();//蜂鸣器

	ExInt_Init();//初始化S100/GPIO27 作为外部中断的输入
	//在Exint.c文件的 interrupt void xint1_isr(void)处理中断信息

	//中断配置步骤-----5
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;    // Enable the PIE block
	EINT;                                 // Enable Global interrupt INTM
	ERTM;//请参看 使用须知 文件夹下的   分享--ERTM、DRTM 在DSP编程中的作用.pdf

    while(1) 
    {
    	//注意，测试外部中断采用S100/GPIO27， 中断服务函数为  Exint.c 文件的  xint1_isr 函数，
    	//按下按键触发D400状态翻转

    	//LED闪烁
		//D401TOGGLE();//交互闪烁
    	D401ON();
		D402TOGGLE();
		DELAY_US(1000000);//延时单位us
    }
}									

//#################################################
//初始化 LED
//-----------------------------------------------
void InitLED()
{
	EALLOW;
	//3个普通LED
	D400MUX = 0;//GPIO功能
	D400DIR = 1;//输出
	D401MUX = 0;
	D401DIR = 1;
	D402MUX = 0;
	D402DIR = 1;

	//RGB LED
	RGB_R_MUX=0;
	RGB_R_DIR = 1;
	RGB_G_MUX=0;
	RGB_G_DIR = 1;
	RGB_B_MUX=0;
	RGB_B_DIR = 1;
	EDIS;
}


//#################################################
//初始化独立按键 S100
//连接到GPIO27
//-----------------------------------------------
void InitKEY()
{
	EALLOW;
	S100MUX = 0;//GPIO功能
	S100DIR = 0;//输入
	S100PUD = 1;//由于开发板外置了上拉电阻，禁用DSP内部上拉
	EDIS;
}

//#################################################
//初始化蜂鸣器接口
//GPIO6控制
//----------------------------------------------
void InitBeep()
{
	BEEPLOW();//默认关闭蜂鸣器输出
	EALLOW;
	BEEPMUX = 0;//普通IO功能
	BEEPDIR = 1;   //输出
	EDIS;
}
//===========================================================================
// No more.
//===========================================================================

 
