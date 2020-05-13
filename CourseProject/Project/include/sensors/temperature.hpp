#ifndef SENSORS_HPP
#define SENSORS_HPP

#include <OneWire.h>
#include <DallasTemperature.h>

namespace sensors {
    class temperature {
        constexpr static uint8_t RESOLUTION_MAX = 12;
    public:
        struct data {
            double temp;
            String temp_str;
        };

        explicit temperature(uint8_t pin);

        void init();

        void update();

        data get_data() const;

    private:
        OneWire one_wire_;
        DallasTemperature sensor_;

        double temp_;
    };
}

#endif // SENSORS_HPP
