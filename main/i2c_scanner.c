/* i2c - Scanner
*/
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "freertos/task.h"

static const char *TAG = "i2c scanner";

#define I2C_MASTER_SCL_IO           22
#define I2C_MASTER_SDA_IO           21
#define I2C_MASTER_NUM              0       /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000  /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0       /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0       /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       100

static esp_err_t check_adress_for_device(uint8_t device_address)
{
    uint8_t write_buf[2] = {0, 0};

    return i2c_master_write_to_device(I2C_MASTER_NUM, device_address, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}

// i2c master initialization
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode               = I2C_MODE_MASTER,
        .sda_io_num         = I2C_MASTER_SDA_IO,
        .scl_io_num         = I2C_MASTER_SCL_IO,
        .sda_pullup_en      = GPIO_PULLUP_ENABLE,
        .scl_pullup_en      = GPIO_PULLUP_ENABLE,
        .master.clk_speed   = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}


void app_main(void)
{
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    while (true) {
        size_t devicesDiscovered = 0;
        for (size_t address = 1; address < 127; address++) {
            if (ESP_OK == check_adress_for_device(address)) {
                ESP_LOGI(TAG, "Found device at address 0x%X", address);
                devicesDiscovered++;
            }
        }
        if (devicesDiscovered == 1){
            ESP_LOGI(TAG, "Found %d device\n", (int)devicesDiscovered);
        } else if (devicesDiscovered > 1) {
            ESP_LOGI(TAG, "Found %d devices\n", (int)devicesDiscovered);   
        } else {
            ESP_LOGI(TAG, "No devices found\n");
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
