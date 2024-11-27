#include <windows.h>
#include <iostream>
#include <chrono>
#include <future>
#include "Desktop.h"

#pragma comment(lib, "Winmm")

int columns, rows;

std::string ScrolledText = R"( _    _       _                           _             ___  ___               _            ______      _                                __  _     _   _                   ____                                                    _           _  __         ___  ___                _                 _____     _          ___  ___      _                         __  _     _   _                   ____                                                      _ _                                              __          ______          _          ______                         __  _     _   _                   ____          _             _ _                             __         __ _                              ___                        __ __       ______                                    _           _             _             _               _         _             _   _            __                       _                                    ___                       _____          _                      __  _____                  ___  ___                                    _____            __   __   ______                                                             _                     _                _            _____             __  
| |  | |     | |                         (_)       _    |  \/  |              (_)          |___  /     | |                              / / | |   | | | |            _    / / /                                                   | |         | | \ \        |  \/  |               | |          _    |  ___|   (_)         |  \/  |     | |                       / / | |   | | | |            _    / / /                                                     | (_)                                             \ \         |  ___|        | |    _    |  _  \                       / / | |   | | | |            _    / / /         | |           (_) |                           / /        / _| |                            / / |                      / / \ \      |  ___|                                  | |         | |           | |           | |             | |       | |           (_) | |          / _|                     | |                           _      |_  |                     |  __ \        | |                    / / |  _  |                 |  \/  |                                   /  __ \ _     _  /  | /  |  | ___ \                                                           (_)                   (_)              | |          /  __ \ _     _    \ \ 
| |  | |_   _| | _____  _ __   __ _ _ __  _  ___  (_)   | .  . | __ _ _ __ ___ _ _ __         / /  __ _| | ___  ___ _____ __  _   _    | |  | |__ | |_| |_ _ __  ___(_)  / / / __  _ __ ___   __ _ _ __ ___   __ _ _ __ _ __   ___| |_   _ __ | |  | |       | .  . |_   _ _____   _| | ____ _  (_)   | |__ _ __ _  ___     | .  . | __ _| |_ _   _  __ _ ___     | |  | |__ | |_| |_ _ __  ___(_)  / / /_      ____      ____      _____  ___  _   _ _ __   __| |_ _ __ ___   __ _  __ _  ___   ___  _ __ __ _   | |        | |_ ___  _ __ | |_  (_)   | | | |___   ___  _ __ ___   | |  | |__ | |_| |_ _ __  ___(_)  / / / __   __ _| |_ ___  _ __ _| | __  ___ ___  _ __ ___    / /__  ___ | |_| |___      ____ _ _ __ ___   / /| |_ __ _  __ _  __ _   / /   | |     | |_ _ __ __ _  __ _ _ __ ___   ___ _ __ | |_ _   _  | | _____   __| |_   _    __| | ___     ___ | |__  ___| |_   _  __ _ _  | |__  _   _| |_ ___  _ __ __ _    ___| | ___ __ __ _ _ __  _   _  (_)       | | ___ _ __ _____   _  | |  \/_ __ ___| |__   ___  ___ ____ | |  | | | |_ __  _   _ ___  | .  . | __ _  __ _ _ __  _   _ _ __ ___   | /  \/| |_ _| |_`| | `| |  | |_/ / __ ___   __ _ _ __ __ _ _ __ ___   _____      ____ _ _ __  _  ___  __      __    _  ___ _____   _| | ___   _  | /  \/| |_ _| |_   | |
| |/\| | | | | |/ / _ \| '_ \ / _` | '_ \| |/ _ \       | |\/| |/ _` | '__/ __| | '_ \       / /  / _` | |/ _ \/ __|_  / '_ \| | | |   | |  | '_ \| __| __| '_ \/ __|   / / / '_ \| '__/ _ \ / _` | '_ ` _ \ / _` | '__| '_ \ / _ \ __| | '_ \| |  | |       | |\/| | | | |_  / | | | |/ / _` |       |  __| '__| |/ __|    | |\/| |/ _` | __| | | |/ _` / __|    | |  | '_ \| __| __| '_ \/ __|   / / /\ \ /\ / /\ \ /\ / /\ \ /\ / / __|/ _ \| | | | '_ \ / _` | | '_ ` _ \ / _` |/ _` |/ _ \ / _ \| '__/ _` |  | |        |  _/ _ \| '_ \| __|       | | | / _ \ / _ \| '_ ` _ \  | |  | '_ \| __| __| '_ \/ __|   / / / '_ \ / _` | __/ _ \| '__| | |/ / / __/ _ \| '_ ` _ \  / / __|/ _ \|  _| __\ \ /\ / / _` | '__/ _ \ / / | __/ _` |/ _` |/ _` | / /    | |     |  _| '__/ _` |/ _` | '_ ` _ \ / _ \ '_ \| __| | | | | |/ / _ \ / _` | | | |  / _` |/ _ \   / _ \| '_ \/ __| | | | |/ _` | | | '_ \| | | |  _/ _ \| '__/ _` |  / _ \ |/ / '__/ _` | '_ \| | | |           | |/ _ \ '__|_  / | | | | | __| '__/ _ \ '_ \ / _ \/ __|_  / | |  | | | | '_ \| | | / __| | |\/| |/ _` |/ _` | '_ \| | | | '_ ` _ \  | |  |_   _|_   _|| |  | |  |  __/ '__/ _ \ / _` | '__/ _` | '_ ` _ \ / _ \ \ /\ / / _` | '_ \| |/ _ \ \ \ /\ / /   | |/ _ \_  / | | | |/ / | | | | |  |_   _|_   _|  | |
\  /\  / |_| |   < (_) | | | | (_| | | | | |  __/  _    | |  | | (_| | | | (__| | | | |    ./ /__| (_| | |  __/ (__ / /| | | | |_| |   | |  | | | | |_| |_| |_) \__ \_ / / /| |_) | | | (_) | (_| | | | | | | (_| | |_ | | | |  __/ |_ _| |_) | |  | |  _    | |  | | |_| |/ /| |_| |   < (_| |  _    | |__| |  | | (__     | |  | | (_| | |_| |_| | (_| \__ \    | |  | | | | |_| |_| |_) \__ \_ / / /  \ V  V /  \ V  V /  \ V  V /\__ \ (_) | |_| | | | | (_| | | | | | | | (_| | (_| |  __/| (_) | | | (_| |  | |  _     | || (_) | | | | |_   _    | |/ / (_) | (_) | | | | | | | |  | | | | |_| |_| |_) \__ \_ / / /| |_) | (_| | || (_) | |  | |   < | (_| (_) | | | | | |/ /\__ \ (_) | | | |_ \ V  V / (_| | | |  __// /  | || (_| | (_| | (_| |/ /     | |  _  | | | | | (_| | (_| | | | | | |  __/ | | | |_| |_| | |   < (_) | (_| | |_| | | (_| | (_) | | (_) | |_) \__ \ | |_| | (_| | | | |_) | |_| | || (_) | | | (_| | |  __/   <| | | (_| | | | | |_| |  _    /\__/ /  __/ |   / /| |_| | | |_\ \ | |  __/ |_) | (_) \__ \/ /  | |  \ \_/ / |_) | |_| \__ \ | |  | | (_| | (_| | | | | |_| | | | | | | | \__/\|_|   |_| _| |__| |_ | |  | | | (_) | (_| | | | (_| | | | | | | (_) \ V  V / (_| | | | | |  __/  \ V  V /    | |  __// /| |_| |   <| |_| | | \__/\|_|   |_|    | |
 \/  \/ \__, |_|\_\___/|_| |_|\__,_|_| |_|_|\___| (_)   \_|  |_/\__,_|_|  \___|_|_| |_|    \_____/\__,_|_|\___|\___/___|_| |_|\__, |   | |  |_| |_|\__|\__| .__/|___(_)_/_/ | .__/|_|  \___/ \__, |_| |_| |_|\__,_|_(_)|_| |_|\___|\__(_) .__/|_|  | | ( )   \_|  |_/\__,_/___|\__, |_|\_\__,_| (_)   \____/_|  |_|\___|    \_|  |_/\__,_|\__|\__, |\__,_|___/    | |  |_| |_|\__|\__| .__/|___(_)_/_/    \_/\_/    \_/\_/    \_/\_(_)___/\___/ \__,_|_| |_|\__,_|_|_| |_| |_|\__,_|\__, |\___(_)___/|_|  \__, |  | | ( )    \_| \___/|_| |_|\__| (_)   |___/ \___/ \___/|_| |_| |_| | |  |_| |_|\__|\__| .__/|___(_)_/_/ | .__/ \__,_|\__\___/|_|  | |_|\_(_)___\___/|_| |_| |_/_/ |___/\___/|_|  \__| \_/\_/ \__,_|_|  \___/_/    \__\__,_|\__,_|\__, /_/      | | ( ) \_| |_|  \__,_|\__, |_| |_| |_|\___|_| |_|\__|\__, | |_|\_\___/ \__,_|\__,_|  \__,_|\___/   \___/|_.__/|___/_|\__,_|\__, |_| |_.__/ \__,_|_| \___/|_|  \__,_|  \___|_|\_\_|  \__,_|_| |_|\__,_| (_)   \____/ \___|_|  /___|\__, |  \____/_|  \___|_.__/ \___/|___/___| | |   \___/| .__/ \__,_|___/ \_|  |_/\__,_|\__, |_| |_|\__,_|_| |_| |_|  \____/          \___/\___/ \_|  |_|  \___/ \__, |_|  \__,_|_| |_| |_|\___/ \_/\_/ \__,_|_| |_|_|\___|   \_/\_/     | |\___/___|\__, |_|\_\\__,_|  \____/             | |
         __/ |                                                                                                                 __/ |    \_\               | |               | |               __/ |                                     | |       /_/  |/                       __/ |                                                          __/ |               \_\               | |                                                                                             __/ |                 __/ | /_/  |/                                                              \_\               | |               | |                      _/ |                                                                                             __/ |       /_/  |/                  __/ |                          __/ |                                                                 __/ |                                                                                                  __/ |                                       \_\       | |                              __/ |                                                                    __/ |                                                                 _/ |          __/ |                               /_/ 
        |___/                                                                                                                 |___/                       |_|               |_|              |___/                                      |_|                                    |___/                                                          |___/                                  |_|                                                                                            |___/                 |___/                                                                                         |_|               |_|                     |__/                                                                                             |___/                                |___/                          |___/                                                                 |___/                                                                                                  |___/                                                  |_|                             |___/                                                                    |___/                                                                 |__/          |___/                                    )";


std::string GetLineFromCin();

// Returns true if dimensions changed
bool UpdateTerminalDimensions()
{
    int PrevRows = rows;
    int PrevCols = columns;

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    columns = info.srWindow.Right - info.srWindow.Left + 1;
    rows = info.srWindow.Bottom - info.srWindow.Top + 1;
    //std::cout << columns << 'x' << rows << std::endl;
    if (PrevRows == rows && PrevCols == columns)
    {
        return false;
    }
    return true;
}

void DrawMandelbrotFractal(TTerminalScreen& Screen, int k)
{
    float i, j, r, x, y = - rows / 2;

    while (y < rows / 2) {
        for (x = 0; x++ < columns; Screen.PutCharAt(x, y + rows / 2, " .:-;!/>)|&IH%*#"[k & 15]))
        {
            for (i = k = r = 0; j = r * r - i * i - 2 + x / 35, i = 2 * r * i + y / 10, j * j + i * i < 11 && k++ < 111; r = j);
        }
        y++;
    }
}

int MandelbrotFractal(int k)
{
    srand(time(NULL));

    UpdateTerminalDimensions();
    TTerminalScreen Screen(columns, rows);
    DrawMandelbrotFractal(Screen, k);

    TPixels Pixels(&Screen);
    Pixels.Draw();
    Screen.PresentScreen();

    TPixels Scroller(&Screen, ScrolledText, columns + 5);

    float alpha = 0.0f, StepAlpha = 0.0f;
    float step = 0.1f;
    int Direction = 1;
    auto future = std::async(std::launch::async, GetLineFromCin);
    float PI2 = 2 * 3.1415;
    float PI = 3.1415;
    float s;
    float TranslateXStep = -1.7;
    size_t ScrolledTextLineWidth = ScrolledText.find('\n');
    if (ScrolledTextLineWidth == std::string::npos)
    {
        ScrolledTextLineWidth = ScrolledText.length();
    }

    while (true)
    {
        COORD coord;
        coord.X = 0;
        coord.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
        {
            auto line = future.get();

            // Set a new line. Subtle race condition between the previous line
            // and this. Some lines could be missed. To aleviate, you need an
            // io-only thread. I'll give an example of that as well.
            future = std::async(std::launch::async, GetLineFromCin);

            break;
        }
        if (UpdateTerminalDimensions())
        {
            Screen.Resize(columns, rows);
            DrawMandelbrotFractal(Screen, k);
            Pixels.Update(&Screen);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        alpha += step;
        if (alpha > PI2)
        {
            alpha -= PI2;
        }
        if (rand() % 100 < 60)
        {
            StepAlpha += 0.1f;
            if (StepAlpha > PI2)
            {
                StepAlpha -= PI2;
            }
            step = sin(StepAlpha) * 0.2f;
        }
        Pixels.Rotate(alpha * Direction);
        s = cos(alpha);
        if (fabs(s) < 0.3f) s = 0.3f;
        Pixels.Scale(s);
        Pixels.Draw();

        Scroller.Translate(TranslateXStep, 0.0f);
        if (fabs(Scroller.GetTranslateX()) > ScrolledTextLineWidth + columns + 5)
        {
            Scroller.SetTranslateX(columns/5);
            Scroller.SetSinusoidalBehavior(!Scroller.GetDoSinusoidalBehavior());
        }
        Scroller.Draw(false);

        Screen.PresentScreen();
    }

    return 1;
}

int DemoWnd()
{
    TTerminalScreen Screen;
    TDesktop pulpit(&Screen); // definicja obiektu pulpit
    TWindow gra(&Screen, 15, 7, 21, 6, '$', "Gra w chinczyka"); // definicja kilku okien
    TWindow kalkulator(&Screen, 2, 3, 14, 6, '@', "Kalkulator");
    TWindow edytor(&Screen, 7, 5, 18, 6, ':', "Edytor");
    // umieszczenie tych okien na pulpicie
    pulpit += &gra;
    pulpit += &kalkulator;
    pulpit += &edytor;
    TWindow zegar(&Screen, 4, 9, 18, 6, '%', "Zegar"); // wymyslamy jeszcze jedno okno
    pulpit += &zegar; // dodanie go do obecnego pulpitu
    std::cin.peek();
    return 0;
}

int main(int argc, char** argv)
{
    PlaySoundW(L"8-Bit Mayhem.wav", GetModuleHandle(NULL), SND_ASYNC | SND_LOOP);
    MandelbrotFractal(10);
    //DemoWnd();

    return 0;
}

std::string GetLineFromCin()
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}
