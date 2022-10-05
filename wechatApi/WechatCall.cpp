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
		//比较最前面两个char字符，不相等直接再一下字符
		if (str[i] != sp[0]) {
			continue;
		}
		//如果开始两个相等那么再比较分隔字符串中下一个字符
		//比较时候i是不增加的，用偏移量来，以防没有配匹退不回去
		//++j是先增加一个直接比较第二个开始，因为前面第一个已经比较了
		int j = 1;
		for (j = 1; j < sp.length(); j++) {

			if (str[i + j] != sp[j]) {
				break;//还没有比较完分隔字符就不同了，所以直接退出这个
			}
		}

		if (j == sp.length()) {

			split.push_back(str.substr(ex, i - ex));

			i = i + j;
			ex = i;
		}

	}
	//剩下全部加入去
	split.push_back(str.substr(ex, -1));
	return move(split);
}

//参数1、JSON串
//参数2、某项的名称
//返回某项的值
string GetDataFromJson(string json, string data)
{
	string buff = "0";//未找到返回 0
	int indexname = json.find(data);//找到某项的位置

	if (indexname > json.length())//未找到返回
	{
		return buff;
	}

	vector<string> vecstring = split(json, "\"");//用引号分割
	for (int i = 0; i < vecstring.max_size(); i++)
	{
		if (data == vecstring[i])
		{

			buff = vecstring.at(i + 4);//取这项的后4项，如果不带引号取后一项
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
	//微信号
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxCount));

	//判断是否为0 是0说明微信号为空
	if (tempcontent[0] == 0)
	{
		wcscpy_s(info->wxcount, wcslen(L"NULL") + 1, L"NULL");
	}
	else
	{
		wcscpy_s(info->wxcount, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());
	}


	//微信ID 这里需要兼容新老微信号  新微信号是指针 老微信号是字符串
	memset(tempcontent, 0, 0x300);
	DWORD pWxid = dwWeChatWin + WxID;
	//如果长度小于6或者大于20 说明这个地方是个指针
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxID));
	if (strlen(tempcontent) < 0x6 || strlen(tempcontent) > 0x14)
	{
		//说明是新的微信号 微信ID用地址保存
		sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxID)));
	}
	else
	{
		sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxID));
	}
	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//小头像
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxSmallHeader)));
	wcscpy_s(info->smallheader, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());



	//大头像
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxBigHeader)));
	wcscpy_s(info->bigheader, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//国家
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxNation));
	wcscpy_s(info->nation, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());

	//省份
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxProvince));
	wcscpy_s(info->province, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//城市
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxCity));
	wcscpy_s(info->city, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//手机号
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxPhoneNumber));
	wcscpy_s(info->phonenumber, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());

	//昵称
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


	//缓存目录
	swprintf_s(info->cachedir, L"%s", (wchar_t*)(*(DWORD*)(dwWeChatWin + WxCacheDir)));


	//登陆设备
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxDevice));
	wcscpy_s(info->device, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//性别
	DWORD nSex = *(DWORD*)(dwWeChatWin + WxSex);
	if (nSex == 1)
	{
		wcscpy_s(info->wxsex, wcslen(L"男") + 1, L"男");
	}
	else if (nSex == 2)
	{
		wcscpy_s(info->wxsex, wcslen(L"女") + 1, L"女");
	}
	else
	{
		wcscpy_s(info->wxsex, wcslen(L"未设置") + 1, L"未设置");
	}


	HWND hInformation = FindWindow(NULL, L"Information");
	if (hInformation == NULL)
	{
		OutputDebugStringA("未查找到Information窗口");
		return;
	}
	COPYDATASTRUCT information_msg;
	information_msg.dwData = WM_GetInformation;
	information_msg.lpData = info.get();
	information_msg.cbData = sizeof(PersonalInformation);
	//发送消息给控制端
	SendMessage(hInformation, WM_COPYDATA, (WPARAM)hInformation, (LPARAM)&information_msg);
}


//************************************************************
// 函数名称: AddWxUser
// 函数说明: 添加好友
// 参    数: wxid 微信ID msg添加好友时要发送的消息
// 返 回 值: void 
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
// 函数名称: OpenUrl
// 函数说明: 打开微信浏览器
// 参    数: void
// 返 回 值: void 
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
// 函数名称: AntiRevoke
// 函数说明: 防撤回
// 参    数: void
// 返 回 值: void 
//************************************************************

