#include "StdAfx.h"
#include "MusicTrack.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MMLfile*	MML
//	���Ԓl
//					����
//==============================================================
MusicTrack::MusicTrack(const wchar_t _strName[]):
	MusicItem(_strName),
	offset_now(0),				//
	offset_loop(0),				//�������[�v
	offset_repeat_a_s(0),		//���s�[�g�`
	offset_repeat_a_b(0),		//���s�[�g�`
	offset_repeat_b_s(0),		//���s�[�g�a
	offset_repeat_b_b(0),		//���s�[�g�a
	DefaultLength(24),
	octave(4),
	octave1(0),
	compile_flag(false),
	echo_flag(false),
	loop_flag(false)
{
	unsigned	int	i = 0;

	while(i < 256){
		oldNote[i] = -1;
		i++;
	}

	//����
	KeySignature[0]	= 0;
	KeySignature[1]	= 0;
	KeySignature[2]	= 0;
	KeySignature[3]	= 0;
	KeySignature[4]	= 0;
	KeySignature[5]	= 0;
	KeySignature[6]	= 0;
	KeySignature[7]	= 0;
}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
MusicTrack::~MusicTrack(void)
{
}

//==============================================================
//		�A�h���X�������肷��B
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::Fix_Address(MusicFile* MUS)
{
	//----------------------
	//Local�ϐ�
	vector<	mml_Address*	>::iterator	itSE;
	vector<	mml_Address*	>::iterator	itSub;
	vector<	mml_Address*	>::iterator	itEnv;
	vector<	mml_Address*	>::iterator	itFDSC;
	vector<	mml_Address*	>::iterator	itFDSM;
	vector<	mml_Address*	>::iterator	itVRC7;
	vector<	mml_Address*	>::iterator	itN163;
	unsigned	int	_no;
	unsigned	int	_sub_offset;
	unsigned	int	_com_offset;

	//----------------------
	//SE
	if(!ptcSE.empty()){
		itSE = ptcSE.begin();
		while(itSE != ptcSE.end()){
			_no			= (*itSE)->get_id();		//�T�u���[�`��No.�̎擾
			_com_offset	= (*itSE)->getOffset();
			if( MUS->ptcSE.count(_no) == 0){
				wcout << L"SE" << _no << L"�Ԃ����݂��܂���B" << endl;
				exit(-1);
			}
			_sub_offset = MUS->ptcSE[_no]->getOffset();	//�w��T�u���[�`�������݂���I�t�Z�b�g
			(*itSE)->set_Address(_sub_offset - _com_offset - 1);
			itSE++;
		}
	}

	//----------------------
	//Surbortine
	if(!ptcSub.empty()){
		itSub = ptcSub.begin();
		while(itSub != ptcSub.end()){
			_no			= (*itSub)->get_id();		//�T�u���[�`��No.�̎擾
			_com_offset	= (*itSub)->getOffset();
			if( MUS->ptcSub.count(_no) == 0){
				wcout << L"�T�u���[�`��" << _no << L"�Ԃ����݂��܂���B" << endl;
				exit(-1);
			}
			_sub_offset = MUS->ptcSub[_no]->getOffset();	//�w��T�u���[�`�������݂���I�t�Z�b�g
			(*itSub)->set_Address(_sub_offset - _com_offset - 1);
			itSub++;
		}
	}

	//----------------------
	//Envelope
	if(!ptcEnv.empty()){
		itEnv = ptcEnv.begin();
		while(itEnv != ptcEnv.end()){
			_no			= (*itEnv)->get_id();		//�G���x���[�vNo.�̎擾
			_com_offset	= (*itEnv)->getOffset();
			if( MUS->ptcEnv.count(_no) == 0){
				wcout << L"�G���x���[�v" << _no << L"�Ԃ����݂��܂���B" << endl;
				exit(-1);
			}
			_sub_offset = MUS->ptcEnv[_no]->getOffset();	//�w��G���x���[�v�����݂���I�t�Z�b�g
			(*itEnv)->set_Address(_sub_offset - _com_offset - 1);
			itEnv++;
		}
	}

	//----------------------
	//FDSC
	if(!ptcFDSC.empty()){
		itFDSC = ptcFDSC.begin();
		while(itFDSC != ptcFDSC.end()){
			_no			= (*itFDSC)->get_id();		//�G���x���[�vNo.�̎擾
			_com_offset	= (*itFDSC)->getOffset();
			if( MUS->ptcFDSC.count(_no) == 0){
				wcout << L"FDSC" << _no << L"�Ԃ����݂��܂���B" << endl;
				exit(-1);
			}
			_sub_offset = MUS->ptcFDSC[_no]->getOffset();	//�w��G���x���[�v�����݂���I�t�Z�b�g
			(*itFDSC)->set_Address(_sub_offset - _com_offset - 1);
			itFDSC++;
		}
	}

	//----------------------
	//FDSM
	if(!ptcFDSM.empty()){
		itFDSM = ptcFDSM.begin();
		while(itFDSM != ptcFDSM.end()){
			_no			= (*itFDSM)->get_id();		//�G���x���[�vNo.�̎擾
			_com_offset	= (*itFDSM)->getOffset();
			if( MUS->ptcFDSM.count(_no) == 0){
				wcout << L"FDSM" << _no << L"�Ԃ����݂��܂���B" << endl;
				exit(-1);
			}
			_sub_offset = MUS->ptcFDSM[_no]->getOffset();	//�w��G���x���[�v�����݂���I�t�Z�b�g
			(*itFDSM)->set_Address(_sub_offset - _com_offset - 1);
			itFDSM++;
		}
	}

	//----------------------
	//OPLL
	if(!ptcOPLL.empty()){
		itVRC7 = ptcOPLL.begin();
		while(itVRC7 != ptcOPLL.end()){
			_no			= (*itVRC7)->get_id();		//�G���x���[�vNo.�̎擾
			_com_offset	= (*itVRC7)->getOffset();
			if( MUS->ptcVRC7.count(_no) == 0){
				wcout << L"VRC7" << _no << L"�Ԃ����݂��܂���B" << endl;
				exit(-1);
			}
			_sub_offset = MUS->ptcVRC7[_no]->getOffset();	//�w��G���x���[�v�����݂���I�t�Z�b�g
			(*itVRC7)->set_Address(_sub_offset - _com_offset - 1);
			itVRC7++;
		}
	}

	//----------------------
	//N163
	if(!ptcWave.empty()){
		itN163 = ptcWave.begin();
		while(itN163 != ptcWave.end()){
			_no			= (*itN163)->get_id();		//�G���x���[�vNo.�̎擾
			_com_offset	= (*itN163)->getOffset();
			if( MUS->ptcN163.count(_no) == 0){
				wcout << L"N163" << _no << L"�Ԃ����݂��܂���B" << endl;
				exit(-1);
			}
			_sub_offset = MUS->ptcN163[_no]->getOffset();	//�w��G���x���[�v�����݂���I�t�Z�b�g
			(*itN163)->set_Address(_sub_offset - _com_offset - 2);
			itN163++;
		}
	}

}

