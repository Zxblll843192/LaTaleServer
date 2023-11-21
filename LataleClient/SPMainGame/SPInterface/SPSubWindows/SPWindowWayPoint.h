#pragma once


class SPWindow;
class SPWindowStatic;
class SPWindowButton;
class SPWindowTreeBox;
struct TREEBOX_ITEM;

#define WIID_WAYPOINT_TOP						(WIID_WAYPOINT	+	1)
#define WIID_WAYPOINT_CENTER					(WIID_WAYPOINT	+	2)
#define WIID_WAYPOINT_BOTTOM					(WIID_WAYPOINT	+	3)

#define WIID_WAYPOINT_TITLE						(WIID_WAYPOINT	+	5)
#define WIID_WAYPOINT_CLOSE						(WIID_WAYPOINT	+	6)

#define WIID_WAYPOINT_LINE1						(WIID_WAYPOINT	+	7)
#define WIID_WAYPOINT_LINE2						(WIID_WAYPOINT	+	8)
#define WIID_WAYPOINT_LINE3						(WIID_WAYPOINT	+	9)

#define WIID_WAYPOINT_SKIN_TREE					(WIID_WAYPOINT	+	10)		//Ʈ�� ��Ʈ�� ��Ų
#define WIID_WAYPOINT_TREE						(WIID_WAYPOINT	+	20)		//Ʈ�� ��Ʈ��

#define WIID_WAYPOINT_SKIN_DESC					(WIID_WAYPOINT	+	100)	//���� ��Ų
#define WiID_WAYPOINT_DESC						(WIID_WAYPOINT	+	110)	//����

#define WIID_WAYPOINT_IMAGE						(WIID_WAYPOINT	+	150)	//�̸��� ���� ��ư
#define WIID_WAYPOINT_POSITION					(WIID_WAYPOINT	+	160)	//��ġ ��ư
#define WIID_WAYPOINT_MOVE						(WIID_WAYPOINT	+	170)	//�̵� ��ư

class SPTreeBoxItemQuest;

class SPWindowWayPoint : public SPWindow 
{
public:
	SPWindowWayPoint( INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);
	virtual ~SPWindowWayPoint();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);
	

protected:
	/**
	 * 
	 @param 
	 @return
	*/
	void InitSubWindow();
	
	/**
	 * �θ� ��带 ������Ʈ �Ѵ� <br> 
	 @param 
	 @return
	*/
	bool UpdateGroup();
	
	/**
	 * �� ��������Ʈ ��带 ������Ʈ �Ѵ� <br>
	 @param 
	 @return
	*/
	bool UpdateWayPoint();

	SPTreeBoxItemQuest* CreateTreeBoxItem( bool bMenuType );
	
	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);

	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnUpdateWayPoint	(WPARAM wParam, LPARAM lParam);
	int OnClose				(WPARAM wParam, LPARAM lParam);
	int OnImage				(WPARAM wParam, LPARAM lParam);
	int OnPosition			(WPARAM wParam, LPARAM lParam);
	int OnMovement			(WPARAM wParam, LPARAM lParam);
	int OnTreeBoxLButtonUp	(WPARAM wParam, LPARAM lParam);
	int OnMoveResult		(WPARAM wParam, LPARAM lParam);			//�̵� ��� ��Ŷ�� ������ �̵� ��ư�� Ǯ���ش�

private:
	SPWindowTreeBox*		m_pTreeBox;
	D3DXCOLOR				m_cStringColor;
	bool					m_bClickNotify;
	SPWindow*				m_pDesc;
	SPWindowButton*			m_pImage;				/**< �̸��� ���� <br> */
	SPWindowButton*			m_pPosition;			/**< ��ġ ���� <br> */
	SPWindowButton*			m_pMove;				/**< �̵� <br> */

	bool	m_bMoveRequest;			/**< �̵� ��û ��ư�� �������� <br> */
	float	m_fDeley;				/**< �̵� ��û ��ư ��Ȱ�� �ð� <br> */
	float	m_fAccumulate;			/**< �̵� ��û �ð� ���ſ� <br> */

	std::string				m_strNotSaveInfo;		/**< ������� ���� WayPoint�� ��� Ʈ�� ������ �̸��� �߰��� ���ڿ� <br> */
	std::string				m_strNotSave;			/**< ������� ���� WayPoint�� ��� Desc������ ��µ� ���ڿ� <br> */

	std::vector<TREEBOX_ITEM*> m_vGroupItem;		/**< �θ������ ������ ����ϴ� ���� <br> */
};



