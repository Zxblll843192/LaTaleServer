#pragma once

//#include "Global/include/FreeType.h"
#include "freetype.h"
#include "FixPool.h"
//#include "TextureD3D.h"
//#include "sdui.h"

#define SICON_BEGIN						0xFE				// ��̬�������忪ͷ�ֽ�
#define DICON_BEGIN						0xFF				// ��̬�������忪ͷ�ֽ�

#define DTF_UnderLine					0x00000020
#define DTF_Bold						0x40000000
#define DTF_BlackFrame					0x20000000
#define DTF_Center						0x00000001
#define DTF_Right						0x00000002         //[xialin 2008/08/19]add
#define DTF_Shadow						0x10000000

#define FONT_SONGTI_12_ASC_SIZE	(12 * 6 * 96 / 8)
#define FONT_SONGTI_12_FNT_SIZE	(2*12 * 126*191)
#define FONT_SONGTI_14_ASC_SIZE	(2*7*14 * 95)
#define FONT_SONGTI_14_FNT_SIZE	(2*14 * 126*191)

enum eFont_Type
{
	FONT_SONGTI          =      0,//����
	FONT_LISHU           =      1,//����
	FONT_FREETYPE_NUM    =      2,//freetype֧�ֵ���������

	FONT_GDI_XINSONG     =   	3,// ������
	FONT_GDI_KAITI		 =		4,// ����
	FONT_GDI_HEITI		 =		5,// ����
	FONT_GDI_FANGSONG	 =		6,// ������
	FONT_GDI_SONG_XIE	 =		7,// ����б��
	FONT_GDI_SONG_CU	 =		8,// ���δ���
	FONT_GDI_YOUYUAN	 =		10,// ��Բ
	FONT_GDI_LISHU		 =		11,// ����
	FONT_GDI_SHUTI		 =		12,// ����
	FONT_GDI_TAOTI		 =		13,// Ҧ��
	FONT_GDI_CAIYUN		 =		14,// ����
	FONT_GDI_XIHEI		 =		15,// ϸ��
	FONT_GDI_XINWEI		 =		16,// ��κ
	FONT_GDI_HANGKAI	 =		17,// �п�
	FONT_GDI_ZHONGSONG	 =		18,// ����

	FONT_NUM             =      19,//֧�ֵ���������
};


enum eFont_Size
{
	FONT_SMALL = 12,
	FONT_MIDDLE = 14,
	FONT_BIG   = 16
};

//�Լ����壬�����m_FreeType.Add����������˳��һ��

#define FONT12_SIZE	(12 * 6 * 96 / 8)

class SPTexture;

class CFontManager
{
	//friend class CTextureD3D;

	struct stExpression
	{
		int	iPos;
		int iIdex;
	};

	struct stTextID
	{
		int		iFontCRC;
		int		iTextCRC;
		DWORD	dwColor;
		DWORD	dwFrameColor;  //[xialin 2008/09/06]add
		DWORD	dwBkColor;
		int		iFontSize;
		DWORD	dwFlag;

		DWORD			dwCount;
		int				iw;
		int				ih;
		int				iExpSize;
		stExpression*	pExp;
		//LPTexture		pTex;
		SPTexture*		pTex;

		stTextID():iFontCRC(0),iTextCRC(0),dwColor(-1),dwBkColor(0),iFontSize(0),dwFlag(0),
			dwCount(0),iw(0),ih(0),iExpSize(0),pExp(0),pTex(NULL),dwFrameColor(0)
		{
		}
	};

	struct stList:public stTextID
	{
		stList *Prev;
		stList *Next;

		stList():Prev(NULL),Next(NULL)
		{
		}
	};

