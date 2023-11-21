
#pragma once

class SPEventModel;

class SPEventUnit {
public:
	SPEventUnit();
	SPEventUnit(SPEventModel** ppEventModel, float fX = 0.0f, float fY = 0.0f, LPARAM lParam = 0);
	~SPEventUnit();

	virtual void SetNull();
	virtual void Init();

	virtual void Process(float fTime);
	virtual void Render(float fTime);
	
	//void SetNull();
	void DeleteCondition();
	void DeleteItem();

	bool CreateEvent(SPEventUnit& pEvent);
	bool CreateEvent(int iID, EVENT_TYPE iType, string strName, int iStage, int iGroup, int iMap, 
		int iPosX, int iPosY, int iLeft, int iTop, int iRight, int iBottom, 
		string strImage, long lMessage, long lAction);

	bool AddCondition(int iCondition, int iValue);
	bool AddItem(int iItem, int iValue);

protected:
	int					m_iModelID;				// SPFXModel instance id	
	MODEL_CLASS_ID		m_ClassID;

	//FXPARAM			m_FXParam;				// �ܺο��� ������ ��
	//FXPARAM			m_FXCurUseParam;		// ���ο��� ������ �ν���Ʈ�� ��

	SPEventModel*		m_pEventModel;
	SPTexture**			m_ppCurImage;
	//SPGameObject*		m_pParent;
	
	//////////////////////////////////////////////////////////////////////////
	float				m_fCamX;
	float				m_fCamY;

	float				m_fAccumulateRender;	
	float				m_fAccumulateProcess;	

	// FrameAnimation
	int					m_iNoFrame;
	int					m_iCurFrame;
	int					m_iCurAlpha;	

	// Particle
	//UINT				m_iMaxRenderParticle;	// �ִ� �׸��� �ִ� ��
	//UINT				m_iMaxParticle;			// � ���� �ﱸ �����ų� 0�̸� �׻� m_iMaxRenderParticle�� ��´�.
	//UINT				m_iCurNOParticle;
	//std::vector<SPFXParticleInstance>	m_vParticleInstance;
	//SPFX_PARTICLE_MOVE	m_ParticleMove;

	// Common
	float				m_fCurRotateDegree;	
	float				m_fModelDelay;
	float				m_fCurDelay;
	D3DXCOLOR			m_RGBA;
	BOOL				m_BLightMap;
	RECT				m_RectSrc;
	RECT				m_RectAdjust;			// ��ƼŬ�϶� �������̴�..
	float				m_fScale;
	bool				m_bLRSwap;	

	//FXPARAM				m_FXParam;			// �ܺο��� ������ ��
	//FXPARAM				m_FXCurUseParam;	// ���ο��� ������ �ν���Ʈ�� ��	
	//FXUNIT_STATE		m_FUState;
	//int					m_iFollowParent;

	bool				m_bRenderCancel;

//private:
public:
	//////////////////////////////////////////////////////////////////////////
	// Event Struct...
	int				m_iEventID;						/**< Event ID not Index <br> */
	EVENT_TYPE		m_iType;						/**< Event Type <br> */
	std::string		m_strName;						/**< Name <br> */

	int				m_iStageID;						/**< Stage ID <br> */
	int				m_iMapGroupID;					/**< Map Group ID <br> */
	int				m_iMapID;						/**< Map ID <br> */
	
	int				m_iPosX;						/**< Map Pos X <br> */		
	int				m_iPosY;						/**< Map Pos Y <br> */

	int				m_iLeft;						/**< Check Area Left Pos <br> */
	int				m_iTop;							/**< Check Area Top Pos <br> */
	int				m_iRight;						/**< Check Area Right Pos <br> */
	int				m_iBottom;						/**< Check Area Bottom Pos <br> */

	std::string		m_strImage;						/**< Image Resource File <br> */
	long			m_lMessageID;					/**< Message Tabel ID <br> */

	long			m_lActionID;					/**< Behavior Action ID <br> */

	std::vector<SPEventCondition*> m_vpCondition;	/**< Check Condition List <br> */
	std::vector<SPEventItem*> m_vpItem;				/**< Check Item Condtion List <br> */	
};


