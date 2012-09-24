#include "StdAfx.h"
#include ".\Envelop.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//		bool		_sub	���̃I�u�W�F�N�g�́A�T�u���[�`���H
//	���Ԓl
//					����
//==============================================================
Envelop::Envelop(MMLfile* MML, unsigned int _id, const char _strName[]):
	MusicItem(_strName),
	m_id(_id)
{
	//----------------------
	//Local�ϐ�


//	�萔��`
enum	Command_ID_mml {
	Env_Num,
	Env_Sweep,
	Env_Hold,
	Env_Loop,
	Env_Release,
	Env_Commma
};

//	�����́AMML�\���Ŏg����R�}���h�B
const	static	Command_Info	Command[] = {
		{	"$",	Env_Num		},
		{	"%",	Env_Num		},
		{	"-",	Env_Num		},
		{	"0",	Env_Num		},
		{	"1",	Env_Num		},
		{	"2",	Env_Num		},
		{	"3",	Env_Num		},
		{	"4",	Env_Num		},
		{	"5",	Env_Num		},
		{	"6",	Env_Num		},
		{	"7",	Env_Num		},
		{	"8",	Env_Num		},
		{	"9",	Env_Num		},
		{	"{",	Env_Sweep	},
		{	"d",	Env_Hold	},
		{	"D",	Env_Hold	},
		{	"|",	Env_Loop	},
		{	"l",	Env_Loop	},
		{	"L",	Env_Loop	},
		{	"r",	Env_Release	},
		{	"R",	Env_Release	},
		{	",",	Env_Commma	}
};

	unsigned	char	cData;
				int		i;
				int		Loop_Normal		= -1;
				int		Loop_Release	= -1;
				bool	Release			= false;
	unsigned	int		ptEnvelop		= 1;

	//------------------------------
	//�N���X�̏����ݒ�


	//------------------------------
	//�R���p�C��

	// { �̌���
	while(MML->cRead() != '{'){
		if(MML->eof()){
			MML->Err("�u���b�N�̊J�n������{��������܂���B");
		}
	}

	code.resize(0);
	code.append((char)1, (char)0);

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

			case(Env_Num):
				MML->Back();
				i = MML->GetInt();
				if( (i<-64) || (i>63)){
					MML->Err("�G���x���[�v�́A-64�`63�͈̔͂Ŏw�肵�ĉ������B");
				}
				code.append((char)1, (char)i & 0x7F);
				ptEnvelop++;
				break;

			case(Env_Sweep):
				break;

			case(Env_Hold):
				i = MML->GetInt();
				if( (i<0) || (i>255)){
					MML->Err("�ێ����Ԃ́A0�`255�͈̔͂Ŏw�肵�ĉ������B");
				}
				while(i>15){
					code.append((char)1, (char)0x8F);
					i -= 16;		//15�������΁A16�t���[���ێ�
				ptEnvelop++;
				}
				code.append((char)1, (char)((i & 0x0F) | 0x80));
				ptEnvelop++;
				break;

			case(Env_Loop):
				if(ptEnvelop > 0x3F){
					MML->Err("���[�v�ʒu���w��ł���͈͂𒴂��܂����B");
				}
				if(Release == false){
					Loop_Normal		= ptEnvelop;
				} else {
					Loop_Release	= ptEnvelop;
				}
				break;

			case(Env_Release):
				if(Loop_Normal == -1){
					MML->Warning("���[�v�|�C���g������܂���B�Ō�̒l�����[�v���܂��B");
					code.append((char)1, (char)(ptEnvelop-1 | 0xC0));
				} else {
					if(ptEnvelop == Loop_Normal){
						MML->Err("L�R�}���h�̒����R�R�}���h��u�����Ƃ͂ł��܂���B");
					}
					code.append((char)1, (char)(Loop_Normal | 0xC0));
				}
				ptEnvelop++;
				code[0] = ptEnvelop;
				Release = true;
				break;

			case(Env_Commma):
				break;

			//unknown command
			default:
				MML->Err("unknown command");
				break;
		}
	}

	if(Release == true){
		if(Loop_Release == -1){
			MML->Warning("�����[�X���̃��[�v�|�C���g������܂���B�Ō�̒l�����[�v���܂��B");
			code.append((char)1, (char)(ptEnvelop-1 | 0xC0));
		} else {
			if(ptEnvelop == Loop_Release){
				MML->Err("L�R�}���h�Ńp�^�[����`���I��邱�Ƃ͂ł��܂���B");
			}
			code.append((char)1, (char)(Loop_Release | 0xC0));
		}
	} else {
		if(Loop_Normal == -1){
			MML->Warning("���[�v�|�C���g������܂���B�Ō�̒l�����[�v���܂��B");
			code.append((char)1, (char)(ptEnvelop-1 | 0xC0));
		} else {
			if(ptEnvelop == Loop_Normal){
				MML->Err("L�R�}���h�Ńp�^�[����`���I��邱�Ƃ͂ł��܂���B");
			}
			code.append((char)1, (char)(Loop_Normal | 0xC0));
		}
	}

	iSize = code.size();
}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
Envelop::~Envelop(void)
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
void	Envelop::getAsm(MusicFile* MUS)
{
	*MUS << MUS->Header.Label.c_str() << "Envelope" << m_id << ":" << endl;
	MusicItem::getAsm(MUS);
}
