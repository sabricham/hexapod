/**
 * @file MotorController.c
 * @brief Motor controller to control the motors of the hexapod robot
 * @author Sabri Chamtouri
 */

//====================================================================================== 
//   Includes 
//======================================================================================

#include "MotorController.h"

//====================================================================================== 
//   Macros
//======================================================================================

#define TAG             "Motor Controller"

//====================================================================================== 
//   Private variables & defines
//======================================================================================

QueueHandle_t ledQueue = NULL;
queueMessage ledQueueMessage;

//====================================================================================== 
//   Private functions & routines
//======================================================================================

//====================================================================================== 
//   Public functions & routines
//======================================================================================
/**
 * @brief Motor controller task function.
 */
void MotorController(void *pvParameters)
{
    //======================================================================================
    ESP_LOGW(TAG, "Starting task");

    esp_task_wdt_add(NULL);
    CreateQueue(&ledQueue, &ledQueueMessage, 3, TAG);

    ESP_LOGW(TAG, "Task started correctly");
    //======================================================================================

    
    while(1)
    {
        // Get messages from other tasks
        if(xQueueReceive(ledQueue, &ledQueueMessage, 0))
        {
            ESP_LOGI(TAG, "Received message");
        }

        // Task loop


        esp_task_wdt_reset();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    
    ESP_LOGE(TAG, "This section should not be reached");
}
/*End of MotorController.c*/