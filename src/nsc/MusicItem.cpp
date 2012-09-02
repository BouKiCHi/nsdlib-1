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
//		MusicFile*	SND
//		int			iOffset
//	���Ԓl
//				����
//==============================================================
MusicItem::MusicItem(const char _strName[]):
	iOffset(0),
	strName(_strName)
{
	//Debug message�@�i���������o�͂���̂Œ��ӁB�j
	if(cOptionSW->cDebug & 0x01){
		cout << "Create Music Object : " << strName << endl;
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
//				����
//==============================================================
unsigned	int		MusicItem::getSize()
{
	return(iSize);
}

//==============================================================
//		�R�[�h�̃I�t�Z�b�g�A�h���X�̎擾
//--------------------------------------------------------------
//	������
//				����
//	���Ԓl
//				����
//==============================================================
unsigned	int		MusicItem::getOffset()
{
	return(iOffset);
}

//==============================================================
//		�I�t�Z�b�g�A�h���X�̐ݒ�
//--------------------------------------------------------------
//	������
//				����
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
		cout << "Object Address [0x" << hex << _offset << dec << "]: " << strName << endl;
	}

	iOffset = _offset;
	_offset	+= code.size();

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
//				����
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