//==============================================================
//		�V�[�P���X�E�I�u�W�F�N�g�̒ǉ�
//--------------------------------------------------------------
//	������
//		MusicItem* _item	�V�[�P���X�E�I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetEvent(MusicItem* _item)
{
	//�T�C�Y�̕��A�I�t�Z�b�g�𑝂₷�B
	offset_now += (unsigned int)_item->getSize();

	//�����object�̃|�C���^��ۑ����Ă����B
	ptcItem.push_back(_item);
}

//==============================================================
//		�L�q�u���b�N�̏I���iEnd of Track�̒ǉ��j
//--------------------------------------------------------------
//	������
//		����
//	���Ԓl
//		����
//==============================================================
size_t	MusicTrack::SetEnd(void)
{
	mml_Address*	_event;

	if(loop_flag == false){
		SetEvent(new mml_general(nsd_EndOfTrack,L"End of Track"));
	} else {
		_event = new mml_Address(nsd_Jump, L"End of Track with LOOP");
		_event->set_Address(offset_loop - offset_now - 1);
		SetEvent(_event);
	}
	iSize = offset_now;

	return(iSize);
}

//==============================================================
//		L	�������[�v
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetLoop()
{
	offset_loop = offset_now;
	loop_flag	= true;
}

//==============================================================
//		[	���s�[�g(A)	�J�n
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetRepeat_A_Start(MMLfile* MML)
{
	int	times = MML->GetInt();

	if( (times <= 255) && (times >=1) ){
		SetEvent(new mml_general(nsd_Repeat_A_Start, times, L"Repeat(A) Start"));
		offset_repeat_a_s = offset_now;	// ] �R�}���h�ł́A���̃R�}���h�ɖ߂�B
		offset_repeat_a_b = 0;
	} else {
		MML->Err(L"���s�[�g�񐔂�1�`255�͈̔͂Ŏw�肵�ĉ������B");
	}

}

