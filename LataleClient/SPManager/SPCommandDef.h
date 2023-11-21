// Copyright (C) metalgeni
//***************************************************************************
// System Name : 
// Comment : 
// Creation : metalgeni 2005-04-7 ���� 1:30:38
//***************************************************************************


#pragma once

#define CHEAT_STRING_MAX 256


/*
	Cheat Command Format

	<Cheat Command>	::= <Command>{<whitespace>|<comma>}<ParameterList>
	<ParamterList>	::= <Param1>[{<whitespace>|<comma>}<ParameterList>]

	
	EX)	warp 100 100

*/
/*
 *	history

	7/13 
		goto �߰� : �ش� ĳ���� ��ó�� �̵�
		haul �߰� : �ش� ĳ���͸� �ڽ��� ��ó�� ��ȯ
		where ���� : �ٸ� ä�λ��� �ش� ĳ���Ϳ� ���� ���� �߰�. ä�� ������ ��ȿ

		* charName�� @(���� ĳ����) ��� ���� 

 */

//////////////////////////////////////////////////////////////////////////
// TODO : Cheat list, command

// Server Side
// "warp" X Y : X,Y�� �����Ѵ�.

// portal charName,posX,posY[,stageID,mapGroupID]		: posX,posY�� ����
// hp charName,HP[,maxHP]								: HP ����
// sp charName,SP[,maxSP]								: SP ����
// ely charName,value									: Ely ����
// Exp charName,value									: EXP ����
// SkillPoint charName,value							: Skill Point ����
// Level charName,value									: Level ����
// GiveItem charName,itemID[,amount,rare]				: Item ���� ȹ��
// LearnSkill charName,skillID							: Skill ���� ȹ��
// AddTitle charName, TitleID							: Ÿ��Ʋ ���� ȹ��
// ExtendSlot charName, ContainerType, OptionalCount	: �����̳� Ȯ��.
// Speedup charname,x_Delta[,y_Delta]					: ĳ���� �ӵ� ����. ��) x_Delta = 100�ϰ��, ���� �ӵ��� 100% ��Ű��� �ǹ�
// MapEvent CharName,mapEventType,mapEventID			: �ش� mapEvent�� �̵�
// Notice displayTime displayOption message				: displayTime = displayOption = 0(reserved). �޼����� �߰��� �������, ���๮��(\n) ����. 
//														:EX) notice 0 0 �����ٿ��\n�α׾ƿ��ٶ��ϴ�.
// ServerStatus charName								: ���� ���� ���. FTP,nPC,nMOB,nLootingBag ����
// Where charName targetName							: targetName ĳ���� ��ġ ���. charName �������� �˷���
// Version charName										: ���� ���� �������. ������ charName �������� ����

// goto			<charName>								// �ش� ĳ���� ��ġ�� �ڽ��� �̵�
// haul			<charName>								// �ش� ĳ���͸� ��ȯ(�ڽ��� ��ġ�� �̵�) ��Ŵ(������)
// Where		[<TargetCharName> | "@"]				// return ="<targetName> [stageID,mapGroupID] posX=[%d] posY=[%d]"

// Client Side

// bgm [0,1]											: BGM On/Off
// cls													: ä��â ���� ��� �����
// CLS													: ä��â ���� ��� �����
// stat													: �⺻ ���� �����ֱ�
// stat_ex												: Ȯ�� ���� �����ֱ�
// fxg													: FX �׷� �����ֱ�
// se	[0,1]											: Sound Effect On/Off
// bgmvol	[0.0 ~ 1.0]									: BGM ����
// sevol	[0.0 ~ 1.0]									: SE ����
// TakeShot												: ��ũ���� ���
// contrast [0.0 ~ 1.0]									: Ǯ��ũ���϶� ���� ����
// SoundStatus											: ��� ���� �������ͽ� �����ֱ�

// BSON													: Beautyshop â ����
// LDTTest												: LDT���� ���� �׽�Ʈ




