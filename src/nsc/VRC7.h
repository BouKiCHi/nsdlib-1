#pragma once
#include "MusicItem.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class VRC7 :
	public MusicItem
{
//�����o�[�ϐ�
private:
	unsigned	int	m_id;
//static	const	Command_Info	Command[];	//�R�}���h�̏��

//�����o�[�֐�
public:
				VRC7(MMLfile* MML, unsigned int _id, const wchar_t _strName[] = L"==== [ VRC7 ]====");
				~VRC7(void);
		void	getAsm(MusicFile* MUS);
};