//==============================================================
//		:	���s�[�g(A)	����
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetRepeat_A_Branch(MMLfile* MML)
{
	if(offset_repeat_a_s != 0){
		if(offset_repeat_a_b == 0){
			offset_repeat_a_b = offset_now + 1;	//�����̈ʒu
			_old_repeatA_Branch = new mml_Address(nsd_Repeat_A_Branch, L"Repeat(A) Branch");
			SetEvent(_old_repeatA_Branch);
		} else {
			MML->Err(L"���s�[�g(A)���� : �R�}���h���d�����Ă��܂��B");
		}
	} else {
		MML->Err(L"���s�[�g(A)�̊J�n [ �R�}���h������܂���B");
	}
}

//==============================================================
//		]	���s�[�g(A)	�I��
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetRepeat_A_End(MMLfile* MML)
{
	mml_Address*	_event;

	if(offset_repeat_a_s != 0){
		_event = new mml_Address(nsd_Repeat_A_End, L"Repeat(A) End");
		_event->set_Address(offset_repeat_a_s - offset_now - 1);
		SetEvent(_event);
		//�������򂪂�������B
		if(offset_repeat_a_b != 0){
			_old_repeatA_Branch->set_Address(offset_now - offset_repeat_a_b);
		}
		offset_repeat_a_s = 0;
	} else {
		MML->Err(L"���s�[�g(A)�̊J�n [ �R�}���h������܂���B");
	}

}

//==============================================================
//		|:	���s�[�g(B)	�J�n
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetRepeat_B_Start(MMLfile* MML)
{
	SetEvent(new mml_general(nsd_Repeat_B_Start, L"Repeat(B) Start"));
	offset_repeat_b_s = offset_now;	// :| �R�}���h�ł́A���̃R�}���h�ɖ߂�B
	offset_repeat_b_b = 0;
}

//==============================================================
//		\	���s�[�g(B)	����
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetRepeat_B_Branch(MMLfile* MML)
{
	if(offset_repeat_b_s != 0){
		if(offset_repeat_b_b == 0){
			offset_repeat_b_b = offset_now;	//�R�}���h�����������������B
			SetEvent(new mml_general(nsd_Repeat_B_Branch, L"Repeat(B) Branch"));
		} else {
			MML->Err(L"���s�[�g(B)���� \\ �R�}���h���d�����Ă��܂��B");
		}
	} else {
		MML->Err(L"���s�[�g(B)�̊J�n |: �R�}���h������܂���B");
	}
}

