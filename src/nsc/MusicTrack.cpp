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
MusicTrack::MusicTrack(const char _strName[]):
	MusicItem(_strName),
	offset_now(0),				//
	offset_loop(0),				//�������[�v
	offset_repeat_a_s(0),		//���s�[�g�`
	offset_repeat_a_b(0),		//���s�[�g�`
	offset_repeat_b_s(0),		//���s�[�g�a
	offset_repeat_b_b(0),		//���s�[�g�a
	loop_flag(false)
{
	//����
	KeySignature[0]	= 0;
	KeySignature[1]	= 0;
	KeySignature[2]	= 0;
	KeySignature[3]	= 0;
	KeySignature[4]	= 0;
	KeySignature[5]	= 0;
	KeySignature[6]	= 0;
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
//		
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
//		
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetRepeat_A_Start(MMLfile* MML)
{
	SetEvent(new mml_general(nsd_Repeat_A_Start, MML, "Repeat(A) Start"));
	offset_repeat_a_s = offset_now;	// ] �R�}���h�ł́A���̃R�}���h�ɖ߂�B
	offset_repeat_a_b = 0;
}

//==============================================================
//		
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
			_old_repeatA_Branch = new mml_Address(nsd_Repeat_A_Branch, "Repeat(A) Branch");
			SetEvent(_old_repeatA_Branch);
		} else {
			MML->Err("���s�[�g(A)���� : �R�}���h���d�����Ă��܂��B");
		}
	} else {
		MML->Err("���s�[�g(A)�̊J�n [ �R�}���h������܂���B");
	}
}

//==============================================================
//		
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
		_event = new mml_Address(nsd_Repeat_A_End, "Repeat(A) End");
		_event->set_Address(offset_repeat_a_s - offset_now - 1);
		SetEvent(_event);
		//�������򂪂�������B
		if(offset_repeat_a_b != 0){
			_old_repeatA_Branch->set_Address(offset_now - offset_repeat_a_b);
		}
		offset_repeat_a_s = 0;
	} else {
		MML->Err("���s�[�g(A)�̊J�n [ �R�}���h������܂���B");
	}

}

//==============================================================
//		
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetRepeat_B_Start(MMLfile* MML)
{
	SetEvent(new mml_general(nsd_Repeat_B_Start, "Repeat(B) Start"));
	offset_repeat_b_s = offset_now;	// :| �R�}���h�ł́A���̃R�}���h�ɖ߂�B
	offset_repeat_b_b = 0;
}

//==============================================================
//		
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
			SetEvent(new mml_general(nsd_Repeat_B_Branch, "Repeat(B) Branch"));
		} else {
			MML->Err("���s�[�g(B)���� \\ �R�}���h���d�����Ă��܂��B");
		}
	} else {
		MML->Err("���s�[�g(B)�̊J�n |: �R�}���h������܂���B");
	}
}

//==============================================================
//		
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
				MML->Err("���s�[�g(A)�̋�Ԃ̓r���ł��B");
			}
			_event = new mml_Address(nsd_Repeat_B_End, "Repeat(B) End");
			_event->set_Address(offset_repeat_b_s - offset_now - 1);
			SetEvent(_event);
		} else {
			MML->Err("���s�[�g(B)���� \\ �R�}���h������܂���ł����B�K������_ \\ �͎w�肵�Ă��������B");
		}
	} else {
		MML->Err("���s�[�g(B)�̊J�n |: �R�}���h������܂���B");
	}
}

//==============================================================
//		
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetEnvelop(unsigned char _opcode, MMLfile* MML)
{
	mml_Address*		_event = new mml_Address(_opcode, "Envelop");
	unsigned	int		_no = MML->GetInt();

	if((_no<0) || (_no>65535)){
		MML->Err("�G���x���[�v�ԍ��́A0�`65535�͈̔͂Ŏw�肵�Ă��������B");
	}
	_event->set_Address( _no & 0xFFFF );
	SetEvent(_event);
	ptcEnvelop.push_back(_event);
}