	struct SFontLib 
	{
		int	width,height;  // ��λ��Ⱥ͸߶ȣ�����Ŀ��ָһ�����ֵĿ��
		LOGFONT	sLogFont;  // �������Խṹ
	};	

private:
	stList* ListAdd(stTextID& textID);
	stList* ListFind(stTextID& textID);
	void ListDel(stList *pList);
	void ListMoveHead(stList *pList);
	void ListWash(DWORD dwCount,DWORD dwDelta);
	void ListClear(void);

	BOOL GetTextTex(stTextID& textID,LPCTSTR str);
	BOOL GetTextTexGDI(stTextID& textID,LPCTSTR str);
	BOOL GetTextTexFreeType(stTextID& textID,LPCTSTR str);
	BOOL GetTextTexFNT(stTextID& textID,LPCTSTR str);
	BOOL GetWordPixel(stTextID& textID,WORD wTemp,int& iw,WORD* pwBuf,WORD wColor);

protected:
	BYTE		m_vAsc12[FONT_SONGTI_12_ASC_SIZE];
	WORD		m_vAsc14[FONT_SONGTI_14_ASC_SIZE];
	BYTE		m_vFnt12[FONT_SONGTI_12_FNT_SIZE];
	BYTE		m_vFnt14[FONT_SONGTI_14_FNT_SIZE];

	WORD*       m_vFace;
	int         m_iFace;
	int         m_iCurFontType;
	//CFreeType	m_FreeType;

	stList*		m_pListHead;
	stList*		m_pListEnd;

	CFixPool	m_FixPool16;
	CFixPool	m_FixPool32;
	CFixPool	m_FixPool64;

	// GDI ����
	HDC         m_hDC;			// ����DC
	HFONT       m_hFont;		// ������
	BITMAPINFO  m_sBmi;			// ����ͼ��ṹ
	int			m_iLastGUIFont;	// ��һ��ʹ�õ�GDI����
	int         m_iLastFontSize;// ��һ��ʹ�õ�GDI����Ĵ�С
	SFontLib    m_sFontLib[FONT_NUM];

public:
	CFontManager(void);
	~CFontManager(void);

	// ������������,����:FONT_SONGTI, eFont_Type����֮һ
	BOOL	SetFont(int iFont = FONT_SONGTI);

	// ȡ���ַ������س���
	int		GetLen(LPCTSTR p0,LPCTSTR p1 = NULL,int iFontSize = 12);

	//[xialin 2008/08/19]add-->dwFrameColor ֧�ֲ�ɫ�߿�
	// �������֣�����dwFlag������(DTF_UnderLine|DTF_Bold|DTF_BlackFrame)���������,dwBkColor��ʾ���ֵı���ɫ
	void	DrawText(RECT* pRect,LPCTSTR str,DWORD dwColor, DWORD dwFrameColor, int iFontSize = 12,DWORD dwFlag = 0,DWORD dwBkColor = 0);

	// �������֣�����dwFlag������(DTF_UnderLine|DTF_Bold|DTF_BlackFrame)���������,dwBkColor��ʾ���ֵı���ɫ,�������죬��ת
	void    DrawTextFX(int x,int y,LPCTSTR str,DWORD dwColor,int iFontSize = 12,DWORD dwFlag = 0,float fScaleX = 1.0,float fScaleY = 1.0,float fRotY = 0,DWORD dwBackColor = 0);

	// ���Ʋ�������
	void	DrawTextPart(int x,int y,LPCTSTR str,DWORD dwColor,int iOffH,int iFontSize = 12,DWORD dwFlag = 0,DWORD dwBkColor = 0);

	// ���ƹ�������
	// iOff������ƫ��
	// iDisArea�����������ؼ��
	// iDisLine��ÿ�м�����ؼ��
	int		DrawTextScroll(int x,int y,LPCTSTR str,DWORD dwColor,int iw,int ih,UINT iOff = 0,int iDisArea = 16,int iDisLine = 0,int iFontSize = 12,DWORD dwFlag = 0,DWORD dwBkColor = 0);
};

extern CFontManager g_Font;