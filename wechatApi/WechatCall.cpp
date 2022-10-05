#include "stdafx.h"
#include "CPublic.h"
#include <stdlib.h >
#include <vector>
#include <stdio.h>
#include <WINSOCK2.H>
#include <string>
#include <Shlwapi.h>
#include <atlconv.h>
#include <algorithm>

#include "shellapi.h"
#include <sstream>
#include <iomanip>
#include <strstream>
#include <map>
#include <iostream>
#include <fstream>


#include "HttpRequest.h"
#include <wechatApi.h>
#pragma comment(lib, "Version.lib")
#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib,"ws2_32.lib")
using namespace std;


vector<string> split(string& str, string sp) {
	vector<string> split;
	//string sp="age";
	int ex = 0;
	for (int i = 0; i < str.length(); i++) {
		//�Ƚ���ǰ������char�ַ��������ֱ����һ���ַ�
		if (str[i] != sp[0]) {
			continue;
		}
		//�����ʼ���������ô�ٱȽϷָ��ַ�������һ���ַ�
		//�Ƚ�ʱ��i�ǲ����ӵģ���ƫ���������Է�û����ƥ�˲���ȥ
		//++j��������һ��ֱ�ӱȽϵڶ�����ʼ����Ϊǰ���һ���Ѿ��Ƚ���
		int j = 1;
		for (j = 1; j < sp.length(); j++) {

			if (str[i + j] != sp[j]) {
				break;//��û�бȽ���ָ��ַ��Ͳ�ͬ�ˣ�����ֱ���˳����
			}
		}

		if (j == sp.length()) {

			split.push_back(str.substr(ex, i - ex));

			i = i + j;
			ex = i;
		}

	}
	//ʣ��ȫ������ȥ
	split.push_back(str.substr(ex, -1));
	return move(split);
}

//����1��JSON��
//����2��ĳ�������
//����ĳ���ֵ
string GetDataFromJson(string json, string data)
{
	string buff = "0";//δ�ҵ����� 0
	int indexname = json.find(data);//�ҵ�ĳ���λ��

	if (indexname > json.length())//δ�ҵ�����
	{
		return buff;
	}

	vector<string> vecstring = split(json, "\"");//�����ŷָ�
	for (int i = 0; i < vecstring.max_size(); i++)
	{
		if (data == vecstring[i])
		{

			buff = vecstring.at(i + 4);//ȡ����ĺ�4������������ȡ��һ��
			break;
		}
	}
	return buff;
}


void GetInformation()
{
	unique_ptr<PersonalInformation> info(new PersonalInformation);

	DWORD dwWeChatWin = GetWeChatWinBase();

	char tempcontent[0x300];
	//΢�ź�
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxCount));

	//�ж��Ƿ�Ϊ0 ��0˵��΢�ź�Ϊ��
	if (tempcontent[0] == 0)
	{
		wcscpy_s(info->wxcount, wcslen(L"NULL") + 1, L"NULL");
	}
	else
	{
		wcscpy_s(info->wxcount, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());
	}


	//΢��ID ������Ҫ��������΢�ź�  ��΢�ź���ָ�� ��΢�ź����ַ���
	memset(tempcontent, 0, 0x300);
	DWORD pWxid = dwWeChatWin + WxID;
	//�������С��6���ߴ���20 ˵������ط��Ǹ�ָ��
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxID));
	if (strlen(tempcontent) < 0x6 || strlen(tempcontent) > 0x14)
	{
		//˵�����µ�΢�ź� ΢��ID�õ�ַ����
		sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxID)));
	}
	else
	{
		sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxID));
	}
	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//Сͷ��
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxSmallHeader)));
	wcscpy_s(info->smallheader, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());



	//��ͷ��
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxBigHeader)));
	wcscpy_s(info->bigheader, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//����
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxNation));
	wcscpy_s(info->nation, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());

	//ʡ��
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxProvince));
	wcscpy_s(info->province, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//����
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxCity));
	wcscpy_s(info->city, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//�ֻ���
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxPhoneNumber));
	wcscpy_s(info->phonenumber, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());

	//�ǳ�
	memset(tempcontent, 0, 0x300);
	if (*(DWORD*)(dwWeChatWin + WxNickName + 0x14) == 0xF)
	{
		sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxNickName));
	}
	else
	{
		sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxNickName)));
	}

	wcscpy_s(info->nickname, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//����Ŀ¼
	swprintf_s(info->cachedir, L"%s", (wchar_t*)(*(DWORD*)(dwWeChatWin + WxCacheDir)));


	//��½�豸
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxDevice));
	wcscpy_s(info->device, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//�Ա�
	DWORD nSex = *(DWORD*)(dwWeChatWin + WxSex);
	if (nSex == 1)
	{
		wcscpy_s(info->wxsex, wcslen(L"��") + 1, L"��");
	}
	else if (nSex == 2)
	{
		wcscpy_s(info->wxsex, wcslen(L"Ů") + 1, L"Ů");
	}
	else
	{
		wcscpy_s(info->wxsex, wcslen(L"δ����") + 1, L"δ����");
	}


	HWND hInformation = FindWindow(NULL, L"Information");
	if (hInformation == NULL)
	{
		OutputDebugStringA("δ���ҵ�Information����");
		return;
	}
	COPYDATASTRUCT information_msg;
	information_msg.dwData = WM_GetInformation;
	information_msg.lpData = info.get();
	information_msg.cbData = sizeof(PersonalInformation);
	//������Ϣ�����ƶ�
	SendMessage(hInformation, WM_COPYDATA, (WPARAM)hInformation, (LPARAM)&information_msg);
}


