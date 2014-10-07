// nsc.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

/****************************************************************/
/*					�O���[�o��									*/
/****************************************************************/
		OPSW*			cOptionSW = NULL;	//�ǂ�����ł��A�N�Z�X����B

//==============================================================
//		�G���[
//--------------------------------------------------------------
//	������
//		int			�G���[�R�[�h
//	���Ԓl
//					����
//==============================================================
void nsc_exit(int no)
{
	throw no;
}
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
				int	iResult	= EXIT_SUCCESS;
	MMLfile			*cMML	= NULL;
    MusicFile		*cSND	= NULL;

#ifdef	_WIN32
	locale::global(std::locale("japanese"));
#else
	setlocale(LC_ALL, "ja_JP.UTF-8");
#endif

	try {
		//==================================
		wcout	<<	L"MML Compiler for NES Sound Driver & Library (NSD.Lib)\n"
					L"    Version 1.22\n"
					L"        Copyright (c) 2012-2014 S.W.\n"	<<	endl;



		//==================================
		//�N���X�̍쐬
		cOptionSW	= new OPSW(argc,argv);							//�I�v�V��������
		if(cOptionSW->cDebug & 0x01){
			wcout << L"\n============ [ 1st phase : Object Creating ] ============" << endl;
		}
		wcout << L"----------------------------------------" << endl;
		wcout << L"*Object creating process" << endl;

		cMML = new MMLfile(cOptionSW->strMMLname.c_str());
		cSND = new MusicFile(cMML, cOptionSW->strCodeName);



		//==================================
		//�A�h���X�̉���
		if(cOptionSW->cDebug & 0x02){
			wcout << L"\n============ [ 2nd phase : Address Setting ] ============" << endl;
		}
		wcout << L"----------------------------------------" << endl;
		wcout << L"*Address settlement process" << endl;


		//�l�l�k����Ă΂��I�u�W�F�N�g�̌��� �� �Ă΂�Ȃ��I�u�W�F�N�g�̍폜
		cSND->Optimize();

		//�A�h���X�̌v�Z
		i = cSND->SetOffset(0);
		cout << "  Music Size = " << setfill(' ')  << setw(5) << i << " [Byte]" << endl;
		i = cSND->SetDPCMOffset(i);
		cout << "  DPCM Size  = " << setfill(' ')  << setw(5) << i << " [Byte]" << endl;

		//�A�h���X�������ɂ��I�y�R�[�h�̃A�h���X����
		cSND->Fix_Address();

		//==================================
		//�ۑ�
		if(cOptionSW->cDebug & 0x04){
			wcout << L"\n============ [ 3rd phase : Music File Outputing ] ============" << endl;
		}

			if((cOptionSW->saveNSF == true) || ((cOptionSW->saveNSF == false)&&(cOptionSW->saveASM == false))){
			cSND->saveNSF(cOptionSW->strNSFname.c_str());
		}

		if(cOptionSW->saveASM == true){
			cSND->saveASM(cOptionSW->strASMname.c_str());
		}



		//==================================
		//Tick Count
		if(cOptionSW->flag_TickCount == true){

			if(cOptionSW->cDebug & 0x04){
				wcout << L"\n============ [ 4th phase : Tick Counting ] ============" << endl;
			}
			wcout << L"----------------------------------------" << endl;
			wcout << L"*Tick counting process" << endl;

			cSND->TickCount();

		} else {
			wcout	<<	L"tick�̃J�E���g�͖���������܂����B"	<<	endl;
		}

	} catch (int no) {
		if (no != EXIT_SUCCESS){
            wcout	<<	L"Error!:" << no << endl;
			iResult	= EXIT_FAILURE;
		}
	}

	//==================================
	//�N���X�̍폜
	if (cSND)
		delete	cSND;
	if (cMML)
		delete	cMML;
	if (cOptionSW)
		delete	cOptionSW;

	return(iResult);
}
