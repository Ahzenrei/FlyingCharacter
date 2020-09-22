#include "GameManager.h"
#include "Windows.h"
#include <iostream>

GameManager::GameManager()
{
    dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    dwBufferCoord = { 0, 0 };
    rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
    new_style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX );
    hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
}

void GameManager::init()
{
	setConsoleWindowStyle(GWL_STYLE);

	clock.start();

    ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
        dwBufferCoord, &rcRegion);
}

void GameManager::WriteToConsole()
{
    WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
        dwBufferCoord, &rcRegion);
}

void GameManager::Flush()
{
    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            buffer[j][i].Char.AsciiChar = ' ';
        }
    }
}

LONG_PTR GameManager::setConsoleWindowStyle(INT n_index)
{
    /*The function does not clear the last error information. if last value was zero.*/
    SetLastError(NO_ERROR);

    HWND hwnd_console = GetConsoleWindow();
    LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console, n_index, new_style);
    SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

    //show window after updating
    ShowWindow(hwnd_console, SW_SHOW);

    return style_ptr;
}
