#pragma once
#include "MusicItem.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class N163 :
	public MusicItem
{
//�����o�[�ϐ�
private:
	unsigned	int	m_id;
//static	const	Command_Info	Command[];	//�R�}���h�̏��

//�����o�[�֐�
public:
				N163(MMLfile* MML, unsigned int _id, const wchar_t _strName[] = L"==== [ N163 ]====");
				~N163(void);
		void	getAsm(MusicFile* MUS);
};
