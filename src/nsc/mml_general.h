#pragma once
#include "musicevent.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class mml_general :
	public MusicEvent
{
//�����o�[�֐�
public:
	mml_general(unsigned char _code, const _CHAR _strName[]=_T("General"));
	mml_general(unsigned char _code, MMLfile* MML, const _CHAR _strName[]=_T("General"));
	mml_general(unsigned char _code, const char _data, const _CHAR _strName[]=_T("General"));
	mml_general(unsigned char _code, const char _n1, const char _n2, const _CHAR _strName[]=_T("General"));
	mml_general(unsigned char _code, const char _n1, const char _n2, const char _n3, const char _n4, const _CHAR _strName[]=_T("General"));
	~mml_general(void);
};