//用来存储备份指令
unsigned char backupCode[1] = { 0 };

void AntiRevoke()
{
	unsigned char fix[1] = { 0xEB };
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxAntiRevoke;
	//修改代码段属性
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 1, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//Patch
	memcpy(backupCode, (LPVOID)dwPathcAddr, 1);
	//Patch
	memcpy((LPVOID)dwPathcAddr, fix, 1);
	//恢复属性
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}

void CancelAntiRevoke()
{
	//0xE8为汇编指令 call
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxAntiRevoke;
	//修改代码段属性
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 1, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//还原的原指令
	memcpy((LPVOID)dwPathcAddr, backupCode, 1);
	//恢复属性
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
	//修改备份指令为空
	memset(backupCode, 0, 1);
}



BOOL isSendTuLing = FALSE;	//是否已经发给了机器人
wchar_t tempwxid[50];	//存放微信ID


//返回地址
DWORD RetkReciveMsgAddr = GetWeChatWinBase() + WxReciveMessage + 5;

//被覆盖的call的地址
DWORD OverReciveMsgCallAddr = GetWeChatWinBase() + WxReciveMessageCall;


//************************************************************
// 函数名称: SendTextMessage
// 函数说明: 发送文本消息
// 参    数: wxid 微信ID msg消息内容
// 返 回 值: void 
//************************************************************
void SendTextMessage(wchar_t* wxid, wchar_t* msg)
{
	//拿到发送消息的call的地址
	DWORD dwSendCallAddr = GetWeChatWinBase() + WxSendMessage;

	//组装微信ID/群ID的结构体
	GeneralStruct id(wxid);
	//消息内容
	GeneralStruct text(msg);

	//取出微信ID和消息的地址
	char* pWxid = (char*)&id.pstr;
	char* pWxmsg = (char*)&text.pstr;

	char buff[0x81C] = { 0 };
	char buff2[0x81C] = { 0 };

	//调用微信发送消息call
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
// 函数名称: GetNicknameByWxid
// 函数说明: 根据微信ID获取昵称
// 参    数: wxid 微信ID
// 返 回 值: wchar_t* 昵称 
//************************************************************
wchar_t* GetNicknameByWxid(wchar_t* userwxid)
{
	DWORD dwCall1 = GetWeChatWinBase() + WxGetUserInfoByWxidCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxGetUserInfoByWxidCall2;
	DWORD dwCall3 = GetWeChatWinBase() + WxGetUserInfoByWxidCall3;

	GeneralStruct pWxid(userwxid);
	char* asmWxid = (char*)&pWxid.pstr;
	char buff[0x3D8] = { 0 };
	DWORD userData = 0;		//用户数据的地址
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
	DWORD wxNickAdd = userData + 0x64;	//昵称
	swprintf_s(tempnickname, L"%s", (wchar_t*)(*((LPVOID*)wxNickAdd)));

	wchar_t* nickname = new wchar_t[100]{ 0 };
	memcpy(nickname, tempnickname, wcslen(tempnickname) * 2);
	return nickname;
}

//保存所有好友列表的map容器
map<wstring, wstring> g_userinfolist;

//************************************************************
// 函数名称: GetNickNameByWxid
// 函数说明: 根据好友列表的微信ID/群ID来获取微信昵称/群昵称
// 参    数: nickname 昵称
// 返 回 值: void 
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

//推荐号列表
wstring g_referencenumber[11] =
{
	L"fmessage",L"qqmail",L"medianote",L"qmessage",L"newsapp",L"filehelper",
	L"weixin", L"tmessage", L"mphelper",L"gh_7aac992b0363", L"qqsafe"
};

//************************************************************
// 函数名称: ReceiveMsgProc
// 函数说明: 接收消息的线程回调函数
// 参    数: Context 上下文
// 返 回 值: void 
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
		BOOL isTextMsg = FALSE;//是否是文字消息
		BOOL isFriendMsg = FALSE;		//是否是好友消息
		BOOL isImageMessage = FALSE;	//是否是图片消息
		BOOL isRadioMessage = FALSE;	//是否是视频消息
		BOOL isVoiceMessage = FALSE;	//是否是语音消息
		BOOL isBusinessCardMessage = FALSE;	//是否是名片消息
		BOOL isExpressionMessage = FALSE;	//是否是名片消息
		BOOL isLocationMessage = FALSE;	//是否是位置消息
		BOOL isSystemMessage = FALSE;	//是否是系统或红包消息
		BOOL isPos_File_Money_XmlLink = FALSE;			//是否位置 文件 转账和链接消息
		BOOL isFriendRequestMessage = FALSE;	//是否是好友请求消息
		BOOL isOther = FALSE;	//是否是其他消息


		switch (msg->dwtype)
		{
		case 0x01:
			isTextMsg = TRUE;
			memcpy(msg->sztype, L"文字", sizeof(L"文字"));
			break;
		case 0x03:
			memcpy(msg->sztype, L"图片", sizeof(L"图片"));
			isImageMessage = TRUE;
			break;
		case 0x22:
			memcpy(msg->sztype, L"语音", sizeof(L"语音"));
			isVoiceMessage = TRUE;
			break;
		case 0x25:
			memcpy(msg->sztype, L"好友确认", sizeof(L"好友确认"));
			isFriendRequestMessage = TRUE;
			break;
		case 0x28:
			memcpy(msg->sztype, L"POSSIBLEFRIEND_MSG", sizeof(L"POSSIBLEFRIEND_MSG"));
			isOther = TRUE;
			break;
		case 0x2A:
			memcpy(msg->sztype, L"名片", sizeof(L"名片"));
			isBusinessCardMessage = TRUE;
			break;
		case 0x2B:
			memcpy(msg->sztype, L"视频", sizeof(L"视频"));
			isRadioMessage = TRUE;
			break;
		case 0x2F:
			//石头剪刀布
			memcpy(msg->sztype, L"表情", sizeof(L"表情"));
			isExpressionMessage = TRUE;
			break;
		case 0x30:
			memcpy(msg->sztype, L"位置", sizeof(L"位置"));
			isLocationMessage = TRUE;
			break;
		case 0x31:
			//共享实时位置
			//文件
			//转账
			//链接
			//收款
			memcpy(msg->sztype, L"共享实时位置、文件、转账、链接", sizeof(L"共享实时位置、文件、转账、链接"));
			isPos_File_Money_XmlLink = TRUE;
			break;
		case 0x32:
			memcpy(msg->sztype, L"VOIPMSG", sizeof(L"VOIPMSG"));
			isOther = TRUE;
			break;
		case 0x33:
			memcpy(msg->sztype, L"微信初始化", sizeof(L"微信初始化"));
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
			memcpy(msg->sztype, L"小视频", sizeof(L"小视频"));
			isRadioMessage = TRUE;
			break;
		case 0x270F:
			memcpy(msg->sztype, L"SYSNOTICE", sizeof(L"SYSNOTICE"));
			isOther = TRUE;
			break;
		case 0x2710:
			//系统消息
			//红包
			memcpy(msg->sztype, L"系统消息", sizeof(L"系统消息"));
			isSystemMessage = TRUE;
			break;
		case 0x2712:
			//提现消息
			memcpy(msg->sztype, L"提现消息", sizeof(L"提现消息"));
			break;
		default:
			break;
		}

		
		//根据微信ID判断是否是好友消息
		wstring wxid_wstr = msg->wxid;
		if (wxid_wstr.find(L"@im.chatroom") != wxid_wstr.npos)
		{
			memcpy(msg->source, L"企业微信群消息", sizeof(L"企业微信群消息"));
		}
		else if (wxid_wstr.find(L"@chatroom") != wxid_wstr.npos)
		{
			memcpy(msg->source, L"群消息", sizeof(L"群消息"));
		}
		else
		{
			memcpy(msg->source, L"好友消息", sizeof(L"好友消息"));
			isFriendMsg = TRUE;
			memcpy(msg->sendername, L"NULL", sizeof(L"NULL"));
		}

		//int flag = strcmp(WCharToChar(msg->wxid), "filehelper");
		//这里处理自动聊天  看需求 可以设置其他条件 如指定某人 群聊
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
		OutputDebugStringA("聊天记录出异常了");
	}
}







