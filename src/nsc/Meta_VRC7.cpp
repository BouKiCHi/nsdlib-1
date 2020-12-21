/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

#include "StdAfx.h"
#include "Meta_VRC7.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		NSF_Header*			_nsf_hed	NSF�w�b�_�[
//		const		char	_strName[]	�N���X�̖��O
//	���Ԓl
//				����
//==============================================================
Meta_VRC7::Meta_VRC7(MMLfile* MML, const char _strName[]):
	MetaItem(_strName)
{
	int	_vrc7	= MML->GetInt();

	if((_vrc7 < 0)||(_vrc7 > 1)){
		MML->Err(_T("#VRC7�́A0��1�Ŏw�肵�Ă��������B"));
	}

	m_size = 1;
	m_data.resize(m_size);

	m_data[0] = (char)_vrc7;
}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
Meta_VRC7::~Meta_VRC7(void)
{
}
