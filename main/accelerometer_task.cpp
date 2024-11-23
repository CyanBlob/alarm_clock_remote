#include "accelerometer_task.h"

#include <cstdio>
#include <cstdlib>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"

// from: https://components.espressif.com/components/espressif/mpu6050/versions/1.2.0?language=en
#include "mpu6050.h"

#define I2C_MASTER_SCL_IO    22 // SCL pin
#define I2C_MASTER_SDA_IO    21 // SDA pin
#define I2C_MASTER_FREQ_HZ   400000
#define I2C_MASTER_NUM       I2C_NUM_0
#define ESP_INTR_FLAG_DEFAULT 0

#define BSP_I2C_NUM 0

static const char *TAG = "accelerometer_task";

static mpu6050_handle_t mpu6050_dev = nullptr;

static mpu6050_acce_value_t acce;
static mpu6050_gyro_value_t gyro;
static complimentary_angle_t complimentary_angle;

static void mpu6050_init()
{
    mpu6050_dev = mpu6050_create(BSP_I2C_NUM, MPU6050_I2C_ADDRESS);
    mpu6050_config(mpu6050_dev, ACCE_FS_4G, GYRO_FS_500DPS);
    mpu6050_wake_up(mpu6050_dev);
}

static void mpu6050_read()
{
    mpu6050_get_acce(mpu6050_dev, &acce);
    mpu6050_get_gyro(mpu6050_dev, &gyro);
    mpu6050_complimentory_filter(mpu6050_dev, &acce, &gyro, &complimentary_angle);
}

static void display_show_acce_data()
{
    ESP_LOGI(TAG, "acce_x:%.2f, acce_y:%.2f, acce_z:%.2f", acce.acce_x, acce.acce_y, acce.acce_z);
}

static void display_show_gyro_data(void)
{
    ESP_LOGI(TAG, "gyro_x:%.2f, gyro_y:%.2f, gyro_z:%.2f", gyro.gyro_x, gyro.gyro_y, gyro.gyro_z);
}

static void display_show_data(void)
{
    ESP_LOGI(TAG, "acce_x:%.2f, acce_y:%.2f, acce_z:%.2f, gyro_x:%.2f, gyro_y:%.2f, gyro_z:%.2f", acce.acce_x, acce.acce_y, acce.acce_z, gyro.gyro_x, gyro.gyro_y, gyro.gyro_z);
}

void accelerometer_task(void *param) {

    i2c_config_t conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = I2C_MASTER_SDA_IO,
            .scl_io_num = I2C_MASTER_SCL_IO,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE
    };

    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;

    auto ret = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (ret != ESP_OK) {
        ESP_LOGE("I2C", "I2C param config failed");
        return;
    }
    ret = i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, ESP_INTR_FLAG_DEFAULT);
    if (ret != ESP_OK) {
        ESP_LOGE("I2C", "I2C driver install failed");
        return;
    }

    mpu6050_init();

    while (true) {
        mpu6050_read();
        display_show_data();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
