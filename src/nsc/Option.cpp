#include "stdafx.h"
#include "Option.h"

//==============================================================
//		�I�v�V��������
//--------------------------------------------------------------
//	������
//			int argc		�I�v�V����������̐�
//			_TCHAR* argv[]	�I�v�V����������
//	���Ԓl
//			SND.name[]		�ϊ�����SND�t�@�C��
//			MML.name[]		�ϊ����MML�t�@�C��
//	�����l
//			�I�v�V�����Ƀt�@�C�������w�肳��Ȃ��ꍇ�́A�w���v�\�����ďI��
//==============================================================
OPSW::OPSW(int argc, char* argv[]):
	//�������ݒ�
	fHelp(0),		//�w���v�́A�f�t�H���g�͕\�����Ȃ��B
	saveNSF(false),
	saveASM(false),
	opt(false),
	cDebug(0)
{

	//----------------------------------
	//��Local �ϐ�
	int		iCount;				//while�̃J�E���g�p
	int		iResult;			//�ėp

	//Option�����p
	int		iOptionChk;			//�I�v�V�����`�F�b�N�p�@�|�C���^
	char	cOption;			//�I�v�V�����`�F�b�N�p�@����
	char	iFlagFilnameExt;	//�g���q���������̃t���O

	//----------------------------------
	//���I�v�V��������
	iCount=1;	//�R�}���h���͔�΂�
	while(iCount!=argc)
	{
		//--------------
		//�I�v�V�����X�C�b�`�ɃX���b�V�������邩�m�F
		if((argv[iCount][0]=='/')||(argv[iCount][0]=='-')){

			//--------------
			//��Option Switch	�i�X���b�V�����������ꍇ�̏����j
			switch(argv[iCount][1]){
				//--------
				//Help�\��
				case 'h' :
				case 'H' :
				case '?' :
					fHelp=1;
					break;
				//--------
				//�A�Z���u�������
				case 'o' :
				case 'O' :
					opt = true;
					break;
				//--------
				//�A�Z���u�������
				case 'a' :
				case 'A' :
					saveASM = true;
					break;
				//--------
				//�m�r�e��
				case 'n' :
				case 'N' :
					saveNSF = true;
					break;
				//--------
				//Debug�̎w��
				case 'D' :
					iResult=sscanf(argv[iCount],"/D%d",&cDebug);
					if((iResult==NULL)||(iResult==EOF)){
						opError(L"-D");
						break;
					};
					break;
				//--------
				//Debug�̎w��
				case 'l' :
				case 'L' :
					//���Ɏw�肳��Ă���H
					if(strCodeName.empty()){
						iFlagFilnameExt=0;		//�g���q�̗L���@Reset
						iOptionChk=0;
						while((cOption=argv[iCount][iOptionChk+2])!=0)
						{
							strCodeName+=cOption;
							if(cOption=='.'){iFlagFilnameExt=1;};
							iOptionChk++;
						};
						if(iFlagFilnameExt==0){
							strCodeName+=".bin";
						};
					} else {
						opError(L"-l Code �t�@�C����2��ȏ�w�肳��܂����B");
						break;
					};
					break;
				//--------
				//�t�@�C���̎w��
				case 'f' :
				case 'F' :
					//��ɁA�t�@�C�����������Ă��邩�`�F�b�N�B
					if(argv[iCount][3]==0){
						opError(L"/F �t�@�C�����������Ă���܂���B");
						break;
					};
					switch(argv[iCount][2]){
					//--------
					//MML�t�@�C���̎w��
					case 'A' :
					case 'a' :
						//���Ɏw�肳��Ă���H
						if(strASMname.empty()){
							iFlagFilnameExt=0;		//�g���q�̗L���@Reset
							iOptionChk=0;
							while((cOption=argv[iCount][iOptionChk+3])!=0)
							{
								strASMname+=cOption;
								if(cOption=='.'){iFlagFilnameExt=1;};
								iOptionChk++;
							};
							if(iFlagFilnameExt==0){
								strASMname+=".s";
							};
						} else {
							opError(L"-fa ASM �t�@�C����2��ȏ�w�肳��܂����B");
							break;
						};
						break;
					case 'N' :
					case 'n' :
						//���Ɏw�肳��Ă���H
						if(strNSFname.empty()){
							iFlagFilnameExt=0;		//�g���q�̗L���@Reset
							iOptionChk=0;
							while((cOption=argv[iCount][iOptionChk+3])!=0)
							{
								strNSFname+=cOption;
								if(cOption=='.'){iFlagFilnameExt=1;};
								iOptionChk++;
							};
							if(iFlagFilnameExt==0){
								strNSFname+=".nsf";
							};
						} else {
							opError(L"-fn NSF �t�@�C����2��ȏ�w�肳��܂����B");
							break;
						};
						break;
					default :
						opError(L"-f");
						break;
					};
				break;
				//--------
				//�f�t�H���g
				default :
					opError(L"");
					break;
			};

		} else{

			//--------------
			//���t�@�C����	�i�X���b�V�������������ꍇ�̏����j
			//���Ɏw�肳��Ă���H
			if(strMMLname.empty()){
				iFlagFilnameExt=0;		//�g���q�̗L���@Reset
				iOptionChk=0;		
				while((cOption=argv[iCount][iOptionChk])!=0)
				{
					strMMLname+=cOption;
					if(cOption=='.'){iFlagFilnameExt=1;};
					iOptionChk++;
				};
				if(iFlagFilnameExt==0){
					strMMLname+=".mml";
				};
			} else {
				opError(L"MML�t�@�C����2��ȏ�w�肳��܂����B");
				break;
			};

		};

		//--------------
		//�����̃I�v�V����
		iCount++;
	};

	//----------------------------------
	//���I�v�V�����Ŏw�肳�ꂽ������������B

	//--------------
	//�w���v�\��
	//�t�@�C������������Ȃ������ꍇ���A�w���v��\������B
	if((fHelp==1)||(strMMLname.empty())){print_help();};

	if(strASMname.empty()){
		iOptionChk=0;		
		while((cOption=strMMLname[iOptionChk])!='.')
		{
			strASMname+=cOption;
			iOptionChk++;
		};
		strASMname+=".s";
	};

	if(strNSFname.empty()){
		iOptionChk=0;		
		while((cOption=strMMLname[iOptionChk])!='.')
		{
			strNSFname+=cOption;
			iOptionChk++;
		};
		strNSFname+=".nsf";
	};


	//--------------
	//

	//	to do	���̑��̃I�v�V������ǉ������Ƃ��́A���̕ӂɒǋL����B

	//----------
	//Debug�p �\��
//	cout << "MML = " << strMMLname << endl;
//	cout << "NSF = " << strNSFname << endl;
//	cout << "BIN = " << strBINname << endl;
//	cout << "ASM = " << strASMname << endl;
//	cout << "C   = " << strCname << endl;


};
//==============================================================
//		�w���v���b�Z�[�W
//--------------------------------------------------------------
//	������
//			�Ȃ�
//	���Ԓl
//			����
//==============================================================
void	OPSW::print_help(){

	wcout	<<	L"MML Compiler for NES Sound Driver & Library\n"
				L"\n"
				L"  Usage : nsc [ -options ] [file(.mml)]\n"
				L"\n"
				L"  -a			Compile to assembly langage.\n"
				L"  -n			Compile to NSF music format.\n"
				L"  -l[file(.bin)]	Filename of the rom code for NSF.\n"
				L"  -fa[file(.s  )]	Filename of the output assembly langage file.\n"
				L"  -fn[file(.nsf)]	Filename of the output NSF music format.\n"
				L"  -h			Print the this help."	<<	endl;

	exit(EXIT_SUCCESS);

};
//==============================================================
//		�f�X�g���N�g
//--------------------------------------------------------------
//	������
//			�Ȃ�
//	���Ԓl
//			����
//==============================================================
OPSW::~OPSW(){


};
//==============================================================
//		�G���[����	�i�v���Z�X���I������j
//--------------------------------------------------------------
//	������
//			char *stErrMsg	�G���[���b�Z�[�W
//	���Ԓl
//			����
//==============================================================
void OPSW::opError(const wchar_t *stErrMsg){

	wcerr << L"�I�v�V�������s���ł��B�F" << stErrMsg << endl;
	exit(EXIT_FAILURE);

};
