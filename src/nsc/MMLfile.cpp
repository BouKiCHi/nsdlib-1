#include "StdAfx.h"
#include "MMLfile.h"

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		const char*	strFileName		�t�@�C����
//	���Ԓl
//				����
//==============================================================
MMLfile::MMLfile(const char*	strFileName):
	offset_Ei(0),
	offset_Ev(0),
	offset_En(0),
	offset_Em(0),
	octave_reverse(false)
{
	//File open
	nowFile	= new FileInput();

	nowFile->fileopen(strFileName);
	ptcFiles.push_back(nowFile);

	iFiles = 0;
}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
MMLfile::~MMLfile(void)
{

	//----------------------
	//Local�ϐ�
	vector	<FileInput*>::iterator	itFiles;

	//----------------------
	//Delete Class
	itFiles = ptcFiles.begin();
	while(itFiles != ptcFiles.end()){
		(*itFiles)->close();
		delete *itFiles;
		itFiles++;
	}
	ptcFiles.clear();

}

//==============================================================
//		�C���N���[�h�t�@�C��
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			����
//	������
//			���݂̃t�@�C���|�C���^�ɏ����Ă���t�@�C�����C���N���[�h����
//==============================================================
void	MMLfile::include()
{
	//----------------------
	//Local�ϐ�
	vector	<FileInput*>::iterator	itFiles;
	string	_name = GetString();

	//----------------------
	//�����t�@�C�����J����Ă��Ȃ����`�F�b�N
	itFiles = ptcFiles.begin();
	while(itFiles != ptcFiles.end()){
		if( *(*itFiles)->GetFilename() == _name ){
			Err(L"���ɓ����t�@�C����#include�ŊJ����Ă��܂��B");
		}
		itFiles++;
	}

	//----------------------
	//File open
	nowFile	= new FileInput();

	nowFile->fileopen(_name.c_str());
	ptcFiles.push_back(nowFile);

	iFiles++; 
}

//==============================================================
//			���݃R���p�C���������̃t�@�C���|�C���^�̎擾
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			int		���݂̃t�@�C���|�C���^
//==============================================================
int		MMLfile::tellg(void)
{
	return(nowFile->tellg());
}

//==============================================================
//			���݃R���p�C���������̃t�@�C���|�C���^�𑊑ΓI�Ɉړ�
//--------------------------------------------------------------
//	������
//			int		�ړ��l
//	���Ԓl
//			����
//==============================================================
void	MMLfile::StreamPointerAdd(long iSize)
{
	nowFile->StreamPointerAdd(iSize);
}

//==============================================================
//			���݃R���p�C���������̃t�@�C���|�C���^���ΓI�Ɉړ�
//--------------------------------------------------------------
//	������
//			int		�ړ��l
//	���Ԓl
//			����
//==============================================================
void	MMLfile::StreamPointerMove(long iSize)
{
	nowFile->StreamPointerMove(iSize);
}

//==============================================================
//			���݃R���p�C���������̃t�@�C���|�C���^����߂�
//--------------------------------------------------------------
//	������
//			int		�ړ��l
//	���Ԓl
//			����
//==============================================================
void	MMLfile::Back(void)
{
	nowFile->Back();
}

//==============================================================
//			���݃R���p�C���������̃t�@�C����[EOF]�`�F�b�N
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			bool		true	[EOF]�����o
//						false	�܂��I��肶��Ȃ��B
//==============================================================
bool	MMLfile::eof(void)
{
	return( nowFile->eof() );
}

//==============================================================
//			MML�t�@�C���̏I���`�F�b�N
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			bool		true	���t�@�C����[EOF]�����o
//						false	�܂��I��肶��Ȃ��B
//==============================================================
bool	MMLfile::eom(void)
{
	if(( iFiles == 0 ) && ( eof() )){
		return(true);
	}
	return(false);
}

//==============================================================
//			�PByte�ǂݍ���
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			char	�ǂݍ��ݒl
//==============================================================
char	MMLfile::cRead(void)
{
	return(nowFile->cRead());
}

