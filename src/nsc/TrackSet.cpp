#include "StdAfx.h"
#include "trackset.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//		bool		_sub	���̃I�u�W�F�N�g�́A�T�u���[�`���H
//	���Ԓl
//					����
//==============================================================
TrackSet::TrackSet(MMLfile* MML, unsigned int _id, bool _sub, const wchar_t _strName[]):
	MusicItem(_strName),
	m_id(_id)
{
	//----------------------
	//Local�ϐ�

//	�萔��`
enum	Command_ID_mml {
	mml_Track,
	mml_KeySignature,
	mml_Macro,
	mml_CallSE,
	mml_Subroutine,

	mml_Loop,
	mml_Repeat_A_Start,
	mml_Repeat_A_Branch,
	mml_Repeat_A_End,
	mml_Repeat_B_Start,
	mml_Repeat_B_Branch,
	mml_Repeat_B_End,

	mml_Tempo,
	mml_Tempo_Relative,

	mml_La,
	mml_Si,
	mml_Do,
	mml_Re,
	mml_Mi,
	mml_Fa,
	mml_Sol,
	mml_Rest,
	mml_Tai,

	mml_Length,
	mml_Gate_q,
	mml_Gate_u,

	mml_Echo,
	mml_Echo_Off,

	mml_Envelop_Voice,
	mml_Envelop_Volume,
	mml_Envelop_Frequency,
	mml_Envelop_Note,

	mml_Envelop_Off_Voice,
	mml_Envelop_Off_Volume,
	mml_Envelop_Off_Frequency,
	mml_Envelop_Off_Note,

	mml_Release_mdoe,
	mml_Release_Voice,
	mml_Release_Volume,

	mml_FDSC,
	mml_FDSM,
	mml_FDSF,
	mml_FDSV,
	mml_VRC7,
	mml_N163,
	mml_Voice,
	mml_N163_Channel,
	mml_FME7_frequency,

	mml_Octave,
	mml_Octave_Up,
	mml_Octave_Down,
	mml_Octave_Up1,
	mml_Octave_Down1,
	mml_Detune_Cent,
	mml_Detune_Register,
	mml_Transpose,
	mml_Transpose_Relative,
	mml_Protament,
	mml_Sweep,

	mml_Volume,
	mml_Volume_Up,
	mml_Volume_Down,

	mml_VRC7_Write,
	mml_Memory_Write,

	mml_Bar
};

//	�����́AMML�\���Ŏg����R�}���h�B
const	static	Command_Info	Command[] = {
		{	"TR",	mml_Track				},
		{	"K",	mml_KeySignature,		},
		{	"SE",	mml_CallSE				},
		{	"S",	mml_Subroutine			},
		{	"$",	mml_Macro,				},

		{	"L",	mml_Loop				},
		{	"|:",	mml_Repeat_B_Start		},
		{	"\\",	mml_Repeat_B_Branch		},
		{	":|",	mml_Repeat_B_End		},
		{	"[",	mml_Repeat_A_Start		},
		{	":",	mml_Repeat_A_Branch		},
		{	"]",	mml_Repeat_A_End		},

		{	"t_",	mml_Tempo_Relative,		},
		{	"t",	mml_Tempo,				},

		{	"a",	mml_La					},
		{	"b",	mml_Si					},
		{	"c",	mml_Do					},
		{	"d",	mml_Re					},
		{	"e",	mml_Mi					},
		{	"f",	mml_Fa					},
		{	"g",	mml_Sol					},
		{	"r",	mml_Rest				},
		{	"^",	mml_Tai					},

		{	"l",	mml_Length				},
		{	"q",	mml_Gate_q				},
		{	"u",	mml_Gate_u				},

		{	"EC*",	mml_Echo_Off			},
		{	"EC",	mml_Echo				},

		{	"E@*",	mml_Envelop_Off_Voice		},
		{	"Ev*",	mml_Envelop_Off_Volume		},
		{	"Em*",	mml_Envelop_Off_Frequency	},
		{	"En*",	mml_Envelop_Off_Note		},

		{	"E@",	mml_Envelop_Voice		},
		{	"Ev",	mml_Envelop_Volume		},
		{	"Em",	mml_Envelop_Frequency	},
		{	"En",	mml_Envelop_Note		},

		{	"Rm",	mml_Release_mdoe		},
		{	"R@",	mml_Release_Voice		},
		{	"Rv",	mml_Release_Volume		},

		{	"@FC",	mml_FDSC				},
		{	"@FM",	mml_FDSM				},
		{	"@FF",	mml_FDSF				},
		{	"@FV",	mml_FDSV				},
		{	"@V",	mml_VRC7				},
		{	"@N",	mml_N163				},
		{	"@",	mml_Voice				},
		{	"NC",	mml_N163_Channel		},
		{	"F",	mml_FME7_frequency		},

		{	"o",	mml_Octave				},
		{	">",	mml_Octave_Up			},
		{	"<",	mml_Octave_Down			},
		{	"`",	mml_Octave_Up1			},
		{	"\"",	mml_Octave_Down1		},
		{	"D%",	mml_Detune_Register		},
		{	"D",	mml_Detune_Cent			},
		{	"__",	mml_Transpose_Relative	},
		{	"_",	mml_Transpose			},
		{	"P",	mml_Protament			},
		{	"s",	mml_Sweep				},

		{	"v",	mml_Volume				},
		{	")",	mml_Volume_Up			},
		{	"(",	mml_Volume_Down			},

		{	"yV",	mml_VRC7_Write			},
		{	"y",	mml_Memory_Write		},

		{	"|",	mml_Bar					}
};

	unsigned	char	cData;
				int		i;

	//------------------------------
	//�N���X�̏����ݒ�
	fSub		= _sub;		//�T�u���[�`���̃t���O
	iTrack		= 0;		//�R���p�C�����̃g���b�N�iDefault = 0�j
	maxTrack	= 0;		//�ő�g���b�N�ԍ�

	//�܂��́A�P�����g���b�N�i0�ԁj�̃I�u�W�F�N�g�����B
	nowTrack	= makeTrack(iTrack);



	//------------------------------
	//�R���p�C��

	// { �̌���
	while(MML->cRead() != '{'){
		if(MML->eof()){
			MML->Err(L"�u���b�N�̊J�n������{��������܂���B");
		}
	}

	// } ������܂ŁA�L�q�u���b�N�����R���p�C������B
	while((cData = MML->GetChar()) != '}'){
		
		// } ������O�ɁA[EOF]��������G���[
		if( MML->eof() ){
			MML->Err(L"�u���b�N�̏I�[������`}'������܂���B");
		}

		//�P�߂�
		MML->Back();


		//�e�R�}���h���̏���
		switch(MML->GetCommandID(Command, sizeof(Command)/sizeof(Command_Info))){

			case(mml_Track):
				if(fSub == true){
					MML->Warning(L"Sub�u���b�N�Ȃ��ł̓g���b�N�w��͂ł��܂���B�������܂��B");
				}
				iTrack = MML->GetInt() - 1;
				if( (iTrack < 0) ){
					MML->Err(L"�g���b�N�ԍ��Ŏw��ł���͈͂𒴂��Ă��܂��B");
				}
				nowTrack = getTrack(iTrack);
				break;

			case(mml_KeySignature):
				nowTrack->SetKeySignature(MML);
				break;

			case(mml_Macro):
				//�� to do 
				break;

			case(mml_CallSE):
				nowTrack->SetSE(MML);
				break;

			case(mml_Subroutine):
				nowTrack->SetSubroutine(MML);
				break;

			case(mml_Loop):
				if(fSub == true){
					MML->Warning(L"Sub�u���b�N�Ȃ��ł͖������[�v�͂ł��܂���B�������܂��B");
				} else {
					nowTrack->SetLoop();
				}
				break;

			case(mml_Repeat_A_Start):
				nowTrack->SetRepeat_A_Start(MML);
				break;

			case(mml_Repeat_A_Branch):
				nowTrack->SetRepeat_A_Branch(MML);
				break;

			case(mml_Repeat_A_End):
				nowTrack->SetRepeat_A_End(MML);
				break;

			case(mml_Repeat_B_Start):
				nowTrack->SetRepeat_B_Start(MML);
				break;

			case(mml_Repeat_B_Branch):
				nowTrack->SetRepeat_B_Branch(MML);
				break;

			case(mml_Repeat_B_End):
				nowTrack->SetRepeat_B_End(MML);
				break;

			case(mml_Tempo):
				SetTempo(MML);
				break;

			case(mml_Tempo_Relative):
				SetEvent(new mml_general(nsd_Relative_Tempo, MML, L"Relative Tempo"));
				break;

			case(mml_La):
				nowTrack->SetNote(MML, 5);
				break;

			case(mml_Si):
				nowTrack->SetNote(MML, 6);
				break;

			case(mml_Do):
				nowTrack->SetNote(MML, 0);
				break;

			case(mml_Re):
				nowTrack->SetNote(MML, 1);
				break;

			case(mml_Mi):
				nowTrack->SetNote(MML, 2);
				break;

			case(mml_Fa):
				nowTrack->SetNote(MML, 3);
				break;

			case(mml_Sol):
				nowTrack->SetNote(MML, 4);
				break;

			case(mml_Rest):
				nowTrack->SetRest(MML);
				break;

			case(mml_Tai):
				nowTrack->SetTai(MML);
				break;

			case(mml_Length):
				nowTrack->SetLength(MML);
				break;

			case(mml_Gate_q):
				SetGatetime(MML);
				break;

			case(mml_Gate_u):
				SetGatetime_u(MML);
				break;

			case(mml_Echo_Off):
				nowTrack->SetEcho();
				break;

			case(mml_Echo):
				nowTrack->SetEcho(MML);
				break;

			case(mml_Envelop_Voice):
				nowTrack->SetEnvelop(nsd_Envelop_Voice, MML, MML->offset_Ei);
				break;

			case(mml_Envelop_Volume):
				nowTrack->SetEnvelop(nsd_Envelop_Volume, MML, MML->offset_Ev);
				break;

			case(mml_Envelop_Frequency):
				nowTrack->SetEnvelop(nsd_Envelop_Frequency, MML, MML->offset_Em);
				break;

			case(mml_Envelop_Note):
				nowTrack->SetEnvelop(nsd_Envelop_Note, MML, MML->offset_En);
				break;

			case(mml_Envelop_Off_Voice):
				MML->Err(L"���F�G���x���[�v�́A@�R�}���h�Ŗ����ɂł��܂��B");
				break;

			case(mml_Envelop_Off_Volume):
				SetEvent(new mml_Address(nsd_Envelop_Volume));
				break;

			case(mml_Envelop_Off_Frequency):
				SetEvent(new mml_Address(nsd_Envelop_Frequency));
				break;

			case(mml_Envelop_Off_Note):
				SetEvent(new mml_Address(nsd_Envelop_Note));
				break;

			case(mml_Release_mdoe):
				SetReleaseMode(MML);
				break;

			case(mml_Release_Voice):
				SetReleaseVoice(MML);
				break;

			case(mml_Release_Volume):
				SetReleaseVolume(MML);
				break;

			case(mml_Voice):
				SetEvent(new mml_general(nsd_Voice, MML, L"Voice"));
				break;

			case(mml_FDSC):
				nowTrack->SetFDSC(MML);
				break;

			case(mml_FDSM):
				nowTrack->SetFDSM(MML);
				break;

			case(mml_FDSF):
				Set_FDS_Frequency(MML);
				break;

			case(mml_FDSV):
				Set_FDS_Volume(MML);
				break;

			case(mml_VRC7):
				nowTrack->SetVRC7(MML);
				break;

			case(mml_N163):
				nowTrack->SetN163(MML);
				break;

			case(mml_N163_Channel):
				SetN163Channel(MML);
				break;

			case(mml_FME7_frequency):
				Set_FME7_Frequency(MML);
				break;

			case(mml_Octave):
				SetOctave(MML);
				break;

			case(mml_Octave_Up):
				if(MML->octave_reverse == true){
					SetOctaveDec();
				} else {
					SetOctaveInc();
				}
				break;

			case(mml_Octave_Down):
				if(MML->octave_reverse == true){
					SetOctaveInc();
				} else {
					SetOctaveDec();
				}
				break;

			case(mml_Octave_Up1):
				SetOctaveOne_Inc();
				break;

			case(mml_Octave_Down1):
				SetOctaveOne_Dec();
				break;

			case(mml_Detune_Cent):
				SetEvent(new mml_general(nsd_Detune_Cent, MML, L"Detune Cent"));
				break;

			case(mml_Detune_Register):
				SetEvent(new mml_general(nsd_Derune_Register, MML, L"Derune Register"));
				break;

			case(mml_Transpose):
				SetEvent(new mml_general(nsd_Transpose, MML, L"Transpose"));
				break;

			case(mml_Transpose_Relative):
				SetEvent(new mml_general(nsd_Relative_Transpose, MML, L"Relative Transpose"));
				break;

			case(mml_Protament):
				SetProtament(MML);
				break;

			case(mml_Sweep):
				SetSweep(MML);
				break;

			case(mml_Volume):
				SetVolume(MML);
				break;

			case(mml_Volume_Up):
				SetVolumeInc();
				break;

			case(mml_Volume_Down):
				SetVolumeDec();
				break;

			case(mml_VRC7_Write):
				SetVRC7_Write(MML);
				break;

			case(mml_Memory_Write):
				SetPoke(MML);
				break;

			case(mml_Bar):
				break;

			//unknown command
			default:
				MML->Err(L"unknown command");
				break;
		}
	}

	if(fSub == true){
		//�T�u���[�`���u���b�N�̏ꍇ
		code.resize(0);
		i = (int)ptcTrack[iTrack]->SetEnd();

	} else {
		//����ȊO�̏ꍇ
		i = 2 + ((maxTrack + 1) * 2);		//�g���b�N���������w�b�_�[�̃T�C�Y���v�Z�B
		code.resize(i);						//�w�b�_�p�ɃR�[�h�T�C�Y���m��

		code[0] = maxTrack + 1;				//�g���b�N��
		code[1] = 0;						//

		//�e�g���b�N�ɏI�[�������āA�ȃf�[�^�̃A�h���X�����쐬
		iTrack = 0;
		while(iTrack <= maxTrack){
			code[iTrack *2 + 2]	= ((i   ) & 0xFF);
			code[iTrack *2 + 3]	= ((i>>8) & 0xFF);
			i += (int)ptcTrack[iTrack]->SetEnd();
			iTrack++;
		}
	}
	iSize = i;

}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
TrackSet::~TrackSet(void)
{
}

