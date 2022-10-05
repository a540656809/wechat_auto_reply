#include "stdafx.h"
#include "CPublic.h"


//************************************************************
// ��������: HookAnyAddress
// ����˵��: Hook�����ַ
// ��    ��: dwHookAddr ��ҪHOOK�ĵ�ַ dwJmpAddress��ת�ĵ�ַ dwBackAddress ���صĵ�ַ
// �� �� ֵ: void 
//************************************************************
void HookAnyAddress(DWORD dwHookAddr, LPVOID dwJmpAddress)
{
	//��װ��ת����
	BYTE jmpCode[5] = { 0 };
	jmpCode[0] = 0xE9;

	//����ƫ��
	*(DWORD*)&jmpCode[1] = (DWORD)dwJmpAddress - dwHookAddr - 5;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	//д���Լ��Ĵ���
	memcpy((void*)dwHookAddr, jmpCode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID)dwHookAddr, 5, OldProtext, &OldProtext);
}


//************************************************************
// ��������: GetWeChatWinBase
// ����˵��: ��ȡWeChatWin��ַ
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
DWORD GetWeChatWinBase()
{
	return (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
}



//************************************************************
// ��������: UTF8ToUnicode
// ����˵��: ��UTF8����תΪUnicode(΢��Ĭ�ϱ���ΪUTF8)
// ��    ��: str ��Ҫת�����ַ���
// �� �� ֵ: wchar_t ���ص��ַ��� 
//************************************************************
wchar_t* UTF8ToUnicode(const char* str)
{
	int    textlen = 0;
	wchar_t* result;
	textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = (wchar_t*)malloc((textlen + 1) * sizeof(wchar_t));
	memset(result, 0, (textlen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);
	return    result;
}




wstring UTF8ToUnicode2(const char* str)
{
	int textlen = 0;
	wchar_t* result;
	textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = (wchar_t*)malloc((textlen + 1) * sizeof(wchar_t));
	memset(result, 0, (textlen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);

	wstring tempstr(result);
	free(result);
	result = NULL;
	return tempstr;
}

void DebugCode(LPVOID pAddress)
{
	char buff[40] = { 0 };
	sprintf_s(buff, "%p", pAddress);
	MessageBoxA(0, buff, "��ַ", 0);
}


char* UnicodeToANSI(const wchar_t* str)
{
	static char result[1024];
	int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, str, -1, result, len, NULL, NULL);
	result[len] = '\0';
	return result;
}


std::wstring get_utf16(const std::string& str, int codepage)
{
	if (str.empty()) return std::wstring();
	int sz = MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), 0, 0);
	std::wstring res(sz, 0);
	MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), &res[0], sz);
	return res;
}




// std:stringתUTF8
std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];    //һ��Ҫ��1����Ȼ�����β�� 
	ZeroMemory(pwBuf, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string strRet(pBuf);

	delete[]pwBuf;
	delete[]pBuf;
	pwBuf = NULL;
	pBuf = NULL;

	return strRet;
}


LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}


char* WCharToChar(wchar_t* pwChar)
{
	size_t len = wcslen(pwChar) + 1;
	size_t converted = 0;
	char* CStr = (char*)malloc(len * sizeof(char));

	wcstombs_s(&converted, CStr, len, pwChar, _TRUNCATE);
	return CStr;
}


// string to wstring
void StringToWstring(std::wstring& szDst, std::string str)
{
	std::string temp = str;
	int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, NULL, 0);
	wchar_t* wszUtf8 = new wchar_t[len + 1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, (LPWSTR)wszUtf8, len);
	szDst = wszUtf8;
	std::wstring r = wszUtf8;
	delete[] wszUtf8;
}

void Wchar_tToString(std::string& szDst, wchar_t* wchar)
{
	wchar_t* wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);//WideCharToMultiByte������
	char* psText;  // psTextΪchar*����ʱ���飬��Ϊ��ֵ��std::string���м����
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);//WideCharToMultiByte���ٴ�����
	szDst = psText;// std::string��ֵ
	delete[]psText;// psText�����
}


wstring wchart_arrayTowstring(wchar_t a[])
{
	wstring wstr = L"";
	int j = 0;
	while (a[j] != L'\0')
	{
		wstr += a[j];
		j++;
	}
	return wstr;
}



//************************************************************
// ��������: wstringToString
// ����˵��: ��wstringת��String
// ��    ��: wstr
// �� �� ֵ: string 
//************************************************************
std::string wstringToString(const std::wstring& wstr)
{
	LPCWSTR pwszSrc = wstr.c_str();
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
		return std::string("");

	char* pszDst = new char[nLen];
	if (!pszDst)
		return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	std::string str(pszDst);
	delete[] pszDst;
	pszDst = NULL;
	return str;
}

