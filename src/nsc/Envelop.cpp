#include "StdAfx.h"
#include "Envelop.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MMLfile*			MML			MML�t�@�C���̃I�u�W�F�N�g
//		unsigned	int		_id			�G���x���[�v�ԍ�
//		const		wchar_t	_strName[]	�I�u�W�F�N�g��
//	���Ԓl
//					����
//==============================================================
Envelop::Envelop(MMLfile* MML, unsigned int _id, const wchar_t _strName[]):
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
		{	"(",	Env_Sweep	},
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

	//------------------------------
	//�N���X�̏����ݒ�

	Loop_Normal		= -1;
	Loop_Release	= -1;
	Release			= false;
	ptEnvelop		= 1;

	code.resize(0);
	code.append((char)1, (char)0);



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

			case(Env_Num):
				MML->Back();
				i = MML->GetInt();
				if( (i<-64) || (i>127)){
					MML->Err(L"�G���x���[�v�́A-64�`127�͈̔͂Ŏw�肵�ĉ������B");
				}
				code.append((char)1, (char)i & 0x7F);
				ptEnvelop++;
				break;

			case(Env_Sweep):
				sweep(MML);
				break;

			case(Env_Hold):
				i = MML->GetInt();
				if( (i<0) || (i>255)){
					MML->Err(L"�ێ����Ԃ́A0�`255�͈̔͂Ŏw�肵�ĉ������B");
				}
				setHold(i);
				break;

			case(Env_Loop):
				if(ptEnvelop > 0x3F){
					MML->Err(L"���[�v�ʒu���w��ł���͈͂𒴂��܂����B");
				}
				if(Release == false){
					Loop_Normal		= ptEnvelop;
				} else {
					Loop_Release	= ptEnvelop;
				}
				break;

			case(Env_Release):
				if(Loop_Normal == -1){
					MML->Warning(L"���[�v�|�C���g������܂���B�Ō�̒l�����[�v���܂��B");
					code.append((char)1, (char)(ptEnvelop-1 | 0xC0));
				} else {
					if(ptEnvelop == Loop_Normal){
						MML->Err(L"L�R�}���h�̒����R�R�}���h��u�����Ƃ͂ł��܂���B");
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
				MML->Err(L"unknown command");
				break;
		}
	}

	if(Release == true){
		if(Loop_Release == -1){
			MML->Warning(L"�����[�X���̃��[�v�|�C���g������܂���B�Ō�̒l�����[�v���܂��B");
			code.append((char)1, (char)(ptEnvelop-1 | 0xC0));
		} else {
			if(ptEnvelop == Loop_Release){
				MML->Err(L"L�R�}���h�Ńp�^�[����`���I��邱�Ƃ͂ł��܂���B");
			}
			code.append((char)1, (char)(Loop_Release | 0xC0));
		}
	} else {
		if(Loop_Normal == -1){
			MML->Warning(L"���[�v�|�C���g������܂���B�Ō�̒l�����[�v���܂��B");
			code.append((char)1, (char)(ptEnvelop-1 | 0xC0));
		} else {
			if(ptEnvelop == Loop_Normal){
				MML->Err(L"L�R�}���h�Ńp�^�[����`���I��邱�Ƃ͂ł��܂���B");
			}
			code.append((char)1, (char)(Loop_Normal | 0xC0));
		}
	}

	if(code.size() > 256){
		MML->Err(L"�G���x���[�v�̒�`����256Byte���z���܂����B");
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
//		�ێ����Ԃ̃Z�b�g
//--------------------------------------------------------------
//	������
//		int		length		�ێ�����
//	���Ԓl
//				����
//==============================================================
void	Envelop::setHold(int length)
{
	while(length>15){
		code.append((char)1, (char)0x8F);
		ptEnvelop++;
		length -= 16;		//15�������΁A16�t���[���ێ�
	}
	code.append((char)1, (char)((length & 0x0F) | 0x80));
	ptEnvelop++;
}

//==============================================================
//		�X�C�[�v
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	Envelop::sweep(MMLfile* MML)
{
	unsigned	char	cData;

	int		iStart;
	int		iEnd;
	int		iLength;
	int		iDelta;

	int		now;
	int		cnt;

	int		i=0;
	int		temp;

	//--------------------------
	//��MML�ǂݍ���

	//
	iStart = MML->GetInt();
	if( (iStart<-64) || (iStart>127)){
		MML->Err(L"�J�n�_�́A-64�`127�͈̔͂Ŏw�肵�ĉ������B");
	}

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err(L"�p�����[�^������܂���B");
	}

	iEnd = MML->GetInt();
	if( (iEnd<-64) || (iEnd>127)){
		MML->Err(L"�I���_�́A-64�`127�͈̔͂Ŏw�肵�ĉ������B");
	}

	cData = MML->GetChar();
	if(cData != ','){
		MML->Err(L"�p�����[�^������܂���B");
	}

	iLength = MML->GetInt();
	if( (iLength<1) || (iLength>255)){
		MML->Err(L"�����́A1�`255�͈̔͂Ŏw�肵�ĉ������B");
	}

	cData = MML->GetChar();
	if((cData != ')') && (cData != '}')){
		MML->Err(L"�p�����[�^������܂���B");
	}

	//--------------------------
	//���e�[�u���쐬

	iDelta = iEnd - iStart;

	while(i<iLength){
		temp = iStart + (iDelta * i) / iLength;
		if(i == 0){
			now = temp;
			cnt	= 0;
		} else if (temp != now){
			code.append((char)1, (char)now & 0x7F);
			ptEnvelop++;
			if(cnt>=1){
				setHold(cnt-1);
			}
			now = temp;
			cnt	= 0;
		} else {
			cnt++;
		}
		i++;
	}

	code.append((char)1, (char)now & 0x7F);
	ptEnvelop++;
	if(cnt>=1){
		setHold(cnt-1);
	}

}

//==============================================================
//		�R�[�h�̎擾
//--------------------------------------------------------------
//	������
//		MusicFile*	MUS		�R�[�h���o�͂���ȃf�[�^�t�@�C���E�I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	Envelop::getAsm(MusicFile* MUS)
{
	*MUS << MUS->Header.Label.c_str() << "Envelope" << m_id << ":" << endl;
	MusicItem::getAsm(MUS);
}
