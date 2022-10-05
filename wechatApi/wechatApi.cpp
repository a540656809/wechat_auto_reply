// WeChatHelper.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"

BOOL g_AutoChat = FALSE;	//是否自动聊
std::string g_tuLingApiKey; //图灵apikey

void setTuLingApiKey(std::string param) {
	g_tuLingApiKey = param;
}


std::string getTuLingApiKey() {
	return g_tuLingApiKey;
}

void setAutoChat(BOOL flag) {
	g_AutoChat = flag;
}


BOOL getAutoChat() {
	return g_AutoChat;
}