//==============================================================
//		�R�[�h�̎擾
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	TrackSet::getAsm(MusicFile* MUS)
{
	//----------------------
	//Local�ϐ�
	unsigned	int	i = 0;
	vector<	MusicItem*>::iterator	itItem;

	if(fSub == false){
		*MUS << "	.byte	$" << hex << setw(2) << setfill('0') << (int)(code[0] & 0xFF) << ", $" << (int)(code[1] & 0xFF) << endl;
		while(i <= maxTrack){
			if(i==0){
				*MUS << "	.word	$";
			} else {
				*MUS << " ,$";
			}
			*MUS << hex << setw(4) << setfill('0') << (int)((code[i*2+2] & 0xFF) | ((code[i*2+3] & 0xFF)<<8));
			i++;
		}
		*MUS << dec << endl;
	}

	if(!ptcItem.empty()){
		itItem = ptcItem.begin();
		while(itItem != ptcItem.end()){
			(*itItem)->getAsm(MUS);
			itItem++;
		}
	}
}

//==============================================================
//		�A�h���X�������肷��B
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	TrackSet::Fix_Address(MusicFile* MUS)
{
	iTrack = 0;
	while(iTrack <= maxTrack){
		ptcTrack[iTrack]->Fix_Address(MUS);
		iTrack++;
	}

}
//==============================================================
//		�g���b�N�̍쐬
//--------------------------------------------------------------
//	������
//		unsigned int _track		�g���b�N�ԍ�
//	���Ԓl
//		MusicTrack*				������g���b�N�E�I�u�W�F�N�g�̃|�C���^
//==============================================================
MusicTrack*	TrackSet::makeTrack(int _track)
{
	//�g���b�N�̃I�u�W�F�N�g�𐶐��B
	MusicTrack*	newTrack	= new MusicTrack();

	//���������A�C�e���͕ۑ�
	ptcItem.push_back(newTrack);		//���N���X"MusicItem"���ŊJ������B
	ptcTrack[_track] = newTrack;

	//�|�C���^��n��
	return(newTrack);
}

