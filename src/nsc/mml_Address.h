#pragma once
#include "musicevent.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class mml_Address :
	public MusicEvent
{
//�����o�[�֐�
public:
	mml_Address(unsigned char _code, const char _strName[]="Address");
	~mml_Address(void);

				void	set_Address(unsigned int _addr);
	unsigned	int		get_Address(void);
};
