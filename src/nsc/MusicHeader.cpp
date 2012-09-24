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
MusicHeader::MusicHeader(MMLfile* MML, string _code):
	iBGM(1),
	iSE(0),
	op_code(false),
	offsetPCM(0x10000),
	Label("_nsd_"),
	title(""),
	copyright(""),
	composer(""),
	segmentSEQ("RODATA"),
	segmentPCM("PCMDATA")
{
	if(_code.empty()){
		op_code = false;
		romcode = "nsd.bin";
	} else {
		op_code = true;
		romcode = _code;
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

void	MusicHeader::Set_SegmentSEQ(MMLfile* MML)
{
	segmentSEQ = MML->GetString();
}

void	MusicHeader::Set_SegmentPCM(MMLfile* MML)
{
	segmentPCM = MML->GetString();
}
void	MusicHeader::Set_Label(MMLfile* MML)
{
	Label = MML->GetString();
}

void	MusicHeader::Set_OffsetPCM(MMLfile* MML)
{
	offsetPCM = MML->GetInt();

	if((offsetPCM < 0xC000) || (offsetPCM > 0x10000)){
		MML->Err("$C000 �` $10000�i��PCM���g�p�j�͈̔͂Ŏw�肵�ĉ������B");
	}
	if((offsetPCM & 0x003F) != 0){
		MML->Warning("��PCM��64�i$40�jByte�ŃA���C�����g���܂��B");
		offsetPCM &= 0xFFC0;
		offsetPCM += 0x0040;
	}
}

void	MusicHeader::Set_RomCode(MMLfile* MML)
{
	if(op_code == true){
		MML->Warning("�I�v�V�����X�C�b�`�Ń����N����R�[�h���w�肳��Ă���̂ŁA#code�͖������܂��B");
		MML->GetString();
	} else {
		romcode = MML->GetString();
	}
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