//************************************************************
// 函数名称: SendMessage
// 函数说明: 将接收到的消息发送给客户端
// 参    数: void
// 返 回 值: void 
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
		//取出消息类型
		msg->dwtype = *((DWORD*)(r_eax + MsgTypeOffset));
		//取出消息内容
		LPVOID pContent = *((LPVOID*)(r_eax + MsgContentOffset));
		swprintf_s(msg->content, L"%s", (wchar_t*)pContent);

		//取出微信ID/群ID
		LPVOID pWxid = *((LPVOID*)(r_eax + WxidOffset));
		swprintf_s(msg->wxid, L"%s", (wchar_t*)pWxid);

		if (StrStrW(msg->wxid, L"gh_"))
		{
			return;
		}

		//取出消息发送者
		LPVOID pSender = *((LPVOID*)(r_eax + GroupMsgSenderOffset));
		swprintf_s(msg->sender, L"%s", (wchar_t*)pSender);
		//取出消息来源
		LPVOID pSource = *((LPVOID*)(r_eax + MsgSourceOffset));
		swprintf_s(msg->source, L"%s", (wchar_t*)pSource);

		//创建线程处理消息
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DealWithMsg, msg, 0, NULL);
		CloseHandle(hThread);
	}
	catch (...)
	{
		OutputDebugStringA("接收消息异常了....");
	}


}

