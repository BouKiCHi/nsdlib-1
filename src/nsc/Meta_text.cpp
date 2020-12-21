/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

#include "StdAfx.h"
#include "Meta_text.h"

//==============================================================
//		コンストラクタ
//--------------------------------------------------------------
//	●引数
//		NSF_Header*			_nsf_hed	NSFヘッダー
//		const		char	_strName[]	クラスの名前
//	●返値
//				無し
//==============================================================
Meta_text::Meta_text(MusicHeader* Header, const char _strName[]):
	MetaItem(_strName)
{
	m_data.clear();
	m_size = 0;

	append(&Header->text);
}

//==============================================================
//		デストラクタ
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
//==============================================================
Meta_text::~Meta_text(void)
{
}