//==============================================================
//		
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::SetSubroutine(MMLfile* MML)
{
	mml_Address*		_event = new mml_Address(nsd_Call, "Subroutine");
	unsigned	int		_no = MML->GetInt();

	if((_no<0) || (_no>65535)){
		MML->Err("�T�u���[�`���ԍ��́A0�`65535�͈̔͂Ŏw�肵�Ă��������B");
	}
	_event->set_Address( _no & 0xFFFF );
	SetEvent(_event);
	ptcSubroutine.push_back(_event);
}

//==============================================================
//		�A�h���X�������肷��B
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MusicTrack::Fix_Address(map<int, Sub*>* ptcSub, map<int, Envelop*>* ptcEnv)
{
	//----------------------
	//Local�ϐ�
	vector<	mml_Address*	>::iterator	itSub;
	vector<	mml_Address*	>::iterator	itEnv;
	unsigned	int	_no;
	unsigned	int	_sub_offset;
	unsigned	int	_com_offset;

	//----------------------
	//
	if(!ptcSubroutine.empty()){
		itSub = ptcSubroutine.begin();
		while(itSub != ptcSubroutine.end()){
			_no			= (*itSub)->get_Address();		//�T�u���[�`��No.�̎擾
			_com_offset	= (*itSub)->getOffset();
			if( ptcSub->count(_no) == 0){
				printf("�T�u���[�`�� %d �Ԃ����݂��܂���B",_no);
				exit(-1);
			}
			_sub_offset = (*ptcSub)[_no]->getOffset();	//�w��T�u���[�`�������݂���I�t�Z�b�g
			(*itSub)->set_Address(_sub_offset - _com_offset - 1);
			itSub++;
		}
	}

	//
	if(!ptcEnvelop.empty()){
		itEnv = ptcEnvelop.begin();
		while(itEnv != ptcEnvelop.end()){
			_no			= (*itEnv)->get_Address();		//�G���x���[�vNo.�̎擾
			_com_offset	= (*itEnv)->getOffset();
			if( ptcEnv->count(_no) == 0){
				printf("�G���x���[�v %d �Ԃ����݂��܂���B",_no);
				exit(-1);
			}
			_sub_offset = (*ptcEnv)[_no]->getOffset();	//�w��G���x���[�v�����݂���I�t�Z�b�g
			(*itEnv)->set_Address(_sub_offset - _com_offset - 1);
			itEnv++;
		}
	}
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
	if(((cData > '0') && (cData < '9')) || (cData == '%')){
		MML->Back();
		Length = MML->GetLength();
	} else {
		MML->Back();
	}

	cData = MML->GetChar();
	if(cData == ','){
		GateTime = MML->GetLength();
	} else if(cData == '&') {
		Slur = true;
	} else {
		MML->Back();
	}

	//�w��ł���͈͂𒴂����ꍇ�B
	while(_key < 0){
		_key += 12;
		SetEvent(new mml_general(nsd_Octave_Down_1, "One time octave down"));
	}

	while(_key >= 12){
		_key -= 12;
		SetEvent(new mml_general(nsd_Octave_Up_1, "One time octave up"));
	}


	//�C�x���g�I�u�W�F�N�g�̍쐬
	_old_note = new mml_note(_key, Length, GateTime, Slur, "Note");
	SetEvent(_old_note);
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
		default:
			MML->Back();
			break;
	}

	//����
	cData = MML->GetChar();
	if(((cData > '0') && (cData < '9')) || (cData == '%')){
		MML->Back();
		Length = MML->GetLength();
	} else {
		MML->Back();
	}

	//�Q�[�g�^�C�� or �^�C
	cData = MML->GetChar();
	if(cData == ','){
		GateTime = MML->GetLength();
	} else if(cData == '&') {
		Slur = true;
	} else {
		MML->Back();
	}

	_old_note = new mml_note(_code, Length, GateTime, Slur, "Rest");
	SetEvent(_old_note);
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
	unsigned	int	iLength = MML->GetLength();
	mml_general*	_event;

	switch(iLength){
		case(96):
			_event = new mml_general(nsd_Length_96, "Length 96");
			break;
		case(72):
			_event = new mml_general(nsd_Length_72, "Length 72");
			break;
		case(48):
			_event = new mml_general(nsd_Length_48, "Length 48");
			break;
		case(36):
			_event = new mml_general(nsd_Length_36, "Length 36");
			break;
		case(32):
			_event = new mml_general(nsd_Length_32, "Length 32");
			break;
		case(24):
			_event = new mml_general(nsd_Length_24, "Length 24");
			break;
		case(18):
			_event = new mml_general(nsd_Length_18, "Length 18");
			break;
		case(16):
			_event = new mml_general(nsd_Length_16, "Length 16");
			break;
		case(12):
			_event = new mml_general(nsd_Length_12, "Length 12");
			break;
		case(9):
			_event = new mml_general(nsd_Length_9,  "Length 9");
			break;
		case(8):
			_event = new mml_general(nsd_Length_8,  "Length 8");
			break;
		case(6):
			_event = new mml_general(nsd_Length_6,  "Length 6");
			break;
		case(4):
			_event = new mml_general(nsd_Length_4,  "Length 4");
			break;
		case(3):
			_event = new mml_general(nsd_Length_3,  "Length 3");
			break;
		case(2):
			_event = new mml_general(nsd_Length_2,  "Length 2");
			break;
		case(1):
			_event = new mml_general(nsd_Length_1,  "Length 1");
			break;
		default:
			_event = new mml_general(nsd_Length, (iLength & 0xFF), "Length");
			break;
	}
	SetEvent(_event);
}

