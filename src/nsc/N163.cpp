#include "StdAfx.h"
#include "N163.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//		bool		_sub	���̃I�u�W�F�N�g�́A�T�u���[�`���H
//	���Ԓl
//					����
//==============================================================
N163::N163(MMLfile* MML, unsigned int _id, const wchar_t _strName[]):
	MusicItem(_strName),
	m_id(_id)
{
	//----------------------
	//Local�ϐ�


//	�萔��`
enum	Command_ID_mml {
	N163_Num,
	N163_Commma
};

//	�����́AMML�\���Ŏg����R�}���h�B
const	static	Command_Info	Command[] = {
		{	"%",	N163_Num	},
		{	"$",	N163_Num	},
		{	"0",	N163_Num	},
		{	"1",	N163_Num	},
		{	"2",	N163_Num	},
		{	"3",	N163_Num	},
		{	"4",	N163_Num	},
		{	"5",	N163_Num	},
		{	"6",	N163_Num	},
		{	"7",	N163_Num	},
		{	"8",	N163_Num	},
		{	"9",	N163_Num	},
		{	",",	N163_Commma	}
};

				int		i;
	unsigned	char	cData;
	unsigned	int		ptN163		= 0;
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

			case(N163_Num):
				MML->Back();
				i = MML->GetInt();
				if( (i<0) || (i>15)){
					MML->Err(L"n163�̔g�`��`�́A0�`15�͈̔͂Ŏw�肵�ĉ������B");
				}
				WAVE.append((char)1, (char)i & 0x0F);
				ptN163++;
				break;

			case(N163_Commma):
				break;

			//unknown command
			default:
				MML->Err(L"unknown command");
				break;
		}
	}
	if(ptN163 > 128){
		MML->Err(L"�T���v������128���z���Ă��܂��B");
	}
	if((ptN163 & 0x03) != 0){
		MML->Err(L"�T���v�����́A�S�̔{���Ƃ��ĉ������B");
	}
	ptN163 >>= 1;
	code.append((char)1, ptN163);
	i = 0;
	while(ptN163>0){
		code.append((char)1, WAVE[i*2+0] | (WAVE[i*2+1]<<4) );
		i++;
		ptN163--;
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
N163::~N163(void)
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
void	N163::getAsm(MusicFile* MUS)
{
	*MUS << MUS->Header.Label.c_str() << "N163" << m_id << ":" << endl;
	MusicItem::getAsm(MUS);
}