//==============================================================
//			�PByte�ǂݍ��݁i�`�F�b�N�t���j
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			char	�ǂݍ��ݒl
//	������
//		�P�����̓ǂݍ��݁B
//		�A���A�ȉ��̋L�q���������ꍇ�́A�������΂��B
//			�E0x20�ȉ��̃L�����N�^�[�R�[�h
//			�E�R�����g
//		�܂��A�C���N���[�h�t�@�C������[EOF]�����o������A�O�̃t�@�C���ɖ߂�
//==============================================================
char	MMLfile::GetChar(void)		//1Byte�̓ǂݍ���
{
	unsigned	char	cData;

	do{
		cData = cRead();

		//[EOM]�H
		if( eom() )
		{
			return(0);

		//[EOF]�H
		} else if( eof() ){
			nowFile->close();
			delete	nowFile;
			ptcFiles.pop_back();
			nowFile = ptcFiles.back();
			iFiles--;
			//continue

		//0x20�ȉ��̐���R�[�h
		} else if(cData <= 0x20){
			//continue

		//�A�Z���u������^�C�v�̃R�����g�H
		} else if(cData == ';'){
			do{
				cData = cRead();		//���̃o�C�g��ǂݍ���
			} while((cData != 0x0A)||eof());
		
		//�b����^�C�v�̃R�����g�H
		} else 	if(cData == '/'){
			cData = cRead();		//���̃o�C�g��ǂݍ���
			switch(cData){

				//�P�s�R�����g
				case('/'):
					do{
						cData = cRead();		//���̃o�C�g��ǂݍ���
					}while((cData != 0x0A)||eof());
					break;

				//�͈̓R�����g
				case('*'):
					do{
						do{
							cData = cRead();		//���̃o�C�g��ǂݍ���
							if(eof()){
								Err(L"�R�����g�I�[ */ ������܂���B");
							}
						}while(cData != '*');
						cData = cRead();
						Back();					//StreamPointerAdd(-1);
					} while(cData != '/');
							cRead();			//StreamPointerAdd(+1); ���������B
					break;

				//����ȊO
				default:
					Err(L"�R�����g�ł����H");
					break;
			}

		//[EOF]�ł��A�R�����g�ł������ꍇ�B
		} else {
			break;		//while(1) �� break;
		}

	}while(1);

	return(cData);
}

//==============================================================
//			������ǂݍ���
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			string	�ǂݍ��񂾕�����
//	������
//			MML����"��"�ň͂܂ꂽ��������擾����B
//==============================================================
string	MMLfile::GetString(void)
{
	char	cData;
	
	string	_str;
	while(cRead() != '"'){
		if(eof()){
			Err(L"������J�n������\"��������܂���B");
		}
	}

	while('"' != (cData = cRead())){
		if(eof()){
			Err(L"������I��������\"��������܂���B");
		}
		_str += cData;
	}
	return(_str);
}

//==============================================================
//			���l�ǂݍ���
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			int		�ǂݍ��񂾐��l
//	������
//			MML����(��)�ň͂܂ꂽ��������擾����B
//==============================================================
int	MMLfile::GetNum(void)
{
	char	cData;
	int		iResult;

	while(cRead() != '('){
		if(eof()){
			Err(L"���l�J�n������(��������܂���B");
		}
	}

	iResult = GetInt();

	while(')' != (cData = cRead())){
		if(eof()){
			Err(L"���l�I��������)��������܂���B");
		}
	}
	return(iResult);
}

//==============================================================
//			���l�ǂݍ���
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			int		�ǂݍ��񂾐��l
//==============================================================
int		MMLfile::GetInt(void)
{
				bool	neg = false;			//����
				int		iResult = 0;			//���Z����
	unsigned	char	cData = GetChar();

	//16�i��
	if(cData == '$'){
		cData = cRead();
		if(cData == '+'){
			neg = false;
			cData	 = cRead();
		}
		if(cData == '-'){
			neg = true;
			cData	 = cRead();
		}
		while(((cData >= '0') && (cData <= '9')) || ((cData >= 'a') && (cData <= 'f')) || ((cData >= 'A') && (cData <= 'F'))){
			iResult <<= 4;
			if((cData >= '0') && (cData <= '9')){
				iResult += (unsigned int)cData - 0x30;
			} else if((cData >= 'A') && (cData <= 'F')){
				iResult += (unsigned int)cData - 0x41 + 10;
			} else if((cData >= 'a') && (cData <= 'f')){
				iResult += (unsigned int)cData - 0x61 + 10;
			}
			cData	 = cRead();
		}

	//�Q�i��
	} else if(cData == '%'){
		cData = cRead();
		if(cData == '-'){
			neg = true;
			cData	 = cRead();
		}
		while((cData >= '0') && (cData <= '1')){
			iResult <<= 1;
			iResult += (unsigned int)cData - 0x30;
			cData	 = cRead();
		}

	//10�i��
	} else if(((cData >= '0') && (cData <= '9')) || (cData == '-') || (cData == '+')){
		if(cData == '+'){
			neg = false;
			cData	 = cRead();
		}
		if(cData == '-'){
			neg = true;
			cData	 = cRead();
		}
		while((cData >= '0') && (cData <= '9')){
			iResult *= 10;
			iResult += (unsigned int)cData - 0x30;
			cData	 = cRead();
		}

	} else {
			Err(L"���l�ȊO���w�肳��܂����B");
	}

	//�|�C���^���P�߂�
	Back();							//	StreamPointerAdd(-1);

	//����
	if(neg == true){
		iResult = -iResult;
	}

	return(iResult);
}

