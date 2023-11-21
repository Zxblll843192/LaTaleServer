#pragma once


enum PAGE_SELECT {
	PAGE_SELECT_BUNDLE_PREV		= 0,		/**< ���� ������ ���� <br> */
	PAGE_SELECT_PREV			= 1,		/**< ������ ������ ���� <br> */
	PAGE_SELECT_NEXT			= 2,		/**< ������ ������ ���� <br> */
	PAGE_SELECT_BUNDLE_NEXT		= 3,		/**< ���� ������ ���� <br> */
	PAGE_SELECT_MAX				= 4,
};

const int PAGE_START			= 1;		/**< ��Ʈ�� ������ ��ư ID <br> */
const int NUMBER_START			= 10;		/**< ��Ʈ�� �ѹ��� ID <br> */
const int MAX_BUNDLE			= 10;		/**< ���鳻 �������� �ִ� ���� <br> */

class SPWindowPageSelect :	public SPWindow
{
public:	
	SPWindowPageSelect(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent);
	~SPWindowPageSelect();

	virtual void Init();
	virtual void Clean();	
	virtual void Process(float fTime);	
	virtual void Render(float fTime);
	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = false);	
	
	/**
	 * ��ư ����� ���� <br>
	 @param PAGE_SELECT buttonType
	 @param int width
	 @param int height
	 @return NULL
	*/
	void SetPageButtonSize(PAGE_SELECT iButton, int iWidth, int iHeight);
	
	/**
	 * ���� ����� ���� <br>
	 @param int width
	 @param int height
	 @return NULL
	*/
	void SetNumberSize(int iWidth, int iHeight);
	
	/**
	 * ���� �÷��� ���� <br>
	 @param D3DXCOLOR
	 @return NULL
	*/
	void SetNumberColor(D3DXCOLOR FontColor);
	
	/**
	 * ��Ʈ�Ѱ� ���� ���� <br>
	 @param int iInterval
	 @return NULL
	*/
	void SetControlInterval(int iInterval);
	
	/**
	 * ��ư �̹��� ���� <br>
	 @param PAGE_SELECT iButton
	 @param const char* szImage
	 @param int iSrcX
	 @param int iSrcY
	 @return NULL
	*/
	void SetPageButtonImage(PAGE_SELECT iButton, const char* szImage, int iSrcX, int iSrcY);
	
	/**
	* ��ư �̹��� ���� <br>
	@param PAGE_SELECT iButton
	@param const char* szImage
	@param int iSrcX
	@param int iSrcY
	@return NULL
	*/
	void SetPageButtonImageHit(PAGE_SELECT iButton, const char* szImage, int iSrcX, int iSrcY);
	
	/**
	* ��ư �̹��� ���� <br>
	@param PAGE_SELECT iButton
	@param const char* szImage
	@param int iSrcX
	@param int iSrcY
	@return NULL
	*/
	void SetPageButtonImagePush(PAGE_SELECT iButton, const char* szImage, int iSrcX, int iSrcY);
	
	/**
	* ��ư �̹��� ���� <br>
	@param PAGE_SELECT iButton
	@param const char* szImage
	@param int iSrcX
	@param int iSrcY
	@return NULL
	*/
	void SetPageButtonImageDisable(PAGE_SELECT iButton, const char* szImage, int iSrcX, int iSrcY);	

	/**
	* �ִ� �������� ȭ�鿡�� ������ ������ ���� ���� <br>
	@param int iMaxPage
	@param int iBundle = MAX_BUNDLE
	@return NULL
	*/
	void SetMaxPageInfo(int iMaxPage, bool bInit = true, int iBundle = MAX_BUNDLE);

	/**
		�ش� �������� ���õȰ����� �����ش�.
		@param int iPage
	 */
	void SetSelectPage(int iPage) ;
	

protected:
	/**
	 * ��Ʈ�� ���ġ�� �Ѵ� <br>
	 @param int iViewPage = 0
	 @return NULL
	*/
	void ArrangeControl(int iViewPage = 0);
	
	/**
	 * ��Ʈ�� ���� ǥ���� ������Ʈ �Ѵ� <br>
	 @param int iBundle = MAX_BUNDLE
	 @return NULL
	*/
	void UpdateContorl(int iBundle = MAX_BUNDLE);
	

protected:
	SPIMESSAGE_OBJ_MAP_DECLARE()
	virtual int OnPageClick		(unsigned int uiID, WPARAM wParam, LPARAM lParam);		/**< ������ ���� ��ư ���� <br> */
	virtual int OnNumberClick	(unsigned int uiID, WPARAM wParam, LPARAM lParam);		/**< ���� ���� ��ư ���� <br> */	


private:	
	SPWindowButton*			m_pPageMove[PAGE_SELECT_MAX];
	SPWindow*				m_pNumber[MAX_BUNDLE];

	bool					m_bShowDebugRect ;	
	D3DXCOLOR				m_SelectColor;
	RECT					m_rtSelect;
	int						m_iInterval;

	int						m_iMaxPage;				/**< �ִ� ������ <br> */
	int						m_iMaxBundle;			/**< �ִ� ���� <br> */
	int						m_iBundleUnit;			/**< ���� ���� <br> */
	int						m_iViewPage;			/**< ������ ������ ���� <br> ������ ���� ��ư�� ���� <br> */

	int						m_iPage;				/**< ���� ������ ������ ������ <br> */
	int						m_iBundle;				/**< ������ ������ ������ <br> */
	int						m_iSelectPage;			/**< ���� ������ <br> m_iBundle * m_iBundleUnit + m_iPage <br> */
	
};
