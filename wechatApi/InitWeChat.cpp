#include "stdafx.h"
#include <strstream>
#include <iostream>
#include <WechatCall.h>
#include "resource.h"
#include <wechatApi.h>





//************************************************************
// 函数名称: IsWxVersionValid
// 函数说明: 检查微信版本是否匹配
// 时    间: 2019/6/30
// 参    数: void
// 返 回 值: BOOL
//************************************************************
BOOL IsWxVersionValid()
{
	DWORD wxBaseAddress = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
	const string wxVersoin = "3.2.1.154";

	WCHAR VersionFilePath[MAX_PATH];
	if (GetModuleFileName((HMODULE)wxBaseAddress, VersionFilePath, MAX_PATH) == 0)
	{
		return FALSE;
	}

	string asVer = "";
	VS_FIXEDFILEINFO* pVsInfo;
	unsigned int iFileInfoSize = sizeof(VS_FIXEDFILEINFO);
	int iVerInfoSize = GetFileVersionInfoSize(VersionFilePath, NULL);
	if (iVerInfoSize != 0) {
		char* pBuf = new char[iVerInfoSize];
		if (GetFileVersionInfo(VersionFilePath, 0, iVerInfoSize, pBuf)) {
			if (VerQueryValue(pBuf, TEXT("\\"), (void**)&pVsInfo, &iFileInfoSize)) {

				int s_major_ver = (pVsInfo->dwFileVersionMS >> 16) & 0x0000FFFF;

				int s_minor_ver = pVsInfo->dwFileVersionMS & 0x0000FFFF;

				int s_build_num = (pVsInfo->dwFileVersionLS >> 16) & 0x0000FFFF;

				int s_revision_num = pVsInfo->dwFileVersionLS & 0x0000FFFF;

				//把版本变成字符串
				strstream wxVer;
				wxVer << s_major_ver << "." << s_minor_ver << "." << s_build_num << "." << s_revision_num;
				wxVer >> asVer;
			}
		}
		delete[] pBuf;
	}

	//版本匹配
	if (asVer == wxVersoin)
	{
		return TRUE;
	}

	//版本不匹配
	return FALSE;
}


//************************************************************
// 函数名称: InitWindow
// 函数说明: 初始化窗口 
// 参    数: HMODULE hModule 句柄
// 返 回 值: void 
//************************************************************
void InitWindow(HMODULE hModule)
{
	//检查当前微信版本
	if (IsWxVersionValid())
	{
		////获取WeChatWin的基址
		//DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
		////检测微信是否登陆
		//DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset;
		//HOOK接收消息
		wchar_t apiKey[100];
		GetDlgItemText((HWND)hModule, IDC_EDIT1, apiKey, 100);
		std::string aimKey;
		Wchar_tToString(aimKey, apiKey);
		setTuLingApiKey(aimKey);

		if (IsDlgButtonChecked((HWND)hModule, IDC_CHECK1) == BST_CHECKED) {
			setAutoChat(TRUE);
			HookChatRecord();
		}
		else {
			setAutoChat(FALSE);
			UnHookChatRecord();
		}

		if (IsDlgButtonChecked((HWND)hModule, IDC_CHECK2) == BST_CHECKED) {
			//防撤回
			AntiRevoke();
		}
		else {
			//防撤回
			CancelAntiRevoke();
		}
	}
	else
	{
		MessageBoxA(NULL, "当前微信版本不匹配，请下载WeChat 3.2.1.154", "错误", MB_OK);
	}
}


void LogoutWeChat()
{
	DWORD dwBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCallAddress = dwBaseAddress + WxLogout;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)dwCallAddress, 0, NULL, 0);
	if (hThread != 0)
	{
		CloseHandle(hThread);
	}
}




//************************************************************
// 函数名称: CheckIsLogin
// 函数说明: 检查微信是否登陆
// 参    数: void
// 返 回 值: void
//************************************************************
void CheckIsLogin()
{
	//获取WeChatWin的基址
	DWORD  dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	while (true)
	{
		DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset;
		if (*(DWORD*)dwIsLogin != 0)
		{
			//查找登陆窗口句柄
			HWND hLogin = FindWindow(NULL, L"Login");
			if (hLogin == NULL)
			{
				OutputDebugStringA("未查找到Login窗口");
				return;
			}
			COPYDATASTRUCT login_msg;
			login_msg.dwData = WM_Login;
			login_msg.lpData = NULL;
			login_msg.cbData = 0;
			//发送消息给控制端
			SendMessage(hLogin, WM_COPYDATA, (WPARAM)hLogin, (LPARAM)&login_msg);
			break;
		}

		Sleep(500);
	}
}