//==============================================================
//		:|	���s�[�g(B)	�I��
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetRepeat_B_End(MMLfile* MML)
{
	mml_Address*	_event;

	if(offset_repeat_b_s != 0){
		if(offset_repeat_b_b != 0){
			if(offset_repeat_b_s < offset_repeat_a_s){
				MML->Err(L"���s�[�g(A)�̋�Ԃ̓r���ł��B");
			}
			_event = new mml_Address(nsd_Repeat_B_End, L"Repeat(B) End");
			_event->set_Address(offset_repeat_b_s - offset_now - 1);
			SetEvent(_event);
		} else {
			MML->Err(L"���s�[�g(B)���� \\ �R�}���h������܂���ł����B�K������_ \\ �͎w�肵�Ă��������B");
		}
	} else {
		MML->Err(L"���s�[�g(B)�̊J�n |: �R�}���h������܂���B");
	}
}

//==============================================================
//		SE	���ʉ��Ăяo��
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetSE(MMLfile* MML)
{
	mml_Address*		_event = new mml_Address(nsd_Call_SE, L"Call SE");
	unsigned	int		_no = MML->GetInt();

	_event->set_id(_no);
	SetEvent(_event);
	ptcSE.push_back(_event);
}

//==============================================================
//		S	�T�u���[�`���Ăяo��
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetSubroutine(MMLfile* MML)
{
	mml_Address*		_event = new mml_Address(nsd_Call, L"Subroutine");
	unsigned	int		_no = MML->GetInt();

	_event->set_id(_no);
	SetEvent(_event);
	ptcSub.push_back(_event);
}

//==============================================================
//		E	�G���x���[�v�ݒ�
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetEnvelop(unsigned char _opcode, MMLfile* MML, int _offset)
{
	mml_Address*		_event = new mml_Address(_opcode, L"Envelop");
	unsigned	int		_no = MML->GetInt() + _offset;

	_event->set_id(_no);
	SetEvent(_event);
	ptcEnv.push_back(_event);
}

//==============================================================
//		@FC	FDS	
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetFDSC(MMLfile* MML)
{
	mml_Address*		_event = new mml_Address(nsd_FDS_Career, L"FDS career wave table");
	unsigned	int		_no = MML->GetInt();

	_event->set_id(_no);
	SetEvent(_event);
	ptcFDSC.push_back(_event);
}

//==============================================================
//		@FM	FDS	
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetFDSM(MMLfile* MML)
{
	mml_Address*		_event = new mml_Address(nsd_FDS_Modlator, L"FDS modulator wave table");
	unsigned	int		_no = MML->GetInt();

	_event->set_id(_no);
	SetEvent(_event);
	ptcFDSM.push_back(_event);
}

//==============================================================
//		@V	VRC7���[�U��`���F�ݒ�
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetVRC7(MMLfile* MML)
{
	mml_Address*		_event = new mml_Address(nsc_VRC7, L"VRC7 user instruments");
	unsigned	int		_no = MML->GetInt();

	_event->set_id(_no);
	SetEvent(_event);
	ptcOPLL.push_back(_event);
}

//==============================================================
//		@N	n163���F�ݒ�
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetN163(MMLfile* MML)
{
	unsigned	char	cData;
	mml_Address*		_event = new mml_Address(nsc_N163,MML->GetInt(),L"n163 wave table");

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err(L"@N �R�}���h�̃p�����[�^������܂���B�Q�w�肵�Ă��������B");
	}

	_event->set_id(MML->GetInt());
	SetEvent(_event);
	ptcWave.push_back(_event);
}

//==============================================================
//		EC*	�^���G�R�[����
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetEcho(void)
{
	echo_flag = false;
}

//==============================================================
//		EC	�^���G�R�[�ݒ�
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetEcho(MMLfile* MML)
{
	unsigned	char	cData;
	unsigned	char	_value;
	unsigned	char	_volume;

	_value = MML->GetInt();
	if((_value<0) || (_value>255)){
		MML->Err(L"EC�R�}���h�̑�P�p�����[�^��0�`255�͈̔͂Ŏw�肵�Ă��������B");
	}

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err(L"EC �R�}���h�̃p�����[�^������܂���B�Q�w�肵�Ă��������B");
	}

	_volume = MML->GetInt();
	if((_volume<0) || (_volume>15)){
		MML->Err(L"EC�R�}���h�̑�Q�p�����[�^��0�`15�͈̔͂Ŏw�肵�Ă��������B");
	}

	echo_flag = true;
	echo_value	= _value;
	echo_volume	= _volume;

}

