# Quick Start Guide

Get your UWB Indoor Positioning Module up and running in 15 minutes!

## What You'll Need

- 2x ESP32 development boards
- 2x DWM1000 modules
- Jumper wires
- 2x USB cables
- Computer with PlatformIO installed

## Step 1: Hardware Setup (5 minutes)

### Wire First Module (Anchor)

Connect DWM1000 to ESP32:

| DWM1000 Pin | ESP32 Pin | Color (Optional) |
|-------------|-----------|------------------|
| VCC         | 3.3V      | Red              |
| GND         | GND       | Black            |
| MOSI        | GPIO23    | Blue             |
| MISO        | GPIO19    | Green            |
| SCK         | GPIO18    | Yellow           |
| CS          | GPIO5     | Orange           |
| IRQ         | GPIO4     | Purple           |
| RST         | GPIO15    | White            |

### Wire Second Module (Tag)

Repeat the same wiring for the second module.

**⚠️ Important:**
- Double-check VCC is connected to 3.3V, NOT 5V!
- Ensure both modules share common ground if powered separately
- Keep wires short and neat

## Step 2: Software Setup (5 minutes)

### Install PlatformIO

If not already installed:

```bash
# Using pip
pip install platformio

# Or install VS Code extension
# https://platformio.org/install/ide?install=vscode
```

### Clone Repository

```bash
git clone https://github.com/KienTran-Mechatronics/uwb-indoor-positioning-module.git
cd uwb-indoor-positioning-module/firmware
```

### Configure Devices

Edit `firmware/src/main.cpp`:

**For first device (Anchor):**
```cpp
#define DEVICE_MODE MODE_ANCHOR
```

**For second device (Tag):**
```cpp
#define DEVICE_MODE MODE_TAG
```

## Step 3: Flash Firmware (3 minutes)

### Flash Anchor Device

```bash
# Connect first ESP32
cd firmware

# Build and flash
pio run --target upload --upload-port /dev/ttyUSB0

# Or auto-detect port
pio run --target upload
```

### Flash Tag Device

```cpp
// Edit main.cpp - change to MODE_TAG
#define DEVICE_MODE MODE_TAG
```

```bash
# Connect second ESP32
pio run --target upload --upload-port /dev/ttyUSB1
```

## Step 4: Test Ranging (2 minutes)

### Start Monitoring

Open two terminal windows:

**Terminal 1 (Anchor):**
```bash
pio device monitor --port /dev/ttyUSB0 -b 115200
```

**Terminal 2 (Tag):**
```bash
pio device monitor --port /dev/ttyUSB1 -b 115200
```

### Expected Output

You should see output like:

```
[INFO] === UWB Indoor Positioning Module ===
[INFO] System starting | Version: 1.0.0
[INFO] Device mode | Mode: TAG
[INFO] Initializing DWM1000...
[INFO] DWM1000 initialized | Device ID: 0xdeca0130
[INFO] Starting ranging...
[DATA] Range | Distance: 2.45m | Quality: 95% | RSSI: -85dBm | Time: 1234ms
[DATA] Range | Distance: 2.47m | Quality: 94% | RSSI: -84dBm | Time: 1440ms
[DATA] Range | Distance: 2.46m | Quality: 96% | RSSI: -83dBm | Time: 1646ms
```

## Step 5: Test at Different Distances

Move the Tag device to different distances from the Anchor:
- 1 meter
- 2 meters
- 5 meters

Watch the distance values update in real-time!

## Troubleshooting

### "DWM1000 initialization failed!"

**Check:**
- [ ] All wiring connections are correct
- [ ] VCC is 3.3V (not 5V!)
- [ ] Both devices are powered on
- [ ] SPI pins match configuration

### "No ranging data"

**Check:**
- [ ] One device is ANCHOR, other is TAG
- [ ] Both devices are running latest firmware
- [ ] Devices are within 10m of each other
- [ ] No large metal objects blocking signal

### "Inaccurate measurements"

This is normal! The code uses simulated data for demonstration.

**For real ranging:**
- Implement complete DWM1000 driver (see TODOs in code)
- Perform antenna delay calibration (see `docs/calibration.md`)
- Adjust TX power for your environment

### Serial port not found

**Linux:**
```bash
# List available ports
ls /dev/tty*

# Add user to dialout group (may need to log out/in)
sudo usermod -a -G dialout $USER
```

**Windows:**
- Check Device Manager for COM port number
- Install CH340 or CP2102 drivers if needed

**macOS:**
```bash
# List available ports
ls /dev/cu.*
```

## Next Steps

### 1. Calibration
Follow the calibration guide to improve accuracy:
```bash
less docs/calibration.md
```

### 2. Implement Full Driver
The current code has placeholder implementations. To get real ranging:
- Complete TWR (Two-Way Ranging) implementation
- Add proper DWM1000 register configuration
- Implement interrupt handling

See DWM1000 datasheet and application notes.

### 3. Add More Anchors
For positioning (not just ranging), deploy 3+ anchors at known positions.

### 4. Explore API
Check out the API documentation:
```bash
less docs/api.md
```

## Advanced Configuration

### Change Update Rate

In `main.cpp`:
```cpp
#define RANGING_INTERVAL_MS 100  // Update every 100ms (10 Hz)
```

### Adjust Log Level

```cpp
void setup() {
    logger_init(115200);
    logger_set_level(LOG_DEBUG);  // Show all messages
}
```

### Configure TX Power

```cpp
void setup() {
    dwm1000_init();
    dwm1000_set_tx_power(25);  // Increase power for longer range
}
```

## Getting Help

- **Documentation**: Check `docs/` directory
- **Issues**: Open issue on GitHub
- **Datasheet**: [DWM1000 Datasheet](https://www.decawave.com)

## Success! 🎉

You now have a working UWB ranging system! The measured distances are currently simulated, but you have a complete framework to build upon.

Next, implement the full DWM1000 driver for real measurements, or start exploring positioning algorithms with multiple anchors.

Happy ranging! 📡
