#include "StdAfx.h"
#include "MusicHeader.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MusicFile*	SND
//		int			iOffset
//	���Ԓl
//				����
//==============================================================
MusicHeader::MusicHeader(MMLfile* MML):
	iBGM(1),
	iSE(0),
	title(""),
	copyright(""),
	composer(""),
	romcode("nsd.bin"),
	segment("RODATA")
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
MusicHeader::~MusicHeader(void)
{
}

void	MusicHeader::Set_Title(MMLfile* MML)
{
	title = MML->GetString();
}

void	MusicHeader::Set_Copyright(MMLfile* MML)
{
	copyright = MML->GetString();
}

void	MusicHeader::Set_Composer(MMLfile* MML)
{
	composer = MML->GetString();
}

void	MusicHeader::Set_Segment(MMLfile* MML)
{
	segment = MML->GetString();
}

void	MusicHeader::Set_RomCode(MMLfile* MML)
{
	romcode = MML->GetString();
}

void	MusicHeader::Set_Number_BGM(MMLfile* MML)
{
	int	_n = MML->GetInt();

	if((_n > 255) || (_n < 0)){
		MML->Err("#BGM��0�`255�ȉ��̒l�Ŏw�肵�Ă��������B");
	}
	iBGM = _n;
}

void	MusicHeader::Set_Number_SE(MMLfile* MML)
{
	int	_n = MML->GetInt();

	if((_n > 255) || (_n < 0)){
		MML->Err("#SE��0�`255�ȉ��̒l�Ŏw�肵�Ă��������B");
	}
	iSE = _n;
}
