#include "StdAfx.h"
#include ".\trackset.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//		bool		_sub	���̃I�u�W�F�N�g�́A�T�u���[�`���H
//	���Ԓl
//					����
//==============================================================
TrackSet::TrackSet(MMLfile* MML, bool _sub, const char _strName[]):
	MusicItem(_strName)
{
	//----------------------
	//Local�ϐ�

//	�萔��`
enum	Command_ID_mml {
	mml_Track,
	mml_KeySignature,
	mml_Macro,
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

	mml_Voice,

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

	mml_Memory_Write,

	mml_Bar
};

//	�����́AMML�\���Ŏg����R�}���h�B
const	static	Command_Info	Command[] = {
		{	"TR",	mml_Track				},
		{	"K",	mml_KeySignature,		},
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

		{	"@",	mml_Voice				},		//������

		{	"o",	mml_Octave				},
		{	">",	mml_Octave_Up			},
		{	"<",	mml_Octave_Down			},
		{	"`",	mml_Octave_Up1			},
		{	"\"",	mml_Octave_Down1		},
		{	"D%",	mml_Detune_Register		},
		{	"D",	mml_Detune_Cent			},
		{	"__",	mml_Transpose_Relative	},
		{	"_",	mml_Transpose			},
		{	"P",	mml_Protament			},		//������
		{	"s",	mml_Sweep				},

		{	"v",	mml_Volume				},
		{	")",	mml_Volume_Up			},
		{	"(",	mml_Volume_Down			},

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
			MML->Err("�u���b�N�̊J�n������{��������܂���B");
		}
	}

	// } ������܂ŁA�L�q�u���b�N�����R���p�C������B
	while((cData = MML->GetChar()) != '}'){
		
		// } ������O�ɁA[EOF]��������G���[
		if( MML->eof() ){
			MML->Err("�u���b�N�̏I�[������`}'������܂���B");
		}

		//�P�߂�
		MML->Back();


		//�e�R�}���h���̏���
		switch(MML->GetCommandID(Command, sizeof(Command)/sizeof(Command_Info))){

			case(mml_Track):
				if(fSub == true){
					MML->Warning("Sub�u���b�N�Ȃ��ł̓g���b�N�w��͂ł��܂���B�������܂��B");
				}
				iTrack = MML->GetInt() - 1;
				if( (iTrack < 0) ){
					MML->Err("�g���b�N�ԍ��Ŏw��ł���͈͂𒴂��Ă��܂��B");
				}
				nowTrack = getTrack(iTrack);
				break;

			case(mml_KeySignature):
				nowTrack->SetKeySignature(MML);
				break;

			case(mml_Macro):
				//�� to do 
				break;

			case(mml_Subroutine):
				nowTrack->SetSubroutine(MML);
				break;

			case(mml_Loop):
				if(fSub == true){
					MML->Warning("Sub�u���b�N�Ȃ��ł͖������[�v�͂ł��܂���B�������܂��B");
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
				nowTrack->SetEvent(new mml_general(nsd_Tempo, MML, "Tempo"));
				break;

			case(mml_Tempo_Relative):
				nowTrack->SetEvent(new mml_general(nsd_Relative_Tempo, MML, "Relative Tempo"));
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
				nowTrack->SetGatetime(MML);
				break;

			case(mml_Gate_u):
				nowTrack->SetGatetime_u(MML);
				break;

			case(mml_Envelop_Voice):
				nowTrack->SetEnvelop(nsd_Envelop_Voice, MML);
				break;

			case(mml_Envelop_Volume):
				nowTrack->SetEnvelop(nsd_Envelop_Volume, MML);
				break;

			case(mml_Envelop_Frequency):
				nowTrack->SetEnvelop(nsd_Envelop_Frequency, MML);
				break;

			case(mml_Envelop_Note):
				nowTrack->SetEnvelop(nsd_Envelop_Note, MML);
				break;

			case(mml_Envelop_Off_Voice):
				MML->Err("���F�G���x���[�v�́A@�R�}���h�Ŗ����ɂł��܂��B");
				break;

			case(mml_Envelop_Off_Volume):
				nowTrack->SetEvent(new mml_Address(nsd_Envelop_Volume));
				break;

			case(mml_Envelop_Off_Frequency):
				nowTrack->SetEvent(new mml_Address(nsd_Envelop_Frequency));
				break;

			case(mml_Envelop_Off_Note):
				nowTrack->SetEvent(new mml_Address(nsd_Envelop_Note));
				break;

			case(mml_Release_mdoe):
				nowTrack->SetReleaseMode(MML);
				break;

			case(mml_Release_Voice):
				nowTrack->SetReleaseVoice(MML);
				break;

			case(mml_Release_Volume):
				nowTrack->SetReleaseVolume(MML);
				break;

			case(mml_Voice):
				nowTrack->SetEvent(new mml_general(nsd_Voice, MML, "Voice"));
				break;

			case(mml_Octave):
				nowTrack->SetOctave(MML);
				break;

			case(mml_Octave_Up):
				if(MML->octave_reverse == true){
					nowTrack->SetEvent(new mml_general(nsd_Octave_Down, "Octave Down"));
				} else {
					nowTrack->SetEvent(new mml_general(nsd_Octave_Up, "Octave Up"));
				}
				break;

			case(mml_Octave_Down):
				if(MML->octave_reverse == true){
					nowTrack->SetEvent(new mml_general(nsd_Octave_Up, "Octave Up"));
				} else {
					nowTrack->SetEvent(new mml_general(nsd_Octave_Down, "Octave Down"));
				}
				break;

			case(mml_Octave_Up1):
				nowTrack->SetEvent(new mml_general(nsd_Octave_Up_1, "One time octave up"));
				break;

			case(mml_Octave_Down1):
				nowTrack->SetEvent(new mml_general(nsd_Octave_Down_1, "One time octave down"));
				break;

			case(mml_Detune_Cent):
				nowTrack->SetEvent(new mml_general(nsd_Detune_Cent, MML, "Detune Cent"));
				break;

			case(mml_Detune_Register):
				nowTrack->SetEvent(new mml_general(nsd_Derune_Register, MML, "Derune Register"));
				break;

			case(mml_Transpose):
				nowTrack->SetEvent(new mml_general(nsd_Transpose, MML, "Transpose"));
				break;

			case(mml_Transpose_Relative):
				nowTrack->SetEvent(new mml_general(nsd_Relative_Transpose, MML, "Relative Transpose"));
				break;

			case(mml_Protament):
				nowTrack->SetProtament(MML);
				break;

			case(mml_Sweep):
				nowTrack->SetSweep(MML);
				break;

			case(mml_Volume):
				nowTrack->SetVolume(MML);
				break;

			case(mml_Volume_Up):
				nowTrack->SetEvent(new mml_general(nsd_Volume_Up, "Volume up"));
				break;

			case(mml_Volume_Down):
				nowTrack->SetEvent(new mml_general(nsd_Volume_Down, "Volume down"));
				break;

			case(mml_Memory_Write):
				nowTrack->SetPoke(MML);
				break;

			case(mml_Bar):
				break;

			//unknown command
			default:
				MML->Err("unknown command");
				break;
		}
	}

	if(fSub == true){
		//�T�u���[�`���u���b�N�̏ꍇ
		code.resize(0);
		i = ptcTrack[iTrack]->SetEnd();

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
			i += ptcTrack[iTrack]->SetEnd();
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
//		�A�h���X�������肷��B
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	TrackSet::Fix_Address(map<int, Sub*>* ptcSub, map<int, Envelop*>* ptcEnvelop)
{
	iTrack = 0;
	while(iTrack <= maxTrack){
		ptcTrack[iTrack]->Fix_Address(ptcSub, ptcEnvelop);
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
			cout << "MusicTrack* TrackSet::getTrack()�֐��ŃG���[���������܂����B" << endl;
			exit(-1);
		}
	}
	maxTrack = i;	//�g���b�N�̍ő�l���L���B

	//�|�C���^���擾����B
	_getTrack = ptcTrack[_track];

	return(_getTrack);
}
