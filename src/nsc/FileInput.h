#pragma once

class FileInput :
	public ifstream
{
protected:
//�����o�[�ϐ�
				string		strFilename;
	unsigned	int			iLine;		//���݂̃��C��
	unsigned	char		readData;

//�����o�[�֐�
public:
					FileInput(void);
					~FileInput(void);
			void	fileopen(const char*	_strFileName);
			void	StreamPointerAdd(__int32 iSize);
			void	StreamPointerMove(__int32 iSize);
			void	Back(void);
			string*	GetFilename(void){return(&strFilename);};
unsigned	int		GetLine(void){return(iLine);};
unsigned	char	cRead();
};
