#ifndef __SPWINDOW_MESSAGELIST_H__
#define __SPWINDOW_MESSAGELIST_H__

//�˴�����Ҫ���ڹ���MessageBox�ĵ����뷵���¼��Ĵ���


#define WIID_MESSAGELIST_FRAME				( WIID_MESSAGELIST + 10 )


struct  MsgList
{
	UINT64   m_uiID;
	char     m_szName[32];
};


class SPWindowMessageList : public SPWindow
{
public:
	SPWindowMessageList(WND_ID WndClassID, INSTANCE_ID InstanceID);
	SPWindowMessageList(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);

	virtual ~SPWindowMessageList();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

	virtual void Show(bool bWithChild = true);

protected:
	SPIMESSAGE_OBJ_MAP_DECLARE()

	int			OnClose					( WPARAM wParam, LPARAM lParam );

protected:
	std::map<INSTANCE_ID, MsgList>				m_mMsgList;		//��Ϣ����
};

#endif