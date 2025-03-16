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

#define PCA9685_ADDRESS     0x40

//====================================================================================== 
//   Private variables & defines
//======================================================================================

QueueHandle_t motorQueue = NULL;
queueMessage motorQueueMessage;

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
    CreateQueue(&motorQueue, &motorQueueMessage, 3, TAG);

    I2CInit();
    
    //Example of PCA9685 usage
    PCA9685Init();
    PCA9685SetFrequency(48);    // Sets to actual 50Hz   
    PCA9685SetAllDutyCycle(10);
    PCA9685SetDutyCycle(LED7, 30);

    ESP_LOGW(TAG, "Task started correctly");
    //======================================================================================
    
    while(1)
    {
        // Get messages from other tasks
        if(xQueueReceive(motorQueue, &motorQueueMessage, 0))
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