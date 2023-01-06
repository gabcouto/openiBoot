#include "openiboot.h"
#include "power.h"
#include "hardware/power.h"

int power_setup() {
	// Deprecated in 2.x
#if 0
	SET_REG(POWER + POWER_CONFIG0, POWER_CONFIG0_RESET);
	SET_REG(POWER + POWER_CONFIG1, POWER_CONFIG1_RESET);
	SET_REG(POWER + POWER_CONFIG2, POWER_CONFIG2_RESET);

	/* turn off everything */
	int toReset = POWER_DEFAULT_DEVICES | POWER_VROM;
	SET_REG(POWER + POWER_OFFCTRL, toReset);

	/* wait for the new state to take effect */
	while((GET_REG(POWER + POWER_SETSTATE) & toReset) != (GET_REG(POWER + POWER_STATE) & toReset));
#endif
	return 0;
}

int power_ctrl(uint32_t device, OnOff on_off) {
	if (device > POWER_STATE_MAX) {
		return -1;
	}
	uint32_t device_register = POWER + POWER_STATE + (device << 2);

	if (on_off == ON) {
		SET_REG(device_register, GET_REG(device_register) | 0xF);
	} else {
		SET_REG(device_register, GET_REG(device_register) & ~0xF);
	}
	
	/* wait for the new state to take effect */
	while ((GET_REG(device_register) & 0xF) != ((GET_REG(device_register) >> 4) & 0xF));

	return 0;
}
