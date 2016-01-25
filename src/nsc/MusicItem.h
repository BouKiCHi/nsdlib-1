/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

#pragma once

/****************************************************************/
/*			�v���g�^�C�v										*/
/****************************************************************/
class	MusicFile;


/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class MusicItem
{
//�����o�[�ϐ�
protected:
	const		_CHAR*		strName;		//�I�u�W�F�N�g�̖���
	list<MusicItem*>		ptcItem;		//�\����
				string		code;
				size_t		iSize;
	unsigned	int			iOffset;		//SND�t�@�C���|�C���^
	

//�����o�[�֐�
public:
	MusicItem(const _CHAR _strName[]=_T(""));
	MusicItem(int _id, const _CHAR _strName[]=_T(""));
	~MusicItem(void);

				void	clear(void);
				void	clear(int _id);
				size_t	getSize();
	unsigned	int		getOffset();
	unsigned	int		SetOffset(unsigned	int	_offset);

	unsigned	char	getCode(unsigned int n);
	virtual		void	getCode(string* _str);
	virtual		void	setCode(string* _str);
	virtual		void	getAsm(MusicFile* MUS);
};
