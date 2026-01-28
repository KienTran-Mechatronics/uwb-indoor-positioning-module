# Calibration Guide

Proper calibration is essential for accurate ranging measurements with the DWM1000 module.

## Overview

The main calibration parameters are:
1. **Antenna Delay** - Compensates for signal propagation delays in antenna and PCB traces
2. **TX Power** - Optimizes signal strength for your environment
3. **Channel Selection** - Chooses best frequency channel

## Antenna Delay Calibration

### Why Calibrate?
The antenna delay accounts for the time it takes for the signal to travel through:
- PCB traces
- Antenna matching circuit
- Antenna itself

Without calibration, ranging errors of 1-2 meters are common.

### Calibration Procedure

#### Equipment Needed
- 2x ESP32 + DWM1000 modules
- Measuring tape or laser distance meter
- Stable mounting surface

#### Steps

1. **Setup Reference Distances**
   - Place modules at known distances: 1m, 2m, 5m, 10m
   - Ensure line-of-sight, no obstacles
   - Use precise measurement tool

2. **Initial Test**
   ```cpp
   // In main.cpp, set initial antenna delay
   dwm1000_set_antenna_delay(16384);  // Default value
   ```

3. **Collect Measurements**
   - At each reference distance, record 50-100 measurements
   - Calculate average measured distance
   - Note the error: `error = measured - actual`

4. **Calculate Correction**
   - If measured > actual: increase antenna delay
   - If measured < actual: decrease antenna delay
   - Formula: `new_delay = old_delay + (error_meters * 15650)`
   
   Example:
   ```
   Actual: 5.00m
   Measured: 5.15m
   Error: +0.15m
   
   New delay = 16384 + (0.15 * 15650) = 18732
   ```

5. **Iterate**
   - Apply new antenna delay value
   - Re-measure at all reference distances
   - Repeat until error < 5cm

6. **Update Firmware**
   ```cpp
   // In dwm1000_driver.cpp or main.cpp
   #define ANTENNA_DELAY_CALIBRATED 18732
   dwm1000_set_antenna_delay(ANTENNA_DELAY_CALIBRATED);
   ```

### Typical Values
- Standard DWM1000 eval board: 16300-16500
- Custom PCB with chip antenna: 16000-17000
- Custom PCB with external antenna: 16500-17500

## TX Power Configuration

### Purpose
Optimize signal strength for:
- Maximum range
- Minimum interference
- Power consumption

### Power Levels
```cpp
// Low power (short range, less interference)
dwm1000_set_tx_power(10);

// Medium power (balanced)
dwm1000_set_tx_power(20);

// High power (maximum range)
dwm1000_set_tx_power(31);
```

### Guidelines
- **Indoor office**: 15-20 (10-15m range)
- **Large warehouse**: 25-31 (20-30m range)
- **Dense deployment**: 10-15 (reduce interference)

## Channel Selection

DWM1000 supports 7 channels (1, 2, 3, 4, 5, 6, 7):

| Channel | Center Frequency | Bandwidth | Typical Use |
|---------|------------------|-----------|-------------|
| 1       | 3494.4 MHz      | 500 MHz   | General     |
| 2       | 3993.6 MHz      | 500 MHz   | General     |
| 3       | 4492.8 MHz      | 500 MHz   | General     |
| 4       | 3993.6 MHz      | 900 MHz   | High precision |
| 5       | 6489.6 MHz      | 500 MHz   | Less interference |
| 7       | 6489.6 MHz      | 900 MHz   | Best precision |

### Recommendations
- **Best accuracy**: Channel 4 or 7 (wider bandwidth)
- **Less interference**: Channel 5 or 7 (higher frequency)
- **General use**: Channel 1, 2, or 3

## Environment-Specific Calibration

### Indoor Multipath
Indoor environments have signal reflections (multipath):

**Symptoms:**
- Fluctuating measurements
- Bias toward longer distances

**Solutions:**
- Use higher TX power
- Enable receiver diagnostics
- Filter outliers in software
- Add antenna diversity

### Metal Objects
Metal near antennas affects calibration:

**Impact:**
- Changes antenna delay
- Reduces signal quality

**Solutions:**
- Keep 5cm clearance from metal
- Re-calibrate in final mounting location
- Use ground plane behind antenna

## Verification

After calibration, verify accuracy:

```cpp
// Test at multiple distances
float distances[] = {1.0, 2.0, 5.0, 10.0};

for (int i = 0; i < 4; i++) {
    float actual = distances[i];
    float measured = measure_average(100);  // 100 samples
    float error = measured - actual;
    float error_percent = (error / actual) * 100;
    
    log_kv3(LOG_INFO, "Calibration check",
            "Actual", String(actual, 2) + "m",
            "Measured", String(measured, 2) + "m",
            "Error", String(error_percent, 1) + "%");
}
```

**Target Accuracy:**
- < 5cm error at 1-5m
- < 10cm error at 5-10m
- < 2% error overall

## Saving Calibration

Store calibration values in non-volatile memory:

```cpp
#include <Preferences.h>

Preferences prefs;

// Save calibration
void save_calibration(uint16_t antenna_delay, uint8_t tx_power) {
    prefs.begin("uwb_cal", false);
    prefs.putUShort("ant_delay", antenna_delay);
    prefs.putUChar("tx_power", tx_power);
    prefs.end();
}

// Load calibration
void load_calibration(uint16_t* antenna_delay, uint8_t* tx_power) {
    prefs.begin("uwb_cal", true);
    *antenna_delay = prefs.getUShort("ant_delay", 16450);  // Default
    *tx_power = prefs.getUChar("tx_power", 20);            // Default
    prefs.end();
}
```

## Troubleshooting

### Large Ranging Errors (> 1m)
- Check antenna delay is in correct range (16000-17500)
- Verify SPI communication is working
- Check for loose connections

### Inconsistent Measurements
- Increase averaging (more samples)
- Check for interference sources
- Verify stable power supply

### No Ranging Data
- Verify both devices are powered
- Check device modes (one anchor, one tag)
- Confirm antenna connections

## Advanced Topics

### Temperature Compensation
Temperature affects crystal oscillator:
- Monitor temperature sensor
- Apply correction factor
- Typical: -0.5cm per 10°C deviation

### Multi-Anchor Calibration
When using multiple anchors:
- Calibrate each anchor individually
- Verify inter-anchor distances
- Use trilateration algorithms

---

For questions or issues, please open a GitHub issue.
