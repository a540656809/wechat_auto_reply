#pragma once
#include <string>
using namespace std;

void HookChatRecord();		//HOOK�����¼
void UnHookChatRecord();
void RecieveWxMesage();		//����΢����Ϣ

void __stdcall SendWxMessage(DWORD r_eax);		//����΢����Ϣ���ͻ���
std::wstring GetMsgByAddress(DWORD memAddress);	//�ӵ�ַ�л�ȡ��Ϣ����
void GetInformation();
void AddWxUser(wchar_t* wxid, wchar_t* msg);	//��Ӻ���
void AntiRevoke();	//������
void CancelAntiRevoke();	//������
void OpenUrl(wchar_t* Url);	//��΢�������
void HookGetFriendList();		//HOOK��ȡ�����б��call
void GetUserListInfo();		    //��ȡ�����б�
void __stdcall SendUserListInfo(DWORD r_esi);		//���ͺ����б�
void SendTextMessage(wchar_t* wxid, wchar_t* msg);	//�����ı���Ϣ
void SendFileMessage(wchar_t* wxid, wchar_t* filepath);	//�����ļ���Ϣ
void SendImageMessage(wchar_t* wxid, wchar_t* filepath);//����ͼƬ��Ϣ
void DeleteUser(wchar_t* wxid);	//ɾ������
void SendXmlCard(wchar_t* RecverWxid, wchar_t* SendWxid, wchar_t* NickName); //����XML��Ƭ
std::string wstringToString(const std::wstring& wstr);
wchar_t* GetNicknameByWxid(wchar_t* userwxid);
wstring GetNickNameByWxid(wstring wxid);
void SetWxRoomAnnouncement(wchar_t* chatroomwxid, wchar_t* Announcement);	//����Ⱥ����
void QuitChatRoom(wchar_t* chatroomwxid);					//�˳�Ⱥ��
void AddGroupMember(wchar_t* chatroomwxid, wchar_t* wxid);	//���Ⱥ��Ա
void ShowChatRoomUser(wchar_t* chatroomwxid);				//��ʾȺ��Ա
void GetUserInfoByWxid(wchar_t* userwxid);					//ͨ��΢��ID��ȡ�û���Ϣ
void SetRoomName(wchar_t* roomwxid, wchar_t* roomname);		//�޸�Ⱥ����
void DelRoomMember(wchar_t* roomid, wchar_t* memberwxid);	//ɾ��Ⱥ��Ա
void SendRoomAtMsg(wchar_t* chatroomid, wchar_t* memberwxid, wchar_t* membernickname, wchar_t* msg); //���Ͱ�����Ϣ