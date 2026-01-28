/**
 * @file dwm1000_driver.h
 * @brief DWM1000 UWB Module Driver
 * 
 * Driver for DecaWave DWM1000 Ultra-Wideband transceiver
 * Provides ranging and positioning functionality
 */

#ifndef DWM1000_DRIVER_H
#define DWM1000_DRIVER_H

#include <Arduino.h>

// DWM1000 Pin Definitions
#define DWM1000_IRQ_PIN     4
#define DWM1000_RST_PIN     15

// DWM1000 Register Addresses (subset)
#define REG_DEV_ID          0x00  // Device ID register
#define REG_SYS_CFG         0x04  // System configuration
#define REG_TX_FCTRL        0x08  // TX frame control
#define REG_RX_FINFO        0x10  // RX frame info
#define REG_TX_TIME         0x17  // TX timestamp
#define REG_RX_TIME         0x15  // RX timestamp

// Device Modes
enum DeviceMode {
    MODE_ANCHOR = 0,  // Stationary reference node
    MODE_TAG = 1      // Mobile node
};

// Device Status
enum DeviceStatus {
    STATUS_IDLE = 0,
    STATUS_TRANSMITTING,
    STATUS_RECEIVING,
    STATUS_ERROR
};

// Ranging Result
struct RangingResult {
    float distance_m;      // Distance in meters
    float quality;         // Signal quality (0-100%)
    uint32_t timestamp_ms; // Measurement timestamp
    int16_t rssi_dbm;      // Received Signal Strength Indicator
};

/**
 * @brief Initialize DWM1000 module
 * @return true if initialization successful, false otherwise
 */
bool dwm1000_init();

/**
 * @brief Reset DWM1000 module
 */
void dwm1000_reset();

/**
 * @brief Read device ID
 * @return 32-bit device ID (should be 0xDECA0130)
 */
uint32_t dwm1000_get_device_id();

/**
 * @brief Configure device mode (Anchor or Tag)
 * @param mode Device mode to set
 * @return true if successful, false otherwise
 */
bool dwm1000_set_mode(DeviceMode mode);

/**
 * @brief Get current device status
 * @return Current device status
 */
DeviceStatus dwm1000_get_status();

/**
 * @brief Perform single ranging measurement
 * @param result Pointer to store ranging result
 * @return true if ranging successful, false otherwise
 */
bool dwm1000_get_range(RangingResult* result);

/**
 * @brief Start continuous ranging mode
 * @return true if successful, false otherwise
 */
bool dwm1000_start_ranging();

/**
 * @brief Stop ranging mode
 */
void dwm1000_stop_ranging();

/**
 * @brief Configure antenna delay (for calibration)
 * @param delay_value Antenna delay value
 */
void dwm1000_set_antenna_delay(uint16_t delay_value);

/**
 * @brief Configure TX power
 * @param power_level Power level (0-31)
 */
void dwm1000_set_tx_power(uint8_t power_level);

/**
 * @brief Check if new ranging data is available
 * @return true if data available, false otherwise
 */
bool dwm1000_data_available();

#endif // DWM1000_DRIVER_H
