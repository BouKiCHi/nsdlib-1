#pragma once

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class MusicTrack :
	public MusicItem
{
//�����o�[�ϐ�
private:
	unsigned	int		offset_now;			//���݂̃I�t�Z�b�g
	unsigned	int		offset_loop;		// L �R�}���h�̃I�t�Z�b�g
	unsigned	int		offset_repeat_a_s;	//�O��� [  �R�}���h�̃I�t�Z�b�g
	unsigned	int		offset_repeat_a_b;	//�O��� :  �R�}���h�̃I�t�Z�b�g
	unsigned	int		offset_repeat_b_s;	//�O��� |: �R�}���h�̃I�t�Z�b�g
	unsigned	int		offset_repeat_b_b;	//�O��� \  �R�}���h�̃I�t�Z�b�g

				char	KeySignature[7];	//����(c,d,e...)

	mml_note*			_old_note;
	mml_Address*		_old_repeatA_Branch;

	vector<	mml_Address*	>	ptcSubroutine;	//�T�u���[�`���R�}���h�ꗗ

//�����o�[�֐�
public:
			MusicTrack(const char _strName[] = "==== [ Music Track ]====");
			~MusicTrack(void);

				void	SetEvent(MusicItem* _item);		//�C�x���g�̒ǉ�

	unsigned	int		SetEnd(void);
				void	SetLoop();
				void	SetRepeat_A_Start(MMLfile* MML);
				void	SetRepeat_A_Branch(MMLfile* MML);
				void	SetRepeat_A_End(MMLfile* MML);
				void	SetRepeat_B_Start(MMLfile* MML);
				void	SetRepeat_B_Branch(MMLfile* MML);
				void	SetRepeat_B_End(MMLfile* MML);
				void	SetSubroutine(MMLfile* MML);
				void	Fix_Address(map<int, Sub*>*	ptcSub);

				void	SetNote(MMLfile* MML, int note);
				void	SetRest(MMLfile* MML);
				void	SetTai(MMLfile* MML);
				void	SetLength(MMLfile* MML);
				void	SetOctave(MMLfile* MML);
				void	SetGatetime(MMLfile* MML);
				void	SetGatetime_q(MMLfile* MML);
				void	SetSweep(MMLfile* MML);
				void	SetVolume(MMLfile* MML);
				void	SetReleaseMode(MMLfile* MML);
				void	SetReleaseVoice(MMLfile* MML);
				void	SetReleaseVolume(MMLfile* MML);
				void	SetPoke(MMLfile* MML);
				void	SetKeySignature(MMLfile* MML);	//�����̐ݒ�
};
