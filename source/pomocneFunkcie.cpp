
#include "pomocneFunkcie.h"

void printData(float* hodnoty,int pocetDat)	{
	//PRINTF("%s ",pa_buffer);
	for(int i = 0;i<pocetDat;i++)	{
		if(hodnoty[i] < 0)	{
			PRINTF("%c=-%d ",i+88,(int)((57.296*hodnoty[i])));
		} else {
			PRINTF("%c=%d ",i+88,(int)((57.296*hodnoty[i])));
		}
	}
	PRINTF("\n");
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

extern "C" void PIT_IRQHandler(void)
	{
		/* Clear interrupt flag.*/
		PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
		pitFlag = true;
	}
