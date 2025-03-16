/**
 * @file PCA9685.c
 * @brief PCA9685 driver to control the PWM signals of up to 16 channels
 * @author Sabri Chamtouri
 */

//====================================================================================== 
//   Includes 
//======================================================================================

#include "PCA9685.h"

//====================================================================================== 
//   Macros
//======================================================================================

//====================================================================================== 
//   Private variables & defines
//======================================================================================

//====================================================================================== 
//   Private functions & routines
//======================================================================================

//====================================================================================== 
//   Public functions & routines
//======================================================================================

/**
 * @brief Initialize the PCA9685
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t PCA9685Init()
{
    uint8_t writeBuffer[1+6];
    memset(writeBuffer, 0, sizeof(writeBuffer));
    size_t sizeBuffer = sizeof(writeBuffer);

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;

    return ESP_OK;
}

/**
 * @brief Set the PWM frequency of the PCA9685
 * @param frequency The frequency to set, max 1526Hz and min 24Hz
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t PCA9685SetFrequency(uint8_t frequency)
{
    uint8_t writeBuffer[2];
    memset(writeBuffer, 0, sizeof(writeBuffer));
    size_t sizeBuffer = sizeof(writeBuffer);

    // Prescale value
    uint8_t prescaleValue = (PCA9685_CLOCK_FREQ / 4096 / frequency)  - 1;

    // Set sleep mode
    writeBuffer[0] = MODE1;
    writeBuffer[1] = MODE1_SLEEP;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;
    
    // Set prescale
    writeBuffer[0] = PRE_SCALE;
    writeBuffer[1] = prescaleValue;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;
    
    // Insert delay of 500us
    usleep(500);
    
    // Set restart mode1
    writeBuffer[0] = MODE1;
    writeBuffer[1] = MODE1_RESTART;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;
    
    // Set totem mode2
    writeBuffer[0] = MODE2;
    writeBuffer[1] = MODE2_OUTDRV;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;

    return ESP_OK;
}

/**
 * @brief Set the duty cycle of all channels of the PCA9685
 * @param channel The channel to set the duty cycle
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t PCA9685SetDutyCycle(e_ChannelHandler handler, float dutyCycle)
{
    uint8_t writeBuffer[2];
    memset(writeBuffer, 0, sizeof(writeBuffer));
    size_t sizeBuffer = sizeof(writeBuffer);

    // Channel ON - MSB
    writeBuffer[0] = handler + 1;
    writeBuffer[1] = (uint16_t)((100 - dutyCycle) * 4096 / 100) >> 8;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;

    // Channel ON - LSB
    writeBuffer[0] = handler;
    writeBuffer[1] = (uint16_t)((100 - dutyCycle) * 4096 / 100) & 0xFF;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;    
    
    // Channel OFF - MSB
    writeBuffer[0] = handler + 3;
    writeBuffer[1] = 4095 >> 8;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;

    // Channel OFF - LSB
    writeBuffer[0] = handler + 2;
    writeBuffer[1] = 4095 & 0xFF;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;
    
   return ESP_OK;
}

/**
 * @brief Set the duty cycle of all channels of the PCA9685
 * @param channel The channel to set the duty cycle
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t PCA9685SetAllDutyCycle(float dutyCycle)
{
    uint8_t writeBuffer[2];
    memset(writeBuffer, 0, sizeof(writeBuffer));
    size_t sizeBuffer = sizeof(writeBuffer);

    // ALL ON - MSB
    writeBuffer[0] = ALL_LED_ON_H;
    writeBuffer[1] = (uint16_t)((100 - dutyCycle) * 4096 / 100) >> 8;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;

    // ALL ON - LSB
    writeBuffer[0] = ALL_LED_ON_L;
    writeBuffer[1] = (uint16_t)((100 - dutyCycle) * 4096 / 100) & 0xFF;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;    
    
    // ALL OFF - MSB
    writeBuffer[0] = ALL_LED_OFF_H;
    writeBuffer[1] = 4095 >> 8;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;

    // ALL OFF - LSB
    writeBuffer[0] = ALL_LED_OFF_L;
    writeBuffer[1] = 4095 & 0xFF;

    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;
    
   return ESP_OK;
}

/**
 * @brief Turn off all the outputs of the PCA9685
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t PCA9685TurnOffAll()
{
    uint8_t writeBuffer[2];
    memset(writeBuffer, 0, sizeof(writeBuffer));
    size_t sizeBuffer = sizeof(writeBuffer);

    // ALL OFF - MSB
    writeBuffer[0] = ALL_LED_OFF_H;
    writeBuffer[1] = 0x10;  // Stop all outputs bit
    
    if(I2CWrite(PCA9685_ADDRESS, writeBuffer, sizeBuffer) != ESP_OK) return ESP_FAIL;

    return ESP_OK;
}

/*End of PCA9685.c*/