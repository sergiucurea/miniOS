#include "main.h"
#include "screen.h"
#include "logging.h"
#include "picMapping.h"
#include "idt.h"

extern void __myfunc(void);


void KernelMain()
{


	ClearScreen();
    InitLogging();
    Log("Logging initialized!\n");
    HelloBoot();
	Log("Message printed to screen.\n");

	picRemaping(0x20, 0x28);
	Log("PIC Mapped\n");
	initIdt();
	Log("IDT initialized\n");

	Log("Trying to generate a page fault\n");
	__myfunc();
	Log("Stoped trying to generate a page fault \n");
	





    // TODO!!! define interrupt routines and dump trap frame


    // TODO!!! Timer programming

    // TODO!!! Keyboard programming

    // TODO!!! Implement a simple console

    // TODO!!! read disk sectors using PIO mode ATA

    // TODO!!! Memory management: virtual, physical and heap memory allocators
}
