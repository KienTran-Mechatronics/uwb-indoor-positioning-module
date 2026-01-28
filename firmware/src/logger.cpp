/**
 * @file logger.cpp
 * @brief Logger implementation
 */

#include "logger.h"

LogLevel g_log_level = LOG_INFO;

// Level name strings
static const char* level_names[] = {
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
    "DATA"
};

void logger_init(uint32_t baud_rate) {
    Serial.begin(baud_rate);
    while (!Serial && millis() < 3000) {
        // Wait for serial with timeout
    }
    delay(100);
}

void logger_set_level(LogLevel level) {
    g_log_level = level;
}

void log_message(LogLevel level, const char* message) {
    if (level > g_log_level) {
        return;
    }
    
    Serial.print("[");
    Serial.print(level_names[level]);
    Serial.print("] ");
    Serial.println(message);
}

void log_kv1(LogLevel level, const char* message, 
             const char* key1, const String& value1) {
    if (level > g_log_level) {
        return;
    }
    
    Serial.print("[");
    Serial.print(level_names[level]);
    Serial.print("] ");
    Serial.print(message);
    Serial.print(" | ");
    Serial.print(key1);
    Serial.print(": ");
    Serial.println(value1);
}

void log_kv2(LogLevel level, const char* message,
             const char* key1, const String& value1,
             const char* key2, const String& value2) {
    if (level > g_log_level) {
        return;
    }
    
    Serial.print("[");
    Serial.print(level_names[level]);
    Serial.print("] ");
    Serial.print(message);
    Serial.print(" | ");
    Serial.print(key1);
    Serial.print(": ");
    Serial.print(value1);
    Serial.print(" | ");
    Serial.print(key2);
    Serial.print(": ");
    Serial.println(value2);
}

void log_kv3(LogLevel level, const char* message,
             const char* key1, const String& value1,
             const char* key2, const String& value2,
             const char* key3, const String& value3) {
    if (level > g_log_level) {
        return;
    }
    
    Serial.print("[");
    Serial.print(level_names[level]);
    Serial.print("] ");
    Serial.print(message);
    Serial.print(" | ");
    Serial.print(key1);
    Serial.print(": ");
    Serial.print(value1);
    Serial.print(" | ");
    Serial.print(key2);
    Serial.print(": ");
    Serial.print(value2);
    Serial.print(" | ");
    Serial.print(key3);
    Serial.print(": ");
    Serial.println(value3);
}

void log_kv4(LogLevel level, const char* message,
             const char* key1, const String& value1,
             const char* key2, const String& value2,
             const char* key3, const String& value3,
             const char* key4, const String& value4) {
    if (level > g_log_level) {
        return;
    }
    
    Serial.print("[");
    Serial.print(level_names[level]);
    Serial.print("] ");
    Serial.print(message);
    Serial.print(" | ");
    Serial.print(key1);
    Serial.print(": ");
    Serial.print(value1);
    Serial.print(" | ");
    Serial.print(key2);
    Serial.print(": ");
    Serial.print(value2);
    Serial.print(" | ");
    Serial.print(key3);
    Serial.print(": ");
    Serial.print(value3);
    Serial.print(" | ");
    Serial.print(key4);
    Serial.print(": ");
    Serial.println(value4);
}
