#pragma once


#define WIID_STORAGE_TOP			(WIID_STORAGE	+	1)		//��Ų TOP
#define WIID_STORAGE_CENTER			(WIID_STORAGE	+	2)		//��Ų CENTER
#define WIID_STORAGE_BOTTOM			(WIID_STORAGE	+	3)		//��Ų BOTTOM

#define WIID_STORAGE_CLOSE			(WIID_STORAGE	+	5)		//Close

#define WIID_STORAGE_MIDDLE			(WIID_STORAGE	+	10)		//��Ų ���� ��

#define WIID_STORAGE_TITLE			(WIID_STORAGE	+	15)		//Ÿ��Ʋ

#define WIID_STORAGE_SKIN		 	(WIID_STORAGE	+	30)		//��ٴ� ��Ų
#define WIID_STORAGE_SKIN_UP_LINE	(WIID_STORAGE	+	31)		//��ٴ� ��Ų ��� ���
#define WIID_STORAGE_SKIN_DOWN_LINE	(WIID_STORAGE	+	32)		//��ٴ� ��Ų �ϴ� ���

#define WIID_STORAGE_ELY_SAVE		(WIID_STORAGE	+	40)		//Ely ����
#define WIID_STORAGE_ELY_LOAD		(WIID_STORAGE	+	50)		//Ely ���

#define WIID_STORAGE_PAGE_UP		(WIID_STORAGE	+	60)		//��ũ�ѹ�
#define WIID_STORAGE_PAGE_DOWN		(WIID_STORAGE	+	70)		//��ũ�ѹ�
#define WIID_STORAGE_SLIDER			(WIID_STORAGE	+	80)		//��ũ�ѹ�

#define WIID_STORAGE_GRID			(WIID_STORAGE	+	90)		//�� Grid 

#define WIID_STORAGE_INPUT_ELY		(WIID_STORAGE	+	100)	//Ely �Է�

#define WIID_STORAGE_ELY_TEXT		(WIID_STORAGE	+	110)	//�����ݾ� ����
#define WIID_STORAGE_ELY			(WIID_STORAGE	+	115)	//����Ǿ� �ִ� Ely
#define WIID_STORAGE_ELY_IMG		(WIID_STORAGE	+	120)	//Ely Image

#define WIID_STORAGE_GRID_LINE		(WIID_STORAGE	+	130)	//Grid Line


const int DEFAULT_STORAGE_SLOT	= 4;			/**< �⺻ ���� �� <br> */
const int LINE_SLOT				= 4;			/**< �� ���ο� ���� ���� �� <br> */
const int MAX_STORAGE_SLOT		= 16;			/**< �ִ� ���� �� <br> ��������� �ƴ� �������̽��� <br> */

class SPWindow;
class SPWindowStatic;
class SPWindowEdit;
class SPWindowButton;
class SPWindowGrid;
class SPWindowSlider;


/**
* @class SPWindowStorage
* @brief â�� ������
* @author Jinhee
* @version 00.00.01
* @date 2005.7.14
* @bug ����
* @warning 
*/
class SPWindowStorage : public SPWindow {

public:
	SPWindowStorage( INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowStorage();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

	virtual void Show(bool bWithChild = true);

	void Refresh();

protected:
	/**
	 * Sub Control�� ����� <br> 
	 @param NONE
	 @return NONE
	*/
	void CreateSubWindow();
	
	/**
	* Slot �� ������ Dest������ �����Ѵ� <br> 
	* //[2006/6/22] ��� ��ü
	@param NONE
	@return NONE
	*/
	//void SetSlotPos();	
	
	/**
	 * ������ �����Ѵ� <br> 
	 * //[2006/6/22] ��� ��ü
	 @param NONE
	 @return NONE
	*/
	//void SlotRender();

	/**
	 * ������ �����ϴ� �ݾ��� �����ش� <br>
	 @param  UINT64	iSaveEly
	 @return bool
	*/
	bool SendSaveEly(UINT64	iSaveEly);
	
	/**
	 * ������ ã�� �ݾ��� �����ش� <br>
	 @param UINT64 iLoadEly
	 @return bool
	*/
	bool SendLoadEly(UINT64 iLoadEly);

public:		

protected:
	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()	

	virtual int OnCursorEnter	( WPARAM, LPARAM );
	virtual int OnCursorOut		( WPARAM, LPARAM );
	virtual int OnCursorLDown	( WPARAM, LPARAM );
	virtual int OnCursorLUp		( WPARAM, LPARAM );	
	virtual int OnRefresh		( WPARAM, LPARAM );	

	int OnCursorMove	(WPARAM wParam, LPARAM lParam);
	int OnGridDown		(WPARAM wParam, LPARAM lParam);
	int OnGridUp		(WPARAM wParam, LPARAM lParam);

	virtual int OnToolTipEnter	( WPARAM, LPARAM );
	virtual int OnToolTipOut	( WPARAM, LPARAM );
	virtual int OnToolTipMove	( WPARAM, LPARAM );
	
	int InitSlot		(WPARAM wParam, LPARAM lParam);		//������ �ʱ�ȭ �Ѵ�
	int SetExtendSlot	(WPARAM wParam, LPARAM lParam);		//������ Ȯ���Ѵ�

	int OnUpdateEly		(WPARAM wParam, LPARAM lParam);
	int OnSaveEly		(WPARAM wParam, LPARAM lParam);
	int OnLoadEly		(WPARAM wParam, LPARAM lParam);
	int	OnInputEly		(WPARAM wParam, LPARAM lParam);

	int OnItemSetting	(WPARAM wParam, LPARAM lParam);
	int OnItemClear		(WPARAM wParam, LPARAM lParam);
	int OnItemAllClear	(WPARAM wParam, LPARAM lParam);
	int OnItemSetStack	(WPARAM wParam, LPARAM lParam);
	int OnItemSetIconSelect(WPARAM wParam, LPARAM lParam);
	int OnItemDisable	(WPARAM wParam, LPARAM lParam);

	int	OnButtonPageUp		( WPARAM wParam, LPARAM lParam );
	int	OnButtonPageDown	( WPARAM wParam, LPARAM lParam );
	int	OnSliderPageUp		( WPARAM wParam, LPARAM lParam );
	int	OnSliderPageDown	( WPARAM wParam, LPARAM lParam );
	int	OnSliderPageNum		( WPARAM wParam, LPARAM lParam );
	int OnSliderButtonUp	( WPARAM wParam, LPARAM lParam );

	int OnClose				( WPARAM wParam, LPARAM lParam );

	// }}

protected:	
	SPWindowSlider* m_pSlider;
	SPWindowGrid*	m_pGrid;

	SPWindowEdit*	m_pElyEdit;
	SPWindowButton*	m_pElySave;	
	SPWindowButton* m_pElyLoad;
	SPWindowStatic*	m_pStorageEly;

	SPWindow*		m_pGridLine[MAX_STORAGE_SLOT]; /**< �׸��庰 �ܰ��� <br> */

	int		m_iSlotCount;						/**< Real Slot <br> */
	int		m_iViewSlotCount;					/**< Render Slot Count <br> */
	
	int		m_iMaxPage;							/**< �ִ� ������(����)�� <br> */
	int		m_iCurPage;							/**< ���� ������(����)�� <br> */

	char	m_szStorageEly[64];					/**< â�� ����Ǿ� �ִ� �ݾ� ���ڿ� <br> */
};
