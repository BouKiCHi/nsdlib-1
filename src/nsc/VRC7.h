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
	unsigned	int		m_id;
				bool	f_Use;				//MML���Ŏg���邩�H

//static	const	Command_Info	Command[];	//�R�}���h�̏��

//�����o�[�֐�
public:
				VRC7(MMLfile* MML, unsigned int _id, const wchar_t _strName[] = L"VRC7");
				~VRC7(void);
		void	setUse(void){f_Use = true;};
		bool	chkUse(void){return(f_Use);};
		void	getAsm(MusicFile* MUS);
};