//==============================================================
//			�����ǂݍ���
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			int		�ǂݍ��񂾐��l
//	������
//		������ǂݍ��ށi�t�_�t���j
//==============================================================
int	MMLfile::readLength(unsigned int DefaultLength){

	char	cData;				//�ǂݍ��ݗp
	int		iLength;			//���� [tick]
	int		iDot;				//�t�_�v�Z�p [tick]
	int		iMod;
	int		i;

	//�ǂݍ���
	cData = GetChar();

	//Length
	if(((cData >= '0') && (cData <= '9')) || (cData == '.')){
		//�|�C���^���P�߂�
		Back();							//StreamPointerAdd(-1);
		if((cData >= '0') && (cData <= '9')){
			i = GetInt();
			iLength = (MML_timebase * 4) / i;
			iMod	= (MML_timebase * 4) % i;
			if(iMod != 0){
				Warning(L"�����̌v�Z�Ŋ���؂�܂���ł����B�����_�͐؎̂Ă��܂��B");
			}
		} else {
			iLength = DefaultLength;
		}

		iDot	= iLength;
		//�t�_
		while((cData = cRead()) == '.'){
			iMod = (iDot & 0x01);
			iDot >>= 1;
			if(iMod != 0){
				Warning(L"�t�_�̌v�Z�Ŋ���؂�܂���ł����B�����_�͐؎̂Ă��܂��B");
			}
			iLength += iDot;
		};
		Back();							//StreamPointerAdd(-1);



	//Tick
	} else if (cData == '%'){
		iLength = GetInt();

	} else {
		iLength = -1;
	}

	return(iLength);
}

//==============================================================
//			�����ǂݍ���
//--------------------------------------------------------------
//	������
//			����
//	���Ԓl
//			int		�ǂݍ��񂾐��l
//					������������ĂȂ��ꍇ�́A -1 ��Ԃ��B
//==============================================================
int		MMLfile::GetLength(unsigned int DefaultLength)	//
{
	char	cData;				//�ǂݍ��ݗp
	int		iLength;			//���� [tick]
	int		iCalc;
	bool	add;

	//�����ǂݍ���
	iLength = readLength(DefaultLength);
	if(iLength == -1){
		return(iLength);
	}

	//�����̉����Z
	cData = cRead();
	while((cData == '+') || (cData == '-')){
		//��Ōv�Z���镄���̃`�F�b�N
		if(cData == '+'){
			add = true;
		} else {
			add = false;
		}
		iCalc = readLength(DefaultLength);
		if(iCalc == -1){
			Err(L"�����̉����Z�l�ɐ��l�ȊO���w�肳��Ă��܂��B");
		}
		if(add == true){
			iLength += iCalc;
		} else {
			iLength -= iCalc;
		}
		cData = cRead();
	};
	Back();							//StreamPointerAdd(-1);

	if((iLength < 1) || (iLength > 255)){
		Err(L"�����́A%1�i96�j�`%255�i1+1+2+8�j�̊ԂŎw�肵�ĉ������B255[tick]�𒴂���ꍇ�̓^�C`&', `^'���g���ĉ������B");
	}

	return(iLength);
}

//==============================================================
//		�R�}���hID�̎擾
//--------------------------------------------------------------
//	������
//		Command_Info*	_command
//		unsigned	int	_size
//	���Ԓl
//		int			�R�}���h�R�[�h�@�i-1��unknown command�j
//==============================================================
int	MMLfile::GetCommandID(const Command_Info _command[], unsigned int _size)
{
	unsigned	int		ptCommand	= tellg();	//���݂̃t�@�C���|�C���^��ێ����Ă����B
	unsigned	int		i			= 0;		//�����p
	unsigned	int		j;						//������`�F�b�N�p

	//�R�}���h������̃`�F�b�N
	while(i < _size){
		StreamPointerMove(ptCommand);
		j = 0;
		do{
			if(_command[i].str[j] == 0){
				return(_command[i].id);
			}
		} while(cRead() == _command[i].str[j++]);
		i++;
	}
	return(-1);
}

//==============================================================
//		�G���[����
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MMLfile::Err(const wchar_t msg[])
{
	//���݂̃t�@�C�����ƁA�s����\��
	cout << "[ ERROR ] " << nowFile->GetFilename()->c_str() << " (Line = " << nowFile->GetLine() << ") : ";

	//�G���[���e��\��
	wcout << msg << endl;

	//�ُ�I��
	exit(-1);
}

//==============================================================
//		���[�j���O����
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
void	MMLfile::Warning(const wchar_t msg[])
{
	//���݂̃t�@�C�����ƁA�s����\��
	cout << "[WARNING] " << nowFile->GetFilename()->c_str() << " (Line = " << nowFile->GetLine() << ") : ";

	//���[�j���O���e��\��
	wcout << msg << endl;
}
