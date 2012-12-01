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
				TrackSet(MMLfile* MML, unsigned int _id, bool _sub, const wchar_t _strName[] = L"==== [ Track Set ]====");
				~TrackSet(void);

		void	getAsm(MusicFile* MUS);
		void	Fix_Address(MusicFile* MUS);

	MusicTrack*	makeTrack(int _track);
	MusicTrack*	getTrack(int _track);

		void	SetEvent(MusicItem* _item);		//�C�x���g�̒ǉ�

		void	SetOctave(MMLfile* MML);
		void	SetOctaveInc();
		void	SetOctaveDec();
		void	SetOctaveOne_Inc();
		void	SetOctaveOne_Dec();

		void	SetVolume(MMLfile* MML);
		void	SetVolumeInc();
		void	SetVolumeDec();

		void	SetReleaseMode(MMLfile* MML);
		void	SetReleaseVoice(MMLfile* MML);
		void	SetReleaseVolume(MMLfile* MML);

		void	SetGatetime(MMLfile* MML);
		void	SetGatetime_u(MMLfile* MML);

		void	SetProtament(MMLfile* MML);
		void	SetSweep(MMLfile* MML);

		void	SetPoke(MMLfile* MML);
		void	SetVRC7_Write(MMLfile* MML);
		void	SetN163Channel(MMLfile* MML);
		void	Set_FME7_Frequency(MMLfile* MML);
};
