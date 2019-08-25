// this file initializes the GDT and IDT
// GDT = Global Descriptor Table
// IDT = Intrrupts Descriptor Table

#include "descriptor_tables.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "screen.h"
// access the ASM functions from C code
extern void gdt_flush(uint32_t);
extern void idt_flush(uint32_t);

// internal function prototypes
static void init_gdt();
static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);
static void init_idt();
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void init_descriptor_tables()
{
	monitor_write("I am in inti descriptor table funct");
	//Initialize the global descriptor table
	init_gdt();
	//Initialize the interrupt descriptor table
	init_idt();
}

static void init_gdt()
{
	monitor_write("I am in inti gdt descriptor table funct");
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base = (uint32_t)& gdt_entries;

	
	gdt_set_gate(0, 0, 0, 0, 0);				// NULL segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // user mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // user mode data segment

	gdt_flush((uint32_t)&gdt_ptr);
}

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	monitor_write("gdt ");
	monitor_write_dec(num);
	monitor_write_pos(": ");
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access = access;

	monitor_write_dec(gdt_entries[num].base_low);
	monitor_write_pos(" ");
	monitor_write_dec(gdt_entries[num].base_middle);
	monitor_write_pos(" ");
	monitor_write_dec(gdt_entries[num].base_high);
	monitor_write_pos(" ");
	monitor_write_dec(gdt_entries[num].limit_low);
	monitor_write_pos(" ");
	monitor_write_dec(gdt_entries[num].granularity);
	monitor_write_pos(" ");
	monitor_write_dec(gdt_entries[num].access);


	
}

static void init_idt()
{
	monitor_write("I am in inti idt descriptor table funct");
	idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
	idt_ptr.base = (uint32_t)& idt_entries;

	//memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

	idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr1, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr2, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr3, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr4, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr5, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr6, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr7, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr8, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr9, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(0, (uint32_t)isr31, 0x08, 0x8E);

	idt_flush((uint32_t)& idt_ptr);
	monitor_write("I am exiting inti idt descriptor table funct");
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	

	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

	idt_entries[num].sel = sel;
	idt_entries[num].always0 = 0;
	// We must uncomment the OR below when we get to using user-mode.
	// It sets the interrupt gate's privilege level to 3.
	idt_entries[num].flags = flags /* | 0x60 */ ; 

	/*
	monitor_write("..");
	monitor_write_dec(idt_entries[num].base_lo);
	monitor_write_pos(" ");
	monitor_write_dec(idt_entries[num].base_hi);
	monitor_write_pos(" ");
	monitor_write_dec(idt_entries[num].sel);
	monitor_write_pos(" ");
	monitor_write_dec(idt_entries[num].flags);
	monitor_write_pos(" ");
	*/


}