//==============================================================
//		�g���b�N�E�I�u�W�F�N�g�̃|�C���^���擾
//--------------------------------------------------------------
//	������
//		unsigned int _track		�g���b�N�ԍ�
//	���Ԓl
//		MusicTrack*				�g���b�N�E�I�u�W�F�N�g�̃|�C���^
//	���Ԓl
//		�w�肳�ꂽ�ԍ��̃g���b�N�E�I�u�W�F�N�g�̃|�C���^���擾����
//		���������ꍇ�͐V���Ƀg���b�N������āA
//		�g���b�N�ԍ����ő�l�𒴂��Ă�����ő�l���X�V����B
//==============================================================
MusicTrack*	TrackSet::getTrack(int _track)
{
			int	i			 = maxTrack;	// i = ������A�ŏI�g���b�N�̔ԍ�
	MusicTrack*	_getTrack;

	//�ŏI�g���b�N�ԍ����w��l������������A�J��Ԃ��B
	while(i < _track){
		i++;
		//�g���b�N��������������
		if(ptcTrack.count(i) == 0){
			_getTrack	= makeTrack(i);
		} else {
			wcout << L"MusicTrack* TrackSet::getTrack()�֐��ŃG���[���������܂����B" << endl;
			exit(-1);
		}
	}
	maxTrack = i;	//�g���b�N�̍ő�l���L���B

	//�|�C���^���擾����B
	_getTrack = ptcTrack[_track];

	return(_getTrack);
}

