#ifndef _MAIN_H_
#define _MAIN_H_

#include <intrin.h>

//
// default types
//

//
// exported functions from __init.asm
//
void __cli(void);
void __sti(void);
void __magic(void);         // MAGIC breakpoint into BOCHS (XCHG BX,BX)
void __enableSSE(void);
void __blabla();
#endif // _MAIN_H_