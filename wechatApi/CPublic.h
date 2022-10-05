#pragma once
#include <string>
using namespace std;

void HookAnyAddress(DWORD dwHookAddr, LPVOID dwJmpAddress);		//HOOK任意地址

DWORD GetWeChatWinBase();		//获取WeChatWin基址

wchar_t* UTF8ToUnicode(const char* str);

wstring UTF8ToUnicode2(const char* str);

void DebugCode(LPVOID pAddress);

char* UnicodeToANSI(const wchar_t* str);

std::wstring get_utf16(const std::string& str, int codepage);

std::string string_To_UTF8(const std::string& str);

LPCWSTR stringToLPCWSTR(std::string orig);

std::string wstringToString(const std::wstring& wstr);

wstring wchart_arrayTowstring(wchar_t a[]);

void Wchar_tToString(std::string& szDst, wchar_t* wchar);

void StringToWstring(std::wstring& szDst, std::string str);

char* WCharToChar(wchar_t* pwChar);