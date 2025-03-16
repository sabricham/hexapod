/**
 * @file PCA9685.h
 * @brief PCA9685 driver to control the PWM signals of up to 16 channels
 * @author Sabri Chamtouri
 */

 #ifndef _PCA9685_H_
 #define _PCA9685_H_
 
//====================================================================================== 
//   Includes 
//======================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "i2cHandler.h"

//====================================================================================== 
//   Macros
//======================================================================================
 
///< Setting Parameters
#define PCA9685_ADDRESS 0x40            // I2C address of the PCA9685
#define PCA9685_FREQUENCY 50            // Frequency of the PWM signal in Hz
#define PCA9685_CLOCK_FREQ 25000000     // Frequency of the internal oscillator in Hz

///< Register definitions
#define MODE1 0x00          // Mode register 1
#define MODE2 0x01          // Mode register 2
#define SUBADR1 0x02        // I2C-bus subaddress 1
#define SUBADR2 0x03        // I2C-bus subaddress 2
#define SUBADR3 0x04        // I2C-bus subaddress 3
#define ALLCALLADR 0x05     // LED All Call I2C-bus address
#define LED0_ON_L 0x06      // LED0 output and brightness control byte 0
#define LED0_ON_H 0x07      // LED0 output and brightness control byte 1
#define LED0_OFF_L 0x08     // LED0 output and brightness control byte 2
#define LED0_OFF_H 0x09     // LED0 output and brightness control byte 3
#define LED1_ON_L 0x0A      // LED1 output and brightness control byte 0
#define LED1_ON_H 0x0B      // LED1 output and brightness control byte 1
#define LED1_OFF_L 0x0C     // LED1 output and brightness control byte 2
#define LED1_OFF_H 0x0D     // LED1 output and brightness control byte 3
#define LED2_ON_L 0x0E      // LED2 output and brightness control byte 0
#define LED2_ON_H 0x0F      // LED2 output and brightness control byte 1
#define LED2_OFF_L 0x10     // LED2 output and brightness control byte 2
#define LED2_OFF_H 0x11     // LED2 output and brightness control byte 3
#define LED3_ON_L 0x12      // LED3 output and brightness control byte 0
#define LED3_ON_H 0x13      // LED3 output and brightness control byte 1
#define LED3_OFF_L 0x14     // LED3 output and brightness control byte 2
#define LED3_OFF_H 0x15     // LED3 output and brightness control byte 3
#define LED4_ON_L 0x16      // LED4 output and brightness control byte 0
#define LED4_ON_H 0x17      // LED4 output and brightness control byte 1
#define LED4_OFF_L 0x18     // LED4 output and brightness control byte 2
#define LED4_OFF_H 0x19     // LED4 output and brightness control byte 3
#define LED5_ON_L 0x1A      // LED5 output and brightness control byte 0
#define LED5_ON_H 0x1B      // LED5 output and brightness control byte 1
#define LED5_OFF_L 0x1C     // LED5 output and brightness control byte 2
#define LED5_OFF_H 0x1D     // LED5 output and brightness control byte 3
#define LED6_ON_L 0x1E      // LED6 output and brightness control byte 0
#define LED6_ON_H 0x1F      // LED6 output and brightness control byte 1
#define LED6_OFF_L 0x20     // LED6 output and brightness control byte 2
#define LED6_OFF_H 0x21     // LED6 output and brightness control byte 3
#define LED7_ON_L 0x22      // LED7 output and brightness control byte 0
#define LED7_ON_H 0x23      // LED7 output and brightness control byte 1
#define LED7_OFF_L 0x24     // LED7 output and brightness control byte 2
#define LED7_OFF_H 0x25     // LED7 output and brightness control byte 3
#define LED8_ON_L 0x26      // LED8 output and brightness control byte 0
#define LED8_ON_H 0x27      // LED8 output and brightness control byte 1
#define LED8_OFF_L 0x28     // LED8 output and brightness control byte 2
#define LED8_OFF_H 0x29     // LED8 output and brightness control byte 3
#define LED9_ON_L 0x2A      // LED9 output and brightness control byte 0
#define LED9_ON_H 0x2B      // LED9 output and brightness control byte 1
#define LED9_OFF_L 0x2C     // LED9 output and brightness control byte 2
#define LED9_OFF_H 0x2D     // LED9 output and brightness control byte 3
#define LED10_ON_L 0x2E     // LED10 output and brightness control byte 0
#define LED10_ON_H 0x2F     // LED10 output and brightness control byte 1
#define LED10_OFF_L 0x30    // LED10 output and brightness control byte 2
#define LED10_OFF_H 0x31    // LED10 output and brightness control byte 3
#define LED11_ON_L 0x32     // LED11 output and brightness control byte 0
#define LED11_ON_H 0x33     // LED11 output and brightness control byte 1
#define LED11_OFF_L 0x34    // LED11 output and brightness control byte 2
#define LED11_OFF_H 0x35    // LED11 output and brightness control byte 3
#define LED12_ON_L 0x36     // LED12 output and brightness control byte 0
#define LED12_ON_H 0x37     // LED12 output and brightness control byte 1
#define LED12_OFF_L 0x38    // LED12 output and brightness control byte 2
#define LED12_OFF_H 0x39    // LED12 output and brightness control byte 3
#define LED13_ON_L 0x3A     // LED13 output and brightness control byte 0
#define LED13_ON_H 0x3B     // LED13 output and brightness control byte 1
#define LED13_OFF_L 0x3C    // LED13 output and brightness control byte 2
#define LED13_OFF_H 0x3D    // LED13 output and brightness control byte 3
#define LED14_ON_L 0x3E     // LED14 output and brightness control byte 0
#define LED14_ON_H 0x3F     // LED14 output and brightness control byte 1
#define LED14_OFF_L 0x40    // LED14 output and brightness control byte 2
#define LED14_OFF_H 0x41    // LED14 output and brightness control byte 3
#define LED15_ON_L 0x42     // LED15 output and brightness control byte 0
#define LED15_ON_H 0x43     // LED15 output and brightness control byte 1
#define LED15_OFF_L 0x44    // LED15 output and brightness control byte 2
#define LED15_OFF_H 0x45    // LED15 output and brightness control byte 3
#define ALL_LED_ON_L 0xFA   // Load all the LEDn_ON registers, byte 0
#define ALL_LED_ON_H 0xFB   // Load all the LEDn_ON registers, byte 1
#define ALL_LED_OFF_L 0xFC  // Load all the LEDn_OFF registers, byte 0
#define ALL_LED_OFF_H 0xFD  // Load all the LEDn_OFF registers, byte 1
#define PRE_SCALE 0xFE      // Prescaler for PWM output frequency
#define TEST_MODE 0xFF      // Defines the test mode to be entered

