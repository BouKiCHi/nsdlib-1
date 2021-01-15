/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

// �ÓI���f��
#include "StdAfx.h"
#include "Sub.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		MMLfile*	MML			MML�t�@�C���̃I�u�W�F�N�g
//		size_t		_id			�T�u���[�`���ԍ�
//		const _CHAR	_strName[]	�I�u�W�F�N�g��
//	���Ԓl
//					����
//==============================================================
Sub::Sub(MMLfile* MML, size_t _id, const _CHAR _strName[]/* = "==== [ Sub ]===="*/):
	TrackSet(MML, _id, true, false, _strName)
{
#ifdef _OPENMP
	omp_init_lock(&lock_TickCount);
#endif
}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
Sub::~Sub()
{
#ifdef _OPENMP
	omp_destroy_lock(&lock_TickCount);
#endif
}

//==============================================================
//		TickCount	�T�u���[�`���Ăяo��
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
unsigned	int	Sub::TickCount(MusicFile* MUS, NSD_WORK* work)
{
	int	_iResult;

#ifdef _OPENMP
	//���̃g���b�N���Ăяo���Ă��鎞�ɁA���������Ȃ��B
	omp_set_lock(&lock_TickCount);
#endif

	_iResult = ptcTrack[0]->TickCount(MUS, work);

#ifdef _OPENMP
	omp_unset_lock(&lock_TickCount);
#endif

	return(_iResult);
}

//==============================================================
//		�R�[�h�̎擾
//--------------------------------------------------------------
//	������
//		MusicFile* MUS		�R�[�h���o�͂���ȃf�[�^�t�@�C���E�I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	Sub::getAsm(MusicFile* MUS)
{
	*MUS << MUS->Header.Label.c_str() << "SUB" << m_id << ":" << endl;
	TrackSet::getAsm(MUS);
}
