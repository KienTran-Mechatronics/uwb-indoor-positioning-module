/**
 * @file logger.h
 * @brief Simple logging system for UWB module
 * 
 * Provides structured logging with levels and key-value pairs
 * Format: [LEVEL] Message | Key: Value | Key: Value
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

// Log levels
enum LogLevel {
    LOG_ERROR = 0,  // Critical errors
    LOG_WARN = 1,   // Warnings
    LOG_INFO = 2,   // General information
    LOG_DEBUG = 3,  // Debug messages
    LOG_DATA = 4    // Measurement data
};

// Global log level (messages below this level won't be printed)
extern LogLevel g_log_level;

/**
 * @brief Initialize logger
 * @param baud_rate Serial baud rate (default: 115200)
 */
void logger_init(uint32_t baud_rate = 115200);

/**
 * @brief Set global log level
 * @param level Minimum level to log
 */
void logger_set_level(LogLevel level);

/**
 * @brief Log a message with level
 * @param level Log level
 * @param message Message string
 */
void log_message(LogLevel level, const char* message);

/**
 * @brief Log message with one key-value pair
 */
void log_kv1(LogLevel level, const char* message, 
             const char* key1, const String& value1);

/**
 * @brief Log message with two key-value pairs
 */
void log_kv2(LogLevel level, const char* message,
             const char* key1, const String& value1,
             const char* key2, const String& value2);

/**
 * @brief Log message with three key-value pairs
 */
void log_kv3(LogLevel level, const char* message,
             const char* key1, const String& value1,
             const char* key2, const String& value2,
             const char* key3, const String& value3);

/**
 * @brief Log message with four key-value pairs
 */
void log_kv4(LogLevel level, const char* message,
             const char* key1, const String& value1,
             const char* key2, const String& value2,
             const char* key3, const String& value3,
             const char* key4, const String& value4);

// Convenience macros
#define LOG_ERROR(msg) log_message(LOG_ERROR, msg)
#define LOG_WARN(msg) log_message(LOG_WARN, msg)
#define LOG_INFO(msg) log_message(LOG_INFO, msg)
#define LOG_DEBUG(msg) log_message(LOG_DEBUG, msg)
#define LOG_DATA(msg) log_message(LOG_DATA, msg)

#endif // LOGGER_H
