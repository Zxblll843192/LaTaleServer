
// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPXMLParser.cpp
//	created:	2007/10/1   Time:12:51
//	purpose:	
//*********************************************************************/

#include "SPXMLParser.h"



//---------------------------------------------------------------------
SPXMLParser::SPXMLParser()
:m_pXDoc(NULL)
{
	Setup();
}




//---------------------------------------------------------------------
SPXMLParser::~SPXMLParser()
{
	Release();
}



//---------------------------------------------------------------------
BOOL SPXMLParser::Setup()
{
	m_pXDoc = NULL;
	CoInitialize(NULL);
	CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_ALL, IID_IXMLDOMDocument, (void**)&m_pXDoc );

	return TRUE;
}



//---------------------------------------------------------------------
VOID SPXMLParser::Release()
{
	if(m_pXDoc == NULL) return;

	m_pXDoc->Release();
	CoUninitialize();
}




//---------------------------------------------------------------------
HRESULT SPXMLParser::Open(LPCTSTR filename)
{
	HRESULT hr;

	VARIANT_BOOL bRes;
	VARIANT var;

	var.vt = VT_BSTR;
	var.bstrVal = (_bstr_t)filename;

	hr = m_pXDoc->load(var, &bRes);

	return hr;
}


//---------------------------------------------------------------------
// Open from Stream
HRESULT SPXMLParser::OpenXML(char* pData)
{
	HRESULT hr;

	VARIANT_BOOL bRes;
	//VARIANT var;

	_bstr_t bstrText = pData;

	hr = m_pXDoc->loadXML(bstrText, &bRes) ;

	return hr;
}


//---------------------------------------------------------------------
/**
	��Ʈ�������� ���path �� ���(Element) �� ã�´�.
*/
XNodeList* SPXMLParser::FindElement(LPCTSTR ElementName)
{
	assert(m_pXDoc != NULL);
	IXMLDOMNodeList* pNodeList = NULL;
	m_pXDoc->selectNodes((_bstr_t)ElementName, &pNodeList); 
	return pNodeList;
}



//---------------------------------------------------------------------
/**
	�־��� ����� ���� ���(Element) �� ã�´�.
	@param XNode* pNode,		: ã�� ����� �θ���.
	@param LPCTSTR ElementName	: ã�� ��Ҹ�
*/

XNodeList* SPXMLParser::FindElement(XNode* pNode, LPCTSTR ElementName )
{	
	assert(pNode != NULL);	 
	IXMLDOMNodeList* pChildNodeList = NULL;
	pNode->selectNodes((_bstr_t)ElementName, &pChildNodeList); 
	return pChildNodeList;
}


//---------------------------------------------------------------------
/**
	�־��� Element ���� �Ӽ�(Attribute)���� �о� �´�.
	@param XNode* pNode			: ã�� �Ӽ��� ������ �ִ� ���, �� ��� : �Է�
	@param const char* AttrName : ã�� �Ӽ���:  �Է�
	@param char* AttrValue		: �Ӽ��� : ���(���ڿ�)
*/
int SPXMLParser::GetAttrValue2Text(XNode* pNode, const char* AttrName, char* AttrValue)
{
	wchar_t	wAttrName[256];
	IXMLDOMNode*			pAttrNode = NULL;	//�Ӽ��� '���'. �� ��Ҵ� �Ӽ��� �������� ���� �� �ִ�.
	IXMLDOMNamedNodeMap*	pMap = NULL;		//�Ӽ��� '���'���� 'ã��','�а�'..�ϱ� ���� Mapping �������̽�.
	VARIANT	var;


	::mbstowcs(wAttrName, AttrName, sizeof(wAttrName));	//�Էµ� �Ӽ��� �̸�(MBS)�� �����ڵ�(WCS)�� ��ȯ.


	pNode->get_attributes(&pMap);						//�־��� ��忡 �����Ǿ��� �Ӽ� ��ġ(�Ӽ� �� Attribute Map) �� �˻��Ѵ�.
	pMap->getNamedItem(wAttrName,&pAttrNode);			//�Ӽ� �㿡�� ���ϴ� �Ӽ��� ã�´�.
	pAttrNode->get_nodeValue(&var);						//�Ӽ��� ��� (VARIANT Ÿ��..�����ϰ� ��ȯ�Ͽ� ��� �ؾ���.)

	//�о� ���� �����͸� �ؽ�Ʈ ���·� ��ȯ, ����.
	::strcpy(AttrValue, (const char*)_bstr_t(var.bstrVal, FALSE));


	return TRUE;
}



//---------------------------------------------------------------------
// pNode ������ ����� ���� �о� �´�.
//
// <Scene>  -- Scene ������ ����� ���� �о� �´�. �Ӽ��� ����.
//     <FileName>..
//     <FrameStart>..
//     <FrameEnd>..
//     ...
// </Scene>
//
int SPXMLParser::GetElementValue(XNode* pNode, const char* ElementName, char* ElementValue, long index /*= 0*/)
{
	BSTR bstr;
	XNodeList* pChildList = FindElement(pNode, ElementName);
	XNode* pChildNode = NULL;
	pChildList->get_item(index, &pChildNode);					//������ ��Ұ� �ϳ������� ����..
	pChildNode->get_text(&bstr); 
	::strcpy(ElementValue,(const char*)_bstr_t(bstr, FALSE));		//@ fix.

	//m_SceneInfo.fFirstFrame = ::atoi(msg);

	return TRUE;

}