//==============================================================
//		�����̐ݒ�
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetKeySignature(MMLfile*	MML)
{
	//�����R�}���h��ID
	enum	KeySignature_ID {
		ks_Sharp,
		ks_Flat,
		ks_Natural,
		ks_c,
		ks_d,
		ks_e,
		ks_f,
		ks_g,
		ks_a,
		ks_b,
		ks_r,
		ks_0,
		ks_s1,
		ks_s2,
		ks_s3,
		ks_s4,
		ks_s5,
		ks_s6,
		ks_s7,
		ks_f1,
		ks_f2,
		ks_f3,
		ks_f4,
		ks_f5,
		ks_f6,
		ks_f7
	};

	//�����R�}���h���̒�`
	static	const	Command_Info	KS_Command[] = {
		{	"+",		ks_Sharp	},
		{	"#",		ks_Sharp	},
		{	"-",		ks_Flat		},
		{	"=",		ks_Natural	},
		{	"*",		ks_Natural	},
		{	"c",		ks_c		},
		{	"d",		ks_d		},
		{	"e",		ks_e		},
		{	"f",		ks_f		},
		{	"g",		ks_g		},
		{	"a",		ks_a		},
		{	"b",		ks_b		},
		{	"r",		ks_r		},
		{	"C_Dur",	ks_0		},	//
		{	"Cis_Dur",	ks_f5		},	//bbbbb
		{	"D_Dur",	ks_s2		},	//##
		{	"Dis_Dur",	ks_f3		},	//bbb
		{	"E_Dur",	ks_s4		},	//####
		{	"F_Dur",	ks_f1		},	//b
		{	"Fis_Dur",	ks_s6		},	//######
		{	"Gs_Dur",	ks_f6		},	//bbbbbb
		{	"G_Dur",	ks_s1		},	//#
		{	"As_Dur",	ks_f4		},	//bbbb
		{	"A_Dur",	ks_s3		},	//###
		{	"B_Dur",	ks_f2		},	//bb
		{	"H_Dur",	ks_s5		}	//#####
	};

	unsigned	char	cData;
				char	sign = 0;

	while(MML->cRead() != '{'){
		if(MML->eof()){
			MML->Err(L"�����R�}���h�E�u���b�N�̊J�n������{��������܂���B");
		}
	}

	// } ������܂ŁA�L�q�u���b�N�����R���p�C������B
	while((cData = MML->GetChar()) != '}'){
		
		// } ������O�ɁA[EOF]��������G���[
		if( MML->eof() ){
			MML->Err(L"�����R�}���h�E�u���b�N�̏I�[������`}'������܂���B");
		}

		//�P�߂�
		MML->StreamPointerAdd(-1);

		switch(MML->GetCommandID(KS_Command, sizeof(KS_Command)/sizeof(Command_Info))){
			case(ks_c):
				KeySignature[0] = sign;
				break;
			case(ks_d):
				KeySignature[1] = sign;
				break;
			case(ks_e):
				KeySignature[2] = sign;
				break;
			case(ks_f):
				KeySignature[3] = sign;
				break;
			case(ks_g):
				KeySignature[4] = sign;
				break;
			case(ks_a):
				KeySignature[5] = sign;
				break;
			case(ks_b):
				KeySignature[6] = sign;
				break;
			case(ks_r):
				KeySignature[7] = sign;
				break;
			case(ks_Natural):
				sign = 0;
				break;
			case(ks_Sharp):
				sign = 1;
				break;
			case(ks_Flat):
				sign = -1;
				break;
			default:
				MML->Err(L"���� K{} �R�}���h�̈����Ŗ��m�̕������w�肳��܂����B");
				break;
		}
	}

	//for Debug
/*
	wcout << L"[0] c = " << (int)KeySignature[0] << endl;
	wcout << L"[1] d = " << (int)KeySignature[1] << endl;
	wcout << L"[2] e = " << (int)KeySignature[2] << endl;
	wcout << L"[3] f = " << (int)KeySignature[3] << endl;
	wcout << L"[4] g = " << (int)KeySignature[4] << endl;
	wcout << L"[5] a = " << (int)KeySignature[5] << endl;
	wcout << L"[6] b = " << (int)KeySignature[6] << endl;
*/
}

