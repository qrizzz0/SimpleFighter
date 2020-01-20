#include "xparameters.h"
#include "handlers.h"

#define INTC_VSYNC_INTERRUPT_ID			65U
#define GPIO_INT 			XGPIO_IR_CH1_MASK
#define INTC_DEVICE_ID 		XPAR_PS7_SCUGIC_0_DEVICE_ID

XScuGic INTCInst;

int InterruptSystemSetup(XScuGic *XScuGicInstancePtr)
{
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			 	 	 	 	 	 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
			 	 	 	 	 	 XScuGicInstancePtr);
	Xil_ExceptionEnable();



	return XST_SUCCESS;

}

int IntcInitFunction(u16 DeviceId, XVtc *XVtcInstancePtr) {
	XScuGic_Config *IntcConfig;
	int status;
	// Interrupt controller initialisation
	IntcConfig = XScuGic_LookupConfig(DeviceId);
	status = XScuGic_CfgInitialize(&INTCInst, IntcConfig, IntcConfig->CpuBaseAddress);
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Call to interrupt setup
	status = InterruptSystemSetup(&INTCInst);
	if(status != XST_SUCCESS) return XST_FAILURE;

	XScuGic_SetPriorityTriggerType(&INTCInst, INTC_VSYNC_INTERRUPT_ID, 8, 3);

	// Connect GPIO interrupt to handler
	status = XScuGic_Connect(&INTCInst,
							 INTC_VSYNC_INTERRUPT_ID,
					  	  	 (Xil_ExceptionHandler)VSYNC_Intr_Handler,
					  	  	 (void *)XVtcInstancePtr);
	if(status != XST_SUCCESS) return XST_FAILURE;

	XScuGic_Enable(&INTCInst, INTC_VSYNC_INTERRUPT_ID);

	XVtc_SelfTest(XVtcInstancePtr);

	return XST_SUCCESS;
}

void initializeInterrupts() {

	int status = IntcInitFunction(INTC_DEVICE_ID, &VtcInst);
	if(status != XST_SUCCESS) return XST_FAILURE;

}
