#ifndef __MOTOR_EXINT_H
#define __MOTOR_EXINT_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Exint
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//S100/GPIO27 ��Ϊ�ⲿ�жϵĲ���
#define EXINT_S100NUM 27
#define S100GPIO GPIO27
#define EXINT_S100MUX GpioCtrlRegs.GPAMUX2.bit.S100GPIO
#define EXINT_S100DIR GpioCtrlRegs.GPADIR.bit.S100GPIO
#define EXINT_S100QSEL GpioCtrlRegs.GPAQSEL2.bit.S100GPIO

extern Uint16 En_D402Flash;

void ExInt_Init(void);

#endif //__MOTOR_EXINT_H