///< MODE1 register bits
#define MODE1_RESTART 0x80  // Restart bit
#define MODE1_EXTCLK  0x40  // External clock bit
#define MODE1_AI      0x20  // Auto-increment bit
#define MODE1_SLEEP   0x10  // Sleep mode bit
#define MODE1_SUB1    0x08  // Subaddress 1 bit
#define MODE1_SUB2    0x04  // Subaddress 2 bit
#define MODE1_SUB3    0x02  // Subaddress 3 bit
#define MODE1_ALLCALL 0x01  // All call address bit

///< MODE2 register bits
#define MODE2_INVRT   0x10  // Invert output logic bit
#define MODE2_OCH     0x08  // Output change on STOP bit
#define MODE2_OUTDRV  0x04  // Output driver mode bit
#define MODE2_OUTNE1  0x02  // Output not enabled bit 1
#define MODE2_OUTNE0  0x01  // Output not enabled bit 0

///< Handlers
typedef enum {
    LED0 = 0x06,
    LED1 = 0x0A,
    LED2 = 0x0E,
    LED3 = 0x12,
    LED4 = 0x16,
    LED5 = 0x1A,
    LED6 = 0x1E,
    LED7 = 0x22,
    LED8 = 0x26,
    LED9 = 0x2A,
    LED10 = 0x2E,
    LED11 = 0x32,
    LED12 = 0x36,
    LED13 = 0x3A,
    LED14 = 0x3E,
    LED15 = 0x42
} e_ChannelHandler;

//====================================================================================== 
//   Public variables & defines
//======================================================================================

//====================================================================================== 
//   Public functions & routines
//======================================================================================

/**
 * @brief Initialize the PCA9685
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t PCA9685Init();

/**
 * @brief Set the frequency of the PWM signal
 * @param frequency The frequency to set
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t PCA9685SetFrequency(uint8_t frequency);

/**
 * @brief Set the duty cycle of all channels of the PCA9685
 * @param channel The channel to set the duty cycle
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t PCA9685SetDutyCycle(e_ChannelHandler handler, float dutyCycle);

/**
 * @brief Set the duty cycle of a specific channel of the PCA9685
 * @param channel The channel to set the duty cycle
 * @param dutyCycle The duty cycle to set
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t PCA9685SetAllDutyCycle(float dutyCycle);

/**
 * @brief Turn off all the channels of the PCA9685
 * @return ESP_OK if success, ESP_FAIL if error
 */
esp_err_t PCA9685TurnOffAll();

#endif /* _PCA9685_H_ */
 