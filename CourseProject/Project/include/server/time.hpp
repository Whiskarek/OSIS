#ifndef SERVER_TIME_HPP
#define SERVER_TIME_HPP

#include <NTPClient.h>
#include <WiFiUdp.h>

namespace server {
    class time {
        constexpr static uint32_t UTC_OFFSET_SECONDS = 3600 * 3;
    public:
        struct data {
            uint8_t hours;
            uint8_t minutes;
            uint8_t seconds;
            String time_str;
        };

        explicit time(const char* server);

        void start();

        void update();

        data get_time() const;

    private:
        WiFiUDP udp_;
        NTPClient client_;

        data time_;
    };
}

#endif // SERVER_TIME_HPP
