#pragma once
#include "MusicItem.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class DPCM :
	public FileInput, public MusicItem
{
//�����o�[�ϐ�
private:
	unsigned	int		m_id;
				bool	f_Use;				//MML���Ŏg���邩�H
	unsigned	char	_DPCM_size;

//�����o�[�֐�
public:
						DPCM(MMLfile* MML, const char* dmcfile, unsigned int _id, const _CHAR _strName[] = _T("==== [ DPCM ]===="));
						~DPCM(void);
	unsigned	char	getDPCMsize(void){return(_DPCM_size);};
				void	getAsm(MusicFile* MUS);
};
