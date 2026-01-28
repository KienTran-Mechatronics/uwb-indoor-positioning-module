# API Reference

## DWM1000 Driver API

### Initialization

#### `bool dwm1000_init()`
Initialize the DWM1000 module and configure SPI communication.

**Returns:** `true` if initialization successful, `false` otherwise

**Example:**
```cpp
if (!dwm1000_init()) {
    Serial.println("DWM1000 initialization failed!");
}
```

---

#### `void dwm1000_reset()`
Perform a hardware reset of the DWM1000 module.

**Example:**
```cpp
dwm1000_reset();
delay(10);  // Wait for module to restart
```

---

#### `uint32_t dwm1000_get_device_id()`
Read the device ID from DWM1000.

**Returns:** 32-bit device ID (expected: 0xDECA0130)

**Example:**
```cpp
uint32_t id = dwm1000_get_device_id();
if (id == 0xDECA0130) {
    Serial.println("DWM1000 detected!");
}
```

---

### Configuration

#### `bool dwm1000_set_mode(DeviceMode mode)`
Configure the device as either anchor or tag.

**Parameters:**
- `mode`: `MODE_ANCHOR` or `MODE_TAG`

**Returns:** `true` if successful

**Example:**
```cpp
dwm1000_set_mode(MODE_ANCHOR);  // Set as anchor
// or
dwm1000_set_mode(MODE_TAG);     // Set as tag
```

---

#### `void dwm1000_set_antenna_delay(uint16_t delay_value)`
Set antenna delay for calibration (improves accuracy).

**Parameters:**
- `delay_value`: Antenna delay in DW1000 time units

**Example:**
```cpp
dwm1000_set_antenna_delay(16450);  // Typical value
```

---

#### `void dwm1000_set_tx_power(uint8_t power_level)`
Configure transmit power.

**Parameters:**
- `power_level`: Power level 0-31 (higher = more power)

**Example:**
```cpp
dwm1000_set_tx_power(20);  // Medium power
```

---

### Ranging Operations

#### `bool dwm1000_get_range(RangingResult* result)`
Perform a single ranging measurement.

**Parameters:**
- `result`: Pointer to `RangingResult` structure to store results

**Returns:** `true` if ranging successful

**Example:**
```cpp
RangingResult result;
if (dwm1000_get_range(&result)) {
    Serial.print("Distance: ");
    Serial.print(result.distance_m);
    Serial.println(" m");
}
```

---

#### `bool dwm1000_start_ranging()`
Start continuous ranging mode.

**Returns:** `true` if successful

**Example:**
```cpp
if (dwm1000_start_ranging()) {
    Serial.println("Ranging started");
}
```

---

#### `void dwm1000_stop_ranging()`
Stop continuous ranging.

**Example:**
```cpp
dwm1000_stop_ranging();
```

---

### Status

#### `DeviceStatus dwm1000_get_status()`
Get current device status.

**Returns:** One of:
- `STATUS_IDLE`
- `STATUS_TRANSMITTING`
- `STATUS_RECEIVING`
- `STATUS_ERROR`

**Example:**
```cpp
DeviceStatus status = dwm1000_get_status();
if (status == STATUS_ERROR) {
    Serial.println("Device error!");
}
```

---

#### `bool dwm1000_data_available()`
Check if new ranging data is available.

**Returns:** `true` if data ready to read

**Example:**
```cpp
if (dwm1000_data_available()) {
    dwm1000_get_range(&result);
}
```

---

## Logger API

### Initialization

#### `void logger_init(uint32_t baud_rate = 115200)`
Initialize the logging system.

**Parameters:**
- `baud_rate`: Serial baud rate (default: 115200)

**Example:**
```cpp
logger_init(115200);
```

---

#### `void logger_set_level(LogLevel level)`
Set minimum log level to display.

**Parameters:**
- `level`: `LOG_ERROR`, `LOG_WARN`, `LOG_INFO`, `LOG_DEBUG`, or `LOG_DATA`

**Example:**
```cpp
logger_set_level(LOG_DEBUG);  // Show all messages
```

---

### Logging Functions

#### `void log_message(LogLevel level, const char* message)`
Log a simple message.

**Example:**
```cpp
log_message(LOG_INFO, "System initialized");
```

---

#### `void log_kv1(LogLevel level, const char* message, const char* key1, const String& value1)`
Log message with one key-value pair.

**Example:**
```cpp
log_kv1(LOG_INFO, "Temperature", "Value", String(temp) + "C");
// Output: [INFO] Temperature | Value: 25.3C
```

---

#### `void log_kv2/log_kv3/log_kv4(...)`
Log message with 2, 3, or 4 key-value pairs.

**Example:**
```cpp
log_kv3(LOG_DATA, "Measurement",
        "Distance", "2.5m",
        "Quality", "95%",
        "RSSI", "-82dBm");
// Output: [DATA] Measurement | Distance: 2.5m | Quality: 95% | RSSI: -82dBm
```

---

### Convenience Macros

```cpp
LOG_ERROR("Critical error occurred");
LOG_WARN("Low battery warning");
LOG_INFO("System ready");
LOG_DEBUG("Variable x = 42");
LOG_DATA("Sensor reading");
```

---

## Data Structures

### RangingResult
```cpp
struct RangingResult {
    float distance_m;      // Distance in meters
    float quality;         // Signal quality 0-100%
    uint32_t timestamp_ms; // Measurement timestamp
    int16_t rssi_dbm;      // RSSI in dBm
};
```

### DeviceMode
```cpp
enum DeviceMode {
    MODE_ANCHOR = 0,  // Stationary reference
    MODE_TAG = 1      // Mobile node
};
```

### DeviceStatus
```cpp
enum DeviceStatus {
    STATUS_IDLE = 0,
    STATUS_TRANSMITTING,
    STATUS_RECEIVING,
    STATUS_ERROR
};
```

---

## Complete Example

```cpp
#include <Arduino.h>
#include "dwm1000_driver.h"
#include "logger.h"

void setup() {
    // Initialize logger
    logger_init(115200);
    LOG_INFO("Starting UWB module");
    
    // Initialize DWM1000
    if (!dwm1000_init()) {
        LOG_ERROR("Init failed!");
        while(1);
    }
    
    // Configure as tag
    dwm1000_set_mode(MODE_TAG);
    
    // Start ranging
    dwm1000_start_ranging();
    LOG_INFO("Ready for ranging");
}

void loop() {
    RangingResult result;
    
    if (dwm1000_get_range(&result)) {
        log_kv2(LOG_DATA, "Range",
                "Distance", String(result.distance_m, 2) + "m",
                "Quality", String(result.quality, 0) + "%");
    }
    
    delay(200);
}
```