//************************************************************
// 函数名称: RecieveMesage
// 函数说明: 接收消息
// 参    数: void
// 返 回 值: void 
//************************************************************
__declspec(naked) void RecieveWxMesage()
{
	//保存现场
	__asm
	{
		pushad;
		push eax;
		call SendWxMessage;
		popad;
		//调用被覆盖的call
		call OverReciveMsgCallAddr;
		//跳转到返回地址
		jmp RetkReciveMsgAddr;
	}
}

__declspec(naked) void CancelRecieveWxMesage()
{
	//保存现场
	__asm
	{
		//调用被覆盖的call
		call OverReciveMsgCallAddr;
		//跳转到返回地址
		jmp RetkReciveMsgAddr;
	}
}

//************************************************************
// 函数名称: HookChatRecord
// 函数说明: HOOK聊天记录
// 参    数: void
// 返 回 值: void 
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
// 函数名称: GetMsgByAddress
// 函数说明: 从地址中获取消息内容
// 参    数: DWORD memAddress  目标地址
// 返 回 值: LPCWSTR	消息内容
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
// 函数名称: ReSendUser
// 函数说明: 再次发送好友信息
// 参    数: user
// 返 回 值: void 
//************************************************************
void ReSendUser(UserListInfo* user)
{
	HWND hWnd = NULL;
	while (true)
	{
		//发送到控制端
		hWnd = FindWindow(NULL, TEXT("微信助手"));
		if (hWnd == NULL)
		{
			Sleep(200);
			continue;
		}
		break;
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//保存一个数值, 可以用来作标志等
	userinfo.cbData = sizeof(UserListInfo);// strlen(szSendBuf);//待发送的数据的长
	userinfo.lpData = user;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
	delete user;
}

//************************************************************
// 函数名称: SendUserListInfo
// 函数说明: 发送好友列表
// 参    数: r_esi 好友列表所在的数据指针
// 返 回 值: void 
//************************************************************
void __stdcall SendUserListInfo(DWORD r_esi)
{
	//个人微信号、群号
	wstring wxid = GetMsgByAddress(r_esi + 0x8);
	wstring nickname = GetMsgByAddress(r_esi + 0x64);

	//好友列表去重
	map<wstring, wstring>::iterator it;
	it = g_userinfolist.find(wxid);
	//如果返回值不等于end() 说明找到了 直接返回防止重复
	if (it != g_userinfolist.end())
	{
		return;
	}
	//如果没有找到 则插入到容器
	g_userinfolist.insert(make_pair(wxid, nickname));

	//排除推荐号列表
	for (int i = 0; i < 11; i++)
	{
		if (g_referencenumber[i] == wxid)
		{
			return;
		}
	}


	unique_ptr<UserListInfo> user(new UserListInfo);

	LPVOID pUserWxid = *((LPVOID*)(r_esi + 0x8));		//微信ID
	LPVOID pUserNumber = *((LPVOID*)(r_esi + 0x1C));	//微信号
	LPVOID pUserNick = *((LPVOID*)(r_esi + 0x64));		//昵称
	LPVOID pUserReMark = *((LPVOID*)(r_esi + 0x50));	//备注

	swprintf_s(user->UserId, L"%s", (wchar_t*)pUserWxid);
	swprintf_s(user->UserNumber, L"%s", (wchar_t*)pUserNumber);
	swprintf_s(user->UserNickName, L"%s", (wchar_t*)pUserNick);
	swprintf_s(user->UserRemark, L"%s", (wchar_t*)pUserReMark);


	//发送到控制端
	HWND hWnd = FindWindow(NULL, TEXT("微信助手"));
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
	userinfo.dwData = WM_GetFriendList;//保存一个数值, 可以用来作标志等
	userinfo.cbData = sizeof(UserListInfo);// strlen(szSendBuf);//待发送的数据的长
	userinfo.lpData = user.get();// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
}


//************************************************************
// 函数名称: GetUserListInfo
// 函数说明: 获取用户信息
// 参    数: void
// 返 回 值: void 
//************************************************************
__declspec(naked) void GetUserListInfo()
{
	__asm
	{
		pushad;
		push esi;
		call SendUserListInfo;
		popad;

		//补充被覆盖的代码
		call overWritedCallAdd;

		//跳回被HOOK指令的下一条指令
		jmp jumBackAddress
	}
}

//************************************************************
// 函数名称: HookGetFriendList
// 函数说明: HOOK获取好友列表的call 

// 时    间: 2019/7/4
// 参    数: void
// 返 回 值: void 
//************************************************************
void HookGetFriendList()
{
	HookAnyAddress(GetWeChatWinBase() + WxFriendList, GetUserListInfo);
}




//************************************************************
// 函数名称: SendFileMessage
// 函数说明: 发送文件消息
// 参    数: wxid 微信ID filepath 文件路径
// 返 回 值: void 
//************************************************************
void SendFileMessage(wchar_t* wxid, wchar_t* filepath)
{
	//构造需要的地址
	DWORD dwBase = GetWeChatWinBase();
	DWORD dwCall1 = dwBase + WxFileMessage1;
	DWORD dwCall2 = dwBase + WxFileMessage2;
	DWORD dwCall3 = dwBase + WxFileMessage3;	//组合数据
	DWORD dwCall4 = dwBase + WxFileMessage4;	//发送消息
	DWORD dwParams = dwBase + WxFileMessageParam;

	char buff[0x528] = { 0 };

	//构造需要的数据
	GeneralStruct wxidStruct(wxid);
	GeneralStruct filePathStruct(filepath);

	//取出需要的数据的地址
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
// 函数名称: SendImageMessage
// 函数说明: 发送图片消息
// 参    数: wxid 微信ID filepath 图片路径
// 返 回 值: void 
//************************************************************
void SendImageMessage(wchar_t* wxid, wchar_t* filepath)
{
	//组装微信ID的数据结构
	GeneralStruct imagewxid(wxid);
	//组装文件路径的数据结构
	GeneralStruct imagefilepath(filepath);
	char buff[0x528] = { 0 };
	char buff2[0x60] = { 0 };


	DWORD dwCall3 = GetWeChatWinBase() + WxSendImageCall3;
	DWORD dwCall1 = GetWeChatWinBase() + WxSendImageCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxSendImageCall2;


	//微信发送图片调用了GidCreateBimapFileCM 之后图片一直被占用 无法删除 patch掉下面的代码
	unsigned char oldcode[5] = { 0 };
	unsigned char fix[5] = { 0x31,0xC0,0x90,0x90,0x90 };
	DWORD dwPathcAddr = GetWeChatWinBase() + WxPatchAddr;
	//修改代码段属性
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 5, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//先保存原有指令
	memcpy(oldcode, (LPVOID)dwPathcAddr, 5);
	//再Patch掉
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
	//调用完之后恢复
	memcpy((LPVOID)dwPathcAddr, oldcode, 5);
	//恢复属性
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}


//************************************************************
// 函数名称: WxDeleteUser
// 函数说明: 删除好友
// 参    数: wxid 微信ID
// 返 回 值: void 
//************************************************************
void DeleteUser(wchar_t* wxid)
{
	DWORD dwBaseAddress = GetWeChatWinBase();
	//构造数据
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
// 函数名称: SendXmlCard
// 函数说明: 发送XML名片
// 参    数: RecverWxid 发送者微信ID SendWxid要发送的微信ID NickName微信昵称
// 返 回 值: void 
//************************************************************
void SendXmlCard(wchar_t* RecverWxid, wchar_t* SendWxid, wchar_t* NickName)
{
	wchar_t xml[0x2000] = { 0 };
	swprintf_s(xml, L"<?xml version=\"1.0\"?><msg bigheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/0\" smallheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/132\" username=\"%s\" nickname=\"%s\" fullpy=\"?\" shortpy=\"\" alias=\"%s\" imagestatus=\"3\" scene=\"17\" province=\"北京\" city=\"中国\" sign=\"\" sex=\"2\" certflag=\"0\" certinfo=\"\" brandIconUrl=\"\" brandHomeUrl=\"\" brandSubscriptConfigUrl= \"\" brandFlags=\"0\" regionCode=\"CN_BeiJing_BeiJing\" />", SendWxid, NickName, SendWxid);
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
// 函数名称: SetWxRoomAnnouncement
// 函数说明: 发送群公告
// 参    数: chartoomwxid 群ID Announcement 群公告
// 返 回 值: void 
//************************************************************
void SetWxRoomAnnouncement(wchar_t* chatroomwxid, wchar_t* Announcement)
{
	//获取WeChatWin的基址
	DWORD callAdrress = GetWeChatWinBase() + WxSetRoomAnnouncement;
	//组装数据
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
		//保存堆栈寄存器
		mov r_esp, esp;
		lea eax, bufferA;
		push eax;
		call callAdrress;

		//恢复堆栈寄存器
		mov eax, r_esp;
		mov esp, eax;
	}
}



//************************************************************
// 函数名称: QuitChatRoom
// 函数说明: 退出群聊
// 参    数: chartoomwxid 群ID 
// 返 回 值: void 
//************************************************************
void QuitChatRoom(wchar_t* chatroomwxid)
{
	DWORD dwBaseAddress = GetWeChatWinBase();
	DWORD dwCallAddr = dwBaseAddress + WxQuitChatRoom;

	//构造数据
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
// 函数名称: AddGroupMember
// 函数说明: 添加群成员
// 参    数: chartoomwxid 群ID  wxid 微信ID
// 返 回 值: void 
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

	//构造需要的数据
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
// 函数名称: GetUserInfoByWxid
// 函数说明: 通过微信ID获取用户信息
// 参    数: userwxid 微信ID
// 返 回 值: void 
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
		mov edi, asmWxid;		//微信ID结构体	
		mov eax, asmBuff;		//缓冲区
		push eax;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		mov dword ptr ds : [ecx] , 0x0;
		mov dword ptr ds : [ecx + 0x4] , 0x0;
		mov dword ptr ds : [ecx + 0x8] , 0x0;
		mov dword ptr ds : [ecx + 0xC] , 0x0;
		mov dword ptr ds : [ecx + 0x10] , 0x0;
		push dword ptr ds : [edi] ;	//微信ID
		call dwCall1;				//call1
		call dwCall2;				//call2
		mov eax, asmHeadBuff;
		push eax;
		mov ecx, asmBuff;
		call dwCall3;
		popad
	}



	LPVOID lpWxid = *((LPVOID*)((DWORD)buff + 0x20));				//微信ID
	LPVOID lpWxcount = *((LPVOID*)((DWORD)buff + 0x34));			//微信账号
	LPVOID lpNickName = *((LPVOID*)((DWORD)buff + 0x7C));			//昵称




	//组装结构体
	UserInfo* userinfo = new UserInfo;
	swprintf_s(userinfo->UserId, L"%s", (wchar_t*)lpWxid);
	swprintf_s(userinfo->UserNickName, L"%s", (wchar_t*)lpNickName);
	swprintf_s(userinfo->UserNumber, L"%s", (wchar_t*)lpWxcount);



	//发送到客户端
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		OutputDebugStringA("未查找到ChatRoomMember窗口");
		return;
	}


	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembers;//保存一个数值, 可以用来作标志等
	userinfodata.cbData = sizeof(UserInfo);// strlen(szSendBuf);//待发送的数据的长
	userinfodata.lpData = userinfo;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);

	delete userinfo;

}


