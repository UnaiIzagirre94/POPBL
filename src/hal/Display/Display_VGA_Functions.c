/**
****************************************************************************
* @file			DISPLAY_VGA_FUNCTIONS.c
* @brief 		File general description
* @version		0.1.0
* @date			2016-11-01
****************************************************************************
* @author		Allende, Imanol
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |  Revised by   |  Description
*  --------- | ------------ | ------------- | ----------------------------
*    0.1.0   | 2016-11-01   |  iallende     | Original version
****************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/
#include "../hal/Display/Display.h"
#include "Display_vga.h"
#include <math.h>
#include "Config.h"
#include "font8x8.h"

/***************************************************************************
 **                                                                       **
 **                      DEFINITIONS AND MACROS                           **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      TYPEDEFS AND STRUCTURES                          **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      PROTOTYPES OF LOCAL FUNCTIONS                    **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      EXPORTED VARIABLES                               **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      GLOBAL VARIABLES                                 **
 **                                                                       **
 ***************************************************************************/
DisplayCtrl vgaCtrl;
u32 vgaBuf[3][DISPLAYDEMO_MAX_FRAME];
u32 frameBuffer[DISPLAYDEMO_MAX_FRAME];

/***************************************************************************
 **                                                                       **
 **                      EXPORTED FUNCTIONS                               **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      LOCAL FUNCTIONS                                  **
 **                                                                       **
 ***************************************************************************/

/**
* @brief Init of the VGA
* @par 	Execution of the DISPLAY_VGA_FUNCTIONS_displayDemoInitializeFroga
* @param Empty
* @return Nothing
*/
void DISPLAY_VGA_FUNCTIONS_displayInit(){
	DISPLAY_VGA_FUNCTIONS_displayDemoInitializeFroga(&vgaCtrl, VGA_VDMA_ID, SCU_TIMER_ID, VGA_BASEADDR, DISPLAY_NOT_HDMI );
}

/**
* @brief Init of the VGA
* @par 	Execution of the DISPLAY_VGA_FUNCTIONS_displayDemoInitializeFroga
* @param &vgaCtrl, VGA_VDMA_ID, SCU_TIMER_ID, VGA_BASEADDR, DISPLAY_NOT_HDMI
* @return 0
*/
int DISPLAY_VGA_FUNCTIONS_displayDemoInitializeFroga(DisplayCtrl *dispPtr, u16 vdmaId, u16 timerId, u32 dispCtrlAddr, int fHdmi){
	int Status = 0;
	char str[50];
	Status = DisplayInitialize(dispPtr, vdmaId, dispCtrlAddr, fHdmi,  vgaBuf, DISPLAYDEMO_STRIDE);
	if (Status != XST_SUCCESS)
	{
#if defined UART
		sprintf(str, "Display Ctrl initialization failed during demo initialization%d\r\n", Status);
		DISPLAY_printString(str);
		return XST_FAILURE;
#endif
	}

	Status = DisplayStart(dispPtr);
	if (Status != XST_SUCCESS)
	{
#if defined UART
		sprintf(str, "Couldn't start display during demo initialization%d\r\n", Status);
		DISPLAY_printString(str);
		return XST_FAILURE;
#endif
	}
	return 0;
}

