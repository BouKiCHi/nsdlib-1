/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

#pragma once
#include "MetaItem.h"

/****************************************************************/
/*																*/
/*			クラス定義											*/
/*																*/
/****************************************************************/
class Meta_DATA :
	public MetaItem
{
//メンバー変数
private:

//メンバー関数
public:
	Meta_DATA(string* nsf_data, const char _strName[] = "DATA");
	~Meta_DATA(void);
};