//************************************************************
// 函数名称: ShowChatRoomUser
// 函数说明: 显示群成员
// 参    数: void
// 返 回 值: void 
//************************************************************
void ShowChatRoomUser(wchar_t* chatroomwxid)
{
	//准备缓冲区
	DWORD dwWxidArr = 0;	//保存微信ID数据的地址
	char buff[0x164] = { 0 };
	char userListBuff[0x174] = { 0 };
	//构造数据
	GeneralStruct pWxid(chatroomwxid);
	char* asmWxid = (char*)&pWxid.pstr;

	//调用call
	DWORD dwCall1 = GetWeChatWinBase() + WxGetRoomUserWxidCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxGetRoomUserWxidCall2;
	DWORD dwCall3 = GetWeChatWinBase() + WxGetRoomUserWxidCall3;
	DWORD dwCall4 = GetWeChatWinBase() + WxGetRoomUserWxidCall4;

	//获取群成员
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

	//拿到微信ID
	wchar_t test[0x100] = { 0 };
	wchar_t tempWxid[0x100] = { 0 };
	char tempWxidA[0x100] = { 0 };
	DWORD userList = *((DWORD*)dwWxidArr);		//userList这个里面的微信ID列表 3.1是ASCII格式的微信ID
	DWORD testTmp = dwWxidArr + 0xB4;
	int Len = *((int*)testTmp);				//取到微信ID的个数



	for (int i = 0; i < Len; i++)
	{
		DWORD temWxidAdd = userList + (i * 0x18);		//0x18是每个微信ID的间隔
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
		//2.再通过微信ID获取群成员信息
		GetUserInfoByWxid(A2W(tempWxidA));
	}


	//完成之后发送消息
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		OutputDebugStringA("未查找到ChatRoomMember窗口");
		return;
	}

	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembersDone;//保存一个数值, 可以用来作标志等
	userinfodata.cbData = 0;// strlen(szSendBuf);//待发送的数据的长
	userinfodata.lpData = NULL;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);
}






