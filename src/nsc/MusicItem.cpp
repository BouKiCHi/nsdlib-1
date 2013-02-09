#include "StdAfx.h"
#include "MusicItem.h"

/****************************************************************/
/*					�O���[�o���ϐ��i�N���X�����ǁE�E�E�j		*/
/****************************************************************/
extern	OPSW*			cOptionSW;	//�I�v�V�������ւ̃|�C���^�ϐ�

//==============================================================
//		�R���X�g���N�^
//--------------------------------------------------------------
//	������
//		const		wchar_t	_strName[]	�I�u�W�F�N�g��
//	���Ԓl
//				����
//==============================================================
MusicItem::MusicItem(const wchar_t _strName[]):
	iOffset(0),
	strName(_strName)
{
	//Debug message�@�i���������o�͂���̂Œ��ӁB�j
	if(cOptionSW->cDebug & 0x01){
		wcout << L"Create Music Object : " << strName << endl;
	}
}

//==============================================================
//		�f�X�g���N�^
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
MusicItem::~MusicItem(void)
{
	//----------------------
	//Local�ϐ�
	vector<	MusicItem*>::iterator	itItem;

	//----------------------
	//Delete Class
	if(!ptcItem.empty()){
		itItem = ptcItem.begin();
		while(itItem != ptcItem.end()){
			delete *itItem;
			itItem++;
		}
		ptcItem.clear();
	}
}

//==============================================================
//		�R�[�h�T�C�Y�̎擾
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//		size_t
//==============================================================
size_t		MusicItem::getSize()
{
	return(iSize);
}

//==============================================================
//		�R�[�h�̃I�t�Z�b�g�A�h���X�̎擾
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//		unsigned	int	
//==============================================================
unsigned	int		MusicItem::getOffset()
{
	return(iOffset);
}

//==============================================================
//		�I�t�Z�b�g�A�h���X�̐ݒ�
//--------------------------------------------------------------
//	������
//		unsigned	int		_offset
//	���Ԓl
//				����
//==============================================================
unsigned	int		MusicItem::SetOffset(unsigned	int _offset)
{
	//----------------------
	//Local�ϐ�
	vector<	MusicItem*>::iterator	itItem;

	//Debug message�@�i���������o�͂���̂Œ��ӁB�j
	if(cOptionSW->cDebug & 0x02){
		wcout << L"Object Address [0x" << hex << _offset << dec << L"]: " << strName << endl;
	}

	iOffset = _offset;
	_offset	+= (unsigned int)code.size();

	if(!ptcItem.empty()){
		itItem = ptcItem.begin();
		while(itItem != ptcItem.end()){
			_offset = (*itItem)->SetOffset(_offset);
			itItem++;
		}
	}

	return(_offset);
}

//==============================================================
//		�R�[�h�̎擾
//--------------------------------------------------------------
//	������
//		string*		_str
//	���Ԓl
//				����
//==============================================================
void	MusicItem::getCode(string* _str)
{
	//----------------------
	//Local�ϐ�
	vector<	MusicItem*>::iterator	itItem;

	_str->append(code);

	if(!ptcItem.empty()){
		itItem = ptcItem.begin();
		while(itItem != ptcItem.end()){
			(*itItem)->getCode(_str);
			itItem++;
		}
	}
}

//==============================================================
//		�R�[�h�̎擾
//--------------------------------------------------------------
//	������
//		MusicFile*	MUS		�R�[�h���o�͂���ȃf�[�^�t�@�C���E�I�u�W�F�N�g
//	���Ԓl
//				����
//==============================================================
void	MusicItem::getAsm(MusicFile* MUS)
{
	//----------------------
	//Local�ϐ�
	unsigned	int	i = 0;
	vector<	MusicItem*>::iterator	itItem;

	if(code.size() > 0){
		while(i < code.size()){
			if(i==0){
				*MUS << "	.byte	$";
			} else {
				*MUS << " ,$";
			}
			*MUS << hex << setw(2) << setfill('0') << (int)(code[i] & 0xFF);
			i++;
		}
		*MUS << dec << endl;
	}

	if(!ptcItem.empty()){
		itItem = ptcItem.begin();
		while(itItem != ptcItem.end()){
			(*itItem)->getAsm(MUS);
			itItem++;
		}
	}
}
