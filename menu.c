#include "openiboot.h"
#include "lcd.h"
#include "util.h"
#include "framebuffer.h"
#include "buttons.h"
#include "timer.h"
#include "images/ConsolePNG.h"
#include "images/iPhoneOSPNG.h"
#include "images/AndroidOSPNG.h"
#include "images/ConsoleSelectedPNG.h"
#include "images/iPhoneOSSelectedPNG.h"
#include "images/AndroidOSSelectedPNG.h"
#include "images/HeaderPNG.h"
#include "images.h"
#include "actions.h"
#include "stb_image.h"
#include "pmu.h"
#include "nand.h"
#include "radio.h"
#include "hfs/fs.h"
#include "ftl.h"
#include "scripting.h"
#include "multitouch.h"
#include "nvram.h"
#include "tasks.h"

int globalFtlHasBeenRestored; /* global variable to tell wether a ftl_restore has been done*/
static TaskDescriptor menu_task;
static uint32_t FBWidth;
static uint32_t FBHeight;



static uint32_t* imgHeader;
static int imgHeaderWidth;
static int imgHeaderHeight;
static int imgHeaderX;
static int imgHeaderY;
volatile uint32_t* OtherFramebuffer;

static void drawSelectionBox() {
	volatile uint32_t* oldFB = CurFramebuffer;

	CurFramebuffer = OtherFramebuffer;
	currentWindow->framebuffer.buffer = CurFramebuffer;
	OtherFramebuffer = oldFB;

	
	lcd_window_address(2, (uint32_t) CurFramebuffer);
}

//static void toggle(/*int forward*/) {
/*	

	drawSelectionBox();
}
*/
void menu_draw()
{
        framebuffer_clear();
        FBWidth = currentWindow->framebuffer.width;
	FBHeight = currentWindow->framebuffer.height;	

	
	imgHeader = framebuffer_load_image(dataHeaderPNG, dataHeaderPNG_size, &imgHeaderWidth, &imgHeaderHeight, TRUE);

	bufferPrintf("menu: images loaded\r\n");


	imgHeaderX = 0;
	imgHeaderY = 0;

	framebuffer_draw_image(imgHeader, imgHeaderX, imgHeaderY, imgHeaderWidth, imgHeaderHeight);

	int y = 32;
	BootEntry *entry = setup_root()->list_ptr.next;
	for(;entry != setup_root(); entry = entry->list_ptr.next)
	{
		if(entry == setup_current())
			framebuffer_setcolors(COLOR_BLACK, COLOR_WHITE);
		else
			framebuffer_setcolors(COLOR_WHITE, COLOR_BLACK);

		framebuffer_setloc(23, y);
		framebuffer_print_force(entry->title);
		y++;
	}

	if(setup_root() == setup_current())
		framebuffer_setcolors(COLOR_BLACK, COLOR_WHITE);
	else
		framebuffer_setcolors(COLOR_WHITE, COLOR_BLACK);

	framebuffer_setloc(23, y);
	framebuffer_print_force("Console");

	framebuffer_setloc(0, 47);
	framebuffer_setcolors(COLOR_WHITE, COLOR_BLACK);
	framebuffer_print_force("           Openiboot 0.2 para iPod Touch 1G");
        OtherFramebuffer = CurFramebuffer;
	CurFramebuffer = (volatile uint32_t*) NextFramebuffer;

	drawSelectionBox();
}

static void menu_run(uint32_t _V)
{
	while(TRUE)
	{
#ifdef BUTTONS_VOLDOWN
		if(buttons_is_pushed(BUTTONS_HOLD)
				|| !buttons_is_pushed(BUTTONS_VOLDOWN))
#else
		if(buttons_is_pushed(BUTTONS_HOLD))
#endif
		{
			setup_entry(setup_current()->list_ptr.next);

			menu_draw();

			udelay(200000);
		}

#ifdef BUTTONS_VOLUP
		if(!buttons_is_pushed(BUTTONS_VOLUP))
		{
			setup_entry(setup_current()->list_ptr.prev);

			menu_draw();

			udelay(200000);
		}
#endif

		if(buttons_is_pushed(BUTTONS_HOME))
		{
			framebuffer_setdisplaytext(TRUE);
			framebuffer_clear();

			// Special case for console
			if(setup_current() == setup_root())
			{
				OpenIBootConsole();
				task_stop();
				return;
			}

			setup_boot();
		}

		task_yield();
	}
}

void menu_main()
{
	task_init(&menu_task, "menu");

	nand_setup();
	fs_setup();

	if(script_run_file("(0)/boot/menu.lst"))
	{
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");
                bufferPrintf("/boot/menu.lst nao encontrado. indo para console...\n");

                OpenIBootConsole();
		return;
	}

	const char* sTempOS = nvram_getvar("opib-temp-os");
	if(sTempOS && *sTempOS)
	{
		nvram_setvar("opib-temp-os","");
		nvram_save();

		setup_title(sTempOS);
		setup_boot();
	}

	setup_entry(setup_default());
	
	pmu_set_iboot_stage(0);
        memcpy((void*)NextFramebuffer, (void*) CurFramebuffer, NextFramebuffer - (uint32_t)CurFramebuffer);
        framebuffer_setdisplaytext(FALSE);
	framebuffer_clear();

	menu_draw();

	task_start(&menu_task, &menu_run, NULL);
}

static void menu_init_boot()
{
	framebuffer_clear();
	bufferPrintf("Loading openiBoot...\n");

	OpenIBootMain = &menu_main;
}
MODULE_INIT_BOOT(menu_init_boot);

