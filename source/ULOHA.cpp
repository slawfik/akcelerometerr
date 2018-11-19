/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL25Z128xxx4_Project_Akcelerometer.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "MMA8451Q/MMA8451Q.h"
//#include "MMA8451Q/MMA8451Q.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
   BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
 //   PRINTF("Hello World%d\n",BUS_CLK);
    PRINTF("Hello World\n");
        /* Enter an infinite loop, just incrementing a counter. */
       // while(1) {

       // }
    LED_BLUE_INIT(kGPIO_DigitalOutput);
    LED_GREEN_INIT(kGPIO_DigitalOutput);
    LED_RED_INIT(kGPIO_DigitalOutput);


    MMA8451Q acc(0x1d);
    float a;
    //float a= acc.getAccX();

    /* Force the counter to be placed into memory. */
    volatile static int i = 0;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
    	a= acc.getAccX();
    	PRINTF("x=%d\n\r",a);
    	//LED_GREEN_TOGGLE();
    	//for( uint32_t a = 0x100000; a>0 ;a-- ) {
    	//}
    	a= acc.getAccY();
    	PRINTF("y=%d\n\r",a);
    	//LED_GREEN_TOGGLE();
    	//for( uint32_t a = 0x100000; a>0 ;a-- ) {
    	//}
    	a= acc.getAccZ();
    	PRINTF("z=%d\n\r\n\r",a);
    	LED_GREEN_TOGGLE();
    	for( uint32_t a = 0x250000; a>0 ;a-- ) {
    	}
    }
    return 0 ;
}
