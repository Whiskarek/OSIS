#ifndef NODEMCU_TEMPERATURE_SENSOR_HPP
#define NODEMCU_TEMPERATURE_SENSOR_HPP

#include <OneWire.h>
#include <DallasTemperature.h>

#define DEBUG

#include "debug.hpp"

class temperature_sensor {
public:
    explicit temperature_sensor(uint8_t wire_bus);

    void init();

    void update_data();

    double get_temperature_c() const;

    double get_temperature_f() const;

private:
    static constexpr char TAG[] = "TEMP_SENSOR";

    OneWire one_wire_;
    DallasTemperature sensor_;
    double temperature_c_;
    double temperature_f_;
};

#endif //NODEMCU_TEMPERATURE_SENSOR_HPP
