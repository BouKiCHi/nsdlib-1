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
				MusicTrack*		nowTrack;	//�R���p�C�����̃g���b�N
				int				iTrack;		//�R���p�C�����̃g���b�N�ԍ�
				int				maxTrack;	//�g���b�N�ԍ��̍ő�l
				bool			fSub;		//�T�u���[�`���L�q�u���b�N���ǂ����̃t���O
				bool			fSE;		//SE���ǂ����̃t���O
	unsigned	int				TrackPt;	//
	unsigned	int				TrackLine;	//
				int				Priority;	//
//�����o�[�֐�
public:
				TrackSet(MMLfile* MML, unsigned int _id, bool _sub, bool _se, const wchar_t _strName[] = L"==== [ Track Set ]====");
				~TrackSet(void);

		void	getAsm(MusicFile* MUS);
		void	Fix_Address(MusicFile* MUS);

		void	TrackChk(MMLfile* MML);
		void	TrackProc(MMLfile* MML);
	MusicTrack*	makeTrack(MMLfile* MML, int _track);
	MusicTrack*	getTrack(MMLfile* MML, int _track);

		void	SetEvent(MusicItem* _item);		//�C�x���g�̒ǉ�

		void	SetTempo(MMLfile* MML);

		void	SetVolume(MMLfile* MML);
		void	SetVolumeInc();
		void	SetVolumeDec();

		void	SetReleaseMode(MMLfile* MML);
		void	SetReleaseVoice(MMLfile* MML);
		void	SetReleaseVolume(MMLfile* MML);

		void	SetProtament(MMLfile* MML);
		void	SetSweep(MMLfile* MML);

		void	SetPoke(MMLfile* MML);
		void	Set_FDS_Frequency(MMLfile* MML);
		void	Set_FDS_Volume(MMLfile* MML);
		void	SetVRC7_Write(MMLfile* MML);
		void	SetN163Channel(MMLfile* MML);
		void	Set_FME7_Frequency(MMLfile* MML);

		void	SetPriority(MMLfile* MML);
};
