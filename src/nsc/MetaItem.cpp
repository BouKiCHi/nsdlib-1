/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

#include "StdAfx.h"
#include "MetaItem.h"

/****************************************************************/
/*					�O���[�o���ϐ��i�N���X�����ǁE�E�E�j		*/
/****************************************************************/
extern	OPSW*			cOptionSW;	//�I�v�V�������ւ̃|�C���^�ϐ�

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		const	char	_strName[]	identifier
//	���Ԓl
//				����
//==============================================================
MetaItem::MetaItem(const char _strName[]):
	m_identifier(_strName),
	m_size(0),
	m_offset(0)
{
	//Debug message�@�i���������o�͂���̂Œ��ӁB�j
	if(cOptionSW->iDebug & DEBUG_Meta_Create){
		_COUT << _T("Create Meta Object : ") << m_identifier << endl;
	}
}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
MetaItem::~MetaItem(void)
{
	clear();

	//Debug message�@�i���������o�͂���̂Œ��ӁB�j
	if(cOptionSW->iDebug & DEBUG_Meta_Delete){
		_COUT << _T("Delete Meta Object : ") << m_identifier << endl;
	}
}

//==============================================================
//		�N���A
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MetaItem::clear(void)
{
	//----------------------
	//Local�ϐ�
	list<	MetaItem*>::iterator	itItem;

	//----------------------
	//clear
	m_data.clear();

	//----------------------
	//Delete Class
	if(!ptcItem.empty()){
		itItem = ptcItem.begin();
		while(itItem != ptcItem.end()){
			delete *itItem;
			itItem++;
		}
		ptcItem.clear();
	}

	m_size = 0;
}

//==============================================================
//		�R�[�h�T�C�Y�̎擾
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//		size_t
//==============================================================
size_t		MetaItem::getSize()
{
	return(m_size);
}

//==============================================================
//		�R�[�h�̃I�t�Z�b�g�A�h���X�̎擾
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//		size_t
//==============================================================
size_t	MetaItem::getOffset()
{
	return(m_offset);
}

//==============================================================
//		�I�t�Z�b�g�A�h���X�̐ݒ�
//--------------------------------------------------------------
//	������
//		size_t	_offset
//	���Ԓl
//				����
//==============================================================
size_t	MetaItem::SetOffset(size_t _offset)
{
	//----------------------
	//Local�ϐ�
	list<	MetaItem*>::iterator	itItem;
	size_t	i = 0;

	//Debug message�@�i���������o�͂���̂Œ��ӁB�j
	if(cOptionSW->iDebug & DEBUG_Meta_Set){
		_COUT << _T("Object Address [0x") << hex << setw(4) << setfill(_T('0')) << _offset << _T("]: ");
		while(i < m_data.size()){
			_COUT	<<	hex	<<	setw(2)	<<	setfill(_T('0'))	<<	(unsigned int)(m_data[i] & 0xFF)	<<	_T(" ");
			i++;
		}
		_COUT  << dec	<< _T(": ") << m_identifier << endl;
	}

	m_offset = _offset;
	_offset	+= m_data.size();

	if(!ptcItem.empty()){
		itItem = ptcItem.begin();
		while(itItem != ptcItem.end()){
			_offset = (*itItem)->SetOffset(_offset);
			itItem++;
		}
	}

	//���̃I�u�W�F�N�g�̃T�C�Y�i�œK����j
	m_size = _offset - m_offset;

	//Size �� ID �̕������Z
	_offset += 8;

	return(_offset);
}

//==============================================================
//		�R�[�h�̎擾
//--------------------------------------------------------------
//	������
//					size_t	�Y����
//	���Ԓl
//		unsigned	char	���e
//==============================================================
unsigned	char	MetaItem::getData(size_t n)
{
	unsigned	char	iData;
	
	if((n<0) || (n>=m_size)){
		iData = 0xFF;
	} else {
		iData = m_data[n];
	}

	return(iData);
}

//==============================================================
//		�R�[�h�̎擾
//--------------------------------------------------------------
//	������
//		string*		_str
//	���Ԓl
//				����
//==============================================================
void	MetaItem::getData(string* _str)
{
	//----------------------
	//Local�ϐ�
	list<	MetaItem*>::iterator	itItem;

	_str->append(m_data);

	if(!ptcItem.empty()){
		itItem = ptcItem.begin();
		while(itItem != ptcItem.end()){
			(*itItem)->getMetaData(_str);
			itItem++;
		}
	}
}

//==============================================================
//		�R�[�h�̎擾
//--------------------------------------------------------------
//	������
//		string*		_str
//	���Ԓl
//				����
//==============================================================
void	MetaItem::getMetaData(string* _str)
{
	string	strSize;

	strSize.resize(4);

	//SIZE
	strSize[0] = (unsigned char)(m_size      ) & 0xFF;
	strSize[1] = (unsigned char)(m_size >>  8) & 0xFF;
	strSize[2] = (unsigned char)(m_size >> 16) & 0xFF;
	strSize[3] = (unsigned char)(m_size >> 24) & 0xFF;
	_str->append(strSize);

	//ID
	_str->append(m_identifier, 4);

	//Data
	getMetaData(_str);
}

//==============================================================
//		�R�[�h�̐ݒ�
//--------------------------------------------------------------
//	������
//		string*		_str
//	���Ԓl
//				����
//==============================================================
void	MetaItem::setMetaData(string* _str)
{
	m_data.clear();
	m_data.assign(*_str);
	m_size = m_data.size();
}

