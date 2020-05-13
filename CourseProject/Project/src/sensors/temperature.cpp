#include "sensors/temperature.hpp"

using namespace sensors;

temperature::temperature(uint8_t pin)
        : one_wire_(pin),
          sensor_(&one_wire_) {
}

void temperature::init() {
    sensor_.setResolution(RESOLUTION_MAX);
    do {
        update();
    } while (temp_ == 85.0 || temp_ == -127.0);
}

void temperature::update() {
    sensor_.requestTemperatures();
    temp_ = sensor_.getTempCByIndex(0);
}

temperature::data temperature::get_data() const {
    return {temp_, String(temp_, 4)};
}