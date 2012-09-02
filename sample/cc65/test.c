
#define	__NES__

#include <nes.h>
#include <conio.h>

void	__fastcall__	nsd_main(void);
void	__fastcall__	nsd_init(void);
void	__fastcall__	nsd_play_bgm(void* ptr);

void	main()
{

	static	const	char	mus[] = {
		0x03,0x00,	// header (Track = 1)
		0x0A,0x00,	// Track 1 sequence address
		0x08,0x00,	// Track 2 sequence address
		0x08,0x00,	// Track 3 sequence address
		0x2A,-12,	// _-12		�iAddr = 0x0008�j
		0x5C,		// q12		�iAddr = 0x000A�j
		0x0E,		// gate mode = 1
		0xC0,16,	// c, gate time = 16 tick
		0x82,		// d
		0x84,		// e
		0x85,		// f
		0x97,		// g&
		0x89,		// a
		0x8B,		// b
		0x29,		// >
		0xE0,96,90,	// c1, gate time = 96 tick
		0x8E,		// r+
		0x6C,		// v12
		0x80,		// c
		0x8D,		// r-
		0x20,		// (
		0x20,		// (
		0x80,		// c
		0x8D,		// r-
		0x21,		// )
		0x21,		// )
		0x3B,		// o4
		0xC0,20,	// c, gate time = 20 tick
		0x8E,		// r+
		0x00		// End of Track
	};

	nsd_init();				//�����h���C�o�̏������B	�K���ĂԁB

	nsd_play_bgm(mus);		//���t�J�n

	while(1){
		waitvblank();
		nsd_main();			//V-Blank���ɌĂяo���B�i�����ɏ����Ȃ��Ă��ANMI���荞�݂ł���Ă��ǂ��B�j
	}
}

