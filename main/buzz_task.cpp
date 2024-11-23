#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "buzz_task.h"
#include <portmacro.h>

static const char *TAG = "buzz_task";

#define GPIO_OUTPUT_SPEED LEDC_HIGH_SPEED_MODE
const int BUZZER_PIN = 19;

#define BUZZ_DELAY_S 1

void buzz_task(void *parm) {
    while (true) {

        vTaskDelay((1000 / portTICK_PERIOD_MS) * BUZZ_DELAY_S);
    }
}
