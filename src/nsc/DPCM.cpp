#include "StdAfx.h"
#include ".\DPCM.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MMLfile*	MML		MML�t�@�C���̃I�u�W�F�N�g
//		bool		_sub	���̃I�u�W�F�N�g�́A�T�u���[�`���H
//	���Ԓl
//					����
//==============================================================
DPCM::DPCM(FileInput* DPCMfile, unsigned int _id, const char _strName[]):
	MusicItem(_strName),
	m_id(_id)
{
	//----------------------
	//Local�ϐ�
	unsigned	int		_size		= DPCMfile->GetSize();
	unsigned	int		i = 0;
	unsigned	char	cData;

	if((_size & 0x000F) != 0x01){
		iSize = (_size & 0x0FF0) + 0x0011;
	} else {
		iSize = _size;
	}
	_DPCM_size = (char)(iSize >> 4);

	code.resize(iSize);

	//��PCM���̂�]��
	while(i < _size){
		cData = DPCMfile->cRead();
		code[i] = cData;
		i++;
	}
	//Padding
	while(i < iSize){
		code[i] = (unsigned char)0xAA;
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
DPCM::~DPCM(void)
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
void	DPCM::getAsm(MusicFile* MUS)
{
	*MUS << ".align	$40\n" << MUS->Header.Label.c_str() << "DPCM" << m_id << ":" << endl;
	MusicItem::getAsm(MUS);
}