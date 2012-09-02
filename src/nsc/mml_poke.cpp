#include "StdAfx.h"
#include ".\mml_poke.h"

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
mml_poke::mml_poke(unsigned int _addr , unsigned char _data, const char _strName[]):
	MusicEvent(_strName)
{
	iSize = 4;
	code.resize(iSize);
	code[0] = nsd_Poke;
	code[1] = ((_addr     ) & 0xFF);
	code[2] = ((_addr >> 8) & 0xFF);
	code[3] = _data;
}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
mml_poke::~mml_poke(void)
{
}
