#ifndef I2C_H_
#define I2C_H_

#define SLAVE_ADDRESS 0x3C
#define READ 1
#define WRITE 0

extern void i2c_init();

extern void init_slave_i2c(uint8_t SLAVE_ADDR);

extern void init_master();

extern void mode(uint8_t SLAVE_ADDR, uint8_t mode);

extern uint32_t I2c_Read_Slave();

extern void I2c_master_Write(uint32_t Data, uint32_t Slave_address);

extern uint32_t I2c_master_read(uint32_t Slave_address);

#endif /* I2C_H_ */
