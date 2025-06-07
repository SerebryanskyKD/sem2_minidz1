#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <string>

static HWND hButton;
static HWND hLabel;
static bool isTimerRunning = false;
static int remainingSeconds = 0;

static void ShutdownPC() {
    system("shutdown /s /f /t 0");
}

static VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    remainingSeconds--;

    if (remainingSeconds <= 0) {
        KillTimer(hwnd, idEvent);
        isTimerRunning = false;
        SetWindowText(hButton, L"Выключить ПК");
        SetWindowText(hLabel, L"Компьютер выключается...");
        ShutdownPC();
    }
    else {
        std::wstring text = L"Отмена (" + std::to_wstring(remainingSeconds) + L" сек)";
        SetWindowText(hButton, text.c_str());
    }
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND:
        if ((HWND)lParam == hButton) {
            if (!isTimerRunning) {
                srand(static_cast<unsigned int>(time(NULL)));
                remainingSeconds = 10 + rand() % 51;

                SetWindowText(hLabel, L"Таймер запущен!");
                SetTimer(hwnd, 1, 1000, TimerProc);
                isTimerRunning = true;
            }
            else {
                KillTimer(hwnd, 1);
                isTimerRunning = false;
                SetWindowText(hButton, L"Выключить ПК");
                SetWindowText(hLabel, L"Таймер отменен");
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"ShutdownButtonClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        L"ShutdownButtonClass",
        L"Кнопка выключения ПК",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;

    hButton = CreateWindowW(
        L"BUTTON",
        L"Выключить ПК",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 50, 200, 40,
        hwnd,
        (HMENU)1,
        hInstance,
        NULL
    );

    hLabel = CreateWindowW(
        L"STATIC",
        L"Нажмите кнопку для запуска таймера",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        50, 100, 200, 30,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
