// nsc.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

/****************************************************************/
/*					�O���[�o��									*/
/****************************************************************/
		OPSW*			cOptionSW;	//�ǂ�����ł��A�N�Z�X����B

//==============================================================
//		���C���֐�
//--------------------------------------------------------------
//	������
//		int		argc	�R�}���h���C������	
//		_TCHAR*	argv[]	�R�}���h���C������
//	���Ԓl
//		int			�G���[�R�[�h
//==============================================================
int	main(int argc, char* argv[])
{
	unsigned	int	i;

#ifdef	_WIN32
	locale::global(std::locale("japanese"));
#else
	setlocale(LC_ALL, "ja_JP.UTF-8");
#endif

	//==================================
	//�N���X�̍쐬
	cOptionSW	= new OPSW(argc,argv);							//�I�v�V��������
	if(cOptionSW->cDebug & 0x01){
		wcout << L"\n============ [ 1st phase : Create Object ] ============\n" << endl;
	}
	MMLfile*	cMML		= new MMLfile(cOptionSW->strMMLname.c_str());
	MusicFile*	cSND		= new MusicFile(cMML, cOptionSW->strCodeName);

	//==================================
	//�A�h���X�̉���
	if(cOptionSW->cDebug & 0x02){
		wcout << L"\n============ [ 2nd phase : Address Setting ] ============\n" << endl;
	}
	i = cSND->SetOffset(0);
	wcout << L"Music Size = " << i << endl;
	i = cSND->SetDPCMOffset(i);
	wcout << L"DPCM Size = " << i << endl;

	cSND->Fix_Address();

	//==================================
	//�ۑ�
	if(cOptionSW->saveNSF == true){
		cSND->saveNSF(cOptionSW->strNSFname.c_str(), cOptionSW->opt);
	}

	if(cOptionSW->saveASM == true){
		cSND->saveASM(cOptionSW->strASMname.c_str());
	}

	//==================================
	//�N���X�̍폜
	delete	cSND;
	delete	cMML;
	delete	cOptionSW;

	return(0);
}
