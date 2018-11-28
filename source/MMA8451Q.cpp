/* Copyright (c) 2010-2011 mbed.org, MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "MMA8451Q.h"

MMA8451Q::MMA8451Q(int addr) : m_addr(addr) {// netreba PinName sda, PinName scl, m_i2c(sda, scl)
    // activate the peripheral
	PRINTF("Initializing Accelerometer\n");
    uint8_t data[2] = {REG_CTRL_REG_1, 0x01};
    writeRegs(data, 2);
}

MMA8451Q::~MMA8451Q() {  }

uint8_t MMA8451Q::getWhoAmI() {
    uint8_t who_am_i = 0;
    readRegs(REG_WHO_AM_I, &who_am_i, 1);
    return who_am_i;
}

float MMA8451Q::getAccX() {
    return (float(getAccAxis(REG_OUT_X_MSB))/4096.0);
}

float MMA8451Q::getAccY() {
    return (float(getAccAxis(REG_OUT_Y_MSB))/4096.0);
}

float MMA8451Q::getAccZ() {
    return (float(getAccAxis(REG_OUT_Z_MSB))/4096.0);
}

void MMA8451Q::getAccAllAxis(float * res) {
    res[0] = getAccX();
    res[1] = getAccY();
    res[2] = getAccZ();
}

void MMA8451Q::getNaklon(float * vstupneData,float * out_Naklon)	{
	out_Naklon[0] = vstupneData[0]/sqrt((vstupneData[1]*vstupneData[1]+vstupneData[2]*vstupneData[2]));
	out_Naklon[1] = vstupneData[1]/sqrt((vstupneData[0]*vstupneData[0]+vstupneData[2]*vstupneData[2]));
	out_Naklon[0] = atan(out_Naklon[0]);
	out_Naklon[1] = atan(out_Naklon[1]);
}

int16_t MMA8451Q::getAccAxis(uint8_t addr) {
    int16_t acc;
    uint8_t res[2];
    readRegs(addr, res, 2);

    acc = (res[0] << 6) | (res[1] >> 2);
    if (acc > UINT14_MAX/2)
        acc -= UINT14_MAX;

    return acc;
}

/*m_addr je adresa sleve*/
void MMA8451Q::readRegs(int addr, uint8_t * data, int len) {
    //uint8_t t[1] = {addr};
    I2C_buss.read(m_addr, addr,data, len);
    //m_i2c.write(m_addr, t, 1, true); //treba prerobit
    //m_i2c.read(m_addr, (char *)data, len); //treba prerobit
}

void MMA8451Q::writeRegs(uint8_t * data, int len) {
    //m_i2c.write(m_addr, (char *)data, len); //treba prerobit
	I2C_buss.write(m_addr, data, len);
}
