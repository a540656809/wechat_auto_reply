// WeChatHelper.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "stdafx.h"

BOOL g_AutoChat = FALSE;	//�Ƿ��Զ���
std::string g_tuLingApiKey; //ͼ��apikey

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