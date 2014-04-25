#include <stdio.h>
#include <math.h>

#include <windows.h>

// windows only

#define NOTE_C 	261.63 	
#define NOTE_Cc	277.18 	
#define NOTE_Db	NOTE_Cc
#define NOTE_D	293.66 
#define NOTE_Dc 311.13 	
#define NOTE_Eb	NOTE_Dc
#define NOTE_E	329.63 	
#define NOTE_F	349.23
#define NOTE_Fc	369.99 	
#define NOTE_Gb NOTE_Fc
#define NOTE_G	392.00 	
#define NOTE_Gc	415.30 	
#define NOTE_Ab NOTE_Gc
#define NOTE_A	440.00
#define NOTE_Ac	466.16
#define NOTE_Bb NOTE_Ac
#define NOTE_B	493.88 
#define NOTE_MUTE 0 

void sleep(int millisec){
	Sleep(millisec);
}

void beep(float note, int octave, int millisec){
	int diff = (octave - 4);
	float freq = note * pow(2, diff);

	if (note < 0.00000001){
		sleep(millisec);
	}else{
		Beep(freq, millisec);
	}
}

void set_color(int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void cls() {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  /*if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;
	*/
  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
}


void show_cursor(bool flag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(out, &cursorInfo);
}