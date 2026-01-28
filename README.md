# UWB Indoor Positioning Module

A starter repository for Ultra-Wideband (UWB) indoor positioning using ESP32 and DWM1000 module. This project provides firmware, drivers, and examples for implementing precise distance measurement and positioning systems.

## Features

- **ESP32 + DWM1000**: Hardware combination for UWB ranging
- **SPI Communication**: Custom SPI driver for DWM1000 interfacing
- **Distance Ranging**: Two-way ranging (TWR) implementation
- **Logging System**: Simple logging format for debugging and data collection
- **Modular Design**: Easy to extend and customize

## Hardware Requirements

### Components
- ESP32 development board (ESP32-DevKitC or similar)
- DWM1000 UWB module
- Jumper wires
- USB cable for programming

### Wiring Diagram

Connect the DWM1000 module to ESP32 as follows:

```
DWM1000          ESP32
---------        -------
VCC       -->    3.3V
GND       -->    GND
MOSI      -->    GPIO23 (MOSI)
MISO      -->    GPIO19 (MISO)
SCK       -->    GPIO18 (SCK)
CS        -->    GPIO5  (CS)
IRQ       -->    GPIO4  (Interrupt)
RST       -->    GPIO15 (Reset)
```

**Important Notes:**
- DWM1000 operates at 3.3V - do NOT use 5V
- Ensure proper grounding between ESP32 and DWM1000
- Keep wiring short to minimize interference
- Add 100nF decoupling capacitor near DWM1000 VCC pin (recommended)

## Directory Structure

```
uwb-indoor-positioning-module/
├── firmware/          # ESP32 firmware source code
│   ├── src/          # Source files
│   ├── include/      # Header files
│   └── platformio.ini # PlatformIO configuration
├── docs/             # Documentation and references
├── hardware/         # PCB designs and schematics
├── tests/            # Test cases and validation scripts
└── results/          # Test results and measurement data
```

## Setup Instructions

### Prerequisites

1. **Install PlatformIO**
   ```bash
   # Using pip
   pip install platformio
   
   # Or install VS Code with PlatformIO extension
   # https://platformio.org/install/ide?install=vscode
   ```

2. **Clone Repository**
   ```bash
   git clone https://github.com/KienTran-Mechatronics/uwb-indoor-positioning-module.git
   cd uwb-indoor-positioning-module/firmware
   ```

### Building the Firmware

```bash
cd firmware
pio run
```

### Flashing to ESP32

1. **Connect ESP32** to your computer via USB

2. **Identify the port:**
   ```bash
   # Linux/macOS
   ls /dev/tty.*
   
   # Windows
   # Check Device Manager for COM port
   ```

3. **Flash the firmware:**
   ```bash
   pio run --target upload
   
   # Or specify port manually
   pio run --target upload --upload-port /dev/ttyUSB0
   ```

4. **Monitor Serial Output:**
   ```bash
   pio device monitor
   # Or
   pio device monitor -b 115200
   ```

## Example: Basic Ranging Demo

The firmware includes a basic ranging example that demonstrates distance measurement between two UWB modules.

### Setup

1. **Flash two ESP32 boards** - one as Anchor (tag) and one as Tag (mobile)
2. **Power both devices**
3. **Open serial monitor** to view ranging results

### Expected Output

```
[INFO] DWM1000 Initialized
[INFO] Device ID: DECA0130
[INFO] Starting ranging...
[DATA] Range: 2.45m | Quality: 95% | Time: 1234ms
[DATA] Range: 2.47m | Quality: 94% | Time: 1240ms
[DATA] Range: 2.46m | Quality: 96% | Time: 1246ms
```

### Configuring Anchor vs Tag

In `firmware/src/main.cpp`, modify:

```cpp
// For Anchor (stationary)
#define DEVICE_MODE MODE_ANCHOR

// For Tag (mobile)
#define DEVICE_MODE MODE_TAG
```

## Logging Format

The firmware uses a simple structured logging format:

```
[LEVEL] Message | Key: Value | Key: Value | ...
```

**Log Levels:**
- `[ERROR]` - Critical errors
- `[WARN]` - Warnings
- `[INFO]` - General information
- `[DEBUG]` - Debug messages
- `[DATA]` - Measurement data

**Example:**
```
[INFO] System initialized | Version: 1.0.0
[DATA] Range: 3.25m | RSSI: -85dBm | Timestamp: 5432
[ERROR] SPI communication failed | Error: TIMEOUT
```

## Calibration

For accurate ranging, calibration is recommended:

1. **Antenna Delay Calibration**: Measure at known distances (1m, 2m, 5m)
2. **Power Configuration**: Adjust TX power based on environment
3. **Channel Selection**: Choose appropriate UWB channel (1-7)

See `docs/calibration.md` for detailed calibration procedures.

## API Reference

### Key Functions

```cpp
// Initialize DWM1000
bool dwm1000_init();

// Perform single ranging measurement
float dwm1000_get_range();

// Configure device mode
void dwm1000_set_mode(DeviceMode mode);

// Get device status
DeviceStatus dwm1000_get_status();
```

See `docs/api.md` for complete API documentation.

## Troubleshooting

### Common Issues

**1. DWM1000 not detected**
- Check wiring connections
- Verify 3.3V power supply
- Ensure SPI pins are correct

**2. No ranging data**
- Confirm both devices are powered
- Check device modes (one anchor, one tag)
- Verify antenna connections

**3. Inaccurate measurements**
- Perform antenna delay calibration
- Check for interference sources
- Ensure line-of-sight between modules

## Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Submit a pull request with clear description

## License

MIT License - see LICENSE file for details

## References

- [DWM1000 Datasheet](https://www.decawave.com/product/dwm1000-module/)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/)
- [UWB IEEE 802.15.4 Standard](https://standards.ieee.org/)

## Support

For issues and questions:
- Open an issue on GitHub
- Check existing documentation in `docs/`

---

**Project Status:** Starter Template - Ready for Development
