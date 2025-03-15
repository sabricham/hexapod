/**
 * @file MotorController.h
 * @brief Motor controller to control the motors of the hexapod robot
 * @author Sabri Chamtouri
 */

#ifndef _MOTOR_CONTROLLER_H_
#define _MOTOR_CONTROLLER_H_

//====================================================================================== 
//   Includes 
//======================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <esp_log.h>
#include <esp_task_wdt.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "gpioHandler.h"
#include "queueHandler.h"
#include "taskHandler.h"

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
 * @brief Motor controller task function.
 */
void MotorController(void *pvParameters);

#endif /* _MOTOR_CONTROLLER_H_ */
