#pragma once

/****************************************************************/
/*																*/
/*			�萔��`											*/
/*																*/
/****************************************************************/
#define	MML_timebase	24

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class MMLfile	// :
//	public FileInput
{
//�����o�[�ϐ�
private:
	vector	<	FileInput*	>		ptcFiles;			//MML�t�@�C��
				FileInput*			nowFile;			//���݂̃t�@�C��
	unsigned	int					iFiles;				//���݂̃t�@�C��No.
public:
				bool				octave_reverse;		//Octave Reverse

//�����o�[�֐�
public:
	MMLfile(const char*	strFileName);
	~MMLfile(void);

				void	include();				//���|�C���^�ɂ���t�@�C����#include����
	
				bool	eof(void);				//���݂̃t�@�C����EOF�`�F�b�N
				bool	eom(void);				//�l�l�k�̏I���`�F�b�N

				int		tellg(void);						//���݂̃t�@�C���̃|�C���^�擾
				void	StreamPointerAdd(__int32 iSize);	//���݂̃t�@�C���̃|�C���^�ړ�
				void	StreamPointerMove(__int32 iSize);	//���݂̃t�@�C���̃|�C���^�ړ�
				void	Back(void);

				char	cRead(void);		//1Byte�ǂݍ���
				char	GetChar(void);		//1Byte�ǂݍ��݁iwith EOF & Commend check�j
				string	GetString(void);	//""�t ������ �ǂݍ���
				int		GetNum(void);		//()�t  ���l  �ǂݍ���
				int		GetInt(void);		//���l�ǂݍ���
				int		GetLength(void);	//�����ǂݍ��݁i���Z�t���j
				int		readLength(void);	//�����ǂݍ���

				int		GetCommandID(const Command_Info _command[], unsigned int _size);	//�R�}���hID���擾

	void		Err(const char* msg);
	void		Warning(const char* msg);
};
