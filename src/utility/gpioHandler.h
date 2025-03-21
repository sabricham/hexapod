#ifndef _GPIO_H_
#define _GPIO_H_

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
#include "driver/gpio.h"
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

void GPIOCreate(uint8_t pin, gpio_int_type_t intrType, gpio_mode_t mode);
void GPIOInstallISR();
void GPIOAddISR(uint8_t pin, gpio_isr_t isrRoutine, void *args);

#endif /* _GPIO_H_ */