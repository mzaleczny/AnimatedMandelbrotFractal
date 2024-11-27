#include <iostream>
#include <vector>
#include <string>
#include <ctime> // deklaracja funkcji time
#include <iomanip>
#include "Desktop.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TTerminalScreen::ClearRect(int Left, int Top, int Right, int Bottom, char BgChar)
{
    int Length = Right - Left;
    for (int y = Top; y <= Bottom; y++)
    {
        Content.replace(y * Width + Left, Length, Length, BgChar);
    }
    for (int i = 0; i < Height - 1; i++)
    {
        Content[(i+1) * Width - 1] = '\n';
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TWindow::Draw()
{
    // zamaluj kolorem tla
    Screen->ClearRect(X, Y, X + Width - 1, Y + Height - 1, Color);
    // narysowanie ramki – dwie linie poziome -------------
    std::string Line(Width, '-');
    Screen->DrawText(X, Y, Line); // górny brzeg
    Screen->DrawText(X, Y + Height - 1, Line); // dolny brzeg
    // cd. rysowania ramki – dwie linie pionowe ------------
    for (int i = 0; i < Height; i++)
    {
        Screen->DrawText(X, Y + i, "|"); // lewy brzeg
        Screen->DrawText(X + Width, Y + i, "|"); // prawy brzeg
    }
    // napisanie tytulu okna na srodku pierwszej linijki
    Screen->DrawText(X + (Width - (Caption.length())) / 2, Y, Caption);
    Screen->PresentScreen();
}


//*****************************************************************************************************************
// definicje funkcji skladowych klasy Tpulpit
//*****************************************************************************************************************
void TDesktop::Refresh()
{
    for (TWindow* Wnd : Windows)
        Wnd->Draw();
}

//*****************************************************************************************************************
// dodawanie okna
void TDesktop::operator+=(TWindow* wnd)
{
    Windows.push_back(wnd);
    Refresh();
}

//*****************************************************************************************************************
// usuwanie okna z pulpitu (czyli z wektora wskazników do okien)
void TDesktop::operator-=(TWindow* wnd)
{
    // odszukanie w tablicy wskaznika do tego okna
    for (unsigned int Index = 0 ; Index < Windows.size(); Index++)
    {
        if (Windows[Index] == wnd)
        {
            Windows.erase(Windows.begin() + Index);
            break;
        }
    }
    Clear(); // najpierw musimy zmazac caly pulpit
    Refresh();
}

//*****************************************************************************************************************
/* wydobycie na sam wierzch zadanego okienka */
void TDesktop::MoveToTop(TWindow* wnd)
{
    // polega na postawieniu go na samym koncu wektora
    // w tym celu najprosciej usunac je z wektora i natychmiast dodac
    *this -= wnd; // czyli pulpit –= okno
    *this += wnd; // czyli pulpit += okno
    Refresh();
}


//*****************************************************************************************************************
void TPixels::InitPixelsFromScreen()
{
    OriginalData.clear();
    ActualData.clear();
    int x = 0;
    int y = 0;
    for (int i = 0; i < Screen->Content.length(); i++)
    {
        char ch = Screen->GetCharAt(x, y);
        TVertex2d v(x, y, ch);
        OriginalData.push_back(v);
        ActualData.push_back(v);
        if (ch == '\n')
        {
            x = 0;
            y++;

        }
        else
        {
            x++;
        }
    }
}

//*****************************************************************************************************************
void TPixels::InitPixelsFromString(const std::string& Text, int XOffset)
{
    OriginalData.clear();
    ActualData.clear();
    int x = XOffset;
    int y = 0;
    for (int i = 0; i < Text.length(); i++)
    {
        char ch = Text[i];
        TVertex2d v(x, y, ch);
        OriginalData.push_back(v);
        ActualData.push_back(v);
        if (ch == '\n')
        {
            x = XOffset;
            y++;

        }
        else
        {
            x++;
        }
    }
}

//*****************************************************************************************************************
void TPixels::Draw(bool ClearBeforeRedraw)
{
    if (ClearBeforeRedraw)
    {
        Screen->Clear();
    }
    for (int i = 0; i < ActualData.size(); i++)
    {
        if (ActualData[i].ch != '\n')
        {
            if (!DoSinusoidalBehavior)
            {
                Screen->PutCharAt(ActualData[i].x + TranslateX, ActualData[i].y + TranslateY, ActualData[i].ch);
            }
            else
            {
                float X = ActualData[i].x + TranslateX;
                float Y = ActualData[i].y + TranslateY + 1.1f * sin(X * 0.17f);
                Screen->PutCharAt(X, Y, ActualData[i].ch);
            }
        }
    }
}

//*****************************************************************************************************************
void TPixels::Rotate(float alpha)
{
    int PivotX = Screen->Width / 2;
    int PivotY = Screen->Height / 2;
    float s = sin(alpha);
    float c = cos(alpha);
    ActualData.clear();
    for (int i = 0; i < OriginalData.size(); i++)
    {
        float X = OriginalData[i].x - PivotX;
        float Y = OriginalData[i].y - PivotY;
        float XRot = X * c - Y * s;
        float YRot = X * s + Y * c;
        XRot = round(XRot + PivotX);
        YRot = round(YRot + PivotY);
        TVertex2d v(XRot, YRot, OriginalData[i].ch);
        ActualData.push_back(v);
    }
}

//*****************************************************************************************************************
void TPixels::Scale(float factor)
{
    int PivotX = Screen->Width / 2;
    int PivotY = Screen->Height / 2;
    for (int i = 0; i < ActualData.size(); i++)
    {
        float X = ActualData[i].x - PivotX;
        float Y = ActualData[i].y - PivotY;
        X *= factor;
        Y *= factor;
        ActualData[i].x = round(X + PivotX);
        ActualData[i].y = round(Y + PivotY);
    }
}
