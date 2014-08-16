#include "StdAfx.h"
#include "FileInput.h"

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
FileInput::FileInput(void):
	readData(0),
	iLine(1)
{
}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
FileInput::~FileInput(void)
{
}

//--------------------------------
//�t�@�C�����J���@�G���[�����t��
//--------------------------------
void	FileInput::fileopen(const char*	_strFileName){

	open(_strFileName,ios_base::in | ios_base::binary);
	if(good()==false){
		perror(_strFileName);
		nsc_exit(EXIT_FAILURE);
	};
	strFilename = _strFileName;
};

//--------------------------------
//���΃V�[�N
//--------------------------------
void	FileInput::StreamPointerAdd(long iSize){
	seekg((long)iSize,ios::cur);
};

//--------------------------------
//��΃V�[�N
//--------------------------------
void	FileInput::StreamPointerMove(long iSize){
		seekg((long)iSize,ios::beg);
};

void	FileInput::Back(void)
{
	StreamPointerAdd(-1);
	if(readData == 0x0A){
		iLine--;
	}

	//�X�V
	read((char*)&readData, sizeof(unsigned char));
	StreamPointerAdd(-1);
}
//--------------------------------
//1Byte�ǂݍ���
//--------------------------------
unsigned	char	FileInput::cRead()
{
	read((char*)&readData, sizeof(unsigned char));
	if(readData == 0x0A){
		iLine++;
	}

	return(readData);
};
//--------------------------------
//�T�C�Y
//--------------------------------
unsigned	int	FileInput::GetSize(){

	unsigned	int	iData;
	unsigned	int	iDataT = tellg();

	seekg(0		,ios::end);
	iData = tellg();
	seekg(iDataT,ios::beg);

	return(iData);
};
