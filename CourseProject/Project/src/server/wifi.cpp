#include "server/wifi.hpp"

#include <server/pages.hpp>

using namespace server;

wifi::wifi(int32_t port) : server_(port), data_(32) {
}

void wifi::init() {
    configure_pages();
}

void wifi::start() {
    server_.begin();
    Serial.println("Web server started!");
}

void wifi::handle() {
    server_.handleClient();
}

void wifi::add_data(const wifi::data &data) {
    if (data_.size() > 1) {
        if (data.temperature.equals(data_.back().temperature))
            return;
    }
    data_.push_back(data);
}

void wifi::configure_pages() {
    Serial.println("Configuring server pages:");

    // page: /all_data
    Serial.print("-- configuring \"");
    Serial.print(pages::all_data::name);
    Serial.println("\" page");
    server_.on(pages::all_data::name, [this]() {
        String temperature_data;
        String time_data;
        bool first = true;
        for (auto d = data_.begin(); d != data_.end(); d = d->next) {
            if (!first) {
                temperature_data += ", ";
                time_data += ", ";
            } else {
                first = false;
            }
            temperature_data += d->value.temperature;
            time_data += "\"" + d->value.time + "\"";
        }
        String data = "{\"time\":[" + time_data + "],\"temp\":[" + temperature_data + "]}";
        Serial.println(data);
        server_.send(pages::all_data::code,
                     pages::all_data::content_type,
                     data);
    });

    // page: /current_data
    Serial.print("-- configuring \"");
    Serial.print(pages::current_data::name);
    Serial.println("\" page");
    server_.on(pages::current_data::name, [this]() {
        auto &last = data_.back();
        String data = last.temperature + " " + last.time;
        Serial.println(data);
        server_.send(pages::current_data::code,
                     pages::current_data::content_type,
                     data);
    });

    // page: /
    Serial.print("-- configuring \"");
    Serial.print(pages::index::name);
    Serial.println("\" page");
    server_.on(pages::index::name, [this]() {
        server_.send(pages::index::code,
                     pages::index::content_type,
                     pages::index::page);
    });
}