//************************************************************
// ��������: AddWxUser
// ����˵��: ��Ӻ���
// ��    ��: wxid ΢��ID msg��Ӻ���ʱҪ���͵���Ϣ
// �� �� ֵ: void 
//************************************************************
void AddWxUser(wchar_t* wxid, wchar_t* msg)
{
	DWORD dwWeChatWinAddr = GetWeChatWinBase();
	DWORD dwParam1 = dwWeChatWinAddr + WxAddWxUserParam1;
	DWORD dwCall1 = dwWeChatWinAddr + WxAddWxUserCall1;
	DWORD dwCall2 = dwWeChatWinAddr + WxAddWxUserCall2;
	DWORD dwCall3 = dwWeChatWinAddr + WxAddWxUserCall3;
	DWORD dwCall4 = dwWeChatWinAddr + WxAddWxUserCall4;
	DWORD dwCall5 = dwWeChatWinAddr + WxAddWxUserCall5;

	GeneralStruct pWxid(wxid);
	GeneralStruct pMsg(msg);

	char* asmWxid = (char*)&pWxid.pstr;
	char* asmMsg = (char*)&pMsg.pstr;
	DWORD asmMsgText = (DWORD)pMsg.pstr;
	char buff3[0x100] = { 0 };
	char* buff = buff3;
	__asm
	{
		sub esp, 0x18;
		mov ecx, esp;
		push  dwParam1;
		call dwCall1;

		sub esp, 0x18;
		mov eax, buff;
		mov ecx, esp;
		push eax;
		call dwCall2;

		push 0x6;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		mov edi, msg;
		push edi;
		call dwCall3;


		push 0x2;
		sub esp, 0x14;
		mov ecx, esp;
		mov ebx, asmWxid;
		push ebx;
		call dwCall4;

		mov ecx, eax;
		call dwCall5;
	}
}



//************************************************************
// ��������: OpenUrl
// ����˵��: ��΢�������
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void OpenUrl(wchar_t* Url)
{
	GeneralStruct pUrl(Url);
	char* asmpUrl = (char*)&pUrl.pstr;
	DWORD dwWeChatWinAddr = GetWeChatWinBase();
	DWORD callAdd1 = dwWeChatWinAddr + WxOpenUrlCall1;
	DWORD callAdd2 = dwWeChatWinAddr + WxOpenUrlCall2;
	__asm {
		pushad
		sub esp, 0x14
		mov eax, asmpUrl
		mov ecx, esp
		push eax
		call callAdd1
		call callAdd2
		add esp, 0x14
		popad
	}
}



//************************************************************
// ��������: AntiRevoke
// ����˵��: ������
// ��    ��: void
// �� �� ֵ: void 
//************************************************************

//�����洢����ָ��
unsigned char backupCode[1] = { 0 };

void AntiRevoke()
{
	unsigned char fix[1] = { 0xEB };
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxAntiRevoke;
	//�޸Ĵ��������
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 1, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//Patch
	memcpy(backupCode, (LPVOID)dwPathcAddr, 1);
	//Patch
	memcpy((LPVOID)dwPathcAddr, fix, 1);
	//�ָ�����
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}

void CancelAntiRevoke()
{
	//0xE8Ϊ���ָ�� call
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxAntiRevoke;
	//�޸Ĵ��������
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 1, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//��ԭ��ԭָ��
	memcpy((LPVOID)dwPathcAddr, backupCode, 1);
	//�ָ�����
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
	//�޸ı���ָ��Ϊ��
	memset(backupCode, 0, 1);
}



BOOL isSendTuLing = FALSE;	//�Ƿ��Ѿ������˻�����
wchar_t tempwxid[50];	//���΢��ID


//���ص�ַ
DWORD RetkReciveMsgAddr = GetWeChatWinBase() + WxReciveMessage + 5;

//�����ǵ�call�ĵ�ַ
DWORD OverReciveMsgCallAddr = GetWeChatWinBase() + WxReciveMessageCall;


//************************************************************
// ��������: SendTextMessage
// ����˵��: �����ı���Ϣ
// ��    ��: wxid ΢��ID msg��Ϣ����
// �� �� ֵ: void 
//************************************************************
void SendTextMessage(wchar_t* wxid, wchar_t* msg)
{
	//�õ�������Ϣ��call�ĵ�ַ
	DWORD dwSendCallAddr = GetWeChatWinBase() + WxSendMessage;

	//��װ΢��ID/ȺID�Ľṹ��
	GeneralStruct id(wxid);
	//��Ϣ����
	GeneralStruct text(msg);

	//ȡ��΢��ID����Ϣ�ĵ�ַ
	char* pWxid = (char*)&id.pstr;
	char* pWxmsg = (char*)&text.pstr;

	char buff[0x81C] = { 0 };
	char buff2[0x81C] = { 0 };

	//����΢�ŷ�����Ϣcall
	__asm {
		push 0x1;
		lea edi, buff2;
		push edi;
		mov ebx, pWxmsg;
		push ebx;
		lea ecx, buff;
		mov edx, pWxid;
		call dwSendCallAddr;
		add esp, 0xC;
	}
}




//************************************************************
// ��������: GetNicknameByWxid
// ����˵��: ����΢��ID��ȡ�ǳ�
// ��    ��: wxid ΢��ID
// �� �� ֵ: wchar_t* �ǳ� 
//************************************************************
wchar_t* GetNicknameByWxid(wchar_t* userwxid)
{
	DWORD dwCall1 = GetWeChatWinBase() + WxGetUserInfoByWxidCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxGetUserInfoByWxidCall2;
	DWORD dwCall3 = GetWeChatWinBase() + WxGetUserInfoByWxidCall3;

	GeneralStruct pWxid(userwxid);
	char* asmWxid = (char*)&pWxid.pstr;
	char buff[0x3D8] = { 0 };
	DWORD userData = 0;		//�û����ݵĵ�ַ
	__asm
	{
		pushad;
		lea edi, buff;
		push edi;
		sub esp, 0x14;
		mov eax, asmWxid;
		mov ecx, esp;
		push eax;
		call dwCall1;
		call dwCall2;
		call dwCall3;
		mov userData, edi;
		popad;
	}

	wchar_t tempnickname[100] = { 0 };
	DWORD wxNickAdd = userData + 0x64;	//�ǳ�
	swprintf_s(tempnickname, L"%s", (wchar_t*)(*((LPVOID*)wxNickAdd)));

	wchar_t* nickname = new wchar_t[100]{ 0 };
	memcpy(nickname, tempnickname, wcslen(tempnickname) * 2);
	return nickname;
}

