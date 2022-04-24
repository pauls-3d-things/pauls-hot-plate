#ifndef CONFIG_H
#define CONFIG_H

// hardware pins for TTGO "weather station"
#define BTN_LEFT 12
#define BTN_MID 14
#define BTN_RIGHT 13

#define PIN_SSR 16

#define SENSOR_PIN A0

// reflow timings, first value is how long it takes to reach, second how long should stay

#define CUSTOM_TEMP_START 180
#define WARMUP_TEMP 80
#define WARMUP_TIME 40
#define PREHEAT_TEMP 150
#define PREHEAT_TIME 40 + 60
#define SOAK_TEMP 180
#define SOAK_TIME 30 + 30
#define REFLOW_TEMP 240
#define REFLOW_TIME 60 + 60
#define COOLDOWN_TEMP 0
#define COOLDOWN_TIME 10

#endif
