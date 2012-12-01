#include "StdAfx.h"
#include "mml_note.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		unsigned	int		code
//		unsigned	int		length
//		unsigned	int		gatetime
//					bool	slur
//		const		char	_strName[]	�N���X�̖��O
//	���Ԓl
//				����
//==============================================================
mml_note::mml_note(int _code, int length, int gatetime, bool slur, const wchar_t _strName[]):
	MusicEvent(_strName)
{
	unsigned	char	opcode = nsd_Note | _code;
	unsigned	int		i = 0;

	if((_code<0) || (_code>15) || (_code==12)){
		wcout << L"mml_note::mml_note()�֐��ŁA�G���[���������܂����B" << endl;
		exit(-1);
	}

	iSize = 1;

	if(slur == true){
		opcode |= nsd_Note_Slur;
	}

	if(length != -1){
		opcode |= nsd_Note_Length;
		iSize++;
	}

	if(gatetime != -1){
		opcode |= nsd_Note_Gate;
		iSize++;
	}

	code.resize(iSize);
	code[i] = opcode;
	i++;

	if(length != -1){
		code[i] = length;
		i++;
	}
	if(gatetime != -1){
		code[i] = gatetime;
		i++;
	}

}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
mml_note::~mml_note(void)
{
}

//==============================================================
//		�^�C
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	mml_note::SetTai(void)
{
	code[0] |= nsd_Note_Slur;
}
