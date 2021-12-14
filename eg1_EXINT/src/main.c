//###########################################################################
//--------M�¶���----------ԭ������------2017-09-08--------------------------------
//�����̲���˵���뿴 ���� ��Ŀ�Ҳ�� Doc�µ�txt�̳��ĵ�

//###########################################################################
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "HK_all_include.h"      //�����ù�������ʹ�õ��ģ�M�¶����Զ�������ģ�ͷ�ļ�

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
   //ʵ����RAM�����д���İ��ˣ�����ʹ�ùٷ���DELAY_US
   memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);

  //-----------------------------------������ϵͳ��ʼ���õģ�һ�㲻��---------------
   //InitKEY();//S100��������ͨIO�ڹ���δ����ʼ��  �����̲�����ͨIO��ʹ�ã���Ϊ�ⲿ�ж���������ʹ�ã������ﲻ�ٳ�ʼ��
	InitLED();//LED��ʼ��
	InitBeep();//������

	ExInt_Init();//��ʼ��S100/GPIO27 ��Ϊ�ⲿ�жϵ�����
	//��Exint.c�ļ��� interrupt void xint1_isr(void)�����ж���Ϣ

	//�ж����ò���-----5
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;    // Enable the PIE block
	EINT;                                 // Enable Global interrupt INTM
	ERTM;//��ο� ʹ����֪ �ļ����µ�   ����--ERTM��DRTM ��DSP����е�����.pdf

    while(1) 
    {
    	//ע�⣬�����ⲿ�жϲ���S100/GPIO27�� �жϷ�����Ϊ  Exint.c �ļ���  xint1_isr ������
    	//���°�������D400״̬��ת

    	//LED��˸
		//D401TOGGLE();//������˸
    	D401ON();
		D402TOGGLE();
		DELAY_US(1000000);//��ʱ��λus
    }
}									

//#################################################
//��ʼ�� LED
//-----------------------------------------------
void InitLED()
{
	EALLOW;
	//3����ͨLED
	D400MUX = 0;//GPIO����
	D400DIR = 1;//���
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
//��ʼ���������� S100
//���ӵ�GPIO27
//-----------------------------------------------
void InitKEY()
{
	EALLOW;
	S100MUX = 0;//GPIO����
	S100DIR = 0;//����
	S100PUD = 1;//���ڿ������������������裬����DSP�ڲ�����
	EDIS;
}

//#################################################
//��ʼ���������ӿ�
//GPIO6����
//----------------------------------------------
void InitBeep()
{
	BEEPLOW();//Ĭ�Ϲرշ��������
	EALLOW;
	BEEPMUX = 0;//��ͨIO����
	BEEPDIR = 1;   //���
	EDIS;
}
//===========================================================================
// No more.
//===========================================================================

 
