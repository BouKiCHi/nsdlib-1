#include "StdAfx.h"
#include "FDSC.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MMLfile*			MML			MML�t�@�C���̃I�u�W�F�N�g
//		unsigned	int		_id			FDSC�ԍ�
//		const		wchar_t	_strName[]	�I�u�W�F�N�g��
//	���Ԓl
//					����
//==============================================================
FDSC::FDSC(MMLfile* MML, unsigned int _id, const wchar_t _strName[]):
	MusicItem(_strName),
	m_id(_id)
{
	//----------------------
	//Local�ϐ�


//	�萔��`
enum	Command_ID_mml {
	FDSC_Num,
	FDSC_Commma
};

//	�����́AMML�\���Ŏg����R�}���h�B
const	static	Command_Info	Command[] = {
		{	"%",	FDSC_Num	},
		{	"$",	FDSC_Num	},
		{	"0",	FDSC_Num	},
		{	"1",	FDSC_Num	},
		{	"2",	FDSC_Num	},
		{	"3",	FDSC_Num	},
		{	"4",	FDSC_Num	},
		{	"5",	FDSC_Num	},
		{	"6",	FDSC_Num	},
		{	"7",	FDSC_Num	},
		{	"8",	FDSC_Num	},
		{	"9",	FDSC_Num	},
		{	",",	FDSC_Commma	}
};

				int		i;
	unsigned	char	cData;
	unsigned	int		ptFDSC		= 0;
				string	WAVE;

	//------------------------------
	//�N���X�̏����ݒ�
	WAVE.clear();

	//------------------------------
	//�R���p�C��

	// { �̌���
	while(MML->cRead() != '{'){
		if(MML->eof()){
			MML->Err(L"�u���b�N�̊J�n������{��������܂���B");
		}
	}

	code.resize(0);

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

			case(FDSC_Num):
				MML->Back();
				i = MML->GetInt();
				if( (i<0) || (i>63)){
					MML->Err(L"FDSC�̔g�`��`�́A0�`63�͈̔͂Ŏw�肵�ĉ������B");
				}
				WAVE.append((char)1, (char)i & 0x3F);
				ptFDSC++;
				break;

			case(FDSC_Commma):
				break;

			//unknown command
			default:
				MML->Err(L"unknown command");
				break;
		}
	}
	if(ptFDSC < 64){
		MML->Err(L"�T���v������64�𒴂��Ă��܂��B");
	}
	if(ptFDSC > 64){
		MML->Err(L"�T���v������64�����ł��B");
	}
	i = 0;
	while(ptFDSC>0){
		code.append((char)1, WAVE[i]);
		i++;
		ptFDSC--;
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
FDSC::~FDSC(void)
{
}
//==============================================================
//		�R�[�h�̎擾
//--------------------------------------------------------------
//	������
//		MusicFile*	MUS		�R�[�h���o�͂���ȃf�[�^�t�@�C���E�I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	FDSC::getAsm(MusicFile* MUS)
{
	*MUS << MUS->Header.Label.c_str() << "FDSC" << m_id << ":" << endl;
	MusicItem::getAsm(MUS);
}