//==============================================================
//		�I�N�^�[�u
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetOctave(MMLfile* MML)
{
	unsigned	int	iOctave = MML->GetInt();

	if( (iOctave <= 9) && (iOctave >=2) ){
		SetEvent(new mml_general(nsd_Octave + iOctave - 2, "Octave"));
	} else {
		MML->Err("�I�N�^�[�u��2�`9�͈̔͂Ŏw�肵�Ă��������Bo1�̗̈�́A���΃I�N�^�[�u�������p���������B");
	}
}

//==============================================================
//		�Q�[�g�^�C��(q)
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetGatetime(MMLfile* MML)
{
	unsigned	int	i = MML->GetInt();

	if( (i <= 15) && (i >= 0) ){
		SetEvent(new mml_general(nsd_GateTime_Byte + i, "Gatetime(q) Byte"));
	} else if( i <= 255) {
		SetEvent(new mml_general(nsd_GateTime_q, i, "Gatetime(q)"));
	} else {
		MML->Err("�p�����[�^�̒l���͈͂��z���܂����B");
	}
}

//==============================================================
//		�Q�[�g�^�C��(u)
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetGatetime_u(MMLfile* MML)
{
	unsigned		int	i;
	unsigned		char	cData;

	//�x���̃��[�h
	cData = MML->GetChar();
	if(cData == '0'){
		i = 0;
	} else {
		MML->Back();
		i = MML->GetLength();
	}
	SetEvent(new mml_general(nsd_GateTime_u, i & 0xFF , "GateTime(u)"));
	
}

//==============================================================
//		�X�C�[�v
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetSweep(MMLfile* MML)
{
	unsigned	int		iSpeed;
	unsigned	int		iDepth;
	unsigned	char	_data;
	unsigned	char	cData;

	iSpeed = MML->GetInt();
	if( (iSpeed < 0) || (iSpeed > 15) ){
		MML->Err("�X�C�[�v�Ŏw��ł���͈͂𒴂��Ă��܂��B0�`15�͈̔͂Ŏw�肵�Ă��������B");
	}

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err("s �R�}���h�̃p�����[�^������܂���B�Q�w�肵�Ă��������B");
	}

	iDepth = MML->GetInt();
	if( (iDepth < 0) || (iDepth > 15) ){
		MML->Err("�X�C�[�v�Ŏw��ł���͈͂𒴂��Ă��܂��B0�`15�͈̔͂Ŏw�肵�Ă��������B");
	}
	_data = ((iSpeed & 0x0F) << 4) | (iDepth & 0x0F);
	SetEvent(new mml_general(nsd_Sweep, _data, "Sweep"));
}

//==============================================================
//		����
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetVolume(MMLfile* MML)
{
	unsigned	int	i = MML->GetInt();

	if( (i <= 15) && (i >= 0) ){
		SetEvent(new mml_general(nsd_Volume + i, "Volume"));
	} else {
		MML->Err("���ʂŎw��ł���͈͂𒴂��Ă��܂��B0�`15�͈̔͂Ŏw�肵�Ă��������B");
	}
}

