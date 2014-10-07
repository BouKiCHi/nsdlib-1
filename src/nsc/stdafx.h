// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#include <stdlib.h>
#include <errno.h>

#include <string.h>

#ifdef	_WIN32
	#include <locale>
#else
	#include <locale.h>
#endif

#ifdef _WIN32
	#define _PATH_SPLIT	';'	// MS�n�� ;
#else
	#define _PATH_SPLIT	':'	// UNIX�n�� :
#endif



#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>

#include <iomanip>

//#include <tchar.h>


/****************************************************************/
/*			�v���g�^�C�v										*/
/****************************************************************/

void nsc_exit(int no);

using namespace std;

class	MusicFile;
class	MMLfile;
class	Sub;

typedef struct {
	char*	str;
	int		id;
} Command_Info;

#include "SearchPass.h"			//�����p�X

#include "FileInput.h"			//�t�@�C�����͗p
#include "FileOutput.h"			//�t�@�C���o�͗p

#include "Option.h"				//�I�v�V����

#include "MusicItem.h"

#include "Patch.h"

#include "FDSC.h"
#include "FDSM.h"
#include "VRC7.h"
#include "N163.h"

#include "DPCM.h"
#include "DPCMinfo.h"

#include "Envelop.h"

#include "MusicEvent.h"			//�e�C�x���g
#include "mml_general.h"		//�ėp
#include "mml_repeat.h"			//�ėp
#include "mml_poke.h"			//��������������
#include "mml_note.h"			//�����E�x��
#include "mml_Address.h"

#include "MusicHeader.h"		//�w�b�_�[

#include "MusicTrack.h"			//�g���b�N���
#include "TrackSet.h"
#include "BGM.h"
#include "SE.h"
#include "Sub.h"

#include "MMLfile.h"		//MML�t�@�C��
#include "MusicFile.h"		//SND�t�@�C��

// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B

/*

	��	to do
	�ENSF�w�b�_�[�̕�����@32�����ȉ��̎��̏���

*/