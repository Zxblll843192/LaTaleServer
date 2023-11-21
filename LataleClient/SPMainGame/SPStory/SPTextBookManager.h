

#pragma once

struct TEXTBOOK_FACTOR
{
	std::string strText;		// ���丮 ����
	std::string strImage;		// ��ȭ
	std::string strBGM;			// �����
	int			iPrePage ;		// ���� ������ Index (������ ù������)
	int			iNextPage ;		// ���� ������ Index (������ ������)
	int			iImageIndex ;	// ��ȭ�� �̹��� Index

	void Clear()
	{
		strText.clear();
		strImage.clear();
		strBGM.clear();
		iPrePage	= 0 ;
		iNextPage	= 0 ;
		iImageIndex = 0 ;
	}
	TEXTBOOK_FACTOR()
	{
		Clear();
	}
	~TEXTBOOK_FACTOR()
	{
		Clear() ;
	}
};


class SPTextBookManager
{
public:
	static SPTextBookManager* GetInstance();
	static void Release();

	bool Init();
	
	TEXTBOOK_FACTOR* GetStoryFactor(int iID);
	void SetTextBookID(int iTextBookID)		{	m_iTextBookID = iTextBookID ;	}
	int GetTextBookID()							{	return m_iTextBookID ;	}
	int	GetImageSrc(int iIndex, int& iPosX, int& iPosY);

private:
	SPTextBookManager();
	~SPTextBookManager();

	bool LoadLDTFile();

private:
	static SPTextBookManager* m_pkInstance;
	int	 m_iTextBookID ;

	std::map< int, TEXTBOOK_FACTOR > m_mStoryFactor;
};

extern SPTextBookManager* g_pkBookManger;

