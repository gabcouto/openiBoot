#ifndef HW_SPI_H
#define HW_SPI_H

// Device
#define SPI0 0x3C300000
#define SPI1 0x3CE00000
#define SPI2 0x3D200000

// Registers

#define CONTROL 0x0
#define SETUP 0x4
#define STATUS 0x8
#define PIN 0xC
#define TXDATA 0x10
#define RXDATA 0x20
#define CLKDIVIDER 0x30
#define SPCNT 0x34
#define SPIDD 0x38

// Values
#define MAX_TX_BUFFER 8
#define TX_BUFFER_LEFT(x) GET_BITS(status, 4, 4)
#define RX_BUFFER_LEFT(x) GET_BITS(status, 8, 4)

#define CLOCK_SHIFT 12
#define MAX_DIVIDER 0x3FF

#define SPI0_CLOCKGATE 0x22
#define SPI1_CLOCKGATE 0x2B
#define SPI2_CLOCKGATE 0x2F

#define SPI0_IRQ 0x9
#define SPI1_IRQ 0xA
#define SPI2_IRQ 0xB

#define GPIO_SPI0_CS0_IPHONE 0x400
#define GPIO_SPI0_CS0_IPOD 0x700

#ifdef CONFIG_IPOD
#define GPIO_SPI2_CS0 0x1804
#define GPIO_SPI2_CS1 0x705
#endif

#ifdef CONFIG_IPHONE_2G
#define GPIO_SPI2_CS0 0x705
#endif

#if defined(CONFIG_IPHONE_4) || defined(CONFIG_IPAD)
#define GPIO_SPI2_CS0 0x705 // No!
#endif

#ifdef CONFIG_IPOD
#define GPIO_SPI0_CS0 GPIO_SPI0_CS0_IPOD
#else
#define GPIO_SPI0_CS0 GPIO_SPI0_CS0_IPHONE
#endif

#define GPIO_SPI1_CS0 0x1800

#ifdef CONFIG_IPHONE_3G
#define GPIO_SPI0_CS1 0x705
#define GPIO_SPI0_CS2 0x706
#endif

#define NUM_SPIPORTS 3

typedef struct SPIRegister {
	uint32_t control;
	uint32_t setup;
	uint32_t status;
	uint32_t pin;
	uint32_t txData;
	uint32_t rxData;
	uint32_t clkDivider;
	uint32_t cnt;
	uint32_t idd;
} SPIRegister;

#endif