//==============================================================
//		�����̃C�x���g�쐬
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//		int			note	�m�[�g�i0:C 1:D 2:E �c 7:B�j
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetNote(MMLfile*	MML,int note)
{
	unsigned		char	cData;
	static	const	char	note_code[]={0,2,4,5,7,9,11};
					int		_key = note_code[note];
	unsigned		int		Length = -1;
	unsigned		int		GateTime = -1;
					bool	Slur = false;

	//�Վ��L��
	cData = MML->GetChar();
	//If Natural then skip
	if((cData != '=') && (cData != '*')){
		_key += KeySignature[note];
		while((cData == '#') || (cData == '+') || (cData == '-')){
			switch(cData){
				case('#'):
				case('+'):
					_key++;
					break;
				case('-'):
					_key--;
					break;
				default:
					break;
			}
			cData = MML->GetChar();	//���̕���
		}
		//�Վ��L���ł͂Ȃ��Ȃ����̂ŁA�|�C���^��߂��B
		MML->Back();
	}

	cData = MML->GetChar();
	if(((cData >= '0') && (cData <= '9')) || (cData == '%') || (cData == '.')){
		MML->Back();
		Length = MML->GetLength(DefaultLength);
	} else {
		MML->Back();
	}

	cData = MML->GetChar();
	if(cData == ','){
		cData = MML->GetChar();
		if(cData == '0'){
			GateTime = 0;
		} else {
			MML->Back();
			GateTime = MML->GetLength(DefaultLength);
		}
	} else if(cData == '&') {
		Slur = true;
	} else {
		MML->Back();
	}

	//�w��ł���͈͂𒴂����ꍇ�B
	while(_key < 0){
		_key += 12;
		SetEvent(new mml_general(nsd_Octave_Down_1, L"One time octave down"));
	}

	while(_key >= 12){
		_key -= 12;
		SetEvent(new mml_general(nsd_Octave_Up_1, L"One time octave up"));
	}


	//�C�x���g�I�u�W�F�N�g�̍쐬
	_old_note = new mml_note(_key, Length, GateTime, Slur, L"Note");
	SetEvent(_old_note);

	pt_oldNote++;
	oldNote[pt_oldNote] = (_key + (octave + octave1)*12) & 0xFF;
	octave1_old = octave1;
	octave1 = 0;
}

