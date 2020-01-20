#ifndef GPIO
#define GPIO

#include "xgpio.h"
#include "xscugic.h"
#include <xvtc.h>
//#include "timer.h"

extern XGpio LEDInst, BTNInst, SWInst, VsyncInst;
extern XVtc	VtcInst;


int InterruptSystemSetup(XScuGic *XScuGicInstancePtr);
void BTN_Intr_Handler(void *InstancePtr);
void SW_Intr_Handler(void *InstancePtr);
void VSYNC_Intr_Handler(void *InstancePtr);
void HDMI_Intr_Handler(void *InstancePtr);
void setTimerSpeed(int sw_value);
void initGPIO();

#endif
