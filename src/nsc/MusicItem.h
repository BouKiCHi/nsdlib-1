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
	const		wchar_t*	strName;		//�I�u�W�F�N�g�̖���
	vector<MusicItem*>		ptcItem;		//�\����
				string		code;
				size_t		iSize;
	unsigned	int			iOffset;		//SND�t�@�C���|�C���^
	

//�����o�[�֐�
public:
	MusicItem(const wchar_t _strName[]=L"");
	~MusicItem(void);

				size_t	getSize();
	unsigned	int		getOffset();
	unsigned	int		SetOffset(unsigned	int	_offset);

	unsigned	char	getCode(int n);
	virtual		void	getCode(string* _str);
	virtual		void	getAsm(MusicFile* MUS);
};