//==============================================================
//		�I�N�^�[�u
//--------------------------------------------------------------
//	������
//		MusicItem* _item
//	���Ԓl
//		����
//==============================================================
void	TrackSet::SetEvent(MusicItem* _item)
{
	nowTrack->SetEvent(_item);
}

//==============================================================
//		�I�N�^�[�u
//--------------------------------------------------------------
//	������
//		MusicItem* _item
//	���Ԓl
//		����
//==============================================================
void	TrackSet::SetTempo(MMLfile* MML)
{
	int	iTempo	= MML->GetInt();

	iTempo = (iTempo * MML->timebase) / 24;
	if((iTempo<0) || (iTempo>255)){
		MML->Err(L"�e���|���͈͂𒴂��܂����B");
	}

	SetEvent(new mml_general(nsd_Tempo, iTempo, L"Tempo"));
}

//==============================================================
//		�I�N�^�[�u
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	TrackSet::SetOctave(MMLfile* MML)
{
	unsigned	int	iOctave = MML->GetInt() - 2;

	if( (iOctave <= 7) && (iOctave >=0) ){
		SetEvent(new mml_general(nsd_Octave + iOctave, L"Octave"));
		nowTrack->SetOctave(iOctave);
	} else {
		MML->Err(L"�I�N�^�[�u��2�`9�͈̔͂Ŏw�肵�Ă��������Bo1�̗̈�́A���΃I�N�^�[�u�������p���������B");
	}
}