/**
* @brief Draw a line
* @par 	Draw a line in the screen through VGA
* @param the width of the line
* @return Nothing
*/
void DISPLAY_VGA_FUNCTIONS_drawLine(int lineWidth){
	int i;
		int height = 0;
		int width = 0;
		u32 wStride;
		u32 iPixelAddr;
		u32 wRed, wBlue, wGreen, wColor;
		u32 wCurrentInt;
		double fRed, fBlue, fGreen, fColor;
		u32 xLeft, xMid, xRight, xInt;
		u32 yMid, yInt;
		double xInc, yInc;
		u32 xcoi, ycoi;


		//Inicializacion
		height = vgaCtrl.vMode.height;
		width = vgaCtrl.vMode.width;
		wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */

		xInt = vgaCtrl.vMode.width / 4; //Four intervals, each with width/4 pixels
		xLeft = xInt;
		xMid = xInt * 2;
		xRight = xInt * 3;
		xInc = 256.0 / ((double) xInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)

		yInt = vgaCtrl.vMode.height / 2; //Two intervals, each with width/2 lines
		yMid = yInt;
		yInc = 256.0 / ((double) yInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)


		wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */

		xInt = width / 7; //Seven intervals, each with width/7 pixels
		xInc = 256.0 / ((double) xInt); //256 color intensities per interval. Notice that overflow is handled for this pattern.

		fBlue = 0.0;
		fRed = 255.0;
		fGreen = 0.0;
		//fColor = fBlue;
		wCurrentInt = 1;
		for(xcoi = 0; xcoi < lineWidth ; xcoi++){
			wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
			iPixelAddr = xcoi;
			for(ycoi = 0; ycoi < height; ycoi++){
				vgaBuf[0][iPixelAddr] = wColor;
				/*
				 * This pattern is printed one vertical line at a time, so the address must be incremented
				 * by the stride instead of just 1.
				 */
				iPixelAddr += wStride;
			}


		}
		/*
		* Flush the framebuffer memory range to ensure changes are written to the
		* actual memory, and therefore accessible by the VDMA.
		*/
		Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);

}

/**
* @brief Draw a vertical line
* @par 	Draw a line in the screen through VGA
* @param the width of the line and the start xand y point
* @return Nothing
*/
void DISPLAY_VGA_FUNCTIONS_drawLineVertical(int x , int y , int lineWidth){
	int i;
		int height = 0;
		int width = 0;
		u32 wStride;
		u32 iPixelAddr;
		u32 wRed, wBlue, wGreen, wColor;
		u32 wCurrentInt;
		double fRed, fBlue, fGreen;
		u32 xLeft, xMid, xRight, xInt;
		u32 yMid, yInt;
		double xInc, yInc;
		u32 xcoi, ycoi;


		//Inicializacion
		height = vgaCtrl.vMode.height;
		width = vgaCtrl.vMode.width;
		wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */

		xInt = vgaCtrl.vMode.width / 4; //Four intervals, each with width/4 pixels
		xLeft = xInt;
		xMid = xInt * 2;
		xRight = xInt * 3;
		xInc = 256.0 / ((double) xInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)

		yInt = vgaCtrl.vMode.height / 2; //Two intervals, each with width/2 lines
		yMid = yInt;
		yInc = 256.0 / ((double) yInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)


		wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */

		xInt = width / 7; //Seven intervals, each with width/7 pixels
		xInc = 256.0 / ((double) xInt); //256 color intensities per interval. Notice that overflow is handled for this pattern.

		fBlue = 0.0;
		fRed = 255.0;
		fGreen = 0.0;
		//fColor = fBlue;
		wCurrentInt = 1;
		for(xcoi = x; xcoi < x+lineWidth ; xcoi++){
			wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
			iPixelAddr = xcoi;
			for(ycoi = 0; ycoi < height; ycoi++){
				vgaBuf[0][iPixelAddr] = wColor;
				/*
				 * This pattern is printed one vertical line at a time, so the address must be incremented
				 * by the stride instead of just 1.
				 */
				iPixelAddr += wStride;
			}


		}
		/*
		* Flush the framebuffer memory range to ensure changes are written to the
		* actual memory, and therefore accessible by the VDMA.
		*/
		Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);

}


