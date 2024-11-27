#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <Windows.h>
class TPixels;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TTerminalScreen
{
    friend class TPixels;
    public:
    std::string Content;
    char BgChar;
    int Width;
    int Height;
public:
    TTerminalScreen(int W = 120, int H = 30) : BgChar(' '), Width(W), Height(H)
    {
        Content.resize(Height * Width, BgChar);
        Clear();
    }

    void Resize(int W, int H)
    {
        Width = W;
        Height = H;
        Content.resize(Height * Width, BgChar);
        Clear();
    }

    //--------------------
    void ClearRect(int Left, int Top, int Right, int Bottom, char BgChar);

    //--------------------
    void PresentScreen()
    {
        std::cout << Content << std::flush;
    }

    //--------------------
    void Clear()
    {
        ClearRect(0, 0, Width - 1, Height - 1, BgChar);
        /*
        COORD topLeft = { 0, 0 };
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        SetConsoleCursorPosition(console, topLeft);
        */
    }

    //-------------------
    void DrawText(int Column, int Row, std::string Text)
    {
        Content.replace(Width * Row + Column, Text.length(), Text);
    }

    //-------------------
    char GetCharAt(int Column, int Row)
    {
        if (Column < 0 || Column >= Width) return -1;
        if (Row < 0 || Row >= Height) return -1;
        int i = Width * Row + Column;
        if (i >= 0 && i < Content.length())
            return Content[i];
        return -1;
    }

    //-------------------
    void PutCharAt(int Column, int Row, char ch)
    {
        if (Column < 0 || Column >= Width - 1) return;
        if (Row < 0 || Row >= Height) return;
        int i = Width * Row + Column;
        if (i >= 0 && i < Content.length())
            Content[i] = ch;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TTerminalDesktop;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TWindow
{
    int X, Y, Width, Height;
    char Color;
    std::string Caption;
    TTerminalScreen* Screen;
public:
    TWindow(TTerminalScreen* screen, int x, int y, int w, int h, char color, std::string caption)
        : Screen(screen), X(x), Y(y), Width(w), Height(h), Color(color), Caption(caption)
    { }
    TTerminalDesktop operator+(TWindow& wnd);
    void Draw();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TDesktop
{
    TTerminalScreen* Screen;
    std::vector<TWindow*> Windows;
public:
    TDesktop(TTerminalScreen* screen) : Screen(screen)
    { }
    void Refresh();
    void Clear() { Screen->Clear(); };
    // ------------ przeladowane operatory
    void operator+=(TWindow* wnd); // dodawanie okienka
    void operator-=(TWindow* wnd); // usuwanie okienka
    void MoveToTop(TWindow* wnd); // wyjmowanie na sam wierzch
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TVertex2d
{
    friend class TPixels;
    int x, y;
    char ch;
public:
    TVertex2d(int _x = 0, int _y = 0, char _ch = ' ') : x(_x), y(_y), ch(_ch)
    { }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TPixels
{
    TTerminalScreen* Screen;
    std::vector<TVertex2d> OriginalData;
    std::vector<TVertex2d> ActualData;
    float TranslateX;
    float TranslateY;
    bool DoSinusoidalBehavior;
    void InitPixelsFromScreen();
    void InitPixelsFromString(const std::string& Text, int XOffset = 0);
public:
    TPixels(TTerminalScreen* screen) : Screen(screen), TranslateX(0.0f), TranslateY(0.0f), DoSinusoidalBehavior(false)
    {
        InitPixelsFromScreen();
    }
    TPixels(TTerminalScreen* screen, std::string& Text, int XOffset) : Screen(screen), TranslateX(0.0f), TranslateY(0.0f), DoSinusoidalBehavior(false)
    {
        InitPixelsFromString(Text, XOffset);
    }
    void Update(TTerminalScreen* screen) { InitPixelsFromScreen(); }
    void Draw(bool ClearBeforeRedraw = true);
    void Translate(float dx, float dy) { TranslateX += dx; TranslateY += dy; }
    float GetTranslateX() const { return TranslateX; }
    float GetTranslateY() const { return TranslateY; }
    void SetTranslateX(float dx) { TranslateX = dx; }
    void SetTranslateY(float dy) { TranslateY = dy; }
    bool GetDoSinusoidalBehavior() const { return DoSinusoidalBehavior; }
    void SetSinusoidalBehavior(bool Value) { DoSinusoidalBehavior = Value; }
    void Rotate(float alpha);
    void Scale(float factor);
};
