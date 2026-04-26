#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ID_BUTTON_OCR 1
#define ID_TOGGLE_THEME 2

HWND hwndLabel;
bool esteModNoapte = false;
HBRUSH brushZi, brushNoapte;

void corecteazaPrefix(char *text)
{
    if (text[0] == 'B')
    {
        memmove(text, text + 1, strlen(text));
    }
}

bool esteNumarRomanesc(const char *text)
{
    int i = 0, len = strlen(text);
    if (len < 6 || len > 10)
        return false;

    if (isalpha(text[i]) && isalpha(text[i + 1]))
    {
        i += 2;
    }
    else
    {
        return false;
    }

    if (text[i] == ' ')
        i++;

    int cifre = 0;
    while (isdigit(text[i]))
    {
        i++;
        cifre++;
    }
    if (cifre < 2 || cifre > 3)
        return false;

    if (text[i] == ' ')
        i++;

    int litere = 0;
    while (isalpha(text[i]))
    {
        i++;
        litere++;
    }

    return (litere >= 2 && litere <= 3 && text[i] == '\0');
}

void pornesteOCR(HWND hwnd)
{
    OPENFILENAME ofn;
    char fisierImagine[MAX_PATH] = "";
    char comanda[512], buffer[1024], rezultat[1024] = "";
    FILE *f;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Imagini\0*.png;*.jpg;*.jpeg;*.bmp\0";
    ofn.lpstrFile = fisierImagine;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        // obtine ora locala
        SYSTEMTIME timp;
        GetLocalTime(&timp);

        // abordarea pentru zi/noapte
        if (timp.wHour >= 6 && timp.wHour < 18)
        {
            
            sprintf(comanda, "tesseract \"%s\" output -l eng --psm 7 >nul 2>nul", fisierImagine);
        }
        else
        {
        
            sprintf(comanda, "tesseract \"%s\" output -l eng --psm 6 >nul 2>nul", fisierImagine);
        }

        system(comanda);

        f = fopen("output.txt", "r");
        if (!f)
        {
            MessageBox(hwnd, "Eroare la deschiderea rezultatului OCR.", "Eroare", MB_ICONERROR);
            return;
        }

        fgets(buffer, sizeof(buffer), f);
        fclose(f);
        remove("output.txt");

        buffer[strcspn(buffer, "\r\n")] = 0;

        int j = 0;
        for (int i = 0; buffer[i]; i++)
        {
            if (!isspace(buffer[i]))
            {
                rezultat[j++] = buffer[i];
            }
        }
        rezultat[j] = '\0';

        corecteazaPrefix(rezultat);

        const char *status = esteNumarRomanesc(rezultat) ? "Numar romanesc valid!" : "Nu e numar valid!";
        char mesajAfisat[1152];
        snprintf(mesajAfisat, sizeof(mesajAfisat), "Text citit: %s\nStatus: %s", rezultat, status);
        SetWindowText(hwndLabel, mesajAfisat);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        // butoanele si label-ul
        CreateWindow("BUTTON", "Selecteaza imagine", WS_VISIBLE | WS_CHILD,
                     30, 40, 160, 30, hwnd, (HMENU)ID_BUTTON_OCR, NULL, NULL);

        CreateWindow("BUTTON", "Mod Zi/Noapte", WS_VISIBLE | WS_CHILD,
                     210, 40, 160, 30, hwnd, (HMENU)ID_TOGGLE_THEME, NULL, NULL);

        hwndLabel = CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD,
                                 30, 100, 340, 60, hwnd, NULL, NULL, NULL);

        // pensule pentru DARK MODE (optional)
        brushZi = CreateSolidBrush(RGB(255, 255, 255));  // Alb
        brushNoapte = CreateSolidBrush(RGB(30, 30, 30)); // Gri închis
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BUTTON_OCR)
        {
            pornesteOCR(hwnd);
        }
        else if (LOWORD(wParam) == ID_TOGGLE_THEME)
        {
            esteModNoapte = !esteModNoapte;
            InvalidateRect(hwnd, NULL, TRUE); // Forțează DARK/WHITE MODE
        }
        break;

    case WM_CTLCOLORSTATIC:
    case WM_CTLCOLORBTN:
    {
        HDC hdc = (HDC)wParam;
        SetBkMode(hdc, TRANSPARENT);
        if (esteModNoapte)
        {
            SetTextColor(hdc, RGB(200, 200, 200));
            return (INT_PTR)brushNoapte;
        }
        else
        {
            SetTextColor(hdc, RGB(0, 0, 0));
            return (INT_PTR)brushZi;
        }
    }

    case WM_ERASEBKGND:
    {
        HDC hdc = (HDC)wParam;
        RECT rc;
        GetClientRect(hwnd, &rc);
        FillRect(hdc, &rc, esteModNoapte ? brushNoapte : brushZi);
        return 1;
    }

    case WM_DESTROY:
        DeleteObject(brushZi);
        DeleteObject(brushNoapte);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    const char CLASS_NAME[] = "OCRWindow";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(CLASS_NAME, "Recunoastere Numar",
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             420, 240, NULL, NULL, hInstance, NULL);

    if (!hwnd)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
