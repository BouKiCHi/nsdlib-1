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
OPSW::OPSW(int argc, _TCHAR* argv[]):
	//�������ݒ�
	fHelp(0),		//�w���v�́A�f�t�H���g�͕\�����Ȃ��B
	saveNSF(false),
	saveBIN(false),
	saveASM(false),
	saveC(false),
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
				case 'a' :
				case 'A' :
					saveASM = true;
					break;
				//--------
				//�o�C�i���[��
				case 'b' :
				case 'B' :
					saveBIN = true;
					break;
				//--------
				//�b�����
				case 'c' :
				case 'C' :
					saveC = true;
					break;
				//--------
				//�b�����
				case 'n' :
				case 'N' :
					saveNSF = true;
					break;
				//--------
				//Debug�̎w��
				case 'D' :
					iResult=sscanf(argv[iCount],"/D%d",&cDebug);
					if((iResult==NULL)||(iResult==EOF)){
						opError("-D");
						break;
					};
					break;
				//--------
				//�t�@�C���̎w��
				case 'f' :
				case 'F' :
					//��ɁA�t�@�C�����������Ă��邩�`�F�b�N�B
					if(argv[iCount][3]==0){
						opError("/F �t�@�C�����������Ă���܂���B");
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
								strASMname+=".asm";
							};
						} else {
							opError("-fa ASM �t�@�C����2��ȏ�w�肳��܂����B");
							break;
						};
						break;
					case 'B' :
					case 'b' :
						//���Ɏw�肳��Ă���H
						if(strBINname.empty()){
							iFlagFilnameExt=0;		//�g���q�̗L���@Reset
							iOptionChk=0;
							while((cOption=argv[iCount][iOptionChk+3])!=0)
							{
								strBINname+=cOption;
								if(cOption=='.'){iFlagFilnameExt=1;};
								iOptionChk++;
							};
							if(iFlagFilnameExt==0){
								strBINname+=".bin";
							};
						} else {
							opError("-fb BIN �t�@�C����2��ȏ�w�肳��܂����B");
							break;
						};
						break;
					case 'C' :
					case 'c' :
						//���Ɏw�肳��Ă���H
						if(strCname.empty()){
							iFlagFilnameExt=0;		//�g���q�̗L���@Reset
							iOptionChk=0;
							while((cOption=argv[iCount][iOptionChk+3])!=0)
							{
								strCname+=cOption;
								if(cOption=='.'){iFlagFilnameExt=1;};
								iOptionChk++;
							};
							if(iFlagFilnameExt==0){
								strCname+=".c";
							};
						} else {
							opError("-fc C �t�@�C����2��ȏ�w�肳��܂����B");
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
							opError("-fn NSF �t�@�C����2��ȏ�w�肳��܂����B");
							break;
						};
						break;
					default :
						opError("-f");
						break;
					};
				break;
				//--------
				//�f�t�H���g
				default :
					opError("");
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
				opError("MML�t�@�C����2��ȏ�w�肳��܂����B");
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

	//--------------
	//�t�@�C���̎w�肪���������ꍇ
	if(strBINname.empty()){
		iOptionChk=0;		
		while((cOption=strMMLname[iOptionChk])!='.')
		{
			strBINname+=cOption;
			iOptionChk++;
		};
		strBINname+=".bin";
	};

	if(strASMname.empty()){
		iOptionChk=0;		
		while((cOption=strMMLname[iOptionChk])!='.')
		{
			strASMname+=cOption;
			iOptionChk++;
		};
		strASMname+=".asm";
	};

	if(strCname.empty()){
		iOptionChk=0;		
		while((cOption=strMMLname[iOptionChk])!='.')
		{
			strCname+=cOption;
			iOptionChk++;
		};
		strCname+=".c";
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

	cout	<<	"MML Compiler for NES Sound Driver & Library\n"
				"\n"
				"  Usage : nsc [ -options ] [file(.mml)]\n"
				"\n"
				"  -a			Compile to assembly langage.\n"
				"  -b			Compile to binary.\n"
				"  -c			Compile to C langage.\n"
				"  -n			Compile to NSF.\n"
				"  -fa[file(.asm)]	Name the output assembly langage file.\n"
				"  -fb[file(.bin)]	Name the output binary file.\n"
				"  -fc[file(.c  )]	Name the output C langage file.\n"
				"  -fn[file(.nsf)]	Name the output NSF file.\n"
				"  -h			Print the this help."	<<	endl;

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
void OPSW::opError(const char *stErrMsg){

	cerr << "�I�v�V�������s���ł��B�F" << stErrMsg << endl;
	exit(EXIT_FAILURE);

};
