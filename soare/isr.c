#include "isr.h"
#include "screen.h"

void isr_handler(registers_t regs)
{
	monitor_write("recieved interrupt: ");
	monitor_write_dec(regs.int_no);
}