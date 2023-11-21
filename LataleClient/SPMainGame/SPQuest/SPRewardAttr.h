#pragma once

class SPQuestAttr;

/**
_Reward_EXP	����ġ ����ġ
_Reward_Ely	���� ����ġ
_Reward_Fame	��ġ ����ġ
_Reward_EffectID1	���� ȿ��1
_Reward_EffectID2	���� ȿ��2
_Reward_EffectID3	���� ȿ��3
_Reward_EffectID4	���� ȿ��4
_Reward_ItemID1	���� ������1
_Reward_StackCount1	���� ������ ��1
_Reward_Rare1	���� ������ ���1
_Reward_ItemID2	���� ������2
_Reward_StackCount2	���� ������ ��2
_Reward_Rare2	���� ������ ���2
_Reward_ItemID3	���� ������3
_Reward_StackCount3	���� ������ ��3
_Reward_Rare3	���� ������ ���3
_Reward_ItemID4	���� ������4
_Reward_StackCount4	���� ������ ��4
_Reward_Rare4	���� ������ ���4
_Reward_ItemID5	���� ������5
_Reward_StackCount5	���� ������ ��5
_Reward_Rare5	���� ������ ���5
_Reward_ItemID6	���� ������6
_Reward_StackCount6	���� ������ ��6
_Reward_Rare6	���� ������ ���6
_Reward_Gpoint	��� ����Ʈ ����ġ
*/

class SPRewardAttr {
public:
	SPRewardAttr();
	~SPRewardAttr();

	void SetRewardAttr(int iID, int iExp, int iEly, int iFame);

protected:
	void Clear();

public:
	int					m_iID;
	int					m_iExp;
	int					m_iEly;
	int					m_iFame;
	int					m_iEffect[QUESTREWARD_MAX_EFFECTID];
	SPQuestItem			m_Item[QUESTREWARD_MAX_ITEM];
	int					m_iGuildPoint;
};

