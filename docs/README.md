# Documentation Index

Welcome to the UWB Indoor Positioning Module documentation!

## Getting Started

- **[Quick Start Guide](quickstart.md)** - Get up and running in 15 minutes
- **[Main README](../README.md)** - Project overview and setup instructions

## Technical Documentation

### Hardware
- **[Hardware README](../hardware/README.md)** - PCB designs, schematics, and wiring
- Wiring diagram - See main README

### Firmware
- **[API Reference](api.md)** - Complete API documentation
- **[Calibration Guide](calibration.md)** - Improve ranging accuracy

### Testing
- **[Test README](../tests/README.md)** - Test procedures and frameworks
- **[Results README](../results/README.md)** - Test results and data formats

## Guides by Task

### First-Time Setup
1. Start with [Quick Start Guide](quickstart.md)
2. Review wiring in [Main README](../README.md)
3. Flash firmware following Quick Start
4. Verify ranging output

### Improving Accuracy
1. Read [Calibration Guide](calibration.md)
2. Follow antenna delay calibration procedure
3. Test at known distances
4. Save calibration values

### Development
1. Review [API Reference](api.md)
2. Study code in `firmware/src/` and `firmware/include/`
3. Implement TODOs in driver code
4. Add tests in `tests/`

### Adding Hardware
1. Check [Hardware README](../hardware/README.md)
2. Follow PCB layout guidelines
3. Update wiring documentation
4. Test with breadboard prototype first

## Key Concepts

### UWB Ranging
Ultra-Wideband ranging measures distance by calculating signal time-of-flight between devices.

**Two-Way Ranging (TWR):**
1. Tag sends poll message
2. Anchor responds
3. Tag sends final message
4. Calculate time-of-flight from timestamps

### Device Modes

**Anchor (Stationary):**
- Known position
- Responds to ranging requests
- Can have multiple anchors

**Tag (Mobile):**
- Unknown position (to be determined)
- Initiates ranging
- Calculates distance to anchors

### Positioning vs Ranging

**Ranging:**
- Measures distance between two devices
- Requires 1 anchor + 1 tag
- Output: Single distance value

**Positioning:**
- Determines 2D/3D coordinates
- Requires 3+ anchors + 1 tag
- Output: (x, y) or (x, y, z) position

## Code Structure

```
firmware/
├── include/
│   ├── spi_driver.h       # SPI communication
│   ├── dwm1000_driver.h   # DWM1000 control
│   └── logger.h           # Logging system
└── src/
    ├── spi_driver.cpp     # SPI implementation
    ├── dwm1000_driver.cpp # DWM1000 implementation
    ├── logger.cpp         # Logging implementation
    └── main.cpp           # Main application
```

## Development Roadmap

### Phase 1: Basic Ranging ✓
- [x] Project structure
- [x] SPI driver placeholder
- [x] DWM1000 driver placeholder
- [x] Logging system
- [x] Example code

### Phase 2: Real Implementation (TODO)
- [ ] Complete SPI communication
- [ ] DWM1000 register configuration
- [ ] TWR implementation
- [ ] Interrupt handling
- [ ] Antenna delay calibration

### Phase 3: Advanced Features (TODO)
- [ ] Multiple anchors
- [ ] Trilateration algorithm
- [ ] Position filtering (Kalman filter)
- [ ] Web interface
- [ ] Data logging to SD card

### Phase 4: Optimization (TODO)
- [ ] Power management
- [ ] Range optimization
- [ ] Multi-path mitigation
- [ ] Production PCB design

## Reference Materials

### Datasheets
- [DWM1000 Datasheet](https://www.decawave.com/product/dwm1000-module/)
- [DW1000 IC Datasheet](https://www.decawave.com/product/dw1000/)
- [ESP32 Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)

### Application Notes
- DWM1000 User Manual (check DecaWave website)
- Sources and Effects of Error in DWM1000 Based TWR Schemes
- Antenna Delay Calibration

### Standards
- IEEE 802.15.4-2011 (UWB PHY)
- IEEE 802.15.4z-2020 (Enhanced Impulse Radio)

## Troubleshooting

Common issues and solutions:

| Problem | Solution | Reference |
|---------|----------|-----------|
| Init failed | Check wiring | [Quick Start](quickstart.md) |
| No ranging | Check device modes | [Main README](../README.md) |
| Inaccurate | Calibrate antenna delay | [Calibration](calibration.md) |
| Low quality | Adjust TX power | [API Reference](api.md) |

## Contributing

When adding documentation:
1. Use Markdown format
2. Add to this index
3. Include code examples
4. Keep language clear and concise

## Support

- **GitHub Issues**: Bug reports and feature requests
- **Discussions**: General questions
- **Pull Requests**: Code contributions

---

**Documentation Version:** 1.0.0  
**Last Updated:** 2024-01-28  
**Status:** Initial Release
