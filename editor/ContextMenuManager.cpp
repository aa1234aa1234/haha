//
// Created by sw_303 on 2026-06-09.
//

#include "ContextMenuManager.h"
#include "ContextMenu.h"
#include <windows.h>

#include "UIContext.h"

ContextMenuManager* ContextMenuManager::instance = 0;

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
     return DefWindowProc(hwnd, msg, wParam, lParam);
}

ContextMenuManager::ContextMenuManager()
{

}



void ContextMenuManager::OpenContextMenu(ContextMenu& menu)
{
     HINSTANCE hInstance = GetModuleHandle(nullptr);
     WNDCLASS wc = {};
     wc.lpfnWndProc = WndProc;
     wc.hInstance = hInstance;
     wc.lpszClassName = "ContextMenu";
     RegisterClass(&wc);
     HWND hMenuWnd = CreateWindowEx(WS_EX_TOPMOST, TEXT("ContextMenu"), TEXT("rf"), WS_POPUPWINDOW, 100, 100, 200, 150, nullptr, nullptr, hInstance, nullptr);
     ShowWindow(hMenuWnd, SW_SHOW);
     UpdateWindow(hMenuWnd);
}

