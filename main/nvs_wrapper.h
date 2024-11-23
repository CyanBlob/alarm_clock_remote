//
// Created by andre on 9/1/2024.
//

#ifndef ALARM_CLOCK_NVS_WRAPPER_H
#define ALARM_CLOCK_NVS_WRAPPER_H

void nvs_init();

void nvs_set(char* key, char* value);
void nvs_get(char* key, char* value, size_t* len);

bool nvs_begin(nvs_open_mode_t mode);
void nvs_end();

#endif //ALARM_CLOCK_NVS_WRAPPER_H