void	TrackSet::SetOctaveInc()
{
	SetEvent(new mml_general(nsd_Octave_Up, L"Octave Up"));
	nowTrack->IncOctave();
}

void	TrackSet::SetOctaveDec()
{
	SetEvent(new mml_general(nsd_Octave_Down, L"Octave Down"));
	nowTrack->DecOctave();
}

void	TrackSet::SetOctaveOne_Inc()
{
	SetEvent(new mml_general(nsd_Octave_Up_1, L"One time octave up"));
	nowTrack->IncOctave1();
}

void	TrackSet::SetOctaveOne_Dec()
{
	SetEvent(new mml_general(nsd_Octave_Down_1, L"One time octave down"));
	nowTrack->DecOctave1();
}

//==============================================================
//		����
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	TrackSet::SetVolume(MMLfile* MML)
{
	unsigned	int	i = MML->GetInt();

	if( (i <= 15) && (i >= 0) ){
		SetEvent(new mml_general(nsd_Volume + i, L"Volume"));
		nowTrack->SetVolume(i);
	} else {
		MML->Err(L"���ʂŎw��ł���͈͂𒴂��Ă��܂��B0�`15�͈̔͂Ŏw�肵�Ă��������B");
	}
}

void	TrackSet::SetVolumeInc()
{
	SetEvent(new mml_general(nsd_Volume_Up, L"Volume up"));
	nowTrack->IncVolume();
}