//==============================================================
//		�����[�X���[�h
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetReleaseMode(MMLfile* MML)
{
	unsigned	int	i = MML->GetInt();
	mml_general*	_event;

	switch(i){
		case(0):
			_event = new mml_general(nsd_GateMode_0,  "GateMode 0");
			break;
		case(1):
			_event = new mml_general(nsd_GateMode_1,  "GateMode 1");
			break;
		case(2):
			_event = new mml_general(nsd_GateMode_2,  "GateMode 2");
			break;
		default:
			MML->Err("�����[�X���[�h�Ŏw��ł���͈͂𒴂��Ă��܂��B0�`2�͈̔͂Ŏw�肵�Ă��������B");
			break;
	}
	SetEvent(_event);
}

//==============================================================
//		�����[�X���F
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetReleaseVoice(MMLfile* MML)
{
	unsigned	int	i = MML->GetInt();

	if( (i <= 7) && (i >= 0) ){
		SetEvent(new mml_general(nsd_Release_Voice + i, "Release Voice"));
	} else {
		MML->Err("�����[�X���F�Ŏw��ł���͈͂𒴂��Ă��܂��B0�`7�͈̔͂Ŏw�肵�Ă��������B");
	}
}

//==============================================================
//		�����[�X����
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetReleaseVolume(MMLfile* MML)
{
	unsigned	int	i = MML->GetInt();

	if( (i <= 15) && (i >= 0) ){
		SetEvent(new mml_general(nsd_Release_Volume + i, "Release Volume"));
	} else {
		MML->Err("���ʂŎw��ł���͈͂𒴂��Ă��܂��B0�`15�͈̔͂Ŏw�肵�Ă��������B");
	}
}

//==============================================================
//		
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	MusicTrack::SetPoke(MMLfile* MML)
{
	unsigned	int	addr;
	unsigned	int	data;
	unsigned	char	cData;

	addr = MML->GetInt();
	if( (addr < 0x0000) || (addr > 0xFFFF) ){
		MML->Err("�p�����[�^�̒l���͈͂��z���܂����B");
	}

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err("y �R�}���h�̃p�����[�^������܂���B�Q�w�肵�Ă��������B");
	}

	data = MML->GetInt();
	if(data > 255){
		MML->Err("�p�����[�^�̒l���͈͂��z���܂����B");
	}
	SetEvent(new mml_poke(addr, data & 0xFF));
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
			MML->Err("�����R�}���h�E�u���b�N�̊J�n������{��������܂���B");
		}
	}

	// } ������܂ŁA�L�q�u���b�N�����R���p�C������B
	while((cData = MML->GetChar()) != '}'){
		
		// } ������O�ɁA[EOF]��������G���[
		if( MML->eof() ){
			MML->Err("�����R�}���h�E�u���b�N�̏I�[������`}'������܂���B");
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
				MML->Err("���� K{} �R�}���h�̈����Ŗ��m�̕������w�肳��܂����B");
				break;
		}
	}

	//for Debug
/*
	cout << "[0] c = " << (int)KeySignature[0] << endl;
	cout << "[1] d = " << (int)KeySignature[1] << endl;
	cout << "[2] e = " << (int)KeySignature[2] << endl;
	cout << "[3] f = " << (int)KeySignature[3] << endl;
	cout << "[4] g = " << (int)KeySignature[4] << endl;
	cout << "[5] a = " << (int)KeySignature[5] << endl;
	cout << "[6] b = " << (int)KeySignature[6] << endl;
*/
}

//==============================================================
//		�L�q�u���b�N�̏I���iEnd of Track�̒ǉ��j
//--------------------------------------------------------------
//	������
//		����
//	���Ԓl
//		����
//==============================================================
unsigned	int	MusicTrack::SetEnd(void)
{
	mml_Address*	_event;

	if(loop_flag == false){
		SetEvent(new mml_general(nsd_EndOfTrack,"End of Track"));
	} else {
		_event = new mml_Address(nsd_Jump, "End of Track with LOOP");
		_event->set_Address(offset_loop - offset_now - 1);
		SetEvent(_event);
	}
	iSize = offset_now;

	return(iSize);
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
	offset_now += _item->getSize();

	//�����object�̃|�C���^��ۑ����Ă����B
	ptcItem.push_back(_item);
}

