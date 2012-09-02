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
	const		char*	strName;		//�I�u�W�F�N�g�̖���
	vector<MusicItem*>	ptcItem;		//�\����
				string	code;
	unsigned	int		iSize;
	unsigned	int		iOffset;		//SND�t�@�C���|�C���^
	

//�����o�[�֐�
public:
	MusicItem(const char _strName[]="");
	~MusicItem(void);

	unsigned	int		getSize();
	unsigned	int		getOffset();
	unsigned	int		SetOffset(unsigned	int	_offset);

	virtual		void	getCode(string* _str);
};
