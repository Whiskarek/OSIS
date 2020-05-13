#ifndef SERVER_WIFI_HPP
#define SERVER_WIFI_HPP

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <util/queue.hpp>

namespace server {
    class wifi {
    public:
        struct data {
            String temperature;
            String time;
        };

        explicit wifi(int32_t port);

        void init();

        void start();

        void handle();

        void add_data(const data &data);

    private:

        void configure_pages();

        ESP8266WebServer server_;

        queue<data> data_;
    };
}

#endif // SERVER_WIFI_HPP
