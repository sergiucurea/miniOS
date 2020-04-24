#include "screen.h"
#include "logging.h"

static PSCREEN gVideo = (PSCREEN)(0x000B8000);

void CursorMove(BYTE row, BYTE col)
{
    WORD location = (row * MAX_COLUMNS) + col;       /* Short is a 16bit type , the formula is used here*/

    //Cursor Low port
    __outbyte(0x3D4, 0x0F);                                    //Sending the cursor low byte to the VGA Controller
    __outbyte(0x3D5, (BYTE)(location & 0xFF));

    //Cursor High port
    __outbyte(0x3D4, 0x0E);                                    //Sending the cursor high byte to the VGA Controller
    __outbyte(0x3D5, (BYTE)((location >> 8) & 0xFF)); //Char is a 8bit type
}

void CursorPosition(WORD pos)
{
    BYTE row, col;

    if (pos > MAX_OFFSET)
    {
        pos = pos % MAX_OFFSET;
    }

    row = pos / MAX_COLUMNS;
    col = pos % MAX_COLUMNS;

    CursorMove(row, col);
}

void HelloBoot()
{


	WORD i, len;

	BYTE* boot = "Hello Boot!";

	len = 0;
	while (boot[len] != 0)
	{
		len++;
	}

	for (i = 0; (i < len) && (i < MAX_OFFSET); i++)
	{
		gVideo[i].color = 10;
		gVideo[i].c = boot[i];
	}

    CursorPosition(i);

}

void ClearScreen()
{
    int i;

    for (i = 0; i < MAX_OFFSET; i++)
    {
        gVideo[i].color = 10;
        gVideo[i].c = ' ';
    }

    CursorMove(0, 0);
}

void putStringLine(BYTE* string, DWORD pos)
{
	WORD len = 0;
	WORD i;

	while (string[len] != 0)
	{
		len++;
	}

	for (i = 0; (i < len) && (i < MAX_OFFSET); i++)
	{
		gVideo[i + pos].color = 10;
		gVideo[i + pos].c = string[i];
	}
	CursorPosition(i);
}

void putChar(BYTE* string, DWORD pos)
{
	WORD len = 0;
	WORD i;

	while (string[len] != 0)
	{
		len++;
	}

	for (i = 0; (i < len) && (i < MAX_OFFSET); i++)
	{
		gVideo[i + pos].color = 10;
		gVideo[i + pos].c = string[i];
	}
	CursorPosition(i);
}
