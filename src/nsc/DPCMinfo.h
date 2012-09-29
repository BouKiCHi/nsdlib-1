#pragma once
#include "MusicItem.h"


typedef	struct{
				string	file;
	unsigned	char	ctrl;
	unsigned	char	DA;
} nsd_dpcm_info;

typedef struct{
	char		Control;			/*	I/O 0x4010	*/
	char		DA;					/*	I/O 0x4011	*/
	char		Address;			/*	I/O 0x4012	*/
	char		Size;				/*	I/O 0x4013	*/
} nsd_dpcm;

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class DPCMinfo :
	public MusicItem
{
//�����o�[�ϐ�
private:
	unsigned	char	max_number;
	unsigned	char	m_id;
	nsd_dpcm_info		infoDPCM[128];
	map< string, DPCM*>	ptcDPCM;	//��PCM
//static	const	Command_Info	Command[];	//�R�}���h�̏��

//�����o�[�֐�
public:
						DPCMinfo(MMLfile* MML, const char _strName[] = "==== [ DPCMinfo ]====");
						~DPCMinfo(void);
				void	setKey(MMLfile* MML, int key);
				void	setNote(MMLfile* MML, int note);
	unsigned	int		setDPCMoffset(unsigned	int _offset);
				void	getDPCMCode(string* _str);
				void	getAsm(MusicFile* MUS);
};
