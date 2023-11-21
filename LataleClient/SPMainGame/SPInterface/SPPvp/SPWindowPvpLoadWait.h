// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPWindowPvpLoadWait.h
//	created:	2007/11/14   Time:11:46
//	purpose:	
//		PVPLoadWait�� Zone���� PVPLoading�� �Ϸ�Ǵ� �������� ��������.
//		������� ��� �Է��� ������ �Ѵ�. -> SPZone, InterfaceManger ó��
//		������� ������ �� Ready ���°� ��������, �ϴܿ� Animation�� �ִ�.
//*********************************************************************/

#pragma once

#define WIID_PVP_LOADWAIT_BG			(WIID_PVP_LOADWAIT + 1)			// Max PVP_MAX_ROOMUSER 8
#define WIID_PVP_LOADWAIT_PLAYER		(WIID_PVP_LOADWAIT + 2)			// Max PVP_MAX_ROOMUSER 8
#define WIID_PVP_LOADWAIT_READY			(WIID_PVP_LOADWAIT + 12)		// Max PVP_MAX_ROOMUSER 8

#define PVP_LOADWAIT_COLOR				RGBA(187, 134, 123, 255)
#define PVP_LOADCOMPLETE_COLOR			RGBA( 84,  69,  44, 255)


class SPWindowPvpLoadWait : public SPWindow {
public:	
	SPWindowPvpLoadWait(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowPvpLoadWait();

	virtual void Init();
	virtual void Clean();

	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);

	virtual void Process(float fTime);
	virtual void Render(float fTime);

	//void SetTestData(int iCount) ;
	void SetLoadBGTexture(const char* strFileName) ;

protected:
	//void SetWaitUser(int iUserCount, const char* pUserList);
	void InitSubControl();

protected:
	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()	
	int OnUpdatePVPWait		( WPARAM wParam, LPARAM lParam );
	int OnClose				( WPARAM wParam, LPARAM lParam );
	//}}

private:
	SPTexture*		m_pTextureBG;
	SPTexture*		m_pTextureWnd;
	SPTexture*		m_pTextureText ;
	RECT			m_rtSrcBG;
	RECT			m_rtDstBG;

	int				m_iAlphaInc;		// ������
	int				m_iAlpha;
	float			m_fAniRender;
	float			m_fAniDelay;
	RECT			m_rtAniSrc;
	RECT			m_rtAniDest;

	RECT		m_rtSrc1;		//[2005/3/21] /**< �̹��� 1 �� <br> */
	RECT		m_rtSrc2;		//[2005/3/21] /**< �̹��� 2 �� <br> */
	RECT		m_rtSrc3;		//[2005/3/21] /**< �̹��� 3 �� ���� �ٴ� <br> */
	RECT		m_rtSrc4;		//[2005/3/21] /**< �̹��� 4 �� �ٴ� <br> */
	RECT		m_rtSrc5;		//[2005/3/21] /**< �̹��� 5 �� �ٴ� <br> */
	RECT		m_rtSrc6;		//[2005/3/21] /**< �̹��� 6 �� �ٴ� <br> */

	RECT		m_rtDest1;		//[2005/3/21] /**< �̹��� 1 �� <br> */
	RECT		m_rtDest2;		//[2005/3/21] /**< �̹��� 2 �� <br> */
	RECT		m_rtDest3;		//[2005/3/21] /**< �̹��� 3 �� ���� �ٴ� <br> */
	RECT		m_rtDest4;		//[2005/3/21] /**< �̹��� 4 �� �ٴ� <br> */
	RECT		m_rtDest5;		//[2005/3/21] /**< �̹��� 5 �� �ٴ� <br> */
	RECT		m_rtDest6;		//[2005/3/21] /**< �̹��� 6 �� �ٴ� <br> */
};