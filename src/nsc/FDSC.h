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
	unsigned	int		m_id;
				bool	f_Use;				//MML���Ŏg���邩�H

//static	const	Command_Info	Command[];	//�R�}���h�̏��

//�����o�[�֐�
public:
				FDSC(MMLfile* MML, unsigned int _id, const wchar_t _strName[] = L"==== [ FDSC ]====");
				~FDSC(void);
		void	getAsm(MusicFile* MUS);
		void	setUse(void){f_Use = true;};
		bool	chkUse(void){return(f_Use);};
};