//�������к����б��map����
map<wstring, wstring> g_userinfolist;

//************************************************************
// ��������: GetNickNameByWxid
// ����˵��: ���ݺ����б��΢��ID/ȺID����ȡ΢���ǳ�/Ⱥ�ǳ�
// ��    ��: nickname �ǳ�
// �� �� ֵ: void 
//************************************************************
wstring GetNickNameByWxid(wstring wxid)
{
	map<wstring, wstring>::iterator it;
	it = g_userinfolist.find(wxid);
	if (it != g_userinfolist.end())
	{
		return it->second;
	}
	else
	{
		return L"NULL";
	}
}

//�Ƽ����б�
wstring g_referencenumber[11] =
{
	L"fmessage",L"qqmail",L"medianote",L"qmessage",L"newsapp",L"filehelper",
	L"weixin", L"tmessage", L"mphelper",L"gh_7aac992b0363", L"qqsafe"
};

//************************************************************
// ��������: ReceiveMsgProc
// ����˵��: ������Ϣ���̻߳ص�����
// ��    ��: Context ������
// �� �� ֵ: void 
//************************************************************
void DealWithMsg(LPVOID Context)
{
	try
	{
		ChatMessageData* msg = (ChatMessageData*)Context;

		for (int i = 0; i < 11; i++)
		{
			wstring aim = msg->wxid;
			int c = aim.compare(g_referencenumber[i]);
			if (c == 0)
			{
				return; 
			}
		}
		BOOL isTextMsg = FALSE;//�Ƿ���������Ϣ
		BOOL isFriendMsg = FALSE;		//�Ƿ��Ǻ�����Ϣ
		BOOL isImageMessage = FALSE;	//�Ƿ���ͼƬ��Ϣ
		BOOL isRadioMessage = FALSE;	//�Ƿ�����Ƶ��Ϣ
		BOOL isVoiceMessage = FALSE;	//�Ƿ���������Ϣ
		BOOL isBusinessCardMessage = FALSE;	//�Ƿ�����Ƭ��Ϣ
		BOOL isExpressionMessage = FALSE;	//�Ƿ�����Ƭ��Ϣ
		BOOL isLocationMessage = FALSE;	//�Ƿ���λ����Ϣ
		BOOL isSystemMessage = FALSE;	//�Ƿ���ϵͳ������Ϣ
		BOOL isPos_File_Money_XmlLink = FALSE;			//�Ƿ�λ�� �ļ� ת�˺�������Ϣ
		BOOL isFriendRequestMessage = FALSE;	//�Ƿ��Ǻ���������Ϣ
		BOOL isOther = FALSE;	//�Ƿ���������Ϣ


		switch (msg->dwtype)
		{
		case 0x01:
			isTextMsg = TRUE;
			memcpy(msg->sztype, L"����", sizeof(L"����"));
			break;
		case 0x03:
			memcpy(msg->sztype, L"ͼƬ", sizeof(L"ͼƬ"));
			isImageMessage = TRUE;
			break;
		case 0x22:
			memcpy(msg->sztype, L"����", sizeof(L"����"));
			isVoiceMessage = TRUE;
			break;
		case 0x25:
			memcpy(msg->sztype, L"����ȷ��", sizeof(L"����ȷ��"));
			isFriendRequestMessage = TRUE;
			break;
		case 0x28:
			memcpy(msg->sztype, L"POSSIBLEFRIEND_MSG", sizeof(L"POSSIBLEFRIEND_MSG"));
			isOther = TRUE;
			break;
		case 0x2A:
			memcpy(msg->sztype, L"��Ƭ", sizeof(L"��Ƭ"));
			isBusinessCardMessage = TRUE;
			break;
		case 0x2B:
			memcpy(msg->sztype, L"��Ƶ", sizeof(L"��Ƶ"));
			isRadioMessage = TRUE;
			break;
		case 0x2F:
			//ʯͷ������
			memcpy(msg->sztype, L"����", sizeof(L"����"));
			isExpressionMessage = TRUE;
			break;
		case 0x30:
			memcpy(msg->sztype, L"λ��", sizeof(L"λ��"));
			isLocationMessage = TRUE;
			break;
		case 0x31:
			//����ʵʱλ��
			//�ļ�
			//ת��
			//����
			//�տ�
			memcpy(msg->sztype, L"����ʵʱλ�á��ļ���ת�ˡ�����", sizeof(L"����ʵʱλ�á��ļ���ת�ˡ�����"));
			isPos_File_Money_XmlLink = TRUE;
			break;
		case 0x32:
			memcpy(msg->sztype, L"VOIPMSG", sizeof(L"VOIPMSG"));
			isOther = TRUE;
			break;
		case 0x33:
			memcpy(msg->sztype, L"΢�ų�ʼ��", sizeof(L"΢�ų�ʼ��"));
			isOther = TRUE;
			break;
		case 0x34:
			memcpy(msg->sztype, L"VOIPNOTIFY", sizeof(L"VOIPNOTIFY"));
			isOther = TRUE;
			break;
		case 0x35:
			memcpy(msg->sztype, L"VOIPINVITE", sizeof(L"VOIPINVITE"));
			isOther = TRUE;
			break;
		case 0x3E:
			memcpy(msg->sztype, L"С��Ƶ", sizeof(L"С��Ƶ"));
			isRadioMessage = TRUE;
			break;
		case 0x270F:
			memcpy(msg->sztype, L"SYSNOTICE", sizeof(L"SYSNOTICE"));
			isOther = TRUE;
			break;
		case 0x2710:
			//ϵͳ��Ϣ
			//���
			memcpy(msg->sztype, L"ϵͳ��Ϣ", sizeof(L"ϵͳ��Ϣ"));
			isSystemMessage = TRUE;
			break;
		case 0x2712:
			//������Ϣ
			memcpy(msg->sztype, L"������Ϣ", sizeof(L"������Ϣ"));
			break;
		default:
			break;
		}

		
		//����΢��ID�ж��Ƿ��Ǻ�����Ϣ
		wstring wxid_wstr = msg->wxid;
		if (wxid_wstr.find(L"@im.chatroom") != wxid_wstr.npos)
		{
			memcpy(msg->source, L"��ҵ΢��Ⱥ��Ϣ", sizeof(L"��ҵ΢��Ⱥ��Ϣ"));
		}
		else if (wxid_wstr.find(L"@chatroom") != wxid_wstr.npos)
		{
			memcpy(msg->source, L"Ⱥ��Ϣ", sizeof(L"Ⱥ��Ϣ"));
		}
		else
		{
			memcpy(msg->source, L"������Ϣ", sizeof(L"������Ϣ"));
			isFriendMsg = TRUE;
			memcpy(msg->sendername, L"NULL", sizeof(L"NULL"));
		}

		//int flag = strcmp(WCharToChar(msg->wxid), "filehelper");
		//���ﴦ���Զ�����  ������ ���������������� ��ָ��ĳ�� Ⱥ��
		if (isFriendMsg == TRUE && getAutoChat() == TRUE
			 && getTuLingApiKey().size() > 0)
		{
			std::string szDest;
			Wchar_tToString(szDest, msg->content);
			std::string content = szDest;
			std::string data = "{\"reqType\":0,\"perception\":{\"inputText\":{\"text\":\""
				+ string_To_UTF8(content) + "\"},\"inputImage\":{\"url\":\"\"},\"inputMedia\":{\"url\":\"\"},\"selfInfo\":{\"location\":{\"city\":\"\",\"province\":\"\",\"street\":\"\"}}},\"userInfo\":{\"apiKey\":\"" 
				+ getTuLingApiKey() + "\",\"userId\":\"\"}}";
			std::string result = HttpsWebRequestPost(Tu_Ling_Domain, Tu_Ling_Url, data);
			result = GetDataFromJson(result, "values");
			std::wstring wdest;
			StringToWstring(wdest, result);
			swprintf_s(msg->content, L"%s", wdest.c_str());
			SendTextMessage((wchar_t*)msg->wxid, msg->content);
		}

		delete msg;
	}
	catch (...)
	{
		OutputDebugStringA("�����¼���쳣��");
	}
}







