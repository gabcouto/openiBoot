#include "openiboot.h"
#include "platform.h"
#include "tasks.h"
#include "util.h"

mainfn_t OpenIBootMain = NULL;

void OpenIBootConsole()
{
	init_modules();
	bufferPrintf("  ___                   _ ____              _   \r\n");
	bufferPrintf(" / _ \\ _ __   ___ _ __ (_) __ )  ___   ___ | |_ \r\n");
	bufferPrintf("| | | | '_ \\ / _ \\ '_ \\| |  _ \\ / _ \\ / _ \\| __|\r\n");
	bufferPrintf("| |_| | |_) |  __/ | | | | |_) | (_) | (_) | |_ \r\n");
	bufferPrintf(" \\___/| .__/ \\___|_| |_|_|____/ \\___/ \\___/ \\__|\r\n");
	bufferPrintf("      |_|                                       \r\n");
	bufferPrintf("\r\n");
	bufferPrintf("version: %s\r\n", OPENIBOOT_VERSION_STR);
	DebugPrintf("                    DEBUG MODE\r\n");
}

void OpenIBootStart()
{
	platform_init();

	OpenIBootMain = &OpenIBootConsole;
	init_boot_modules();

	OpenIBootMain();

	tasks_run(); // Runs forever.
}

void OpenIBootShutdown()
{
	exit_modules();
	platform_shutdown();
}
