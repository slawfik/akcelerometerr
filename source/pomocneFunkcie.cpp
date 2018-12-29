
#include "pomocneFunkcie.h"

uint8_t crcArray[] = { 	0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
					157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
					35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
					190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
					70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
					219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
					101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
					248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
					140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
					17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
					175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
					50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
					202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
					87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
					233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
					116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53 };

uint8_t calculateCRC(uint8_t* inputData,uint8_t dataLen)	{
	uint8_t CRC_value = 0;
	uint8_t index = 0;
	for(uint8_t i = 0;i<dataLen;i++)	{
		index = CRC_value ^ inputData[i];
		CRC_value = crcArray[index];
	}

	return CRC_value;
}

void printData(float* hodnoty,int pocetDat,bool stupne)	{
	//PRINTF("%s ",pa_buffer);
	if(stupne) {
		for(int i = 0;i<pocetDat;i++)	{
			if(hodnoty[i] < 0)	{
				PRINTF("%c=-%d ",i+88,(int)((57.296*hodnoty[i])));
			} else {
				PRINTF("%c=%d ",i+88,(int)((57.296*hodnoty[i])));
			}
		}
	} else {
		for(int i = 0;i<pocetDat;i++)	{
			if(hodnoty[i] < 0)	{
				PRINTF("%c=-%d ",i+88,(int)(1000*hodnoty[i]));
			} else {
				PRINTF("%c=%d ",i+88,(int)(1000*hodnoty[i]));
			}
		}
	}
	PRINTF("\n\r");
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
