#pragma once
#include "MusicItem.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class FDSC :
	public MusicItem
{
//�����o�[�ϐ�
private:
	unsigned	int	m_id;
//static	const	Command_Info	Command[];	//�R�}���h�̏��

//�����o�[�֐�
public:
				FDSC(MMLfile* MML, unsigned int _id, const wchar_t _strName[] = L"==== [ FDSC ]====");
				~FDSC(void);
		void	getAsm(MusicFile* MUS);
};
