;---------------------------------------
;
; Startup code for cc65 (NES version)
;
; by Groepaz/Hitmen <groepaz@gmx.net>
; based on code by Ullrich von Bassewitz <uz@cc65.org>
;
;---------------------------------------
;   Changed by S.W.
;	- add the code for nsd.lib
;	- delete (comment out) the c runtime
;
;note;
;	���̃X�^�[�g�A�b�v�icrt0.s�j���g�p����ꍇ�A
;	�b���ꂩ�琶�������I�u�W�F�N�g�́A�����N���Ȃ��ŉ������B
;	�I�[���E�A�Z���u������ł̊J����z�肵���X�^�[�g�A�b�v�ł��B
;	�b����p�̏������R�[�h�������^�C���̕ϐ��̈�́A�S�č폜���Ă��܂��B
;
;---------------------------------------

;	.export		_exit
	.export		__STARTUP__ : absolute = 1      ; Mark as startup
;	.import		initlib, donelib, callmain
;	.import		push0, _main, zerobss, copydata
;	.import		ppubuf_flush

	.import		_main

	; Linker generated symbols
	.import		__RAM_START__, __RAM_SIZE__
	.import		__SRAM_START__, __SRAM_SIZE__
	.import		__ROM0_START__, __ROM0_SIZE__
	.import		__STARTUP_LOAD__,__STARTUP_RUN__, __STARTUP_SIZE__
	.import		__CODE_LOAD__,__CODE_RUN__, __CODE_SIZE__
	.import		__RODATA_LOAD__,__RODATA_RUN__, __RODATA_SIZE__

;	.include	"zeropage.inc"
	.include	"nes.inc"
	.include	"..\..\include\nsd.inc"

; ------------------------------------------------------------------------
; 16 bytes INES header
; ------------------------------------------------------------------------

.segment	"HEADER"

;    +--------+------+------------------------------------------+
;    | Offset | Size | Content(s)                               |
;    +--------+------+------------------------------------------+
;    |   0    |  3   | 'NES'                                    |
;    |   3    |  1   | $1A                                      |
;    |   4    |  1   | 16K PRG-ROM page count                   |
;    |   5    |  1   | 8K CHR-ROM page count                    |
;    |   6    |  1   | ROM Control Byte #1                      |
;    |        |      |   %####vTsM                              |
;    |        |      |    |  ||||+- 0=Horizontal mirroring      |
;    |        |      |    |  ||||   1=Vertical mirroring        |
;    |        |      |    |  |||+-- 1=SRAM enabled              |
;    |        |      |    |  ||+--- 1=512-byte trainer present  |
;    |        |      |    |  |+---- 1=Four-screen mirroring     |
;    |        |      |    |  |                                  |
;    |        |      |    +--+----- Mapper # (lower 4-bits)     |
;    |   7    |  1   | ROM Control Byte #2                      |
;    |        |      |   %####0000                              |
;    |        |      |    |  |                                  |
;    |        |      |    +--+----- Mapper # (upper 4-bits)     |
;    |  8-15  |  8   | $00                                      |
;    | 16-..  |      | Actual 16K PRG-ROM pages (in linear      |
;    |  ...   |      | order). If a trainer exists, it precedes |
;    |  ...   |      | the first PRG-ROM page.                  |
;    | ..-EOF |      | CHR-ROM pages (in ascending order).      |
;    +--------+------+------------------------------------------+

	.byte	$4e,$45,$53,$1a	; "NES"^Z
	.byte	2		; ines prg  - Specifies the number of 16k prg banks.
	.byte	1		; ines chr  - Specifies the number of 8k chr banks.
	.byte	%00000001	; ines mir  - Specifies VRAM mirroring of the banks.
	.byte	%00000000	; ines map  - Specifies the NES mapper used.
	.byte	0,0,0,0,0,0,0,0	; 8 zeroes


; ------------------------------------------------------------------------
; Startup code
; ------------------------------------------------------------------------

.segment	"STARTUP"

start:

	;---------------
	; setup the CPU and System-IRQ
	sei
	cld

	;---------------
	;Clear memory
	jsr	_zero_mem

	;---------------
	;init nsd.lib
	jsr	_nsd_init	;V-Blank���荞�݂�L���ɂ���O�ɌĂ�
				;�iPPU�̏������O�ɌĂԁj

	;---------------
	;init PPU
	jsr	_ppu_init

	;---------------
	;Call main
	jsr	_main

	jmp	start

; ------------------------------------------------------------------------
; System V-Blank Interupt (60Hz)
; ------------------------------------------------------------------------
nmi:
	pha
	tya
	pha
	txa
	pha

	;---------------
	;Call main of nsd.lib
	jsr	_nsd_main		;���t����

	pla
	tax
	pla
	tay
	pla

	rti

; ------------------------------------------------------------------------
; System IRQ Interupt
; ------------------------------------------------------------------------
irq:
	pha
	tya
	pha
	txa
	pha



	pla
	tax
	pla
	tay
	pla

	rti

; ------------------------------------------------------------------------
; 	Zero memory
; ------------------------------------------------------------------------
.proc	_zero_mem

	lda	#0
	ldx	#0
@L:
	sta	$0000,x	;Stack�̓N���A���Ȃ��B
	sta	$0200,x
	sta	$0300,x
	sta	$0400,x
	sta	$0500,x
	sta	$0600,x
	sta	$0700,x
	inx
	bne	@L

	rts
.endproc

; ------------------------------------------------------------------------
; Init PPU
; ------------------------------------------------------------------------
.proc	_ppu_init

	;---------------
	; PPU Control
	lda	#%10101000		;V-Blank NMI: enable
	sta	PPU_CTRL1

	lda	#%00011110
	sta	PPU_CTRL2

	;---------------
	; Wait for vblank
@wait:	lda	PPU_STATUS
	bpl	@wait

	;---------------
	; reset scrolling
	lda	#0
	sta	PPU_VRAM_ADDR1
	sta	PPU_VRAM_ADDR1

	;---------------
	; Make all sprites invisible
	lda	#$00
	ldy	#$f0
	sta	PPU_SPR_ADDR
	ldx	#$40
@loop:	sty	PPU_SPR_IO
	sta	PPU_SPR_IO
	sta	PPU_SPR_IO
	sty	PPU_SPR_IO
	dex
	bne	@loop

	rts

.endproc

; ------------------------------------------------------------------------
; hardware vectors
; ------------------------------------------------------------------------

.segment "VECTORS"

	.word	nmi		; $fffa vblank nmi
	.word	start		; $fffc reset
	.word	irq		; $fffe irq / brk

; ------------------------------------------------------------------------
; character data
; ------------------------------------------------------------------------

.segment "CHARS"

	.include	"neschar.inc"

