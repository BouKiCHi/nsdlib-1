#pragma once
#include "MusicEvent.h"

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
	mml_note(int _code, int length, int gatetime, bool slur, const _CHAR _strName[]=_T("Note"));
	~mml_note(void);
	void	SetTai(void);
};
