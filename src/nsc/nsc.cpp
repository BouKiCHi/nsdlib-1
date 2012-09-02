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
int	__cdecl	_tmain(int argc, _TCHAR* argv[])
{

	//==================================
	//�N���X�̍쐬
	cOptionSW	= new OPSW(argc,argv);							//�I�v�V��������
	if(cOptionSW->cDebug & 0x01){
		cout << "\n============ [ 1st phase : Create Object ] ============\n" << endl;
	}
	MMLfile*	cMML		= new MMLfile(cOptionSW->strMMLname.c_str());
	MusicFile*	cSND		= new MusicFile(cMML);

	//==================================
	//�A�h���X�̉���
	if(cOptionSW->cDebug & 0x02){
		cout << "\n============ [ 2nd phase : Address Setting ] ============\n" << endl;
	}
	cSND->SetOffset(0);
	cSND->Fix_Address();

	//==================================
	//�o�C�i���̍쐬
	cSND->make_binary();

	//==================================
	//�ۑ�
	if(cOptionSW->saveASM == true){
		cSND->saveASM(cOptionSW->strASMname.c_str());
	}
	if(cOptionSW->saveBIN == true){
		cSND->saveBIN(cOptionSW->strBINname.c_str());
	}
	if(cOptionSW->saveC == true){
		cSND->saveC(cOptionSW->strCname.c_str());
	}
	if(cOptionSW->saveNSF == true){
		cSND->saveNSF(cOptionSW->strNSFname.c_str());
	}


	//==================================
	//�N���X�̍폜
	delete	cSND;
	delete	cMML;
	delete	cOptionSW;

	return(0);
}
