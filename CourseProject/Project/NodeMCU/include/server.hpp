#ifndef NODEMCU_SERVER_HPP
#define NODEMCU_SERVER_HPP

#include <ESP8266WebServer.h>
#include "debug.hpp"

class BasicServer {
public:
    BasicServer(const char *ssid, const char *password, const std::size_t port)
            : ssid_(ssid),
              password_(password),
              port_(port),
              server_(port_) {
    }

    virtual ~BasicServer() = default;

    virtual bool init() = 0;

    void handle() {
        server_.handleClient();
    }

protected:
    const char *ssid_;
    const char *password_;
    const std::size_t port_;
    ESP8266WebServer server_;
};

class APServer : public BasicServer {
public:
    explicit APServer(const char *ssid, const std::size_t port = 80)
            : BasicServer(ssid, nullptr, port) {
    }

    bool init() override {
        LOG("AP_SERVER", String("Opening Access Point with SSID \"") + String(ssid_) + String("\" ..."));
        bool result = WiFi.softAP(ssid_);
        if (!result) {
            LOG("AP_SERVER", "Error while opening Access Point");
            return false;
        }
        IPAddress ap_ip = WiFi.softAPIP();
        LOG("AP_SERVER", String("Access Point opened. Server IP: ") + ap_ip.toString());
        init_paths();
        return true;
    }

private:
    void init_paths() {
        LOG("AP_SERVER", "Initializing server paths");

    }
};

#endif //NODEMCU_SERVER_HPP