void	TrackSet::SetVolumeDec()
{
	SetEvent(new mml_general(nsd_Volume_Down, L"Volume down"));
	nowTrack->DecVolume();
}

//==============================================================
//		�����[�X���[�h
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	TrackSet::SetReleaseMode(MMLfile* MML)
{
	mml_general*	_event;
	unsigned	int	i = MML->GetInt();

	switch(i){
		case(0):
			_event = new mml_general(nsd_GateMode_0,  L"GateMode 0");
			break;
		case(1):
			_event = new mml_general(nsd_GateMode_1,  L"GateMode 1");
			break;
		case(2):
			_event = new mml_general(nsd_GateMode_2,  L"GateMode 2");
			break;
		default:
			MML->Err(L"�����[�X���[�h�Ŏw��ł���͈͂𒴂��Ă��܂��B0�`2�͈̔͂Ŏw�肵�Ă��������B");
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
void	TrackSet::SetReleaseVoice(MMLfile* MML)
{
	unsigned	int	i = MML->GetInt();

	if( (i <= 7) && (i >= 0) ){
		SetEvent(new mml_general(nsd_Release_Voice + i, L"Release Voice"));
	} else {
		MML->Err(L"�����[�X���F�Ŏw��ł���͈͂𒴂��Ă��܂��B0�`7�͈̔͂Ŏw�肵�Ă��������B");
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
void	TrackSet::SetReleaseVolume(MMLfile* MML)
{
	unsigned	int	i = MML->GetInt();

	if( (i <= 15) && (i >= 0) ){
		SetEvent(new mml_general(nsd_Release_Volume + i, L"Release Volume"));
	} else {
		MML->Err(L"���ʂŎw��ł���͈͂𒴂��Ă��܂��B0�`15�͈̔͂Ŏw�肵�Ă��������B");
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
void	TrackSet::SetGatetime(MMLfile* MML)
{
	unsigned	int	i = MML->GetInt();

	if( (i <= 15) && (i >= 0) ){
		SetEvent(new mml_general(nsd_GateTime_Byte + i, L"Gatetime(q) Byte"));
	} else if( i <= 255) {
		SetEvent(new mml_general(nsd_GateTime_q, i, L"Gatetime(q)"));
	} else {
		MML->Err(L"�p�����[�^�̒l���͈͂��z���܂����B");
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
void	TrackSet::SetGatetime_u(MMLfile* MML)
{
	unsigned		int	i;
	unsigned		char	cData;

	//�x���̃��[�h
	cData = MML->GetChar();
	if(cData == '0'){
		i = 0;
	} else {
		MML->Back();
		i = MML->GetLength(nowTrack->GetDefaultLength());
	}
	SetEvent(new mml_general(nsd_GateTime_u, i & 0xFF , L"GateTime(u)"));
	
}

//==============================================================
//		
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	TrackSet::SetProtament(MMLfile* MML)
{
	unsigned	char	cData;

				int		_Decay;
				int		_Rate;
				int		_Depth;
				int		_Target;

	_Decay = MML->GetInt();
	if( (_Decay < 0) || (_Decay > 255) ){
		MML->Err(L"�|���^�����g�̑�1�p�����[�^�́A0�`255�͈̔͂Ŏw�肵�Ă��������B");
	}
	_Decay++;

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err(L"P �R�}���h�̃p�����[�^������܂���B�S�w�肵�Ă��������B");
	}

	_Rate = MML->GetInt();
	if( (_Rate < 1) || (_Rate > 256) ){
		MML->Err(L"�|���^�����g�̑�2�p�����[�^�́A1�`256�͈̔͂Ŏw�肵�Ă��������B");
	}

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err(L"P �R�}���h�̃p�����[�^������܂���B�S�w�肵�Ă��������B");
	}

	_Depth = MML->GetInt();
	if( (_Depth < -128) || (_Depth > 127) ){
		MML->Err(L"�|���^�����g�̑�3�p�����[�^�́A-128�`127�͈̔͂Ŏw�肵�Ă��������B");
	}
	_Decay++;

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err(L"P �R�}���h�̃p�����[�^������܂���B�S�w�肵�Ă��������B");
	}

	_Target = MML->GetInt();
	if( (_Target < -128) || (_Target > 127) ){
		MML->Err(L"�|���^�����g�̑�4�p�����[�^�́A-128�`127�͈̔͂Ŏw�肵�Ă��������B");
	}
	SetEvent(new mml_general(nsd_Portamento, _Decay & 0xFF,_Rate & 0xFF,_Depth & 0xFF,_Target & 0xFF, L"Portamento"));
}

//==============================================================
//		�X�C�[�v
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	TrackSet::SetSweep(MMLfile* MML)
{
				int		iSpeed;
				int		iDepth;
	unsigned	char	_data;
	unsigned	char	cData;

	iSpeed = MML->GetInt();

	cData = MML->GetChar();
	if(cData != ','){
		if( (iSpeed < 0) || (iSpeed > 255) ){
			MML->Err(L"0�`255�͈̔͂Ŏw�肵�Ă��������B");
		}
		MML->Back();
		_data = iSpeed;
	} else {
		if( (iSpeed < 0) || (iSpeed > 15) ){
			MML->Err(L"�X�C�[�v�Ŏw��ł���͈͂𒴂��Ă��܂��B0�`15�͈̔͂Ŏw�肵�Ă��������B");
		}
		iDepth = MML->GetInt();
		if( (iDepth < 0) || (iDepth > 15) ){
			MML->Err(L"�X�C�[�v�Ŏw��ł���͈͂𒴂��Ă��܂��B0�`15�͈̔͂Ŏw�肵�Ă��������B");
		}
		_data = ((iSpeed & 0x0F) << 4) | (iDepth & 0x0F);
	}

	SetEvent(new mml_general(nsd_Sweep, _data, L"Sweep"));
}

//==============================================================
//		
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//		����
//==============================================================
void	TrackSet::SetPoke(MMLfile* MML)
{
	unsigned	int	addr;
	unsigned	int	data;
	unsigned	char	cData;

	addr = MML->GetInt();
	if( (addr < 0x0000) || (addr > 0xFFFF) ){
		MML->Err(L"�p�����[�^�̒l���͈͂��z���܂����B");
	}

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err(L"y �R�}���h�̃p�����[�^������܂���B�Q�w�肵�Ă��������B");
	}

	data = MML->GetInt();
	if(data > 255){
		MML->Err(L"�p�����[�^�̒l���͈͂��z���܂����B");
	}
	SetEvent(new mml_poke(addr, data & 0xFF));
}

//==============================================================
//			FDS	�L�����A���g���ݒ�
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	TrackSet::Set_FDS_Frequency(MMLfile* MML)
{
	int	i = MML->GetInt();

	if( (i <= 0x0FFF) && (i >=0) ){
		unsigned	char	c0 = ( i       & 0xFF);
		unsigned	char	c1 = ((i >> 8) & 0xFF);
		SetEvent(new mml_general(nsd_FDS_Frequency,c0,c1,L"FDS career frequency"));
	} else {
		MML->Err(L"FDS�̃L�����A���g���́A0�`4095�͈̔͂Ŏw�肵�ĉ������B");
	}
}

//==============================================================
//			FDS	Master volume
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	TrackSet::Set_FDS_Volume(MMLfile* MML)
{
	int		i = MML->GetInt();

	if((i<=3 ) && (i>=0)){
		SetEvent(new mml_general(nsd_FDS_Volume,i,L"FDS Master volume"));
	} else {
		MML->Err(L"FDS�̃}�X�^�[���ʂ́A0�`3�͈̔͂Ŏw�肵�ĉ������B");
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
void	TrackSet::SetVRC7_Write(MMLfile* MML)
{
	unsigned	char	cData;

				int		_Reg;
				int		_Dat;

	_Reg = MML->GetInt();
	if( (_Reg < 0) || (_Reg > 0x40) ){
		MML->Err(L"�|���^�����g�̑�1�p�����[�^�́A0�`63�͈̔͂Ŏw�肵�Ă��������B");
	}

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err(L"P �R�}���h�̃p�����[�^������܂���B�S�w�肵�Ă��������B");
	}

	_Dat = MML->GetInt();
	if( (_Dat < 0) || (_Dat > 255) ){
		MML->Err(L"�|���^�����g�̑�2�p�����[�^�́A0�`255�͈̔͂Ŏw�肵�Ă��������B");
	}

	SetEvent(new mml_general(nsc_VRC7_reg,_Reg,_Dat, L"VRC7 Register Write"));
}

//==============================================================
//		NC	n163�`�����l�����ݒ�
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	TrackSet::SetN163Channel(MMLfile* MML)
{
	int	i = MML->GetInt();

	if( (i <= 8) && (i >=1) ){
		SetEvent(new mml_general(nsc_N163_Channel,i-1,L"n163 channel"));
	} else {
		MML->Err(L"n163�̃`�����l������1�`8�͈̔͂Ŏw�肵�Ă��������B");
	}

}

//==============================================================
//			SUNSOFT 5b �G���x���[�v���g���ݒ�
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	TrackSet::Set_FME7_Frequency(MMLfile* MML)
{
	int	i = MML->GetInt();

	if( (i <= 0xFFFF) && (i >=0) ){
		unsigned	char	c0 = ( i       & 0xFF);
		unsigned	char	c1 = ((i >> 8) & 0xFF);
		SetEvent(new mml_general(nsc_FME7_frequency,c0,c1,L"FME7 envelop frequency"));
	} else {
		MML->Err(L"FME7�̃n�[�h�E�F�A�G���x���[�v���g���́A0�`65535�͈̔͂Ŏw�肵�ĉ������B");
	}
}

