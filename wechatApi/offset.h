#pragma once
#define WxFriendList 0x5244A8					//�����б� 1
#define WxFriendListCall 0x64550				//�����б� 1
#define WxReciveMessage 0x3DF42C			//������Ϣ 	 1
#define WxReciveMessageCall 0x87A70			//������Ϣ 	  1
#define WxGoToQrCode1 0x264830				//��ת����ά�� 1
#define WxGoToQrCode2 0x3ADE40				//��ת����ά�� 1
#define WxQrCodeOffset 0x266AAC				//��ȡ��ά�� 1
#define WxQrCodeOffsetCall 0x58BD30			//��ȡ��ά�� 1
#define WxSendMessage 0x3B63B0				//�����ı���Ϣ 1
#define WxLogout 0x4E7210						//�˳� 1
#define WxFileMessage1 0x58DA10				 //�����ļ���Ϣ 1
#define WxFileMessage2 0x58DA50				 //�����ļ���Ϣ 1
#define WxFileMessage3 0x68D00				 //�����ļ���Ϣ 1
#define WxFileMessage4 0x2C1960				 //�����ļ���Ϣ 1
#define WxFileMessageParam 0x17FFE10		 //�����ļ���Ϣ 1
#define WxSendImageCall3 0x58DA50			//����ͼƬ��Ϣ 1
#define WxSendImageCall1 0x639F0			//����ͼƬ��Ϣ 1
#define WxSendImageCall2 0x3B5C70			//����ͼƬ��Ϣ 1
#define WxPatchAddr 0x3B2AE6				//����ͼƬ��Ϣ 1
#define WxSetRoomAnnouncement 0x3074E0			//����Ⱥ���� 1
#define WxDeleteUser 0x325C80					//ɾ������ 1
#define WxQuitChatRoom 0x3045B0					//�˳�Ⱥ�� 1
#define WxAddGroupMemberCall1 0x827B0			//���Ⱥ��Ա 1
#define WxAddGroupMemberCall2 0x58DB60			//���Ⱥ��Ա 1
#define WxAddGroupMemberCall3 0x932D0			//���Ⱥ��Ա 1
#define WxAddGroupMemberCall4 0x2FF220			//���Ⱥ��Ա 1
#define WxAddGroupMemberParam1 0x1AD1B34		//���Ⱥ��Ա 1
#define WxAddGroupMemberParam2 0x1AD2358		//���Ⱥ��Ա 1
#define WxSendXmlCard 0x3B63B0				//������Ƭ 1
#define WxGetRoomUserWxidCall1 0x512DD0			//��ȡȺ��ԱID 1
#define WxGetRoomUserWxidCall2 0x379A90			//��ȡȺ��ԱID 1
#define WxGetRoomUserWxidCall3 0x5193F0			//��ȡȺ��ԱID 1
#define WxGetRoomUserWxidCall4 0x5137F0			//��ȡȺ��ԱID 1
#define WxGetUserInfoWithNoNetworkCall1 0x58DDD0		 //����΢��ID��ȡ�û���Ϣ 1
#define WxGetUserInfoWithNoNetworkCall2 0x3245E0		 //����΢��ID��ȡ�û���Ϣ 1
#define WxGetUserInfoWithNoNetworkCall3 0x4FD8F0		 //����΢��ID��ȡ�û���Ϣ 1
#define WxGetUserInfoByWxidCall1 0x58DA50		//����΢��ID��ȡ�û���Ϣ 1
#define WxGetUserInfoByWxidCall2 0x63930		//����΢��ID��ȡ�û���Ϣ 1
#define WxGetUserInfoByWxidCall3 0x3245E0		//����΢��ID��ȡ�û���Ϣ 1
#define WxAddWxUserParam1 0x1730C30				//��Ӻ��� 1
#define WxAddWxUserCall1 0x57860				//��Ӻ��� 1
#define WxAddWxUserCall2 0x83780				//��Ӻ��� 1
#define WxAddWxUserCall3 0x58DA10				//��Ӻ��� 1
#define WxAddWxUserCall4 0x58DA50				//��Ӻ��� 1
#define WxAddWxUserCall5 0x322B20				//��Ӻ��� 1
#define WxSetRoomName 0x303A50					//�޸�Ⱥ���� 1
#define WxCllectMoneyCall1 0x9C5310				//�տ� 1
#define WxCllectMoneyCall2 0x9C5390				//�տ� 1
#define WxAgreeUserRequestCall1 0x1F0360		//ͬ��������� 1
#define WxAgreeUserRequestCall2 0x5D860			//ͬ��������� 1
#define WxAgreeUserRequestCall3 0x10FFA0		//ͬ��������� 1
#define WxAgreeUserRequestCall4 0x1D7180		//ͬ��������� 1
#define WxAgreeUserRequestParam 0x1AB2E98		//ͬ��������� 1
#define WxGetExpressionsAddr 0x2D3C68			//��ȡ΢�ű���  ûɶ�� ȥ��
#define WxGetExpressionsCallAddr 0x2D7E60		//��ȡ΢�ű���  ûɶ�� ȥ��
#define WxDelRoomMemberCall1 0x58DA50			//ɾ��Ⱥ��Ա 1
#define WxDelRoomMemberCall2 0x7CD80			//ɾ��Ⱥ��Ա 1
#define WxDelRoomMemberCall3 0x2FF410			//ɾ��Ⱥ��Ա 1
#define WxOpenUrlCall1 0x58DA50					//������� 1
#define WxOpenUrlCall2 0x9C9CA0					//������� 1
#define WxPackageMsgData 0x827B0		//��װ������Ϣ���ݽṹ 1
#define WxAntiRevoke 0x3DED99			//������ 1
//�����¼ƫ��
#define MsgTypeOffset 0x30				//��Ϣ���͵�ƫ�� 
#define MsgContentOffset 0x68			//��Ϣ���ݵ�ƫ�� 
#define MsgSourceOffset 0x1B8			//��Ϣ��Դ��ƫ�� 
#define WxidOffset 0x40					//΢��ID/ȺIDƫ�� 	
#define GroupMsgSenderOffset 0x164		//Ⱥ��Ϣ������ƫ�� 
//������Ϣ ��ַ 
#define WxSelfInfoBase 0x1AD1AF0				// 1
// ��½��־λ 
#define LoginSign_Offset 0x1AD4858	// 1
//΢��ID ASCIIָ��
#define WxID WxSelfInfoBase+0x44	//
//��ͷ�� ASCIIָ��
#define WxBigHeader WxSelfInfoBase+0x384	//
//Сͷ�� ASCIIָ��
#define WxSmallHeader WxSelfInfoBase+0x39C	//
//���� ASCII�ַ�
#define WxNation WxSelfInfoBase+0x298		//
//΢�ź� ASCII�ַ�
#define WxCount WxSelfInfoBase+0x220		//
//���� ASCII�ַ�
#define WxProvince WxSelfInfoBase+0x1A8		//
//����  ASCII�ַ�
#define WxCity WxSelfInfoBase+0x1C0			//
//�ֻ��� ASCII�ַ�
#define WxPhoneNumber WxSelfInfoBase+0xF0   //
//�ǳ� ASCII�ַ�
#define WxNickName WxSelfInfoBase+0xBC		//
//����Ŀ¼  Unicodeָ��
#define WxCacheDir WxSelfInfoBase+0x10		//
//��½�豸 ASCII�ַ�
#define WxDevice WxSelfInfoBase+0x510		//
//�Ա� 
#define WxSex WxSelfInfoBase+0x1A4			//
