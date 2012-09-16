#include "StdAfx.h"
#include ".\mml_general.h"

//==============================================================
//		�R���X�g���N�^�i����0Byte�j
//--------------------------------------------------------------
//	������
//		unsigned	int		code
//		const		char	_strName[]	�N���X�̖��O
//	���Ԓl
//				����
//==============================================================
mml_general::mml_general(unsigned char _code, const char _strName[]):
	MusicEvent(_strName)
{
	iSize = 1;
	code.resize(iSize);
	code[0] = _code;
}

//==============================================================
//		�R���X�g���N�^�i����1Byte�j
//--------------------------------------------------------------
//	������
//		unsigned	int		code
//		MMLfile*			MML
//		const		char	_strName[]	�N���X�̖��O
//	���Ԓl
//				����
//==============================================================
mml_general::mml_general(unsigned char _code, MMLfile* MML, const char _strName[]="General"):
	MusicEvent(_strName)
{
	int		_data = MML->GetInt();

	if( (_data<-128) || (_data>255) ){
		MML->Err("�p�����[�^�̒l���͈͂��z���܂����B");
	}

	iSize = 2;
	code.resize(iSize);
	code[0] = _code;
	code[1] = (_data & 0xFF);
}

//==============================================================
//			�R���X�g���N�^�i����1Byte�j
//--------------------------------------------------------------
//	������
//		unsigned	int		code
//		const		char	_data
//		const		char	_strName[]	�N���X�̖��O
//	���Ԓl
//				����
//==============================================================
mml_general::mml_general(unsigned char _code, const char _data, const char _strName[]/*="General"*/):
	MusicEvent(_strName)
{
	iSize = 2;
	code.resize(iSize);
	code[0] = _code;
	code[1] = _data;
}

//==============================================================
//			�R���X�g���N�^�i����1Byte�j
//--------------------------------------------------------------
//	������
//		unsigned	int		code
//		const		char	_data
//		const		char	_strName[]	�N���X�̖��O
//	���Ԓl
//				����
//==============================================================
mml_general::mml_general(unsigned char _code, const char _n1, const char _n2, const char _n3, const char _n4, const char _strName[]/*="General"*/):
	MusicEvent(_strName)
{
	iSize = 5;
	code.resize(iSize);
	code[0] = _code;
	code[1] = _n1;
	code[2] = _n2;
	code[3] = _n3;
	code[4] = _n4;
}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
mml_general::~mml_general(void)
{
}