//************************************************************
// 函数名称: SetRoomName
// 函数说明: 修改群名称
// 参    数: roomwxid 群ID roomname群名称
// 返 回 值: void 
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
// 函数名称: SendRoomAtMsg
// 函数说明: 发送艾特消息
// 参    数: chatroomid 群ID memberwxid 群成员微信ID membernickname群成员昵称 msg 消息内容
// 返 回 值: void 
//************************************************************
void SendRoomAtMsg(wchar_t* chatroomid, wchar_t* memberwxid, wchar_t* membernickname, wchar_t* msg)
{
	//调用call组装数据格式
	DWORD dwDllBase = GetWeChatWinBase();
	DWORD dwPackageMsgDataCall = dwDllBase + WxPackageMsgData;
	DWORD dwSendTextCall = dwDllBase + WxSendMessage;

	//组装文本内容
	wchar_t tempmsg[500] = { 0 };
	swprintf_s(tempmsg, L"@%s %s", membernickname, msg);

	//组装微信ID数据结构体
	GeneralStruct wxid(memberwxid);
	//组装群ID数据结构体
	GeneralStruct roomid(chatroomid);
	//组装消息文本数据结构体
	GeneralStruct textcontent(tempmsg);
	//0x81C缓冲区
	BYTE buff[0x81C] = { 0 };

	//微信ID数据结构指针
	wchar_t* pWxid = (wchar_t*)&wxid.pstr;
	//群ID数据结构指针
	wchar_t* pRoomId = (wchar_t*)&roomid.pstr;
	//消息文本数据结构指针
	wchar_t* pTextContent = (wchar_t*)&textcontent.pstr;

	//装数据结构体缓冲区
	char databuff[16] = { 0 };
	//调用组装数据格式call
	__asm
	{
		mov eax, pWxid;			//微信ID结构体
		push eax;
		lea ecx, databuff;
		call dwPackageMsgDataCall;
	}


	//调用call发送艾特消息
	__asm
	{
		mov edx, pRoomId;		//群ID结构体
		lea eax, databuff;		//组装的数据结构
		push 0x1;
		push eax;
		mov ebx, pTextContent;	//消息文本的指针
		push ebx;
		lea ecx, buff;			//0x81C缓冲区
		call dwSendTextCall;	//发送消息call
		add esp, 0xC;
	}
}


//************************************************************
// 函数名称: DelRoomMember
// 函数说明: 删除群成员
// 参    数: roomid 群ID memberwxid 群成员微信ID 
// 返 回 值: void 
//************************************************************
void DelRoomMember(wchar_t* roomid, wchar_t* memberwxid)
{
	//拿到call的数据地址
	DWORD dwCall1 = GetWeChatWinBase() + WxDelRoomMemberCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxDelRoomMemberCall2;
	DWORD dwCall3 = GetWeChatWinBase() + WxDelRoomMemberCall3;

	//组装群ID结构体
	GeneralStruct roomiddata(roomid);

	//组装微信ID结构体
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

