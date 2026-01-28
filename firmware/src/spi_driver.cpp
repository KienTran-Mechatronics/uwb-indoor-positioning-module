/**
 * @file spi_driver.cpp
 * @brief SPI Driver implementation for DWM1000
 */

#include "spi_driver.h"

static SPIClass* spi_instance = nullptr;

bool spi_init() {
    // Initialize CS pin
    pinMode(SPI_CS_PIN, OUTPUT);
    digitalWrite(SPI_CS_PIN, HIGH);  // Deselect by default
    
    // Initialize SPI
    spi_instance = new SPIClass(VSPI);
    spi_instance->begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CS_PIN);
    
    delay(10);  // Allow SPI to stabilize
    
    return true;
}

void spi_select() {
    digitalWrite(SPI_CS_PIN, LOW);
    delayMicroseconds(1);  // Short delay for setup time
}

void spi_deselect() {
    delayMicroseconds(1);  // Short delay before deselect
    digitalWrite(SPI_CS_PIN, HIGH);
}

bool spi_write(uint8_t reg_addr, const uint8_t* data, uint16_t len) {
    if (!spi_instance || !data || len == 0) {
        return false;
    }
    
    spi_instance->beginTransaction(SPISettings(SPI_CLOCK_SPEED, SPI_BIT_ORDER, SPI_MODE));
    spi_select();
    
    // Write register address (write mode: MSB = 1)
    spi_instance->transfer(reg_addr | 0x80);
    
    // Write data
    for (uint16_t i = 0; i < len; i++) {
        spi_instance->transfer(data[i]);
    }
    
    spi_deselect();
    spi_instance->endTransaction();
    
    return true;
}

bool spi_read(uint8_t reg_addr, uint8_t* data, uint16_t len) {
    if (!spi_instance || !data || len == 0) {
        return false;
    }
    
    spi_instance->beginTransaction(SPISettings(SPI_CLOCK_SPEED, SPI_BIT_ORDER, SPI_MODE));
    spi_select();
    
    // Write register address (read mode: MSB = 0)
    spi_instance->transfer(reg_addr & 0x7F);
    
    // Read data
    for (uint16_t i = 0; i < len; i++) {
        data[i] = spi_instance->transfer(0x00);
    }
    
    spi_deselect();
    spi_instance->endTransaction();
    
    return true;
}

bool spi_write_byte(uint8_t reg_addr, uint8_t value) {
    return spi_write(reg_addr, &value, 1);
}

bool spi_read_byte(uint8_t reg_addr, uint8_t* value) {
    return spi_read(reg_addr, value, 1);
}
