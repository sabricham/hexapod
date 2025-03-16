#include "i2cHandler.h"

//====================================================================================== 
//   Macros
//======================================================================================

#define TAG             "I2C Handler"

#define I2C_MASTER_SCL_IO           22          //< GPIO number used for I2C master clock
#define I2C_MASTER_SDA_IO           21          //< GPIO number used for I2C master data 
#define I2C_MASTER_NUM              I2C_NUM_0   //< I2C port number for master dev
#define I2C_MASTER_FREQ_HZ          100000      //< I2C master clock frequency
#define I2C_MASTER_TX_BUF           0           //< I2C master doesn't need buffer
#define I2C_MASTER_RX_BUF           0           //< I2C master doesn't need buffer
#define I2C_MASTER_TIMEOUT_MS       1000

//======================================================================================
//   Private variables & defines
//======================================================================================

//====================================================================================== 
//   Private functions & routines
//======================================================================================

//======================================================================================
//   Public variables & defines
//======================================================================================

//======================================================================================
//   Public functions & routines
//======================================================================================

esp_err_t I2CInit(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    esp_err_t err = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "I2C param config failed");
        return err;
    }
    err = i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF, I2C_MASTER_TX_BUF, 0);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "I2C driver install failed");
    }
    return err;
}

esp_err_t I2CWrite(uint8_t i2cAddress, uint8_t *writeBuffer, size_t sizeBuffer)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (i2cAddress << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write(cmd, writeBuffer, sizeBuffer, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t I2CRead(uint8_t i2cAddress, uint8_t *readBuffer, size_t sizeBuffer)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (i2cAddress << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, readBuffer, sizeBuffer, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);
    return ret;
}