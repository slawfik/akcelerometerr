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
 * @file    ULOHA.cpp
 * @brief   Application entry point.
 */
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "fsl_pit.h"
#include "MMA8451Q.h"

#define FF_FAL_REG ((volatile uint8_t*) 0x15)
#define PERIODA_VZORKOVANIA 800000

//#define PIT_IRQ_ID PIT_IRQn
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)



volatile bool pitFlag = false;

extern "C" void PIT_IRQHandler(void)
	{
		/* Clear interrupt flag.*/
		PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
		pitFlag = true;
	}

void initPit(uint64_t pa_usec){
	pit_config_t pitConfig;
    PIT_GetDefaultConfig(&pitConfig);

    PIT_Init(PIT, &pitConfig);

    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(pa_usec, PIT_SOURCE_CLOCK));

    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

    EnableIRQ(PIT_IRQn);

    PRINTF("\r\nStarting channel No.0 ...");
    PIT_StartTimer(PIT, kPIT_Chnl_0);
}

/*	deltaT - perioda vzorkovania*/
void hornopriepust_Filter(float *value,float deltaT,float* axisValue)	{
	int fc = 5;
	float alfa = 1/(2*3.14*deltaT*fc+1);
	value[0] = alfa * value[0] + (alfa*(axisValue[0] - axisValue[3]));
	value[1] = alfa * value[1] + (alfa*(axisValue[1] - axisValue[4]));
	value[2] = alfa * value[2] + (alfa*(axisValue[2] - axisValue[5]));
}

void dolnopriepust_Filter(float *value,float deltaT,float* axisValue)	{
	int fc = 5;
	float alfa = (2*3.14*deltaT*fc)/(1+(2*3.14*deltaT*fc));
	value[0] = alfa * axisValue[0] + (1-alfa) * value[0];
	value[1] = alfa * axisValue[1] + (1-alfa) * value[0];
	value[2] = alfa * axisValue[2] + (1-alfa) * value[0];
}

int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

    initPit(PERIODA_VZORKOVANIA);

    LED_BLUE_INIT(LOGIC_LED_ON);
    float out_HPF[3] = {0,0,0};
    float out_DPF[3] = {0,0,0};
    float _hodnotyOs[6] = {0,0,0,0,0,0};
    int pom1 ,pom2;
    MMA8451Q acc(0x1d);

    while(1) {
    	if (true == pitFlag)    {
    			LED_BLUE_ON();
				_hodnotyOs[0] = acc.getAccX();
    			LED_BLUE_OFF();
				_hodnotyOs[1] = acc.getAccY();
				_hodnotyOs[2] = acc.getAccZ();
				hornopriepust_Filter(out_HPF,(float)PERIODA_VZORKOVANIA/1000000,_hodnotyOs);
				dolnopriepust_Filter(out_DPF,(float)PERIODA_VZORKOVANIA/1000000,_hodnotyOs);
				_hodnotyOs[3] = _hodnotyOs[0];
				_hodnotyOs[4] = _hodnotyOs[1];
				_hodnotyOs[5] = _hodnotyOs[2];

				pom1 = (int)(out_HPF[0]*1000); pom2 = (int)(_hodnotyOs[0]*1000);
				PRINTF("X=%d --> X-hornoPF_X=%d\n",pom2,pom2-pom1);
				//PRINTF("HORNO_PRIEPUST_F:\nX = %d	Y = %d	Z = %d\n",(int)(out_HPF[0]*1000),(int)(out_HPF[1]*1000),(int)(out_HPF[2]*1000));
				PRINTF("DOLNO_PRIEPUST_F:\nX = %d	Y = %d	Z = %d\n\n",(int)(out_DPF[0]*1000),(int)(out_DPF[1]*1000),(int)(out_DPF[2]*1000));
				pitFlag = false;
    	}

    }
    return 0 ;
}

