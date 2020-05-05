#include "temperature_sensor.hpp"

constexpr char temperature_sensor::TAG[];

temperature_sensor::temperature_sensor(uint8_t wire_bus)
        : one_wire_(wire_bus),
          sensor_(&one_wire_),
          temperature_c_(0),
          temperature_f_(0) {
}

void temperature_sensor::init() {
    LOG(TAG, "Initializing temperature sensor");
    sensor_.begin();
    LOG(TAG, "Setting sensor resolution to 12 bits");
    sensor_.setResolution(12);
}

void temperature_sensor::update_data() {
    LOG(TAG, "Requesting temperature");
    sensor_.requestTemperatures();
    temperature_c_ = sensor_.getTempCByIndex(0);
    temperature_f_ = sensor_.getTempFByIndex(0);
    LOG(TAG, String("Temperature in C: ") + String(temperature_c_));
    LOG(TAG, String("Temperature in F: ") + String(temperature_f_));
}

double temperature_sensor::get_temperature_c() const {
    LOG(TAG, String("Returning temperature in C: ") + String(temperature_c_));
    return temperature_c_;
}

double temperature_sensor::get_temperature_f() const {
    LOG(TAG, String("Returning temperature in F: ") + String(temperature_f_));
    return temperature_f_;
}
