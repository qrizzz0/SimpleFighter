#include "xgpio.h"
#include "xscugic.h"
#include <xvtc.h>
#include "interrupt_variables.h"
#include "../Media/Graphics.h"

#define XVTC_DEVICE_ID			XPAR_VTC_0_DET_VSYNC_EN

XVtc	VtcInst;

u8 vsyncCount;
u32 fpsCounterCount, fps;


void VSYNC_Intr_Handler(XVtc *InstancePtr) {
	vsyncCount++;
	counter++;
	if (PictureReady == 1) {
		changeFrameBuffer();
		PictureReady = 0;
		fps += 60 / vsyncCount;
		vsyncCount = 0;
		fpsCounterCount++;
	}
	if (fpsCounterCount >= 120) {
		xil_printf("FPS: %d\n\r", fps / 120);
		fpsCounterCount = 0;
		fps = 0;
	}
}

void JOY_Intr_Handler_1(void *InstancePtr) {

}

void JOY_Intr_Handler_2(void *InstancePtr) {

}

