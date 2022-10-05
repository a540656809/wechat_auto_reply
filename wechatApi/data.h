#pragma once
#include <minwindef.h>


//΢��ͨ�ýṹ��
struct GeneralStruct
{
	wchar_t* pstr;
	int iLen;
	int iMaxLen;
	int full1;
	int full2;
	GeneralStruct(wchar_t* pString)
	{
		pstr = pString;
		iLen = wcslen(pString);
		iMaxLen = iLen * 2;
		full1 = 0;
		full2 = 0;
	}
};

//�洢WM_COPYDATA��Ϣ��ͨ��������
union MessageUnion
{
	//ͨ����Ϣ�ṹ��
	struct MessageStruct
	{
		wchar_t msgdata1[MAX_PATH];
		wchar_t msgdata2[MAX_PATH];
	}genericmsg;

	//������Ƭ��Ϣ�ṹ��
	struct XmlCardMessage
	{
		wchar_t RecverWxid[50];		//�����ߵ�΢��ID
		wchar_t SendWxid[50];		//��Ҫ���͵�΢��ID
		wchar_t NickName[50];		//�ǳ�
	}xmlcardmsg;
	//���Ͱ�����Ϣ
	struct AtMsg
	{
		wchar_t chatroomid[50] = { 0 };
		wchar_t membermsgdata1[50] = { 0 };
		wchar_t membernickname[50] = { 0 };
		wchar_t msgmsgdata2[100] = { 0 };
	}atmsg;
	//XML������Ϣ
	struct SendXmlArticleStruct
	{
		wchar_t title[50];
		wchar_t subtitle[50];
		wchar_t urllink[200];
		wchar_t picpath[260];
		wchar_t selfwxid[50];
		wchar_t recverwxid[50];
	}xmlartmsg;
};


//������Ϣ�Ľṹ��
struct PersonalInformation
{
	wchar_t wxid[40];			//΢��ID
	wchar_t wxcount[40];		//΢���˺�
	wchar_t v1[150];			//V1
	wchar_t nickname[50];		//΢���ǳ�
	wchar_t remark[50];			//��ע
	wchar_t wxsex[10];			//�Ա�
	wchar_t phonenumber[30];	//�ֻ���
	wchar_t device[20];			//��½�豸
	wchar_t nation[20];			//����
	wchar_t province[20];		//ʡ��
	wchar_t city[20];			//����
	wchar_t area[20];			//����
	wchar_t language[10];		//����
	wchar_t bigheader[0x100];	//��ͷ��
	wchar_t smallheader[0x100];	//Сͷ��
	wchar_t signature[50];		//����ǩ��
	wchar_t background[0x100];	//����Ȧ����
	wchar_t cachedir[MAX_PATH];	//����Ŀ¼
	wchar_t startdir[MAX_PATH];	//����Ŀ¼
};


//�޸ı�ע�ṹ�� 0x22B��λ�ñ�����1
struct SetRemarkStruct
{
	int full1 = 0x800;			//4
	int full2 = 0;				//8
	wchar_t* UnicodeWxid;		//0xC
	int UnicodeWxidLen;			//0x10
	int UnicodeWxidMaxLen;		//0x14
	int full5 = 0;				//0x18
	int full6 = 0;				//0x1C
	char full3[0x34] = { 0 };	//0x20
	wchar_t* Remark;			//0x54
	int RemarkLen;				//0x58
	int RemarkMaxLen;			//0x5C
	int full7 = 0;				//0x60
	int full8 = 0;				//0x64
	char full9[0x1C3] = { 0 };	//0x68
	int full10 = 1;				//0x228
	char full11[0x259] = { 0 };	//0x68
};


//�����¼����Ϣ�ṹ��
struct ChatMessageData
{
	DWORD dwtype;				//��Ϣ����
	wchar_t sztype[0x20];			//��Ϣ����
	wchar_t source[0x400];			//��Ϣ��Դ
	wchar_t wxid[0x40];			//΢��ID/ȺID
	wchar_t wxname[0x200];			//΢������/Ⱥ����
	wchar_t sender[0x100];			//��Ϣ������
	wchar_t sendername[0x100];		//��Ϣ�������ǳ�
	wchar_t content[0x5000];	//��Ϣ����
};

//V1
struct v1Info
{
	int fill = 0;
	wchar_t* v1 = 0;
	int v1Len;
	int maxV1Len;
	char fill2[0x41C] = { 0 };
	DWORD v2 = { 0 };
};

//V2
struct v2Info
{
	char fill[0x24C] = { 0 };
	DWORD fill3 = 0x25;
	char fill4[0x40] = { 0 };
	wchar_t* v2;
	int v2Len;
	int maxV2Len;
	char fill2[0x8] = { 0 };
};


//�տ�ṹ��
struct CllectMoneyStruct
{
	wchar_t* ptransferid;
	int transferidLen;
	int transferidMaxLen;
	char full[0x8] = { 0 };
	wchar_t* pwxid;
	int wxidLen;
	int wxidMaxLen;
	char full2[0x8] = { 0 };
};


//����ͼƬ�ṹ��
struct DwonImgStruct
{
	//92C
	char fill[0x14] = { 0 };
	DWORD params = 0;
	DWORD params1 = 0;
	char fill2[0x10] = { 0 };
	DWORD params2 = 0;
	char fill3[0x38] = { 0 };
	wchar_t* imgXml;
	int xmlLen = 0;
	int xmlMaxLen = 0;
	char fill4[0xC8] = { 0 };
	wchar_t* thumbImgPath;
	int thumbLen = 0;
	int thumbMaxLen = 0;
	char fill5[0x8] = { 0 };
	wchar_t* hImgPath;
	int hImgLen = 0;
	int hImgMaxLen = 0;
	char fill6[0x700] = { 0 };
};

//ͨ��΢��ID��ȡ�û���Ϣ�ṹ��
struct UserInfo
{
	wchar_t UserId[0x100];
	wchar_t UserNumber[0x100];
	wchar_t UserNickName[0x100];
};


//�����б���Ϣ�ṹ��
struct UserListInfo
{
	wchar_t UserId[80];
	wchar_t UserNumber[80];
	wchar_t UserRemark[80];
	wchar_t UserNickName[80];
};

//������ϸ��Ϣ
struct UserInfoDetail
{
	wchar_t UserId[50];			//΢��ID
	wchar_t UserNumber[50];		//΢���˺�
	wchar_t V1[200];				//V1
	wchar_t Remark[50];			//��ע
	wchar_t UserNickName[50];	//΢���ǳ�
	wchar_t smallHeader[1024] = { 0 };	//Сͷ��
	wchar_t bigHeader[1024] = { 0 };	//��ͷ��
};

//�����Ⱥ��ȺID�ṹ��
struct RoomIdStruct
{
	char fill2[0x8] = { 0 };
	wchar_t* str;
	int strLen = 0;
	int maxLen = 0;
	char fill[0x8] = { 0 };
};



