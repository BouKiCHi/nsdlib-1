#pragma once
#include "musicevent.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class mml_note :
	public MusicEvent
{
//�����o�[�֐�
public:
	mml_note(int _code, int length, int gatetime, bool slur, const wchar_t _strName[]=L"Note");
	~mml_note(void);
	void	SetTai(void);
};
