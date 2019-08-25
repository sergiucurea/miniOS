#include <stdint.h>

// struct that contains the value of one GDT entry
struct gdt_entry_struct 
{
	#pragma pack(push, 1)

	uint16_t limit_low;				// the lower 16 bits of the limit	
	uint16_t base_low;				// the lower 16 bits of the base
	uint8_t base_middle;			// the next 8 bits of the base
	uint8_t access;					// access flags to determine ring
	uint8_t granularity;			
	uint8_t base_high;				// the last 8 bits of the base

	#pragma pack(pop)
};
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
	#pragma pack(push, 1)

	uint16_t limit;			// the upper 16 limit of all selector limits;
	uint32_t base;			// the address of the first gdt_entry_t struct;	

	#pragma pack(pop)
};
typedef struct gdt_ptr_struct gdt_ptr_t;

void init_descriptor_tables();


// struct that describes an interrupt gate.

struct idt_entry_struct
{
#pragma pack(push)
#pragma pack(1)

	uint16_t base_lo;	// the lower 16 bits of the address to jump to when this interrupt fires;
	uint16_t sel;		// kernel segement selector
	uint8_t always0;	// this must always be zero.
	uint8_t flags;		// more flags.
	uint16_t base_hi;	// the upper 16 bits of the address to jump to 

	#pragma pack(pop)
};
typedef struct idt_entry_struct idt_entry_t;

// this struct describes a pointer to an array of interrupt handlers
struct idt_ptr_struct
{
#pragma pack(push)
#pragma pack(1)

	uint16_t limit;
	uint32_t base;		// the address of the first element in our idt_entry_t array

	#pragma pack(pop)
};
typedef struct idt_ptr_struct idt_ptr_t;

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();