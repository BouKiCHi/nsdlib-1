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
//static	const	Command_Info	Command[];	//�R�}���h�̏��

//�����o�[�֐�
public:
				Envelop(MMLfile* MML, const char _strName[] = "==== [ Envelop ]====");
				~Envelop(void);
};
