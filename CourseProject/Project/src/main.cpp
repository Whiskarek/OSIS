#include <server/wifi.hpp>
#include <server/time.hpp>
#include <sensors/temperature.hpp>
#include <properties/wifi.hpp>
#include <properties/time.hpp>

sensors::temperature temp_sensor(D1);
server::wifi wifi_server(80);
server::time time_server(properties::time::time_server);

void connect_wifi(const char *ssid, const char *password) {
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup(void) {
    Serial.begin(115200);
    connect_wifi(properties::wifi::ssid, properties::wifi::password);
    temp_sensor.init();
    wifi_server.init();
    wifi_server.start();
    time_server.start();
}

void loop(void) {
    temp_sensor.update();
    time_server.update();
    wifi_server.add_data({temp_sensor.get_data().temp_str, time_server.get_time().time_str});
    wifi_server.handle();
    delay(1000);
}