//************************************************************
// ��������: SendMessage
// ����˵��: �����յ�����Ϣ���͸��ͻ���
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void __stdcall SendWxMessage(DWORD r_eax)
{
	if (IsBadReadPtr((void*)r_eax, 4) || IsBadReadPtr((void*)(r_eax + MsgTypeOffset), 4) || IsBadReadPtr((void*)(r_eax + MsgContentOffset), 4) || IsBadReadPtr((void*)(r_eax + WxidOffset), 4) || IsBadReadPtr((void*)(r_eax + GroupMsgSenderOffset), 4))
	{
		return;
	}
	try
	{
		ChatMessageData* msg = new ChatMessageData;
		//ȡ����Ϣ����
		msg->dwtype = *((DWORD*)(r_eax + MsgTypeOffset));
		//ȡ����Ϣ����
		LPVOID pContent = *((LPVOID*)(r_eax + MsgContentOffset));
		swprintf_s(msg->content, L"%s", (wchar_t*)pContent);

		//ȡ��΢��ID/ȺID
		LPVOID pWxid = *((LPVOID*)(r_eax + WxidOffset));
		swprintf_s(msg->wxid, L"%s", (wchar_t*)pWxid);

		if (StrStrW(msg->wxid, L"gh_"))
		{
			return;
		}

		//ȡ����Ϣ������
		LPVOID pSender = *((LPVOID*)(r_eax + GroupMsgSenderOffset));
		swprintf_s(msg->sender, L"%s", (wchar_t*)pSender);
		//ȡ����Ϣ��Դ
		LPVOID pSource = *((LPVOID*)(r_eax + MsgSourceOffset));
		swprintf_s(msg->source, L"%s", (wchar_t*)pSource);

		//�����̴߳�����Ϣ
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DealWithMsg, msg, 0, NULL);
		CloseHandle(hThread);
	}
	catch (...)
	{
		OutputDebugStringA("������Ϣ�쳣��....");
	}


}

//************************************************************
// ��������: RecieveMesage
// ����˵��: ������Ϣ
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
__declspec(naked) void RecieveWxMesage()
{
	//�����ֳ�
	__asm
	{
		pushad;
		push eax;
		call SendWxMessage;
		popad;
		//���ñ����ǵ�call
		call OverReciveMsgCallAddr;
		//��ת�����ص�ַ
		jmp RetkReciveMsgAddr;
	}
}

__declspec(naked) void CancelRecieveWxMesage()
{
	//�����ֳ�
	__asm
	{
		//���ñ����ǵ�call
		call OverReciveMsgCallAddr;
		//��ת�����ص�ַ
		jmp RetkReciveMsgAddr;
	}
}

//************************************************************
// ��������: HookChatRecord
// ����˵��: HOOK�����¼
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void HookChatRecord()
{
	HookAnyAddress(GetWeChatWinBase() + WxReciveMessage, RecieveWxMesage);
}

void UnHookChatRecord()
{
	HookAnyAddress(GetWeChatWinBase() + WxReciveMessage, CancelRecieveWxMesage);
}

//************************************************************
// ��������: GetMsgByAddress
// ����˵��: �ӵ�ַ�л�ȡ��Ϣ����
// ��    ��: DWORD memAddress  Ŀ���ַ
// �� �� ֵ: LPCWSTR	��Ϣ����
//************************************************************
std::wstring GetMsgByAddress(DWORD memAddress)
{
	wstring tmp;
	DWORD msgLength = *(DWORD*)(memAddress + 4);
	if (msgLength > 0) {
		WCHAR* msg = new WCHAR[msgLength + 1]{ 0 };
		wmemcpy_s(msg, msgLength + 1, (WCHAR*)(*(DWORD*)memAddress), msgLength + 1);
		tmp = msg;
		delete[]msg;
	}
	return  tmp;
}


DWORD overWritedCallAdd = GetWeChatWinBase() + WxFriendListCall;

DWORD jumBackAddress = GetWeChatWinBase() + WxFriendList + 5;



