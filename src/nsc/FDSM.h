#pragma once
#include "MusicItem.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class FDSM :
	public MusicItem
{
//�����o�[�ϐ�
private:
	unsigned	int	m_id;
//static	const	Command_Info	Command[];	//�R�}���h�̏��

//�����o�[�֐�
public:
				FDSM(MMLfile* MML, unsigned int _id, const wchar_t _strName[] = L"==== [ FDSM ]====");
				~FDSM(void);
		void	getAsm(MusicFile* MUS);
};
