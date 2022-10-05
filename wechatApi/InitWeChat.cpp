#include "stdafx.h"
#include <strstream>
#include <iostream>
#include <WechatCall.h>
#include "resource.h"
#include <wechatApi.h>





//************************************************************
// ��������: IsWxVersionValid
// ����˵��: ���΢�Ű汾�Ƿ�ƥ��
// ʱ    ��: 2019/6/30
// ��    ��: void
// �� �� ֵ: BOOL
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

				//�Ѱ汾����ַ���
				strstream wxVer;
				wxVer << s_major_ver << "." << s_minor_ver << "." << s_build_num << "." << s_revision_num;
				wxVer >> asVer;
			}
		}
		delete[] pBuf;
	}

	//�汾ƥ��
	if (asVer == wxVersoin)
	{
		return TRUE;
	}

	//�汾��ƥ��
	return FALSE;
}


//************************************************************
// ��������: InitWindow
// ����˵��: ��ʼ������ 
// ��    ��: HMODULE hModule ���
// �� �� ֵ: void 
//************************************************************
void InitWindow(HMODULE hModule)
{
	//��鵱ǰ΢�Ű汾
	if (IsWxVersionValid())
	{
		////��ȡWeChatWin�Ļ�ַ
		//DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
		////���΢���Ƿ��½
		//DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset;
		//HOOK������Ϣ
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
			//������
			AntiRevoke();
		}
		else {
			//������
			CancelAntiRevoke();
		}
	}
	else
	{
		MessageBoxA(NULL, "��ǰ΢�Ű汾��ƥ�䣬������WeChat 3.2.1.154", "����", MB_OK);
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
// ��������: CheckIsLogin
// ����˵��: ���΢���Ƿ��½
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void CheckIsLogin()
{
	//��ȡWeChatWin�Ļ�ַ
	DWORD  dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	while (true)
	{
		DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset;
		if (*(DWORD*)dwIsLogin != 0)
		{
			//���ҵ�½���ھ��
			HWND hLogin = FindWindow(NULL, L"Login");
			if (hLogin == NULL)
			{
				OutputDebugStringA("δ���ҵ�Login����");
				return;
			}
			COPYDATASTRUCT login_msg;
			login_msg.dwData = WM_Login;
			login_msg.lpData = NULL;
			login_msg.cbData = 0;
			//������Ϣ�����ƶ�
			SendMessage(hLogin, WM_COPYDATA, (WPARAM)hLogin, (LPARAM)&login_msg);
			break;
		}

		Sleep(500);
	}
}
