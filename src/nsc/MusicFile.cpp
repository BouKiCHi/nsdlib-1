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
MusicFile::MusicFile(MMLfile* MML, const char _strName[]):
	MusicItem(_strName),
	Header(MML)
{
	//----------------------
	//Local�ϐ�


//	�萔��`
enum	Command_ID_MusicFile {
	//NSF Header
	id_include,
	id_Title,
	id_Composer,
	id_Copyright,
	id_bgm_num,
	id_se_num,

	id_Segment,
	id_Code,

	id_OctaveReverse,

	//Block
	id_Envelop,
	id_Macro,
	id_Sub,
	id_BGM,
	id_SE
};

//	�����́AMML�\���Ŏg����R�}���h�B
const	static	Command_Info	Command[] = {
		{	"#Include",			id_include		},
		{	"#include",			id_include		},
		{	"#Title",			id_Title		},
		{	"#title",			id_Title		},
		{	"#Composer",		id_Composer		},
		{	"#composer",		id_Composer		},
		{	"#Copyright",		id_Copyright	},
		{	"#copyright",		id_Copyright	},
		{	"#Segment",			id_Segment		},
		{	"#segment",			id_Segment		},
		{	"#Code",			id_Code			},
		{	"#code",			id_Code			},
		{	"#OctaveReverse",	id_OctaveReverse},
		{	"#octaveReverse",	id_OctaveReverse},
		{	"#BGM",				id_bgm_num		},
		{	"#bgm",				id_bgm_num		},
		{	"#SE",				id_se_num		},
		{	"#se",				id_se_num		},
		{	"Envelop",			id_Envelop		},
		{	"envelop",			id_Envelop		},
		{	"$",				id_Macro		},
		{	"Sub",				id_Sub			},
		{	"sub",				id_Sub			},
		{	"BGM",				id_BGM			},
		{	"bgm",				id_BGM			},
		{	"SE",				id_SE			},
		{	"se",				id_SE			},
	};

	unsigned	int		i;
	unsigned	char	cData;
				BGM*	_bgm;
				SE*		_se;
				Sub*	_sub;
	string		msg;

//	map<	int,	Envelop*	>::iterator	itEnvelop;
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
			case(id_include):
				MML->include();
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
			case(id_Segment):
				Header.Set_Segment(MML);
				break;
			case(id_Code):
				Header.Set_RomCode(MML);
				break;
			case(id_OctaveReverse):
				MML->octave_reverse = true;		//����́AMML�t�@�C���̑����B
				break;
			case(id_bgm_num):
				Header.Set_Number_BGM(MML);
				break;
			case(id_se_num):
				Header.Set_Number_SE(MML);
				break;
//			case(id_Envelop):
//				break;
			case(id_Sub):
				i = MML->GetNum();
				//�d���`�F�b�N
				if(ptcSub.count(i) != 0){
					MML->Err("Sub()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				//�͈̓`�F�b�N
				_sub = new Sub(MML);
				ptcItem.push_back(_sub);
				ptcSub[i] = _sub;
				iSize += _sub->getSize();	//BGM�̃T�C�Y���X�V
				break;
			case(id_BGM):
				i = MML->GetNum();
				//�d���`�F�b�N
				if(ptcBGM.count(i) != 0){
					MML->Err("BGM()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				//�͈̓`�F�b�N
				if((Header.iBGM <= i) || (i<0)){
					MML->Err("BGM()�u���b�N�Ŏw��ł���͈͂𒴂��Ă��܂��B\n#BGM�̐��l���m�F���Ă��������B");
				}
				_bgm = new BGM(MML);
				ptcItem.push_back(_bgm);
				ptcBGM[i] = _bgm;
				iSize += _bgm->getSize();	//BGM�̃T�C�Y���X�V
				break;
			case(id_SE):
				i = MML->GetNum();
				//�d���`�F�b�N
				if(ptcSE.count(i) != 0){
					MML->Err("SE()�u���b�N�œ����ԍ����w�肳��܂����B");
				}
				//�͈̓`�F�b�N
				if((Header.iSE <= i) || (i<0)){
					MML->Err("SE()�u���b�N�Ŏw��ł���͈͂𒴂��Ă��܂��B\n#SE�̐��l���m�F���Ă��������B");
				}
				_se = new SE(MML);
				ptcItem.push_back(_se);
				ptcSE[i] = _se;
				iSize += _se->getSize();	//BGM�̃T�C�Y���X�V
				break;
			default:
				MML->Err("unknown command");
				break;
		}
		
	} while( !MML->eom() );

	//Check
	if( Header.iBGM + Header.iSE > 255){
		Err("BGM��SE�̐����A���v��255���z���܂����B");
	}

	i = 0;
	while(i < Header.iBGM){
		if(ptcBGM.count(i) == 0){
			Err("BGM�f�[�^������܂���B");
		};
		i++;
	}

	i = 0;
	while(i < Header.iSE){
		if(ptcSE.count(i) == 0){
			Err("SE �f�[�^������܂���B");
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
//		�A�h���X�������肷��B
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::Fix_Address(void)
{
	unsigned	int			iBGM	= 0;
	unsigned	int			iSE		= 0;

	while(iBGM < Header.iBGM){
		ptcBGM[iBGM]->Fix_Address(&ptcSub);
		iBGM++;
	}
	while(iSE < Header.iSE){
		ptcSE[iSE]->Fix_Address(&ptcSub);
		iSE++;
	}

}

//==============================================================
//		
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::init_romimg(void)
{
	memset(romimg, 0, sizeof(romimg));

}

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
	string	_str;
	unsigned	int			i		= 2;
	unsigned	int			iBGM	= 0;
	unsigned	int			iSE		= 0;
	unsigned	__int16*	pt;

	unsigned	int		_size	= 4 + (Header.iBGM + Header.iSE)*2;

	_str.clear();
	_str.resize(_size);

	pt = (unsigned __int16*)_str.c_str();

	_str[0] = Header.iBGM;
	_str[1] = Header.iSE;
	pt[1]	=	0;			//��PCM info �̃A�h���X

	while(iBGM < Header.iBGM){
		pt[i] = 0x8000 + _size + ptcBGM[iBGM]->getOffset();
		i++;
		iBGM++;
	}
	while(iSE < Header.iSE){
		pt[i] = 0x8000 + _size + ptcSE[iSE]->getOffset();
		i++;
		iSE++;
	}

	getCode(&_str);
	code = _str;
}
		
//==============================================================
//		�m�r�e�̍쐬
//--------------------------------------------------------------
//	������
//		const char*	strFileName	�R�[�h
//	���Ԓl
//				����
//==============================================================
void	MusicFile::make_nsf(const char*	strFileName)
{
	FileInput*	_romcode	= new FileInput();
	_romcode->fileopen(strFileName);

	unsigned	__int16*	_nsd_init	=	((unsigned	__int16*)romimg) + 0x7FF0/sizeof(unsigned	__int16);
	unsigned	__int16*	_nsd_main	=	((unsigned	__int16*)romimg) + 0x7FF2/sizeof(unsigned	__int16);

	//ROM�C���[�W�Ƀo�C�i���[��]��
	init_romimg();
	memcpy((char *)romimg, code.c_str(), code.size());

	_romcode->read((char*)(romimg + 0x6000), 0x2000);
	_romcode->close();	

	//NSF�w�b�_�[�̍쐬
	nsf.Name[0]			= 'N';
	nsf.Name[1]			= 'E';
	nsf.Name[2]			= 'S';
	nsf.Name[3]			= 'M';
	nsf.Name[4]			= 0x1A;
	nsf.Version			= 1;
	nsf.MusicNumber		= Header.iBGM + Header.iSE;
	nsf.StartMusicNumber= 1;
	nsf.LoadAddress		= 0x8000;
	nsf.InitAddress		= *_nsd_init;
	nsf.MainAddress		= *_nsd_main;
	nsf.Frequency_NTSC	= 0x411A;
	nsf.Frequency_PAL	= 0x4E20;
	nsf.Video			= 0;
	nsf.External		= 0;
	nsf.Bank[0]			= 0;
	nsf.Bank[1]			= 0;
	nsf.Bank[2]			= 0;
	nsf.Bank[3]			= 0;
	nsf.Bank[4]			= 0;
	nsf.Bank[5]			= 0;
	nsf.Bank[6]			= 0;
	nsf.Bank[7]			= 0;
	nsf.Null1			= 0;
	nsf.Null2			= 0;
	nsf.Null3			= 0;
	nsf.Null4			= 0;

	memcpy(&nsf.Title, Header.title.c_str(), 32);
	memcpy(&nsf.Composer, Header.composer.c_str(), 32);
	memcpy(&nsf.Copyright, Header.copyright.c_str(), 32);

	delete	_romcode;
}

//==============================================================
//		�o�C�i���t�@�C���ւ̕ۑ�
//--------------------------------------------------------------
//	������
//		const char*	strFileName		�t�@�C����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::saveBIN(const char*	strFileName)
{
	//----------------------
	//File open
	fileopen(strFileName);

	write(code.c_str(), code.size());
	//----------------------
	//Close file
	close();
}

//==============================================================
//		�m�r�e�`���ւ̕ۑ�
//--------------------------------------------------------------
//	������
//		const char*	strFileName		�t�@�C����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::saveNSF(const char*	strFileName)
{
	//----------------------
	//File open
	fileopen(strFileName);

	make_nsf(Header.romcode.c_str());
	write((char*)&nsf, sizeof(nsf));
	write(romimg, sizeof(romimg));

	//----------------------
	//Close file
	close();
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
	//----------------------
	//File open
	fileopen(strFileName);

	//----------------------
	//Close file
	close();
}

//==============================================================
//		�b����\�[�X�ւ̕ۑ�
//--------------------------------------------------------------
//	������
//		const char*	strFileName		�t�@�C����
//	���Ԓl
//				����
//==============================================================
void	MusicFile::saveC(const char*	strFileName)
{
	//----------------------
	//File open
	fileopen(strFileName);

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
void	MusicFile::Err(const char* msg)
{
	cout << "[ ERROR ] : " << msg << endl;

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
void	MusicFile::Warning(const char* msg)
{
	//���݂̃t�@�C�����ƁA�s����\��
	cout << "[WARNING] : " << msg << endl;
}
