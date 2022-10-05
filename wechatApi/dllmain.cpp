// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <stdio.h>
#include "resource.h"
#include <InitWeChat.h>
#define _AFXDLL

BOOL CALLBACK Dlgproc(
    HWND hwndDlg,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);
void db(HMODULE hModule);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        //启动线程来初始化界面
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)db, hModule, 0, NULL);
        break;
    }
    case DLL_THREAD_ATTACH:
    {
     
    }
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void db(HMODULE hModule) {
    DialogBox(hModule, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Dlgproc);
}

BOOL CALLBACK Dlgproc(
    HWND hwndDlg,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (uMsg)
    {
        // 窗口关闭消息
    case WM_CLOSE:
        EndDialog(hwndDlg, IDCANCEL);
        break;
        // 命令消息
    case WM_COMMAND:
        //低位字
        switch (LOWORD(wParam))
        {
            //点了生效按钮
        case IDC_BUTTON1:
            // 使用windows API来创建线程，std::thread 会卡死，原因不明。
            InitWindow((HMODULE)hwndDlg);
            break;
        }
    }
    /* 一定要返回 FALSE */
    return FALSE;
}
