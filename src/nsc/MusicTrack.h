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

				bool	compile_flag;		//���݃R���p�C�����H
	unsigned	int		offset_now;			//���݂̃I�t�Z�b�g

				bool	loop_flag;
	unsigned	int		offset_loop;		// L �R�}���h�̃I�t�Z�b�g
	unsigned	int		offset_repeat_a_s;	//�O��� [  �R�}���h�̃I�t�Z�b�g
	unsigned	int		offset_repeat_a_b;	//�O��� :  �R�}���h�̃I�t�Z�b�g
	unsigned	int		offset_repeat_b_s;	//�O��� |: �R�}���h�̃I�t�Z�b�g
	unsigned	int		offset_repeat_b_b;	//�O��� \  �R�}���h�̃I�t�Z�b�g
				int		count_repeat_a;
	unsigned	int		DefaultLength;

				bool	echo_flag;			//�^���G�R�[ �t���O
				bool	echo_slur;			//�^���G�R�[ �X���[�łȂ���H
				int		echo_length;		//�^���G�R�[ ����
	unsigned	char	echo_volume;		//�^���G�R�[ ����
	unsigned	char	echo_value;			//�^���G�R�[ ���O�H
				char	oldNote[256];		//�^���G�R�[�p�o�b�t�@

	unsigned	char	pt_oldNote;			//�O��̉���
				char	volume;				//����
				char	octave;				//�I�N�^�[�u
				char	octave1;			//
				char	octave1_old;		//

	unsigned	int		gatetime_q;
	unsigned	int		gatetime_Q;
	unsigned	int		QMax;

				int		opt_DefaultLength;
				int		opt_gatetime_q;			//
				int		opt_gatetime_u;			//
				int		opt_volume;

				bool	jump_flag;			//�W�����v�t���O

	//��������p
				char	KeySignature[8];	//����(c,d,e,f,g,a,b,r)
				char	nowKey;				//���݂̒�
				char	nowScale;			//���݂̃X�P�[���i���[�h�j
				
	mml_note*			_old_note;
	mml_Address*		_old_repeatA_Branch;
	mml_repeat*			_old_repeat;

	vector<	mml_Address*	>	ptcFDSC;		//FDS Carrer
	vector<	mml_Address*	>	ptcFDSM;		//FDS Modlator
	vector<	mml_Address*	>	ptcOPLL;		//VRC7, OPLL
	vector<	mml_Address*	>	ptcWave;		//N163
	vector<	mml_Address*	>	ptcSE;			//���ʉ��R�}���h�ꗗ
	vector<	mml_Address*	>	ptcSub;			//�T�u���[�`���R�}���h�ꗗ
	vector<	mml_Address*	>	ptcEnv;			//�G���x���[�v�R�}���h�ꗗ

//�����o�[�֐�
public:
			MusicTrack(MMLfile* MML, const wchar_t _strName[] = L"==== [ Music Track ]====");
			~MusicTrack(void);

				void	Fix_Address(MusicFile* MUS);
				void	SetEvent(MusicItem* _item);		//�C�x���g�̒ǉ�

				bool	GetCompileFlag(void){return(compile_flag);};
				void	SetCompileFlag(bool _flag){compile_flag = _flag;};

				size_t	SetEnd(void);
				void	SetLoop();

				void	SetRepeat_A_Start(MMLfile* MML);
				void	SetRepeat_A_Branch(MMLfile* MML);
				void	SetRepeat_A_End(MMLfile* MML);
				void	SetRepeat_B_Start();
				void	SetRepeat_B_Branch(MMLfile* MML);
				void	SetRepeat_B_End(MMLfile* MML);

				void	SetSE(MMLfile* MML);
				void	SetSubroutine(MMLfile* MML);
				void	SetEnvelop(unsigned char _opcode, MMLfile* MML, int _offset);
				void	SetFDSC(MMLfile* MML);
				void	SetFDSM(MMLfile* MML);
				void	SetVRC7(MMLfile* MML);
				void	SetN163(MMLfile* MML);

				void	SetEcho(void);
				void	SetEcho(MMLfile* MML);

				void	SetJump(MMLfile* MML);

				void	Set_q(int i);
				void	SetGatetime_Q(MMLfile* MML);
				void	SetGatetime(MMLfile* MML);
				void	SetGatetime_u(MMLfile* MML);

				void	SetKeyFlag(char _c, char _d, char _e, char _f, char _g, char _a, char _b);
				void	SetKey(int _key, int _scale);

				void	SetMajor();
				void	SetMinor();
				void	SetHMinor(MMLfile* MML);
				void	SetMMinor(MMLfile* MML);
				void	SetScale(MMLfile* MML);
				void	SetKeySignature(MMLfile* MML);	//�����̐ݒ�

				void	ResetEcho();
				void	GenerateEcho(int Length, int GateTime, bool	Slur);
				void	SetNote(MMLfile* MML, int note);
				void	SetRest(MMLfile* MML, int mode);
				void	SetTai(MMLfile* MML);
				void	SetLength(MMLfile* MML);

				void	SetOctave(MMLfile* MML);
				void	SetOctaveInc();
				void	SetOctaveDec();
				void	SetOctaveOne_Inc();
				void	SetOctaveOne_Dec();
		
				void	SetVolume(char _v){volume = _v;	opt_volume = volume;};
				void	IncVolume(void){	volume++;	if(volume>15){volume = 15;}	opt_volume = volume;	};
				void	DecVolume(void){	volume--;	if(volume<0){volume = 0;}	opt_volume = volume;	};
	unsigned	int		GetDefaultLength(void){return(DefaultLength);};

				void	Reset_opt(void){
					opt_volume			= -1;
					opt_gatetime_q		= -1;
					opt_gatetime_u		= -1;
					opt_DefaultLength	= -1;
				}
				int		Get_opt_volume(void){		return(opt_volume);	};
};
