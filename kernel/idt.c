#include "dataTypes.h"
#include "screen.h"
#include "logging.h"
#pragma pack(push,1)
typedef struct {
	WORD baseLow; // the lower 16 bits of the address to jump when this interrupt fires
	WORD sel; // kernel segment selector
	BYTE always0; // always zero
	BYTE flags;
	WORD   baseMid;
	DWORD baseHigh; // the upper 16 bits of the address
	DWORD   reserved;
}idtEntry;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
	WORD limit;
	QWORD base;
}idtPointer;
#pragma pack(pop)

extern void __load_idt();
extern void __isr14();


idtEntry idt[256];
idtPointer pidt;

void setIdtGate(BYTE num, QWORD base, WORD sel, BYTE flags)
{
	

	
	idt[num].baseLow = base & 0xFFFF;
	idt[num].baseMid = (base >> 16) & 0xFFFF;
	idt[num].baseHigh = (base >> 32) & 0xFFFFFFFF;
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
	idt[num].reserved = 0;



}

void initIdt(void) {
	pidt.limit = (sizeof(idtEntry) * 256) - 1;
	pidt.base = (DWORD)& idt;

	setIdtGate(14, (DWORD)__isr14, 0x08, 0x8E);
	

	__load_idt();
}

void isr14_handler(void)
{
	Log("Page Fault interrupted started\n");
	ClearScreen();
	putStringLine("Page Fault Interrupt", 0);
	Log("Page Fault interrupted ended\n");

}