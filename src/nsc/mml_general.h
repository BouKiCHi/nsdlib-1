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
	~mml_general(void);
};
