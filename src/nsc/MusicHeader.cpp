#include "StdAfx.h"
#include "MusicHeader.h"

//==============================================================
//		コンストラクタ
//--------------------------------------------------------------
//	●引数
//		MusicFile*	SND
//		int			iOffset
//	●返値
//				無し
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
//		デストラクタ
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
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
		MML->Err("$C000 〜 $10000（�儕CM未使用）の範囲で指定して下さい。");
	}
	if((offsetPCM & 0x003F) != 0){
		MML->Warning("�儕CMは64（$40）Byteでアライメントします。");
		offsetPCM &= 0xFFC0;
		offsetPCM += 0x0040;
	}
}

void	MusicHeader::Set_RomCode(MMLfile* MML)
{
	if(op_code == true){
		MML->Warning("オプションスイッチでリンクするコードが指定されているので、#codeは無視します。");
		MML->GetString();
	} else {
		romcode = MML->GetString();
	}
}

void	MusicHeader::Set_Number_BGM(MMLfile* MML)
{
	int	_n = MML->GetInt();

	if((_n > 255) || (_n < 0)){
		MML->Err("#BGMは0〜255以下の値で指定してください。");
	}
	iBGM = _n;
}

void	MusicHeader::Set_Number_SE(MMLfile* MML)
{
	int	_n = MML->GetInt();

	if((_n > 255) || (_n < 0)){
		MML->Err("#SEは0〜255以下の値で指定してください。");
	}
	iSE = _n;
}
