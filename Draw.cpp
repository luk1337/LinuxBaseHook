#include <iostream>
#include <vector>
#include <thread>
#include <stdlib.h>
#include <stdarg.h>
#include "Draw.h"
#include "Hooks.h"

void CDraw::InitFont(int size, const char* name) {
    font = g_pSurface->CreateFont();
    g_pSurface->SetFontGlyphSet(font, name, size, 0, 0, 0, 0x80);
}

int CDraw::WidthCalc(const char* input) {
    int wide = 0;
    int tall = 0;
    int iBufSize = 255;

    wchar_t* pszUnicode = new wchar_t [iBufSize];

    mbstowcs(pszUnicode, input, iBufSize);

    g_pSurface->GetTextSize(font, pszUnicode, wide, tall);

    delete [ ] pszUnicode;

    return wide;
}

std::wstring stringToWide(const std::string& text) {
    std::wstring wide(text.length(), L' ');
    std::copy(text.begin(), text.end(), wide.begin());

    return wide;
}

void CDraw::DrawString(bool center, int x, int y, int r, int g, int b, int a, const char *text, ...) {
    char szBuffer[255];

    if (!text )
        return;

    va_list va_args;
    va_start(va_args, text);
    vsprintf(szBuffer, text,  va_args);

    if (center)
        x -= WidthCalc(szBuffer) / 2;

    g_pSurface->DrawSetTextColor(r, g, b, a);
    g_pSurface->DrawSetTextFont(font);
    g_pSurface->DrawSetTextPos(x, y);

    std::wstring wide = stringToWide(std::string(szBuffer));
    g_pSurface->DrawPrintText (wide.c_str(), wide.length());
}


void CDraw::DrawOutlinedRect(int x, int y, int w, int h, int r, int g, int b, int a) {
    g_pSurface->DrawSetColor(r, g, b, a);
    g_pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}
