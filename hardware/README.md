# Hardware Documentation

## Overview

This directory contains hardware-related files for the UWB Indoor Positioning Module project.

## Contents (To Be Added)

### PCB Design Files
- KiCad project files for custom PCB
- Schematic diagrams
- PCB layout files
- Gerber files for manufacturing

### Bill of Materials (BOM)
- Component list with part numbers
- Recommended suppliers
- Cost estimates

### Mechanical Drawings
- Enclosure designs
- Mounting dimensions
- 3D printable parts

## Quick Reference

### Minimum Hardware Setup

**Option 1: Breadboard Prototype**
- ESP32-DevKitC development board
- DWM1000 module (breakout board)
- Jumper wires
- Breadboard
- USB cable

**Option 2: Custom PCB**
- Integrated ESP32 + DWM1000 board
- Onboard voltage regulation
- Antenna connector (U.FL or SMA)
- Programming header

## Wiring Reference

See main README.md for detailed wiring connections.

```
DWM1000  →  ESP32
-----------------
VCC      →  3.3V
GND      →  GND
MOSI     →  GPIO23
MISO     →  GPIO19
SCK      →  GPIO18
CS       →  GPIO5
IRQ      →  GPIO4
RST      →  GPIO15
```

## Design Notes

### Power Supply
- DWM1000 requires 3.3V ±10%
- Peak current: ~150mA during TX
- Use low-noise LDO regulator
- Add 10µF + 100nF capacitors near DWM1000

### PCB Layout Guidelines
- Keep SPI traces short (< 5cm)
- Use ground plane
- Keep antenna away from noisy circuits
- Add 50Ω impedance matching for antenna
- Consider antenna placement for optimal coverage

### Antenna Selection
- Chip antenna: Compact, lower cost, reduced range
- External antenna: Better performance, flexible placement
- Recommended: Taoglas antenna for UWB band

## Testing Points

When designing custom PCB, include test points for:
- Power rails (3.3V, GND)
- SPI signals (MOSI, MISO, SCK, CS)
- DWM1000 IRQ line
- Reset line

## Future Enhancements

- Battery power option (Li-ion + charging circuit)
- Display interface (OLED/LCD)
- Additional I/O for sensors
- Multiple anchor deployment boards

---

For PCB design files and schematics, check the `kicad/` subdirectory (to be added).
