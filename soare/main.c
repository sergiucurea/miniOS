#include "boot.h"
#include "screen.h"
#include "descriptor_tables.h"

void EntryPoint(void)
{
	//__magic();                  // break into BOCHS
	init_descriptor_tables();
	HelloBoot();
	monitor_write("This is a message ");
	monitor_write_pos("mata");



	_asm __volatile{
		int 3h
		int 4h
	}
	
	monitor_write("This is a message after interrupt");

}