#pragma once
#include "stdafx.h"

BOOL IsWxVersionValid();	//检查当前微信版本
void CheckIsLogin();	//检测微信是否登陆

void InitWindow(HMODULE hModule);	//初始化窗口
void LogoutWeChat();