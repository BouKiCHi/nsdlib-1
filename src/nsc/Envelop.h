#pragma once
#include "MusicItem.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class Envelop :
	public MusicItem
{
//�����o�[�ϐ�
private:
	unsigned	int		m_id;
				int		Loop_Normal;
				int		Loop_Release;
				bool	Release;
				int		ptEnvelop;

//static	const	Command_Info	Command[];	//�R�}���h�̏��

//�����o�[�֐�
public:
				Envelop(MMLfile* MML, unsigned int _id, const wchar_t _strName[] = L"==== [ Envelop ]====");
				~Envelop(void);
		void	setHold(int length);
		void	sweep(MMLfile* MML);
		void	getAsm(MusicFile* MUS);
};
