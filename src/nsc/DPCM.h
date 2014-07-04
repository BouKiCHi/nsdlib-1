#pragma once
#include "MusicItem.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class DPCM :
	public MusicItem
{
//�����o�[�ϐ�
private:
	unsigned	int		m_id;
				bool	f_Use;				//MML���Ŏg���邩�H
	unsigned	char	_DPCM_size;

//static	const	Command_Info	Command[];	//�R�}���h�̏��

//�����o�[�֐�
public:
				DPCM(FileInput* DPCMfile, unsigned int _id, const wchar_t _strName[] = L"==== [ DPCM ]====");
				~DPCM(void);
	unsigned	char	getDPCMsize(void){return(_DPCM_size);};
				void	getAsm(MusicFile* MUS);
};
