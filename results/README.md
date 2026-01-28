# Test Results

## Overview

This directory stores test results, calibration data, and measurement logs from the UWB Indoor Positioning Module.

## Directory Structure

```
results/
├── accuracy/          # Distance accuracy test results
├── calibration/       # Calibration data and parameters
├── performance/       # Performance benchmark results
└── logs/             # Raw measurement logs
```

## File Naming Convention

Use timestamps in filenames for easy sorting and reference:
- `accuracy_YYYYMMDD_HHMMSS.csv`
- `calibration_YYYYMMDD_HHMMSS.json`
- `performance_YYYYMMDD_HHMMSS.txt`
- `log_YYYYMMDD_HHMMSS.log`

## Data Formats

### Accuracy Test Results (CSV)

```csv
timestamp,actual_distance_m,measured_distance_m,error_m,quality_percent,rssi_dbm
1640000000,1.00,1.02,0.02,95.0,-80
1640000001,1.00,1.01,0.01,96.0,-79
...
```

### Calibration Data (JSON)

```json
{
  "timestamp": "2024-01-15T10:30:00Z",
  "antenna_delay": 16450,
  "tx_power": 20,
  "channel": 5,
  "test_distances": [1.0, 2.0, 5.0, 10.0],
  "mean_errors": [0.02, 0.03, 0.05, 0.08],
  "std_deviations": [0.01, 0.02, 0.03, 0.05]
}
```

### Performance Logs (TXT)

```
=== UWB Performance Test ===
Date: 2024-01-15 10:30:00
Duration: 600s
Samples: 3000

Ranging Rate:
  Mean: 5.0 Hz
  Min: 4.8 Hz
  Max: 5.2 Hz

Accuracy (1-10m range):
  Mean Error: 4.2 cm
  Std Dev: 2.1 cm
  Max Error: 12.3 cm

Signal Quality:
  Mean: 93.5%
  Min: 85.0%
  Max: 98.0%
```

## Example Results

### Sample Accuracy Test

Create example result files after running tests:

```bash
# Run accuracy test
cd tests
python accuracy_test.py --distance 5.0 --samples 100

# Results saved to:
# results/accuracy/accuracy_20240115_103000.csv
```

### Sample Calibration

```bash
# Run calibration procedure
python calibration_wizard.py

# Results saved to:
# results/calibration/calibration_20240115_110000.json
```

## Analyzing Results

### Python Analysis Script

```python
# Example analysis (to be implemented)
import pandas as pd
import matplotlib.pyplot as plt

# Load data
df = pd.read_csv('results/accuracy/accuracy_20240115_103000.csv')

# Calculate statistics
mean_error = df['error_m'].mean()
std_error = df['error_m'].std()

# Plot results
plt.figure(figsize=(10, 6))
plt.scatter(df['actual_distance_m'], df['measured_distance_m'])
plt.plot([0, 10], [0, 10], 'r--')  # Perfect line
plt.xlabel('Actual Distance (m)')
plt.ylabel('Measured Distance (m)')
plt.title(f'Ranging Accuracy (Error: {mean_error:.3f}m ± {std_error:.3f}m)')
plt.savefig('results/accuracy_plot.png')
```

## Baseline Results

Expected performance (after calibration):

| Metric | Target | Typical |
|--------|--------|---------|
| Accuracy (1-5m) | < 5cm | 3-4cm |
| Accuracy (5-10m) | < 10cm | 5-8cm |
| Precision (std dev) | < 3cm | 2cm |
| Update Rate | 5 Hz | 5 Hz |
| Signal Quality | > 90% | 92-95% |

## Data Retention

- Keep calibration results permanently
- Archive accuracy tests monthly
- Clean up old raw logs (> 30 days) as needed

## .gitignore

Note: Large data files should not be committed to git. Add to `.gitignore`:
```
results/**/*.csv
results/**/*.log
results/**/raw_*.txt
```

Keep summary files and calibration data in git.

---

For data analysis tools and scripts, see `tests/analysis/` directory (to be added).
