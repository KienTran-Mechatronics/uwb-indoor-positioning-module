# Test Directory

## Overview

This directory contains test cases and validation scripts for the UWB Indoor Positioning Module.

## Test Structure

```
tests/
├── unit/              # Unit tests for individual modules
├── integration/       # Integration tests
├── calibration/       # Calibration test scripts
└── performance/       # Performance benchmarks
```

## Test Categories

### Unit Tests
Test individual components in isolation:
- SPI driver functionality
- DWM1000 driver API
- Logger output formatting
- Configuration management

### Integration Tests
Test complete system functionality:
- Two-device ranging
- Multi-anchor positioning
- Error handling and recovery
- Power consumption

### Calibration Tests
Validation of calibration procedures:
- Antenna delay verification
- Distance accuracy testing
- Signal quality metrics

### Performance Tests
System performance evaluation:
- Ranging update rate
- Accuracy vs distance
- Multi-path rejection
- Battery life (if applicable)

## Running Tests

### Prerequisites

```bash
cd tests
pip install -r requirements.txt  # Install test dependencies (to be added)
```

### Unit Tests Example

```python
# Example unit test structure (to be implemented)
import pytest
from uwb_test_utils import *

def test_spi_communication():
    """Test SPI read/write operations"""
    # Test implementation here
    pass

def test_ranging_calculation():
    """Test ranging distance calculation"""
    # Test implementation here
    pass
```

### Hardware-in-Loop Tests

For tests requiring actual hardware:

```bash
# Flash test firmware to device
cd ../firmware
pio run --target upload

# Run hardware tests
cd ../tests
python run_hardware_tests.py --port /dev/ttyUSB0
```

## Test Data Collection

### Accuracy Test

```python
# Example test script (to be implemented)
"""
Test ranging accuracy at known distances
"""
distances = [1.0, 2.0, 3.0, 5.0, 10.0]  # meters
samples = 100

for distance in distances:
    measurements = collect_samples(samples)
    mean_distance = calculate_mean(measurements)
    std_dev = calculate_std(measurements)
    error = mean_distance - distance
    
    print(f"Distance: {distance}m")
    print(f"  Mean: {mean_distance:.3f}m")
    print(f"  Std Dev: {std_dev:.3f}m")
    print(f"  Error: {error:.3f}m ({error/distance*100:.1f}%)")
```

## Test Results

Test results should be saved to the `results/` directory with timestamps:
- `results/accuracy_test_YYYYMMDD_HHMMSS.csv`
- `results/calibration_YYYYMMDD_HHMMSS.json`
- `results/performance_YYYYMMDD_HHMMSS.txt`

## Test Fixtures

### Physical Test Setup
- Optical table or stable surface
- Laser distance meter for reference
- Multiple anchors at known positions
- Controlled environment (minimal interference)

### Software Mocks
Mock objects for testing without hardware:
- Mock SPI interface
- Mock DWM1000 responses
- Simulated ranging data

## Continuous Integration

### Automated Tests
Tests that can run in CI/CD:
- Code compilation (all platforms)
- Static analysis
- Unit tests (mocked hardware)
- Documentation generation

### Manual Tests
Tests requiring hardware setup:
- Full system ranging tests
- Calibration procedures
- Long-term stability tests
- Environmental testing

## Test Documentation

Each test should include:
- Purpose and scope
- Prerequisites
- Setup instructions
- Expected results
- Pass/fail criteria

## Example Test Case

```cpp
// Example embedded test (to be added)
/**
 * Test: SPI Communication
 * Verify SPI read/write to DWM1000 device ID register
 */
void test_spi_device_id() {
    uint32_t device_id = dwm1000_get_device_id();
    
    if (device_id == 0xDECA0130) {
        LOG_INFO("PASS: Device ID correct");
    } else {
        log_kv2(LOG_ERROR, "FAIL: Device ID incorrect",
                "Expected", "0xDECA0130",
                "Got", String(device_id, HEX));
    }
}
```

## Contributing Tests

When adding new tests:
1. Follow existing test structure
2. Document test purpose and procedure
3. Include expected results
4. Add to CI if possible
5. Update this README

## Tools and Libraries

### Recommended Testing Tools
- PlatformIO unit testing framework
- pytest for Python tests
- matplotlib for data visualization
- pandas for data analysis

---

For specific test implementations, see subdirectories.
