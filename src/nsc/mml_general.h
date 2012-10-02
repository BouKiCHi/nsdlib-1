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
	mml_general(unsigned char _code, const char _strName[]/*="General"*/);
	mml_general(unsigned char _code, MMLfile* MML, const char _strName[]/*="General"*/);
	mml_general(unsigned char _code, const char _data, const char _strName[]/*="General"*/);
	mml_general(unsigned char _code, const char _n1, const char _n2, const char _strName[]/*="General"*/);
	mml_general(unsigned char _code, const char _n1, const char _n2, const char _n3, const char _n4, const char _strName[]/*="General"*/);
	~mml_general(void);
};
