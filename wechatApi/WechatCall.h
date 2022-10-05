#pragma once
#include <string>
using namespace std;

void HookChatRecord();		//HOOK聊天记录
void UnHookChatRecord();
void RecieveWxMesage();		//接收微信消息

void __stdcall SendWxMessage(DWORD r_eax);		//发送微信消息到客户端
std::wstring GetMsgByAddress(DWORD memAddress);	//从地址中获取消息内容
void GetInformation();
void AddWxUser(wchar_t* wxid, wchar_t* msg);	//添加好友
void AntiRevoke();	//防撤回
void CancelAntiRevoke();	//防撤回
void OpenUrl(wchar_t* Url);	//打开微信浏览器
void HookGetFriendList();		//HOOK获取好友列表的call
void GetUserListInfo();		    //获取好友列表
void __stdcall SendUserListInfo(DWORD r_esi);		//发送好友列表
void SendTextMessage(wchar_t* wxid, wchar_t* msg);	//发送文本消息
void SendFileMessage(wchar_t* wxid, wchar_t* filepath);	//发送文件消息
void SendImageMessage(wchar_t* wxid, wchar_t* filepath);//发送图片消息
void DeleteUser(wchar_t* wxid);	//删除好友
void SendXmlCard(wchar_t* RecverWxid, wchar_t* SendWxid, wchar_t* NickName); //发送XML名片
std::string wstringToString(const std::wstring& wstr);
wchar_t* GetNicknameByWxid(wchar_t* userwxid);
wstring GetNickNameByWxid(wstring wxid);
void SetWxRoomAnnouncement(wchar_t* chatroomwxid, wchar_t* Announcement);	//设置群公告
void QuitChatRoom(wchar_t* chatroomwxid);					//退出群聊
void AddGroupMember(wchar_t* chatroomwxid, wchar_t* wxid);	//添加群成员
void ShowChatRoomUser(wchar_t* chatroomwxid);				//显示群成员
void GetUserInfoByWxid(wchar_t* userwxid);					//通过微信ID获取用户信息
void SetRoomName(wchar_t* roomwxid, wchar_t* roomname);		//修改群名称
void DelRoomMember(wchar_t* roomid, wchar_t* memberwxid);	//删除群成员
void SendRoomAtMsg(wchar_t* chatroomid, wchar_t* memberwxid, wchar_t* membernickname, wchar_t* msg); //发送艾特消息