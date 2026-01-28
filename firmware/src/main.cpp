/**
 * @file main.cpp
 * @brief UWB Indoor Positioning - Main Application
 * 
 * Example ranging demo for ESP32 + DWM1000
 */

#include <Arduino.h>
#include "dwm1000_driver.h"
#include "logger.h"

// Configuration
#define DEVICE_MODE MODE_TAG  // Change to MODE_ANCHOR for anchor device
#define RANGING_INTERVAL_MS 200  // Time between ranging measurements

// Global variables
unsigned long last_ranging_time = 0;

void setup() {
    // Initialize logger
    logger_init(115200);
    delay(500);
    
    LOG_INFO("=== UWB Indoor Positioning Module ===");
    log_kv1(LOG_INFO, "System starting", "Version", "1.0.0");
    log_kv1(LOG_INFO, "Device mode", "Mode", 
            DEVICE_MODE == MODE_ANCHOR ? "ANCHOR" : "TAG");
    
    // Initialize DWM1000
    LOG_INFO("Initializing DWM1000...");
    if (!dwm1000_init()) {
        LOG_ERROR("DWM1000 initialization failed!");
        log_kv1(LOG_ERROR, "Check wiring", "Status", "FAILED");
        while (1) {
            delay(1000);  // Halt on error
        }
    }
    
    // Read and display device ID
    uint32_t device_id = dwm1000_get_device_id();
    log_kv1(LOG_INFO, "DWM1000 initialized", "Device ID", 
            "0x" + String(device_id, HEX));
    
    // Configure device mode
    if (!dwm1000_set_mode(DEVICE_MODE)) {
        LOG_ERROR("Failed to set device mode!");
    }
    
    // Start ranging
    if (dwm1000_start_ranging()) {
        LOG_INFO("Starting ranging...");
        log_kv1(LOG_INFO, "Ranging started", "Interval", 
                String(RANGING_INTERVAL_MS) + "ms");
    } else {
        LOG_ERROR("Failed to start ranging!");
    }
    
    LOG_INFO("Setup complete. Ready for operation.");
}

void loop() {
    unsigned long current_time = millis();
    
    // Perform ranging at specified interval
    if (current_time - last_ranging_time >= RANGING_INTERVAL_MS) {
        last_ranging_time = current_time;
        
        RangingResult result;
        
        // Get ranging measurement
        if (dwm1000_get_range(&result)) {
            // Log ranging data with all metrics
            log_kv4(LOG_DATA, "Range",
                    "Distance", String(result.distance_m, 2) + "m",
                    "Quality", String(result.quality, 0) + "%",
                    "RSSI", String(result.rssi_dbm) + "dBm",
                    "Time", String(result.timestamp_ms) + "ms");
            
            // Check quality and warn if poor
            if (result.quality < 70.0f) {
                log_kv1(LOG_WARN, "Low signal quality", 
                        "Quality", String(result.quality, 1) + "%");
            }
        } else {
            LOG_ERROR("Ranging measurement failed!");
            log_kv1(LOG_ERROR, "Check devices", "Status", 
                    dwm1000_get_status() == STATUS_ERROR ? "ERROR" : "TIMEOUT");
        }
    }
    
    // Check for status changes
    static DeviceStatus last_status = STATUS_IDLE;
    DeviceStatus current_status = dwm1000_get_status();
    
    if (current_status != last_status) {
        const char* status_str = "UNKNOWN";
        switch (current_status) {
            case STATUS_IDLE: status_str = "IDLE"; break;
            case STATUS_TRANSMITTING: status_str = "TX"; break;
            case STATUS_RECEIVING: status_str = "RX"; break;
            case STATUS_ERROR: status_str = "ERROR"; break;
        }
        log_kv1(LOG_DEBUG, "Status change", "Status", status_str);
        last_status = current_status;
    }
    
    // Small delay to prevent tight loop
    delay(10);
}
