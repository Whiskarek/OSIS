#ifndef NODEMCU_DEBUG_HPP
#define NODEMCU_DEBUG_HPP

#include "settings.hpp"

#ifdef DEBUG

#define INIT(x) Serial.begin(x)
#define LOG(tag, text) { \
    auto tmp_tag = (tag); \
    auto tmp_text = (text); \
    Serial.print('['); \
    Serial.print(tmp_tag); \
    Serial.print("] "); \
    Serial.println(tmp_text); \
}

#else

#define INIT(x)
#define LOG(tag, text)

#endif

#endif //NODEMCU_DEBUG_HPP
