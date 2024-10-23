// main.cpp
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
// #include "gap_buffer.cpp"
#include "dll_buffer.cpp"

using namespace std;
namespace fs = std::filesystem;

GapBuffer a(2);
// Cursor position
int cursorX = 0, cursorY = 0;
std::vector<std::string> buffer = {""};
Node *superhead = new Node("");

Node *cur;

// parent of all nodes;

void basicInitialize()
{
    insert(superhead, "");
}

void clearScreen()
{
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void moveCursor(int x, int y)
{
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void render()
{
    clearScreen();
    display(superhead->next);
    moveCursor(cursorX, cursorY);
}

void processInput()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hInput, &mode);

    // Set the console mode to enable raw input
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    INPUT_RECORD input;
    DWORD read;
    while (true)
    {
        ReadConsoleInput(hInput, &input, 1, &read);

        if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown)
        {
            char c = input.Event.KeyEvent.uChar.AsciiChar;
            if (c == 27) // ESC to quit
            {
                clearScreen();
                exit(0);
            }
            else if (c == '\b')
            { // Handle backspace
                if (cursorX == 0)
                {
                    if (cur->prev == superhead)
                    {
                        continue;
                    }
                    int newCursor = (cur->prev)->g->maxCursor();
                    Node *s = join(cur->prev, cur);
                    cur = s;
                    cursorX = newCursor;
                    cursorY--;
                }
                else
                {
                    int a = cur->g->back();
                    if (a)
                        cursorX--;
                }
            }
            else if (c == '\r')
            { // Handle return (Enter)
                breakNode(cur);
                cur = cur->next;
                cursorY++;
                cursorX = 0;
            }
            else if (c != 0)
            { // Handle normal character input
                cur->g->insert(c);
                cursorX++;
            }

            // Handle arrow keys (non-ASCII characters)
            if (input.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
            {
                cur->g->left();
                cursorX--;
            }
            else if (input.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
            {
                cur->g->right();
                cursorX++;
                cursorX = min(cursorX, cur->g->maxCursor());
            }
            else if (input.Event.KeyEvent.wVirtualKeyCode == VK_UP && cursorY > 0)
            {
                if (cur->prev != superhead)
                {
                    cur = cur->prev;
                    cursorY--;
                    cursorX = min(cursorX, cur->g->maxCursor());
                }
            }
            else if (input.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
            {
                if (cur->next)
                {
                    cur = cur->next;
                    cursorY++;
                    cursorX = min(cursorX, cur->g->maxCursor());
                }
            }
            cur->g->move(cursorX);
            render(); // Update the screen with the current buffer content
        }
    }
}
int main()
{
    basicInitialize();
    cur = superhead->next;
    processInput();
    return 0;
}
