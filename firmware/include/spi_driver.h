/**
 * @file spi_driver.h
 * @brief SPI Driver for DWM1000 communication
 * 
 * This driver provides low-level SPI communication functions
 * for interfacing with the DWM1000 UWB module.
 */

#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <Arduino.h>
#include <SPI.h>

// SPI Pin Definitions
#define SPI_MOSI_PIN    23
#define SPI_MISO_PIN    19
#define SPI_SCK_PIN     18
#define SPI_CS_PIN      5

// SPI Configuration
#define SPI_CLOCK_SPEED 2000000  // 2 MHz (DWM1000 max: 20 MHz)
#define SPI_BIT_ORDER   MSBFIRST
#define SPI_MODE        SPI_MODE0

/**
 * @brief Initialize SPI interface
 * @return true if initialization successful, false otherwise
 */
bool spi_init();

/**
 * @brief Write data to SPI device
 * @param reg_addr Register address to write to
 * @param data Pointer to data buffer
 * @param len Length of data to write
 * @return true if write successful, false otherwise
 */
bool spi_write(uint8_t reg_addr, const uint8_t* data, uint16_t len);

/**
 * @brief Read data from SPI device
 * @param reg_addr Register address to read from
 * @param data Pointer to buffer for received data
 * @param len Length of data to read
 * @return true if read successful, false otherwise
 */
bool spi_read(uint8_t reg_addr, uint8_t* data, uint16_t len);

/**
 * @brief Write single byte to SPI device
 * @param reg_addr Register address
 * @param value Value to write
 * @return true if write successful, false otherwise
 */
bool spi_write_byte(uint8_t reg_addr, uint8_t value);

/**
 * @brief Read single byte from SPI device
 * @param reg_addr Register address
 * @param value Pointer to store read value
 * @return true if read successful, false otherwise
 */
bool spi_read_byte(uint8_t reg_addr, uint8_t* value);

/**
 * @brief Select SPI device (pull CS low)
 */
void spi_select();

/**
 * @brief Deselect SPI device (pull CS high)
 */
void spi_deselect();

#endif // SPI_DRIVER_H
