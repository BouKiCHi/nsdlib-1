
#pragma once

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class OPSW {
//�����o�[�ϐ�
public:
	unsigned	char		cDebug;			//�f�o�b�O�p
				bool		saveNSF;
				bool		saveASM;
				bool		opt;
				char		fHelp;			//�w���v���w�肵�����H
				string		strMMLname;		//�w�肵��MML�t�@�C����
				string		strNSFname;		//�w�肵��NSF�t�@�C����
				string		strASMname;		//�w�肵��ASM�t�@�C����
				string		strCodeName;	//ROM Code�̖��O

//�����o�[�֐�
public:
		OPSW();								//�������̂�
		OPSW(int argc, char* argv[]);		//�������e����A�N���X�����������t�@�C���I�[�v��
		~OPSW();							//�t�@�C���N���[�Y
private:
void	opError(const wchar_t *stErrMsg);		//�I�v�V�����G���[
void	print_help();						//help message
};
