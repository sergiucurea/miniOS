#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "boot.h"
#include <stdint.h>

#define MAX_LINES       80
#define MAX_COLUMNS     80
#define MAX_OFFSET      6400 //80 lines * 80 chars


#pragma pack(push)
#pragma pack(1)
typedef struct _SCREEN
{
    char c;
    BYTE color;
}SCREEN, *PSCREEN;
#pragma pack(pop)

void HelloBoot();
void monitor_write(char *string);
void monitor_write_pos(char* string);
void monitor_write_dec(uint32_t n);

void SetColor(BYTE Color);
void ClearScreen();
void PutChar(char C, int Pos);
void PutString(char* String, int Pos);
void PutStringLine(char* String, int Line);


#endif // _SCREEN_H_