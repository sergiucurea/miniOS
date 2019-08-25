#include <stdint.h>

typedef struct registers
{
	uint32_t ds;										// data segement selector
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;		// pushed by pusha
	uint32_t int_no, err_code;							// interrupt number and error code (if applicable)
	uint32_t eip, cs, eflags, useresp, ss;				// pushed by the processor automatically
} registers_t;
