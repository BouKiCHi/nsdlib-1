#pragma once
#include "musicevent.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class mml_poke :
	public MusicEvent
{
//�����o�[�֐�
public:
	mml_poke(unsigned int _addr , unsigned char _data,  const _CHAR _strName[]=_T("Poke"));
	~mml_poke(void);
};
