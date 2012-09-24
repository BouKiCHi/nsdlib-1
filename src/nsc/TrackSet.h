#pragma once
#include "MusicItem.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class TrackSet :
	public MusicItem
{
//�����o�[�ϐ�
protected:
	unsigned	int				m_id;		//ID

private:
//static	const	Command_Info	Command[];	//�R�}���h�̏��
	map<int,	MusicTrack*	>	ptcTrack;	//�g���b�N�E�I�u�W�F�N�g�̃|�C���^
				MusicTrack*		nowTrack;	//�R���p�C�����̃g���b�N�ԍ�
	unsigned	int				iTrack;		//�R���p�C�����̃g���b�N�ԍ�
	unsigned	int				maxTrack;	//�g���b�N�ԍ��̍ő�l
				bool			fSub;		//�T�u���[�`���L�q�u���b�N���ǂ����̃t���O

//�����o�[�֐�
public:
				TrackSet(MMLfile* MML, unsigned int _id, bool _sub, const char _strName[] = "==== [ Track Set ]====");
				~TrackSet(void);

		void	Fix_Address(map<int, Sub*>* ptcSub, map<int, Envelop*>* ptcEnvelop);

	MusicTrack*	makeTrack(int _track);
	MusicTrack*	getTrack(int _track);
	void	getAsm(MusicFile* MUS);
};
