#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "HK_all_include.h"

void ExInt_Init(void);
interrupt void xint1_isr(void);

//###########################################################################
//�ⲿ�жϣ��½��ؼ��
//����XINT1�ⲿ�ж�
//---------------------------------------------------------------------------------------------
void ExInt_Init(void)
{
	//��ʼ��S100/GPIO27��Ϊ�ж�����
	EALLOW;
	EXINT_S100MUX = 0;
	EXINT_S100DIR = 0;
	EXINT_S100QSEL = 0;
	EDIS;

	EALLOW;
	GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = EXINT_S100NUM;  //��λ���ĸ������ж�
	EDIS;

	//�жϴ�������
	XIntruptRegs.XINT1CR.bit.POLARITY = 2;                 // 1Ϊ�����أ�0��2Ϊ�½��أ�3Ϊ˫����

	//�ж����ò���-----1,����ģ���ж�ʹ�ܣ�
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;                   // Enable XINT1

	//�ж����ò���-----2����ӳ���жϷ�����
	EALLOW;
    PieVectTable.XINT1 = &xint1_isr;
	EDIS;
	//�ж����ò���-----3������CPU�жϾ���Y
	IER |= M_INT1;
	//�ж����ò���-----4������CPU�жϾ���X
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Gropu 1 INT4   //XINT1
}

//###########################################################################
//����S100ʱCPU������жϺ���
//D400 LED״̬�ı�
//��������������֤�ⲿ�жϹ��ܣ����������ⲿ�ж�ʵ�ְ����ļ��
//���ڰ����л�е�������ʰ���һ��S100ʱ�����ܴ��ڲ�ֹһ�δ����ⲿ�ж�
//---------------------------------------------------------------------------------------------
interrupt void xint1_isr(void)
{
	D400TOGGLE(); //D400 LED״̬��ת����ָʾ�������ⲿ�ж�
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;//����ж�Group1�ı�ʶλ
}

