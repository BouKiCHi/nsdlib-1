
#define	__NES__

#include <nes.h>
#include <conio.h>

#include	"..\..\include\nsd.h"


//�ȃf�[�^
extern	const	char		Test_BGM0[];		//�b����Ȃ̂ŁA�V���{���擪��'_'�͕s�v�B
extern	const	nsd_dpcm	Test_DPCMinfo[];	//�b����Ȃ̂ŁA�V���{���擪��'_'�͕s�v�B

//���C�����[�`��
void	main()
{

	nsd_init();				//�����h���C�o�̏������B	�K���ĂԁB
	nsd_set_dpcm(Test_DPCMinfo);	//��PCM����\���̂̃Z�b�g

	nsd_play_bgm(Test_BGM0);		//���t�J�n

	while(1){
		waitvblank();
		nsd_main();			//V-Blank���ɌĂяo���B�i�����ɏ����Ȃ��Ă��ANMI���荞�݂ł���Ă��ǂ��B�j
	}

}

