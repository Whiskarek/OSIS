#include <Arduino.h>
#include "debug.hpp"
#include "temperature_sensor.hpp"

static constexpr char TAG[] = "MAIN";

temperature_sensor ts(D1);

void setup() {
    INIT(9600);
    ts.init();
}

void loop() {
    ts.update_data();
    LOG(TAG, ts.get_temperature_c());
    LOG(TAG, ts.get_temperature_f());
    LOG(TAG, "...");
}