//==============================================================
//		�x���̃C�x���g�쐬
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetRest(MMLfile*	MML)
{
	unsigned		char	cData;
	unsigned		char	_code = 0x0F;
	unsigned		int		Length = -1;
	unsigned		int		GateTime = -1;
					bool	Slur = false;

					char	now_note = oldNote[pt_oldNote];
					char	old_note = oldNote[(pt_oldNote - echo_value) & 0xFF];

	//�x���̃��[�h
	cData = MML->GetChar();
	switch(cData){
		case('-'):
			_code = 0x0D;
			break;
		case('#'):
		case('+'):
			_code = 0x0E;
			break;
		case('='):
		case('*'):
			_code = 0x0F;
			break;
		default:
			MML->Back();
			switch(KeySignature[7]){
				case(-1):
					_code = 0x0D;
					break;
				case(+1):
					_code = 0x0E;
					break;
				default:
					_code = 0x0F;
					break;
			}
			break;
	}

	//����
	cData = MML->GetChar();
	if(((cData >= '0') && (cData <= '9')) || (cData == '%') || (cData == '.')){
		MML->Back();
		Length = MML->GetLength(DefaultLength);
	} else {
		MML->Back();
	}

	//�Q�[�g�^�C�� or �^�C
	cData = MML->GetChar();
	if(cData == ','){
		cData = MML->GetChar();
		if(cData == '0'){
			GateTime = 0;
		} else {
			MML->Back();
			GateTime = MML->GetLength(DefaultLength);
		}
	} else if(cData == '&') {
		Slur = true;
	} else {
		MML->Back();
	}

	if((echo_flag == false) || (_code != 0x0F) || (old_note == -1)){
		_old_note = new mml_note(_code, Length, GateTime, Slur, L"Rest");
		SetEvent(_old_note);
	} else {
		char	now_octave = (now_note / 12) - octave1_old;
		char	old_octave = (old_note / 12);
//		int		i = 0;

		//Echo volume
		SetEvent(new mml_general(nsd_Volume + echo_volume, L"Echo Volume"));

		//Echo note
		if(old_octave < now_octave){
			while(old_octave < now_octave){
				old_octave++;
				SetEvent(new mml_general(nsd_Octave_Down_1, L"One time octave down"));
			}
		} else if(old_octave > now_octave){
			while(old_octave > now_octave){
				old_octave--;
				SetEvent(new mml_general(nsd_Octave_Up_1, L"One time octave up"));
			}
		}
		_old_note = new mml_note(old_note % 12, Length, GateTime, Slur, L"Echo Note");
		SetEvent(_old_note);


		//volume return
		SetEvent(new mml_general(nsd_Volume + volume, L"Volume"));
	}
}

//==============================================================
//		�^�C�̃I�u�W�F�N�g�쐬�i�x���ō��j
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetTai(MMLfile* MML)
{
	_old_note->SetTai();
	SetRest(MML);
}

//==============================================================
//		�ȗ����̉���
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetLength(MMLfile* MML)
{
	DefaultLength = MML->GetLength(DefaultLength);
	mml_general*	_event;

	switch(DefaultLength){
		case(96):
			_event = new mml_general(nsd_Length_96, L"Length 96");
			break;
		case(72):
			_event = new mml_general(nsd_Length_72, L"Length 72");
			break;
		case(48):
			_event = new mml_general(nsd_Length_48, L"Length 48");
			break;
		case(36):
			_event = new mml_general(nsd_Length_36, L"Length 36");
			break;
		case(32):
			_event = new mml_general(nsd_Length_32, L"Length 32");
			break;
		case(24):
			_event = new mml_general(nsd_Length_24, L"Length 24");
			break;
		case(18):
			_event = new mml_general(nsd_Length_18, L"Length 18");
			break;
		case(16):
			_event = new mml_general(nsd_Length_16, L"Length 16");
			break;
		case(12):
			_event = new mml_general(nsd_Length_12, L"Length 12");
			break;
		case(9):
			_event = new mml_general(nsd_Length_9,  L"Length 9");
			break;
		case(8):
			_event = new mml_general(nsd_Length_8,  L"Length 8");
			break;
		case(6):
			_event = new mml_general(nsd_Length_6,  L"Length 6");
			break;
		case(4):
			_event = new mml_general(nsd_Length_4,  L"Length 4");
			break;
		case(3):
			_event = new mml_general(nsd_Length_3,  L"Length 3");
			break;
		case(2):
			_event = new mml_general(nsd_Length_2,  L"Length 2");
			break;
		case(1):
			_event = new mml_general(nsd_Length_1,  L"Length 1");
			break;
		default:
			_event = new mml_general(nsd_Length, (DefaultLength & 0xFF), L"Length");
			break;
	}
	SetEvent(_event);
}

