#pragma once
#include "musicevent.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class mml_repeat :
	public MusicEvent
{
//�����o�[�֐�
public:
	mml_repeat(const wchar_t _strName[]=L"Repeat(A) Start");
	~mml_repeat(void);
	void	set_count(unsigned char count);
};
