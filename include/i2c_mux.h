/*
i2c_mux.h:
provide simple functions to controll the IIC Multiplexer
 */

#ifndef I2C_MUX_H
#define I2C_MUX_H

    void i2cScann (void);

    void selectMuxPort(uint8_t adress);

#endif // !I2C_MUX_H