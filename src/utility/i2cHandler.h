#ifndef _I2C_H_
#define _I2C_H_

//====================================================================================== 
//   Includes 
//======================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/i2c.h"
#include "esp_log.h"

//====================================================================================== 
//   Macros
//======================================================================================

//====================================================================================== 
//   Public variables & defines
//======================================================================================

//====================================================================================== 
//   Public functions & routines
//======================================================================================

/**
 * @brief i2c master initialization
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t I2CInit(void);

/**
 * @brief Write to an I2C slave device
 * @param i2cAddress The I2C address of the slave device
 * @param writeBuffer The buffer to write
 * @param sizeBuffer The size of the buffer
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t I2CWrite(uint8_t i2cAddress, uint8_t *writeBuffer, size_t sizeBuffer);

/**
 * @brief Read from an I2C slave device
 * @param i2cAddress The I2C address of the slave device
 * @param readBuffer The buffer to store the read data
 * @param sizeBuffer The size of the buffer
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t I2CRead(uint8_t i2cAddress, uint8_t *readBuffer, size_t sizeBuffer);

#endif /* _I2C_H_ */