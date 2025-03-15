/**
 * @file main.c
 * @brief Main application file for Hexapod project 
 * @author Sabri Chamtouri
 */

/*--------------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------------*/

#include <stdio.h>

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "MotorController.h"

#include "gpioHandler.h"
#include "queueHandler.h"
#include "taskHandler.h"

/*--------------------------------------------------------------------------------*/
// Macros and Defines
/*--------------------------------------------------------------------------------*/

#define TAG         "Main"
QueueHandle_t mainQueue = NULL;
queueMessage mainQueueMessage;
int mainMessagesParams[MESSAGE_PARAMS_LENGTH];

/*--------------------------------------------------------------------------------*/
// Private variables
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Private Functions
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Public Functions
/*--------------------------------------------------------------------------------*/
/**
 * @brief Main application entry point.
 */
void app_main(void)
{
    // Create the MotorController task

    
    ESP_LOGW(TAG, "System startup procedure");
    ESP_LOGW(TAG, "-------------------------------------------");
    ESP_LOGW(TAG, "             Hexapod Robot                 ");
    ESP_LOGW(TAG, "                 v1.0                      ");
    ESP_LOGW(TAG, "               Prototype                   ");
    ESP_LOGW(TAG, "-------------------------------------------");

    ESP_LOGW(TAG, "Starting system tasks");
    StartTask(MotorController, "MotorController", configMINIMAL_STACK_SIZE * 2, tskIDLE_PRIORITY + 2);
    ESP_LOGW(TAG, "System tasks started successfully");
    
    ESP_LOGW(TAG, "Starting task");
    CreateQueue(&mainQueue, &mainQueueMessage, 10, TAG);
    ESP_LOGW(TAG, "Task started correctly");

    while(1)
    {
        // Get messages from other tasks
        if(xQueueReceive(mainQueue, &mainQueueMessage, 0))
        {
            ESP_LOGI(TAG, "Received message");
        }

        // Task logic
        vTaskDelay(1);
    }

    ESP_LOGE(TAG, "This section should not be reached");
    return;
}
/*End of main.c*/