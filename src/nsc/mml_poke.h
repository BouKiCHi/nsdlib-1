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
	mml_poke(unsigned int _addr , unsigned char _data,  const char _strName[]="Poke");
	~mml_poke(void);
};