//************************************************************
// ��������: ReSendUser
// ����˵��: �ٴη��ͺ�����Ϣ
// ��    ��: user
// �� �� ֵ: void 
//************************************************************
void ReSendUser(UserListInfo* user)
{
	HWND hWnd = NULL;
	while (true)
	{
		//���͵����ƶ�
		hWnd = FindWindow(NULL, TEXT("΢������"));
		if (hWnd == NULL)
		{
			Sleep(200);
			continue;
		}
		break;
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//����һ����ֵ, ������������־��
	userinfo.cbData = sizeof(UserListInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfo.lpData = user;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
	delete user;
}

//************************************************************
// ��������: SendUserListInfo
// ����˵��: ���ͺ����б�
// ��    ��: r_esi �����б����ڵ�����ָ��
// �� �� ֵ: void 
//************************************************************
void __stdcall SendUserListInfo(DWORD r_esi)
{
	//����΢�źš�Ⱥ��
	wstring wxid = GetMsgByAddress(r_esi + 0x8);
	wstring nickname = GetMsgByAddress(r_esi + 0x64);

	//�����б�ȥ��
	map<wstring, wstring>::iterator it;
	it = g_userinfolist.find(wxid);
	//�������ֵ������end() ˵���ҵ��� ֱ�ӷ��ط�ֹ�ظ�
	if (it != g_userinfolist.end())
	{
		return;
	}
	//���û���ҵ� ����뵽����
	g_userinfolist.insert(make_pair(wxid, nickname));

	//�ų��Ƽ����б�
	for (int i = 0; i < 11; i++)
	{
		if (g_referencenumber[i] == wxid)
		{
			return;
		}
	}


	unique_ptr<UserListInfo> user(new UserListInfo);

	LPVOID pUserWxid = *((LPVOID*)(r_esi + 0x8));		//΢��ID
	LPVOID pUserNumber = *((LPVOID*)(r_esi + 0x1C));	//΢�ź�
	LPVOID pUserNick = *((LPVOID*)(r_esi + 0x64));		//�ǳ�
	LPVOID pUserReMark = *((LPVOID*)(r_esi + 0x50));	//��ע

	swprintf_s(user->UserId, L"%s", (wchar_t*)pUserWxid);
	swprintf_s(user->UserNumber, L"%s", (wchar_t*)pUserNumber);
	swprintf_s(user->UserNickName, L"%s", (wchar_t*)pUserNick);
	swprintf_s(user->UserRemark, L"%s", (wchar_t*)pUserReMark);


	//���͵����ƶ�
	HWND hWnd = FindWindow(NULL, TEXT("΢������"));
	if (hWnd == NULL)
	{
		UserListInfo* outuser = new UserListInfo;

		swprintf_s(outuser->UserId, L"%s", (wchar_t*)pUserWxid);
		swprintf_s(outuser->UserNumber, L"%s", (wchar_t*)pUserNumber);
		swprintf_s(outuser->UserNickName, L"%s", (wchar_t*)pUserNick);
		swprintf_s(outuser->UserRemark, L"%s", (wchar_t*)pUserReMark);


		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReSendUser, outuser, 0, NULL);
		CloseHandle(hThread);
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//����һ����ֵ, ������������־��
	userinfo.cbData = sizeof(UserListInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfo.lpData = user.get();// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
}


//************************************************************
// ��������: GetUserListInfo
// ����˵��: ��ȡ�û���Ϣ
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
__declspec(naked) void GetUserListInfo()
{
	__asm
	{
		pushad;
		push esi;
		call SendUserListInfo;
		popad;

		//���䱻���ǵĴ���
		call overWritedCallAdd;

		//���ر�HOOKָ�����һ��ָ��
		jmp jumBackAddress
	}
}

//************************************************************
// ��������: HookGetFriendList
// ����˵��: HOOK��ȡ�����б��call 

// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void HookGetFriendList()
{
	HookAnyAddress(GetWeChatWinBase() + WxFriendList, GetUserListInfo);
}




//************************************************************
// ��������: SendFileMessage
// ����˵��: �����ļ���Ϣ
// ��    ��: wxid ΢��ID filepath �ļ�·��
// �� �� ֵ: void 
//************************************************************
void SendFileMessage(wchar_t* wxid, wchar_t* filepath)
{
	//������Ҫ�ĵ�ַ
	DWORD dwBase = GetWeChatWinBase();
	DWORD dwCall1 = dwBase + WxFileMessage1;
	DWORD dwCall2 = dwBase + WxFileMessage2;
	DWORD dwCall3 = dwBase + WxFileMessage3;	//�������
	DWORD dwCall4 = dwBase + WxFileMessage4;	//������Ϣ
	DWORD dwParams = dwBase + WxFileMessageParam;

	char buff[0x528] = { 0 };

	//������Ҫ������
	GeneralStruct wxidStruct(wxid);
	GeneralStruct filePathStruct(filepath);

	//ȡ����Ҫ�����ݵĵ�ַ
	char* pFilePath = (char*)&filePathStruct.pstr;
	char* pWxid = (char*)&wxidStruct.pstr;



	__asm {
		pushad;
		sub esp, 0x14;
		lea eax, buff;
		mov ecx, esp;
		push eax;
		call dwCall2;

		push 0;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		push dwParams;
		call dwCall1;

		sub esp, 0x14;
		mov ecx, esp;
		mov ebx, pFilePath;
		push ebx;
		call dwCall2;

		sub esp, 0x14;
		mov eax, pWxid;
		mov ecx, esp;
		push eax;
		call dwCall2;

		lea eax, buff;
		push eax;
		call dwCall3;

		mov ecx, eax;
		call dwCall4;
		popad;
	}
}



//************************************************************
// ��������: SendImageMessage
// ����˵��: ����ͼƬ��Ϣ
// ��    ��: wxid ΢��ID filepath ͼƬ·��
// �� �� ֵ: void 
//************************************************************
void SendImageMessage(wchar_t* wxid, wchar_t* filepath)
{
	//��װ΢��ID�����ݽṹ
	GeneralStruct imagewxid(wxid);
	//��װ�ļ�·�������ݽṹ
	GeneralStruct imagefilepath(filepath);
	char buff[0x528] = { 0 };
	char buff2[0x60] = { 0 };


	DWORD dwCall3 = GetWeChatWinBase() + WxSendImageCall3;
	DWORD dwCall1 = GetWeChatWinBase() + WxSendImageCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxSendImageCall2;


	//΢�ŷ���ͼƬ������GidCreateBimapFileCM ֮��ͼƬһֱ��ռ�� �޷�ɾ�� patch������Ĵ���
	unsigned char oldcode[5] = { 0 };
	unsigned char fix[5] = { 0x31,0xC0,0x90,0x90,0x90 };
	DWORD dwPathcAddr = GetWeChatWinBase() + WxPatchAddr;
	//�޸Ĵ��������
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 5, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//�ȱ���ԭ��ָ��
	memcpy(oldcode, (LPVOID)dwPathcAddr, 5);
	//��Patch��
	memcpy((LPVOID)dwPathcAddr, fix, 5);


	__asm
	{
		pushad;
		sub esp, 0x14;
		lea eax, buff2;
		mov ecx, esp;
		push eax;
		call dwCall3;
		lea ebx, imagefilepath;
		push ebx;
		lea eax, imagewxid;
		push eax;
		lea eax, buff;
		push eax;
		call dwCall1;
		mov ecx, eax;
		call dwCall2;
		popad;
	}
	//������֮��ָ�
	memcpy((LPVOID)dwPathcAddr, oldcode, 5);
	//�ָ�����
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}


//************************************************************
// ��������: WxDeleteUser
// ����˵��: ɾ������
// ��    ��: wxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void DeleteUser(wchar_t* wxid)
{
	DWORD dwBaseAddress = GetWeChatWinBase();
	//��������
	GeneralStruct structWxid(wxid);
	DWORD* asmMsg = (DWORD*)&structWxid.pstr;
	DWORD dwCallAddr = dwBaseAddress + WxDeleteUser;

	__asm
	{
		mov ecx, 0;
		push ecx;
		mov esi, asmMsg;
		push esi;
		call  dwCallAddr;
	}
}


//************************************************************
// ��������: SendXmlCard
// ����˵��: ����XML��Ƭ
// ��    ��: RecverWxid ������΢��ID SendWxidҪ���͵�΢��ID NickName΢���ǳ�
// �� �� ֵ: void 
//************************************************************
void SendXmlCard(wchar_t* RecverWxid, wchar_t* SendWxid, wchar_t* NickName)
{
	wchar_t xml[0x2000] = { 0 };
	swprintf_s(xml, L"<?xml version=\"1.0\"?><msg bigheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/0\" smallheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/132\" username=\"%s\" nickname=\"%s\" fullpy=\"?\" shortpy=\"\" alias=\"%s\" imagestatus=\"3\" scene=\"17\" province=\"����\" city=\"�й�\" sign=\"\" sex=\"2\" certflag=\"0\" certinfo=\"\" brandIconUrl=\"\" brandHomeUrl=\"\" brandSubscriptConfigUrl= \"\" brandFlags=\"0\" regionCode=\"CN_BeiJing_BeiJing\" />", SendWxid, NickName, SendWxid);
	GeneralStruct pWxid(RecverWxid);
	GeneralStruct pXml(xml);


	char* asmWxid = (char*)&pWxid.pstr;
	char* asmXml = (char*)&pXml.pstr;
	char buff[0x20C] = { 0 };
	DWORD callAdd = GetWeChatWinBase() + WxSendXmlCard;


	__asm {
		mov eax, asmXml
		push 0x2A
		mov edx, asmWxid
		push 0x0
		push eax
		lea ecx, buff
		call callAdd
		add esp, 0xC
	}
}

//************************************************************
// ��������: SetWxRoomAnnouncement
// ����˵��: ����Ⱥ����
// ��    ��: chartoomwxid ȺID Announcement Ⱥ����
// �� �� ֵ: void 
//************************************************************
void SetWxRoomAnnouncement(wchar_t* chatroomwxid, wchar_t* Announcement)
{
	//��ȡWeChatWin�Ļ�ַ
	DWORD callAdrress = GetWeChatWinBase() + WxSetRoomAnnouncement;
	//��װ����
	CHAR bufferA[0xD0] = { 0 };
	DWORD* bufA = (DWORD*)&bufferA;

	CHAR buffer[0xD0] = { 0 };
	DWORD* buf = (DWORD*)&buffer;

	buf[0] = (DWORD)chatroomwxid;
	buf[1] = wcslen(chatroomwxid);
	buf[2] = wcslen(chatroomwxid) * 2;
	buf[3] = 0;
	buf[4] = 0;

	buf[0 + 5] = (DWORD)Announcement;
	buf[1 + 5] = wcslen(Announcement);
	buf[2 + 5] = wcslen(Announcement) * 2;
	buf[3 + 5] = 0;
	buf[4 + 5] = 0;

	bufA[0] = (DWORD)&buffer;
	bufA[1] = bufA[0] + 0x60;
	bufA[2] = bufA[0] + 0x60;

	DWORD r_esp = 0;
	__asm
	{
		//�����ջ�Ĵ���
		mov r_esp, esp;
		lea eax, bufferA;
		push eax;
		call callAdrress;

		//�ָ���ջ�Ĵ���
		mov eax, r_esp;
		mov esp, eax;
	}
}



//************************************************************
// ��������: QuitChatRoom
// ����˵��: �˳�Ⱥ��
// ��    ��: chartoomwxid ȺID 
// �� �� ֵ: void 
//************************************************************
void QuitChatRoom(wchar_t* chatroomwxid)
{
	DWORD dwBaseAddress = GetWeChatWinBase();
	DWORD dwCallAddr = dwBaseAddress + WxQuitChatRoom;

	//��������
	GeneralStruct structWxid(chatroomwxid);
	DWORD* asmMsg = (DWORD*)&structWxid.pstr;

	__asm
	{
		mov ebx, asmMsg;
		push ebx;
		call dwCallAddr;
	}
}


//************************************************************
// ��������: AddGroupMember
// ����˵��: ���Ⱥ��Ա
// ��    ��: chartoomwxid ȺID  wxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void AddGroupMember(wchar_t* chatroomwxid, wchar_t* wxid)
{
	DWORD dwBase = GetWeChatWinBase();
	DWORD dwCallAddr1 = dwBase + WxAddGroupMemberCall1;
	DWORD dwCallAddr2 = dwBase + WxAddGroupMemberCall2;
	DWORD dwCallAddr3 = dwBase + WxAddGroupMemberCall3;
	DWORD dwCallAddr4 = dwBase + WxAddGroupMemberCall4;

	DWORD dwParam = dwBase + WxAddGroupMemberParam1;
	DWORD dwParam2 = dwBase + WxAddGroupMemberParam2;

	//������Ҫ������
	GeneralStruct wxidStruct(wxid);
	RoomIdStruct chatroomStruct = { 0 };
	chatroomStruct.str = chatroomwxid;
	chatroomStruct.strLen = wcslen(chatroomwxid) * 2;
	chatroomStruct.maxLen = wcslen(chatroomwxid) * 4;

	char wxidBuff[0xC] = { 0 };
	char tempWxid[0x14] = { 0 };
	char tempBuff[0x14] = { 0 };

	char* pWxid = (char*)&wxidStruct.pstr;
	char* pChatRoom = (char*)&chatroomStruct.fill2;

	__asm {
		pushad;
		lea esi, wxidBuff;
		mov ecx, esi;
		mov eax, pWxid;
		push eax;
		call dwCallAddr1;

		push 0;
		push dwParam;
		lea ecx, tempWxid;
		call dwCallAddr2;

		sub esp, 0x14;
		mov ecx, pChatRoom;
		mov eax, esp;
		push eax;
		call dwCallAddr3;

		push esi;
		mov ecx, dwParam2;
		call dwCallAddr4;
		popad;
	}
}


//************************************************************
// ��������: GetUserInfoByWxid
// ����˵��: ͨ��΢��ID��ȡ�û���Ϣ
// ��    ��: userwxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void GetUserInfoByWxid(wchar_t* userwxid)
{
	DWORD WechatBase = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	DWORD dwCall1 = WechatBase + WxGetUserInfoWithNoNetworkCall1;
	DWORD dwCall2 = WechatBase + WxGetUserInfoWithNoNetworkCall2;
	DWORD dwCall3 = WechatBase + WxGetUserInfoWithNoNetworkCall3;

	char buff[0x508] = { 0 };
	char* asmHeadBuff = buff;
	char* asmBuff = &buff[0x18];

	GeneralStruct pWxid(userwxid);
	char* asmWxid = (char*)&pWxid.pstr;

	__asm
	{
		pushad;
		mov edi, asmWxid;		//΢��ID�ṹ��	
		mov eax, asmBuff;		//������
		push eax;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		mov dword ptr ds : [ecx] , 0x0;
		mov dword ptr ds : [ecx + 0x4] , 0x0;
		mov dword ptr ds : [ecx + 0x8] , 0x0;
		mov dword ptr ds : [ecx + 0xC] , 0x0;
		mov dword ptr ds : [ecx + 0x10] , 0x0;
		push dword ptr ds : [edi] ;	//΢��ID
		call dwCall1;				//call1
		call dwCall2;				//call2
		mov eax, asmHeadBuff;
		push eax;
		mov ecx, asmBuff;
		call dwCall3;
		popad
	}



	LPVOID lpWxid = *((LPVOID*)((DWORD)buff + 0x20));				//΢��ID
	LPVOID lpWxcount = *((LPVOID*)((DWORD)buff + 0x34));			//΢���˺�
	LPVOID lpNickName = *((LPVOID*)((DWORD)buff + 0x7C));			//�ǳ�




	//��װ�ṹ��
	UserInfo* userinfo = new UserInfo;
	swprintf_s(userinfo->UserId, L"%s", (wchar_t*)lpWxid);
	swprintf_s(userinfo->UserNickName, L"%s", (wchar_t*)lpNickName);
	swprintf_s(userinfo->UserNumber, L"%s", (wchar_t*)lpWxcount);



	//���͵��ͻ���
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		OutputDebugStringA("δ���ҵ�ChatRoomMember����");
		return;
	}


	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembers;//����һ����ֵ, ������������־��
	userinfodata.cbData = sizeof(UserInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfodata.lpData = userinfo;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);

	delete userinfo;

}


//************************************************************
// ��������: ShowChatRoomUser
// ����˵��: ��ʾȺ��Ա
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void ShowChatRoomUser(wchar_t* chatroomwxid)
{
	//׼��������
	DWORD dwWxidArr = 0;	//����΢��ID���ݵĵ�ַ
	char buff[0x164] = { 0 };
	char userListBuff[0x174] = { 0 };
	//��������
	GeneralStruct pWxid(chatroomwxid);
	char* asmWxid = (char*)&pWxid.pstr;

	//����call
	DWORD dwCall1 = GetWeChatWinBase() + WxGetRoomUserWxidCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxGetRoomUserWxidCall2;
	DWORD dwCall3 = GetWeChatWinBase() + WxGetRoomUserWxidCall3;
	DWORD dwCall4 = GetWeChatWinBase() + WxGetRoomUserWxidCall4;

	//��ȡȺ��Ա
	__asm
	{
		lea ecx, buff[16];
		call dwCall1;
		lea eax, buff[16];
		push eax;
		mov ebx, asmWxid;
		push ebx;
		call dwCall2;
		mov ecx, eax;
		call dwCall3;
		lea eax, buff;
		push eax;
		lea ecx, buff[16];
		call dwCall4;
		mov dwWxidArr, eax;
	}

	//�õ�΢��ID
	wchar_t test[0x100] = { 0 };
	wchar_t tempWxid[0x100] = { 0 };
	char tempWxidA[0x100] = { 0 };
	DWORD userList = *((DWORD*)dwWxidArr);		//userList��������΢��ID�б� 3.1��ASCII��ʽ��΢��ID
	DWORD testTmp = dwWxidArr + 0xB4;
	int Len = *((int*)testTmp);				//ȡ��΢��ID�ĸ���



	for (int i = 0; i < Len; i++)
	{
		DWORD temWxidAdd = userList + (i * 0x18);		//0x18��ÿ��΢��ID�ļ��
		int flags = (int)(*((LPVOID*)(temWxidAdd + 0x14)));
		if (flags == 0xF)
		{
			sprintf_s(tempWxidA, "%s", (char*)temWxidAdd);
		}
		else
		{
			sprintf_s(tempWxidA, "%s", (char*)*((LPVOID*)temWxidAdd));
		}

		USES_CONVERSION;
		//2.��ͨ��΢��ID��ȡȺ��Ա��Ϣ
		GetUserInfoByWxid(A2W(tempWxidA));
	}


	//���֮������Ϣ
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		OutputDebugStringA("δ���ҵ�ChatRoomMember����");
		return;
	}

	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembersDone;//����һ����ֵ, ������������־��
	userinfodata.cbData = 0;// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfodata.lpData = NULL;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);
}






//************************************************************
// ��������: SetRoomName
// ����˵��: �޸�Ⱥ����
// ��    ��: roomwxid ȺID roomnameȺ����
// �� �� ֵ: void 
//************************************************************
void SetRoomName(wchar_t* roomwxid, wchar_t* roomname)
{
	GeneralStruct pRoomwxid(roomwxid);
	GeneralStruct pRoomname(roomname);
	char* asmWxid = (char*)&pRoomwxid.pstr;
	char* asmRoomname = (char*)&pRoomname.pstr;

	DWORD dwWeChatWinAddr = GetWeChatWinBase();
	DWORD dwCall1 = dwWeChatWinAddr + WxSetRoomName;

	__asm
	{
		mov edx, asmRoomname;
		mov ecx, asmWxid;
		call dwCall1;
	}
}


//************************************************************
// ��������: SendRoomAtMsg
// ����˵��: ���Ͱ�����Ϣ
// ��    ��: chatroomid ȺID memberwxid Ⱥ��Ա΢��ID membernicknameȺ��Ա�ǳ� msg ��Ϣ����
// �� �� ֵ: void 
//************************************************************
void SendRoomAtMsg(wchar_t* chatroomid, wchar_t* memberwxid, wchar_t* membernickname, wchar_t* msg)
{
	//����call��װ���ݸ�ʽ
	DWORD dwDllBase = GetWeChatWinBase();
	DWORD dwPackageMsgDataCall = dwDllBase + WxPackageMsgData;
	DWORD dwSendTextCall = dwDllBase + WxSendMessage;

	//��װ�ı�����
	wchar_t tempmsg[500] = { 0 };
	swprintf_s(tempmsg, L"@%s %s", membernickname, msg);

	//��װ΢��ID���ݽṹ��
	GeneralStruct wxid(memberwxid);
	//��װȺID���ݽṹ��
	GeneralStruct roomid(chatroomid);
	//��װ��Ϣ�ı����ݽṹ��
	GeneralStruct textcontent(tempmsg);
	//0x81C������
	BYTE buff[0x81C] = { 0 };

	//΢��ID���ݽṹָ��
	wchar_t* pWxid = (wchar_t*)&wxid.pstr;
	//ȺID���ݽṹָ��
	wchar_t* pRoomId = (wchar_t*)&roomid.pstr;
	//��Ϣ�ı����ݽṹָ��
	wchar_t* pTextContent = (wchar_t*)&textcontent.pstr;

	//װ���ݽṹ�建����
	char databuff[16] = { 0 };
	//������װ���ݸ�ʽcall
	__asm
	{
		mov eax, pWxid;			//΢��ID�ṹ��
		push eax;
		lea ecx, databuff;
		call dwPackageMsgDataCall;
	}


	//����call���Ͱ�����Ϣ
	__asm
	{
		mov edx, pRoomId;		//ȺID�ṹ��
		lea eax, databuff;		//��װ�����ݽṹ
		push 0x1;
		push eax;
		mov ebx, pTextContent;	//��Ϣ�ı���ָ��
		push ebx;
		lea ecx, buff;			//0x81C������
		call dwSendTextCall;	//������Ϣcall
		add esp, 0xC;
	}
}


//************************************************************
// ��������: DelRoomMember
// ����˵��: ɾ��Ⱥ��Ա
// ��    ��: roomid ȺID memberwxid Ⱥ��Ա΢��ID 
// �� �� ֵ: void 
//************************************************************
void DelRoomMember(wchar_t* roomid, wchar_t* memberwxid)
{
	//�õ�call�����ݵ�ַ
	DWORD dwCall1 = GetWeChatWinBase() + WxDelRoomMemberCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxDelRoomMemberCall2;
	DWORD dwCall3 = GetWeChatWinBase() + WxDelRoomMemberCall3;

	//��װȺID�ṹ��
	GeneralStruct roomiddata(roomid);

	//��װ΢��ID�ṹ��
	wchar_t wxidbuff[0xD0] = { 0 };
	DWORD* dwBuff = (DWORD*)&wxidbuff;
	dwBuff[0] = (DWORD)memberwxid;
	dwBuff[1] = wcslen(memberwxid);
	dwBuff[2] = wcslen(memberwxid) * 2;
	dwBuff[3] = 0;
	dwBuff[4] = 0;


	wchar_t datatbuffer[0xD0] = { 0 };
	DWORD* dwDatabuf = (DWORD*)&datatbuffer;
	dwDatabuf[0] = (DWORD)&wxidbuff;
	dwDatabuf[1] = dwDatabuf[0] + 0x14;
	dwDatabuf[2] = dwDatabuf[0] + 0x14;


	__asm
	{
		pushad;
		sub esp, 0x14;
		mov ecx, esp;
		lea ebx, roomiddata.pstr;
		push ebx;
		call dwCall1;
		lea edi, datatbuffer;
		push edi;
		call dwCall2;
		mov ecx, eax;
		call dwCall3;
		popad;
	}
}

