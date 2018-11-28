/**
 * @file    ULOHA.cpp
 * @brief   TOMAS SLAVKOVSKY.
 */

#include "pomocneFunkcie.h"

volatile bool pitFlag = false;

int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

    LED_BLUE_INIT(LOGIC_LED_ON);
    initPit(PERIODA_VZORKOVANIA);

    float out_HPF[3] = {0,0,0};
    float out_DPF[3] = {0,0,0};
    float out_Naklon[2] = {0,0};
    float _hodnotyOs[6] = {0,0,0,0,0,0};
    MMA8451Q acc(0x1d);

    while(1) {
    	if (true == pitFlag)    {
    			LED_BLUE_TOGGLE();
				_hodnotyOs[0] = acc.getAccX();
				_hodnotyOs[1] = acc.getAccY();
				_hodnotyOs[2] = acc.getAccZ();

				hornopriepust_Filter(out_HPF,(float)PERIODA_VZORKOVANIA/1000000,_hodnotyOs);
				dolnopriepust_Filter(out_DPF,(float)PERIODA_VZORKOVANIA/1000000,_hodnotyOs);
				acc.getNaklon(out_DPF, out_Naklon);

				_hodnotyOs[3] = _hodnotyOs[0];
				_hodnotyOs[4] = _hodnotyOs[1];
				_hodnotyOs[5] = _hodnotyOs[2];

				//pom1 = (int)(out_HPF[0]*1000); pom2 = (int)(_hodnotyOs[0]*1000);
				//PRINTF("X=%d --> X-hornoPF_X=%d\n",pom2,pom2-pom1);
				PRINTF("NAKLON_STUPNE: ");
				printData(out_Naklon, 2);
				PRINTF("DOLNO_PRIEPUST_F: ");
				printData(out_DPF, 3);
				PRINTF("DOLNO_PRIEPUST_F: ");
				printData(out_HPF, 3);
				PRINTF("\n\n");
				pitFlag = false;
    	}

    }
    return 0 ;
}

