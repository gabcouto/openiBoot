#ifndef CLOCK_H
#define CLOCK_H

#include "openiboot.h"
#include "hardware/clock.h"

typedef enum ClockDivisorCode {
	ClockDivisorCode0 = 0,
	ClockDivisorCode1 = 1,
	ClockDivisorCode2 = 2,
	ClockDivisorCode3 = 3
} ClockDivisorCode;

extern uint32_t ClockPLL;
extern uint32_t PLLFrequencies[NUM_PLL];

extern uint32_t ClockFrequency;
extern uint32_t MemoryFrequency;
extern uint32_t BusFrequency;
extern uint32_t PeripheralFrequency;
extern uint32_t UnknownFrequency;
extern uint32_t DisplayFrequency;
extern uint32_t FixedFrequency;
extern uint32_t TimebaseFrequency;

extern uint32_t ClockSDiv;

extern uint32_t TicksPerSec;

typedef enum FrequencyBase {
	FrequencyBaseClock,
	FrequencyBaseMemory,
	FrequencyBaseBus,
	FrequencyBasePeripheral,
	FrequencyBaseUnknown,
	FrequencyBaseDisplay,
	FrequencyBaseFixed,
	FrequencyBaseTimebase,
	FrequencyBaseUsbPhy,
} FrequencyBase;

#ifdef CONFIG_S5L8900
int clock_set_base_divisor(ClockDivisorCode code);
int clock_setup();
void clock_gate_switch(uint32_t gate, OnOff on_off);
uint32_t clock_get_frequency(FrequencyBase freqBase);
uint32_t clock_calculate_frequency(uint32_t pdiv, uint32_t mdiv, FrequencyBase freqBase);
void clock_set_sdiv(int sdiv);
#elif defined(CONFIG_A4)
uint32_t CalculatedFrequencyTable[55];
int clock_setup();
void clock_gate_switch(uint32_t gate, OnOff on_off);
uint32_t clock_get_frequency(FrequencyBase freqBase);
#elif defined(CONFIG_S5L8720)
int clock_set_base_divisor(ClockDivisorCode code);
int clock_setup();
void clock_gate_switch(uint32_t gate, OnOff on_off);
uint32_t clock_get_frequency(FrequencyBase freqBase);
unsigned int clock_get_base_frequency();
#endif

#endif
