#include "server/time.hpp"

using namespace server;

time::time(const char *server)
        : udp_{},
          client_(udp_, server, UTC_OFFSET_SECONDS),
          time_{} {
}

void time::start() {
    client_.begin();
    Serial.println("Time server started!");
}

void time::update() {
    client_.update();
    time_.hours = client_.getHours();
    time_.minutes = client_.getMinutes();
    time_.seconds = client_.getSeconds();
    String h = String(time_.hours);
    if (h.length() < 2)
        h = "0" + h;
    String m = String(time_.minutes);
    if (m.length() < 2)
        m = "0" + m;
    String s = String(time_.seconds);
    if (s.length() < 2)
        s = "0" + s;
    time_.time_str = h + ":" + m + ":" + s;

}

time::data time::get_time() const {
    return time_;
}