/**
* @brief Draw a line between two coordinates
* @par 	Draw a line in the screen through VGA
* @param the width of the line and x and y of the two coordinates
* @return Nothing
*/
void DISPLAY_VGA_FUNCTIONS_drawLine2Pto(int x0, int y0 , int x1, int y1 ){
	int height_limit = 0;
	int width_limit = 0;
	u32 wStride;
	u32 iPixelAddr;
	u32 wColor;
	double fRed, fBlue, fGreen;
	u32 x, y;
	float malda=0;
	int aux = 0;
	//Inicializacion
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */
	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
	fBlue = 0.0;
	fRed = 255.0;
	fGreen = 0.0;
	//comprobar los limites
	//establecer el color
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
	//
	if (x1 < x0){
		aux = x0;
		x0=x1;
		x1=aux;
		aux = y0;
		y0=y1;
		y1=aux;
	}
	malda= (float)(y1-y0)/(float)(x1-x0);
	for(x = x0 ; x <x1; x++){
			iPixelAddr = x +  (  (y0 +  (int)( (x-x0) * malda ) ) * wStride ) ;
			vgaBuf[0][iPixelAddr] = wColor;
			//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);

	}
			/*
		* Flush the framebuffer memory range to ensure changes are written to the
		* actual memory, and therefore accessible by the VDMA.
		*/
	Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);

}

/**
* @brief Update the frame of the VGA
* @par 	Draw a line in the screen through VGA
* @param Empty
* @return Nothing
*/
void DISPLAY_VGA_FUNCTIONS_updateFrame(){
	static int i = 0;
	Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);
}

void DISPLAY_VGA_FUNCTIONS_borrarFrameBuffer(){

	u32 x;
	int y;
	int height_limit = 0;
	int width_limit = 0;
	u32 wStride;
	u32 iPixelAddr;
	double fRed, fBlue, fGreen;
	u32 wColor;
	//
	int index = 0;


	fBlue = 0;
	fRed = 0;
	fGreen = 0;
	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	for( x = 0 ; x <= height_limit; x++){
		for ( y = 0 ; y <  width_limit ; y++ ){
			iPixelAddr = x + ((y)*wStride);
			frameBuffer[iPixelAddr] = wColor;
		}
	}
}

/**
* @brief Copy the frame
* @par 	Used to replace it later and do not have a blinking
* @param Empty
* @return Nothing
*/
void DISPLAY_VGA_FUNCTIONS_copiarFrameBuffer(){

	u32 x;
	int y;
	int height_limit = 0;
	int width_limit = 0;
	u32 wStride;
	u32 iPixelAddr;
	double fRed, fBlue, fGreen;
	u32 wColor;
	//
	int index = 0;

	fBlue = 0;
	fRed = 0;
	fGreen = 0;
	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	for( x = 0 ; x <= height_limit; x++){
		for ( y = 0 ; y <  width_limit ; y++ ){
		iPixelAddr = x + ((y)*wStride);
		vgaBuf[index][iPixelAddr] = frameBuffer[iPixelAddr];
		}
	}
}

/**
* @brief Dsipaly Char through the VGA
* @param the x and y coordinates and the character to print
* @return Nothing
*/
void DISPLAY_VGA_FUNCTIONS_displayChar(int x0 , int y0 , char kar){
	int height_limit = 0;
		int width_limit = 0;
		u32 wStride;
		u32 iPixelAddr;
		u32 wColor;
		double fRed, fBlue, fGreen;
		u32 x, y;
		int i = 0;
		char line = 0;
		char auxByte = 0;
		char mask = 0x01;
		//Inicializacion
		height_limit = vgaCtrl.vMode.height;
		width_limit = vgaCtrl.vMode.width;
		wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */
		wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
		fBlue = 255.0;
		fRed = 221.0;
		fGreen = 182.0;
		//comprobar los limites
		//establecer el color
		wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
		//
		for (i = 0 ; i < 8 ; i++){
			line = font8x8_basic[(int)kar][i];
			for(x = 0 ; x <8; x++){
				auxByte = line & (mask<<x);
				if ( auxByte > 0){
					iPixelAddr = (x0+x) +  (  (y0 + i ) * wStride ) ;
					frameBuffer[iPixelAddr] = wColor;
				}
			}
		}

				/*
			* Flush the framebuffer memory range to ensure changes are written to the
			* actual memory, and therefore accessible by the VDMA.
			*/
		//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);


}







