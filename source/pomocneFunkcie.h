/*
 * pomocneFunkcie.h
 *
 *  Created on: 27. 11. 2018
 *      Author: tomas
 */

#ifndef POMOCNEFUNKCIE_H_
#define POMOCNEFUNKCIE_H_

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_pit.h"
#include "MMA8451Q.h"

#define FF_FAL_REG ((volatile uint8_t*) 0x15)
#define PERIODA_VZORKOVANIA 400000
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
#define TERMINAL_ADDR 0xd0
#define START_BYTE 0xA0
extern volatile bool pitFlag;

extern "C" void PIT_IRQHandler(void);
void printData(float* hodnoty,int pocetDat,bool stupne);
void initPit(uint64_t pa_usec);
void hornopriepust_Filter(float *value,float deltaT,float* axisValue);
void dolnopriepust_Filter(float *value,float deltaT,float* axisValue);
uint8_t calculateCRC(uint8_t* inputData,uint8_t dataLen);
void decimal_to_tex(uint8_t* input_string,const uint8_t data_len,uint8_t* output);
#endif /* POMOCNEFUNKCIE_H_ */
