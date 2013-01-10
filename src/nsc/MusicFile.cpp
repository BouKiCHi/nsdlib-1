#include "StdAfx.h"
#include "MusicFile.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MMLfile* MML	�l�l�k�t�@�C���̃I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
MusicFile::MusicFile(MMLfile* MML, string _code, const wchar_t _strName[]):
	MusicItem(_strName),
	cDPCMinfo(NULL),
	Header(MML, _code)
{
	//----------------------
	//Local�ϐ�


//	�萔��`
enum	Command_ID_MusicFile {
	//for NSF output
	id_Title,
	id_Composer,
	id_Copyright,
	id_OffsetPCM,
	id_Code,

	//for ASM output
	id_SegmentSEQ,
	id_SegmentPCM,
	id_Label,

	//General
	id_include,
	id_OctaveReverse,
	id_bgm_num,
	id_se_num,
	id_offset_Ei,
	id_offset_Ev,
	id_offset_En,
	id_offset_Em,

	//Block
	id_DPCM,
	id_FDSC,
	id_FDSM,
	id_VRC7,
	id_N163,
	id_Envelop,
	id_Macro,
	id_Sub,
	id_BGM,
	id_SE
};

//	�����́AMML�\���Ŏg����R�}���h�B
const	static	Command_Info	Command[] = {
		//for NSF output
		{	"#Title",			id_Title		},
		{	"#title",			id_Title		},
		{	"#Composer",		id_Composer		},
		{	"#composer",		id_Composer		},
		{	"#Copyright",		id_Copyright	},
		{	"#copyright",		id_Copyright	},
		{	"#OffsetPCM",		id_OffsetPCM	},	//Offset Address of ��PCM
		{	"#offsetPCM",		id_OffsetPCM	},	//Offset Address of ��PCM
		{	"#Code",			id_Code			},
		{	"#code",			id_Code			},
		//for ASM output
		{	"#Segment",			id_SegmentSEQ	},	//Segment name for Sequence
		{	"#segment",			id_SegmentSEQ	},
		{	"#SegmentSEQ",		id_SegmentSEQ	},	//Segment name for Sequence
		{	"#segmentSEQ",		id_SegmentSEQ	},
		{	"#SegmentPCM",		id_SegmentPCM	},	//Segment name for ��PCM
		{	"#segmentPCM",		id_SegmentPCM	},
		{	"#Label",			id_Label		},
		{	"#label",			id_Label		},
		//General
		{	"#Include",			id_include		},
		{	"#include",			id_include		},
		{	"#OctaveReverse",	id_OctaveReverse},
		{	"#octaveReverse",	id_OctaveReverse},
		{	"#BGM",				id_bgm_num		},
		{	"#bgm",				id_bgm_num		},
		{	"#SE",				id_se_num		},
		{	"#se",				id_se_num		},
		{	"#OffsetE@",		id_offset_Ei	},
		{	"#offsetE@",		id_offset_Ei	},
		{	"#OffsetEv",		id_offset_Ev	},
		{	"#offsetEv",		id_offset_Ev	},
		{	"#OffsetEm",		id_offset_Em	},
		{	"#offsetEm",		id_offset_Em	},
		{	"#OffsetEn",		id_offset_En	},
		{	"#offsetEn",		id_offset_En	},
		//Block
		{	"DPCM",				id_DPCM			},
		{	"FDSC",				id_FDSC			},
		{	"FDSM",				id_FDSM			},
		{	"VRC7",				id_VRC7			},
		{	"N163",				id_N163			},
		{	"Envelope",			id_Envelop		},
		{	"envelope",			id_Envelop		},
		{	"Envelop",			id_Envelop		},
		{	"envelop",			id_Envelop		},
		{	"Sub",				id_Sub			},
		{	"sub",				id_Sub			},
		{	"BGM",				id_BGM			},
		{	"bgm",				id_BGM			},
		{	"SE",				id_SE			},
		{	"se",				id_SE			},

		//for 1 command
		{	"D",				id_DPCM			},
		{	"FC",				id_FDSC			},
		{	"FM",				id_FDSM			},
		{	"O",				id_VRC7			},
		{	"V",				id_VRC7			},
		{	"N",				id_N163			},
		{	"E",				id_Envelop		},
		{	"S",				id_Sub			},
		{	"$",				id_Macro		},

		//for mck/ppmck
		{	"@DPCM",			id_DPCM			},
		{	"@FM",				id_FDSC			},
		{	"@MW",				id_FDSM			},
		{	"@OP",				id_VRC7			},
		{	"@N",				id_N163			},
		{	"@E",				id_Envelop		},
	};

	unsigned	int			i;
	unsigned	char		cData;
				FDSC*		_fdsc;
				FDSM*		_fdsm;
				VRC7*		_vrc7;
				N163*		_n163;
				Envelop*	_env;
				BGM*		_bgm;
				SE*			_se;
				Sub*		_sub;
	string		msg;

	map<	int,	Envelop*	>::iterator	itEnvelop;
	map<	int,	BGM*		>::iterator	itBGM;
	map<	int,	SE*			>::iterator	itSE;
	map<	int,	Sub*		>::iterator	itSub;

	iSize = 0;

	do{
		
		//�P�����ǂݍ��݁i�R�����g�`�F�b�N�Ainclude�t�@�C���̏I�[�`�F�b�N������j
		cData = MML->GetChar();

		//[EOF]�`�F�b�N
		if( MML->eom() ){
			break;
		}

		//�P�߂�
		MML->StreamPointerAdd(-1);

		//�R�}���h������̃`�F�b�N
		switch(MML->GetCommandID(Command, sizeof(Command)/sizeof(Command_Info))){
			//for NSF output
			case(id_Code):
				Header.Set_RomCode(MML);
				break;
			case(id_Title):
				Header.Set_Title(MML);
				break;
			case(id_Composer):
				Header.Set_Composer(MML);
				break;
			case(id_Copyright):
				Header.Set_Copyright(MML);
				break;
			case(id_OffsetPCM):
				Header.Set_OffsetPCM(MML);
				break;
			//for ASM output
			case(id_SegmentSEQ):
				Header.Set_SegmentSEQ(MML);
				break;
			case(id_SegmentPCM):
				Header.Set_SegmentPCM(MML);
				break;
			case(id_Label):
				Header.Set_Label(MML);
				break;
			//General
			case(id_include):
				MML->include();
				break;
			case(id_bgm_num):
				Header.Set_Number_BGM(MML);
				break;
			case(id_se_num):
				Header.Set_Number_SE(MML);
				break;
			case(id_OctaveReverse):
				MML->octave_reverse = true;		//����́AMML�t�@�C���̑����B
				break;
			case(id_offset_Ei):
				MML->offset_Ei = MML->GetInt();
				break;
			case(id_offset_Ev):
				MML->offset_Ev = MML->GetInt();
				break;
			case(id_offset_En):
				MML->offset_En = MML->GetInt();
				break;
			case(id_offset_Em):
				MML->offset_Em = MML->GetInt();
				break;
			//MML
			case(id_DPCM):
				if(cDPCMinfo != NULL){
					MML->Err(L"DPCM�u���b�N�͂P�܂łł��B");
				}
				cDPCMinfo = new DPCMinfo(MML);
				ptcItem.push_back(cDPCMinfo);
				iSize += cDPCMinfo->getSize();	//BGM�̃T�C�Y���X�V
				break;
			case(id_FDSC):
				i = MML->GetNum();

				//�d���`�F�b�N
				if(ptcFDSC.count(i) != 0){
					MML->Err(L"FDSC()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				_fdsc = new FDSC(MML, i);
				ptcItem.push_back(_fdsc);
				ptcFDSC[i] = _fdsc;
				iSize += _fdsc->getSize();	//BGM�̃T�C�Y���X�V
				break;
			case(id_FDSM):
				i = MML->GetNum();

				//�d���`�F�b�N
				if(ptcFDSM.count(i) != 0){
					MML->Err(L"FDSM()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				_fdsm = new FDSM(MML, i);
				ptcItem.push_back(_fdsm);
				ptcFDSM[i] = _fdsm;
				iSize += _fdsm->getSize();	//BGM�̃T�C�Y���X�V
				break;
			case(id_VRC7):
				i = MML->GetNum();

				//�d���`�F�b�N
				if(ptcVRC7.count(i) != 0){
					MML->Err(L"VRC7()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				_vrc7 = new VRC7(MML, i);
				ptcItem.push_back(_vrc7);
				ptcVRC7[i] = _vrc7;
				iSize += _vrc7->getSize();	//BGM�̃T�C�Y���X�V
				break;
			case(id_N163):
				i = MML->GetNum();

				//�d���`�F�b�N
				if(ptcN163.count(i) != 0){
					MML->Err(L"N163()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				_n163 = new N163(MML, i);
				ptcItem.push_back(_n163);
				ptcN163[i] = _n163;
				iSize += _n163->getSize();	//BGM�̃T�C�Y���X�V
				break;
			case(id_Envelop):
				i = MML->GetNum();
				//�d���`�F�b�N
				if(ptcEnv.count(i) != 0){
					MML->Err(L"Envelop()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				_env = new Envelop(MML, i);
				ptcItem.push_back(_env);
				ptcEnv[i] = _env;
				iSize += _env->getSize();	//BGM�̃T�C�Y���X�V
				break;
			case(id_Macro):
				//�������@to do
				break;
			case(id_Sub):
				i = MML->GetNum();
				//�d���`�F�b�N
				if(ptcSub.count(i) != 0){
					MML->Err(L"Sub()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				//�͈̓`�F�b�N
				_sub = new Sub(MML, i);
				ptcItem.push_back(_sub);
				ptcSub[i] = _sub;
				iSize += _sub->getSize();	//BGM�̃T�C�Y���X�V
				break;
			case(id_BGM):
				i = MML->GetNum();
				//�d���`�F�b�N
				if(ptcBGM.count(i) != 0){
					MML->Err(L"BGM()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				//�͈̓`�F�b�N
				if((Header.iBGM <= i) || (i<0)){
					MML->Err(L"BGM()�u���b�N�Ŏw��ł���͈͂𒴂��Ă��܂��B\n#BGM�̐��l���m�F���Ă��������B");
				}
				_bgm = new BGM(MML, i);
				ptcItem.push_back(_bgm);
				ptcBGM[i] = _bgm;
				iSize += _bgm->getSize();	//BGM�̃T�C�Y���X�V
				break;
			case(id_SE):
				i = MML->GetNum();
				//�d���`�F�b�N
				if(ptcSE.count(i) != 0){
					MML->Err(L"SE()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				//�͈̓`�F�b�N
				if((Header.iSE <= i) || (i<0)){
					MML->Err(L"SE()�u���b�N�Ŏw��ł���͈͂𒴂��Ă��܂��B\n#SE�̐��l���m�F���Ă��������B");
				}
				_se = new SE(MML, i);
				ptcItem.push_back(_se);
				ptcSE[i] = _se;
				iSize += _se->getSize();	//BGM�̃T�C�Y���X�V
				break;
			default:
				MML->Err(L"unknown command");
				break;
		}
		
	} while( !MML->eom() );

	//Check
	if( Header.iBGM + Header.iSE > 255){
		Err(L"BGM��SE�̐����A���v��255���z���܂����B");
	}

	i = 0;
	while(i < Header.iBGM){
		if(ptcBGM.count(i) == 0){
			Err(L"BGM�f�[�^������܂���B");
		};
		i++;
	}

	i = 0;
	while(i < Header.iSE){
		if(ptcSE.count(i) == 0){
			Err(L"SE �f�[�^������܂���B");
		};
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
MusicFile::~MusicFile(void)
{
}

//==============================================================
//		��PCM�̃I�t�Z�b�g�A�h���X���v�Z
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//		unsigned	int	��PCM�̍��v�T�C�Y
//==============================================================
unsigned	int		MusicFile::SetDPCMOffset(void)
{
	unsigned	int	i;

	dpcm_code.clear();
	if(cDPCMinfo != NULL){
		cDPCMinfo->getDPCMCode(&dpcm_code);
		i = cDPCMinfo->setDPCMoffset(Header.offsetPCM);
	} else {
		i = Header.offsetPCM;
	}
	return(i - Header.offsetPCM);
}

//==============================================================
//		�A�h���X�������肷��B
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::Fix_Address(void)
{
	map<int,Sub*	>::iterator	itSub;

	unsigned	int			iBGM	= 0;
	unsigned	int			iSE		= 0;

	while(iBGM < Header.iBGM){
		ptcBGM[iBGM]->Fix_Address(this);
		iBGM++;
	}
	while(iSE < Header.iSE){
		ptcSE[iSE]->Fix_Address(this);
		iSE++;
	}

	if(!ptcSub.empty()){
		itSub = ptcSub.begin();
		while(itSub != ptcSub.end()){
			itSub->second->Fix_Address(this);
			itSub++;
		}
	}
}

/*
//==============================================================
//		�ȃo�C�i���C���[�W�̍쐬
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::make_binary(void)
{

}
*/		
//==============================================================
//		�m�r�e�̍쐬
//--------------------------------------------------------------
//	������
//		const char*	strFileName	�R�[�h
//	���Ԓl
//				����
//==============================================================
void	MusicFile::make_bin(size_t rom_size)
{
				string		_str;
	unsigned	int			i		= 2;
	unsigned	int			iBGM	= 0;
	unsigned	int			iSE		= 0;
	unsigned	short*		pt;

				size_t		_size	= 4 + (Header.iBGM + Header.iSE)*2;


	//�ȃo�C�i���[�̍쐬
	_str.clear();
	_str.resize(_size);

	pt = (unsigned short*)_str.c_str();

	_str[0] = Header.iBGM;
	_str[1] = Header.iSE;

	if(cDPCMinfo != NULL){
		pt[1]	= 0x8000 + (unsigned short)rom_size - 0x80 + (unsigned short)_size + cDPCMinfo->getOffset();	//��PCM info �̃A�h���X
	} else {
		pt[1]	= 0;
	}

	while(iBGM < Header.iBGM){
		pt[i] = 0x8000 + (unsigned short)rom_size - 0x80 + (unsigned short)_size + ptcBGM[iBGM]->getOffset();
		i++;
		iBGM++;
	}
	while(iSE < Header.iSE){
		pt[i] = 0x8000 + (unsigned short)rom_size - 0x80 + (unsigned short)_size + ptcSE[iSE]->getOffset();
		i++;
		iSE++;
	}

	getCode(&_str);
	code = _str;

	//��PCM�̍쐬
	dpcm_code.clear();
	if(cDPCMinfo != NULL){
		cDPCMinfo->getDPCMCode(&dpcm_code);
	}

}

//==============================================================
//		�m�r�e�`���ւ̕ۑ�
//--------------------------------------------------------------
//	������
//		const char*	strFileName		�t�@�C����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::saveNSF(const char*	strFileName,bool opt)
{

	unsigned	int		i,j;
				size_t	bin_size;
				size_t	mus_size;
				size_t	pcm_size;
	unsigned	char	mus_bank;
	unsigned	char	pcm_bank;
				char*	romimg		= new char[0x8000+0x80];
	NSF_Header*			nsf			= (NSF_Header*)romimg;
	FileInput*			_romcode	= new FileInput();




	//NSF�p�R�[�h�̓]��
	_romcode->fileopen(Header.romcode.c_str());
	bin_size = _romcode->GetSize();
	_romcode->read(romimg, bin_size);
	_romcode->close();
	delete		_romcode;

	//�V�[�P���X�̃o�C�i���𐶐�
	make_bin(bin_size);

	mus_size = bin_size - 0x80 + code.size();
	if(opt == true){
		mus_bank = (unsigned char)(mus_size >> 12);
		if((mus_size & 0x0FFF) != 0){
			mus_bank++;
		}
	} else {
		mus_bank = (Header.offsetPCM - 0x8000) >> 12; 
	}


	//�T�C�Y�`�F�b�N
	if((0x8000 + mus_size) > Header.offsetPCM){
		wcout << L"�R�[�h�E�V�[�P���X�̃T�C�Y�����e�l���z���܂����B" << endl;
		wcout << L"�@���e�l�F" << Header.offsetPCM - 0x8000 << L"[Byte]" << endl;
		wcout << L"�@�T�C�Y�F" << (unsigned int)mus_size << L"[Byte]" << endl;
		exit(-1);
	}

	//��PCM
	pcm_size = dpcm_code.size();
	pcm_bank = (unsigned char)(pcm_size >> 12);
	if((pcm_size & 0x0FFF) != 0){
		pcm_bank++;
	}
	//��PCM�T�C�Y�`�F�b�N
	if(	(Header.offsetPCM + pcm_size) > 0x10000	){
		wcout << L"��PCM�̃T�C�Y�����e�l���z���܂����B" << endl;
		wcout << L"�@���e�l�F" << 0x10000 - Header.offsetPCM << L"[Byte]" << endl;
		wcout << L"�@�T�C�Y�F" << (unsigned int)pcm_size << L"[Byte]" << endl;
		exit(-1);
	}

	//NSF�w�b�_�[�̍X�V
	nsf->MusicNumber		= Header.iBGM + Header.iSE;
	memcpy(&nsf->Title, Header.title.c_str(), 32);
	memcpy(&nsf->Composer, Header.composer.c_str(), 32);
	memcpy(&nsf->Copyright, Header.copyright.c_str(), 32);

	//----------------------
	//�m�r�e��������
	fileopen(strFileName);

	if(cDPCMinfo == NULL){
		write(romimg, bin_size);			//NSF�w�b�_�[ �� �R�[�h�̏�������
		write(code.c_str(), code.size());	//�V�[�P���X�̏�������
	//	//0 padding
	//	while(mus_size < ((unsigned int)mus_bank<<12)){
	//		put(0);		//0 padding
	//		mus_size++;
	//	}
	} else {
		//�w�b�_�[�Ƀo���N���������B
		if(opt == true){
			i = 0;
			while(i < mus_bank){
				nsf->Bank[i] = i;
				i++;
			}
			while(i < ((Header.offsetPCM - 0x8000)>>12)){
				nsf->Bank[i] = 0;
				i++;
			}
			j = 0;
			while(i < 8){
				if(j < pcm_bank){
					nsf->Bank[i] = mus_bank + j;
				} else {
					nsf->Bank[i] = 0;
				}
				i++;
				j++;
			}
		}
		//�R�[�h���V�[�P���X
		write(romimg, bin_size);			//NSF�w�b�_�[ �� �R�[�h�̏�������
		write(code.c_str(), code.size());	//�V�[�P���X�̏�������
		while(mus_size < ((unsigned int)mus_bank<<12)){
			put(0);		//0 padding
			mus_size++;
		}
		//��PCM
		write(dpcm_code.c_str(), pcm_size);		//��PCM�̏�������
		if(opt == true){
			while(pcm_size < ((unsigned int)pcm_bank<<12)){
				put(0);		//0 padding
				pcm_size++;
			}
		}
	}

	close();

	//----------------------
	//Exit
	delete[]	romimg;
}

//==============================================================
//		�A�Z���u������\�[�X�ւ̕ۑ�
//--------------------------------------------------------------
//	������
//		const char*	strFileName		�t�@�C����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::saveASM(const char*	strFileName)
{
	unsigned	int			iBGM	= 0;
	unsigned	int			iSE		= 0;

	//----------------------
	//File open
	fileopen(strFileName);

	//Header
	*this <<	";===============================================================\n"
				";		Music file for NES Sound Driver & Library\n"
				";			for assembly language (ca65.exe)\n"
				";===============================================================\n"
				<<endl;

	//Export of Sequence
	while(iBGM < Header.iBGM){
		*this	<<	"	.export		"	<<	Header.Label	<<	"BGM"	<<	iBGM	<<	endl;
		iBGM++;
	}
	while(iSE < Header.iSE){
		*this	<<	"	.export		"	<<	Header.Label	<<	"SE"	<<	iSE	<<	endl;
		iSE++;
	}

	if(cDPCMinfo != NULL){
		*this	<<	"	.export		"	<<	Header.Label	<<	"DPCMinfo"	<<	endl;
	}

	//MML
	*this <<	"\n\n.segment	"	<<	'"'	<<	Header.segmentSEQ	<<	'"' << endl;

	getAsm(this);

	//----------------------
	//Close file
	close();
}

//==============================================================
//		�G���[����
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::Err(const wchar_t msg[])
{
	wcout << L"[ ERROR ] : " << msg << endl;

	//�ُ�I��
	exit(-1);
}

//==============================================================
//		���[�j���O����
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::Warning(const wchar_t msg[])
{
	//���݂̃t�@�C�����ƁA�s����\��
	wcout << L"[WARNING] : " << msg << endl;
}
