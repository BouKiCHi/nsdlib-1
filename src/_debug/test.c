
#define	__NES__

#include <nes.h>
#include <conio.h>

void	__fastcall__	nsd_main(void);
void	__fastcall__	nsd_init(void);
void	__fastcall__	nsd_play_bgm(void* ptr);

void	main()
{

	static	const	char	mus[] = {
		0x01,0x00,	// header (Track = 1)
		0x04,0x00,	// Track 1 sequence address
		0x5C,		// q12
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
		0x00		// End of Track
	};

	nsd_init();				//音源ドライバの初期化。	必ず呼ぶ。

	nsd_play_bgm(mus);		//演奏開始

	while(1){
		waitvblank();
		nsd_main();			//V-Blank毎に呼び出す。（ここに書かなくても、NMI割り込みでやっても良い。）
	}
}

