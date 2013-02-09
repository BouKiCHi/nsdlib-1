;=======================================================================
;
;	NES Sound Driver Libraly		Track Sequencer
;
;=======================================================================

	.setcpu		"6502"

	.export		nsd_sequence

	.import		_nsd_snd_keyon
	.import		_nsd_snd_keyoff
	.import		_nsd_snd_sweep
	.import		_nsd_snd_voice
	.import		_nsd_play_se
	.import		nsd_work
	.importzp	nsd_work_zp

	.include	"nes.inc"
	.include	"nsd.inc"

;=======================================================================
;		nsd_keyon
;-----------------------------------------------------------------------
;<<Contents>>
;	Key On
;<<Input>>
;	x	Channel * 2
;<<Output>>
;	nothing
;=======================================================================
.proc	nsd_keyon

	;tai check
	lda	__tai,x
	and	#$02
	bne	exit		;�O��̉������^�C�E�X���[�������I��

	;Hardware key on
	jsr	_nsd_snd_keyon

	;Software key on
	lda	__chflag,x
	and	#~nsd_chflag::KeyOff
	ora	#nsd_chflag::KeyOff
	sta	__chflag,x

	;-----------------------
	;�ȍ~�́A��PCM�ł͕s�v
	cpx	#nsd::TR_BGM5
	beq	exit

	;���g���ݒ��K���ĂԂ悤�ɁB
	lda	#$FF
	sta	__frequency,x
	sta	__frequency + 1,x

	;Portamento
	lda	__por_depth,x
	bne	@L		;�|���^�����g���I�����Ă�����A����������B
	lda	#0
	sta	__por_target,x
@L:

	;Envelop Key on
	lda	#$00
	sta	__Envelop_F,x
	lda	#$01
	sta	__env_freq_ptr,x
	sta	__env_note_ptr,x

	;-----------------------
	;�ȍ~�́A�O�p�g�ł͕s�v
	cpx	#nsd::TR_BGM3
	beq	exit

	lda	#$00
	sta	__Envelop_V,x
	lda	#$01
	sta	__env_voi_ptr,x
	sta	__env_vol_ptr,x

	;���F�G���x���[�v
	lda	__env_voice + 1,x	;�������@�œK���@������
	bne	@L2			;���ʃG���x���[�v��������������
	lda	__env_voice,x		;������KeyOn���̉��F�ɂ���B
	jsr	_nsd_snd_voice		;
@L2:

exit:	rts
.endproc

;=======================================================================
;		nsd_keyoff
;-----------------------------------------------------------------------
;<<Contents>>
;	Key Off
;<<Input>>
;	x	Channel * 2
;<<Output>>
;	nothing
;=======================================================================
.proc	nsd_keyoff

	; to do	tai check
	lda	__tai,x
	and	#$01
	beq	@L			;����̉������^�C�E�X���[�������I��
@E:	rts
@L:	lda	__chflag,x
	and	#nsd_chflag::KeyOff
	cmp	#nsd_chflag::KeyOff
	bne	@E			;Key On(=3)�̎��̂݁A�����B

	;Hardware key off
	jsr	_nsd_snd_keyoff

	;Software key Off
	lda	__chflag,x
	and	#~nsd_chflag::KeyOff
	ora	__gatemode,x
	sta	__chflag,x

	;-----------------------
	;�ȍ~�́A��PCM�ł͕s�v
	cpx	#nsd::TR_BGM5
	beq	exit

	;Portamento
	lda	#$00
	tay
	sta	__por_depth,x		;�|���^�����g���I��������B

	;Frequency Envelop keyoff
	lda	__env_frequency + 1,x
	beq	Freq_End
	sta	__ptr + 1
	lda	__env_frequency,x
	sta	__ptr
	lda	(__ptr),y
	beq	Freq_End
	sta	__env_freq_ptr,x
	lda	__Envelop_F,x
	and	#$F0
	sta	__Envelop_F,x
Freq_End:

	;Note Envelop keyoff
	lda	__env_note + 1,x
	beq	Note_End
	sta	__ptr + 1
	lda	__env_note,x
	sta	__ptr
	lda	(__ptr),y
	beq	Note_End
	sta	__env_note_ptr,x
	lda	__Envelop_F,x
	and	#$0F
	sta	__Envelop_F,x
Note_End:

	;-----------------------
	;�ȍ~�́A�O�p�g�ł͕s�v
	cpx	#nsd::TR_BGM3
	beq	exit

	;Voice Envelop keyoff
	lda	__env_voice + 1,x
	beq	Voice_End
	sta	__ptr + 1
	lda	__env_voice,x
	sta	__ptr
	lda	(__ptr),y
	beq	Voice_End
	sta	__env_voi_ptr,x
	lda	__Envelop_V,x
	and	#$0F
	sta	__Envelop_V,x
Voice_End:

	;Volume Envelop keyoff
	lda	__env_volume + 1,x
;	beq	Volume_End		;��{�I�ɂ͗L�����낤�̂ŁA�R�����g�A�E�g���Ă����B
	sta	__ptr + 1
	lda	__env_volume,x
	sta	__ptr
	lda	(__ptr),y
	beq	Volume_End
	sta	__env_vol_ptr,x
	lda	__Envelop_V,x
	and	#$F0
	sta	__Envelop_V,x
Volume_End:

	;���F�G���x���[�v
	lda	__chflag,x
	and	#$01			;�������@�œK���@������
	beq	@VoiceE			;gatemode = 1 ��������A
	lda	__voice,x		;������KeyOff���̉��F�ɂ���B
	shr	a, 4			; a = release voice
	jsr	_nsd_snd_voice		;
@VoiceE:

exit:	rts
.endproc

;=======================================================================
;		nsd_load_sequence;
;-----------------------------------------------------------------------
;<<Contents>>
;	read sequence data
;<<Input>>
;	x	Channel * 2
;	nds_work.Sequence_ptr
;<<Output>>
;	a	sequence data
;=======================================================================
.proc	nsd_load_sequence
	lda	(__Sequence_ptr,x)	;[6]
	inc	__Sequence_ptr,x	;[6]
	bne	exit			;[2]
	inc	__Sequence_ptr + 1,x
exit:	rts				;[6]
.endproc

;=======================================================================
;		nsd_load_ptr;
;-----------------------------------------------------------------------
;<<Contents>>
;	read sequence data (pointer)
;<<Input>>
;	x	Channel * 2
;	nds_work.Sequence_ptr
;<<Output>>
;	__ptr	now pointer
;	__tmp	sequence data
;	a	__tmp + 1
;=======================================================================
.proc	nsd_load_ptr

	ldy	__Sequence_ptr,x	;
	sty	__ptr			;
	ldy	__Sequence_ptr + 1,x	;
	sty	__ptr + 1		;__ptr = __Sequence_ptr

	lda	(__Sequence_ptr,x)	;[6]
	inc	__Sequence_ptr,x	;[6]
	bne	@L1			;[2]
	inc	__Sequence_ptr + 1,x
@L1:	sta	__tmp

	lda	(__Sequence_ptr,x)	;[6]
	inc	__Sequence_ptr,x	;[6]
	bne	@L2			;[2]
	inc	__Sequence_ptr + 1,x
@L2:	sta	__tmp + 1		;__tmp = value

	rts
.endproc

;=======================================================================
;	void	nsd_sequence(void);
;-----------------------------------------------------------------------
;<<Contents>>
;	Play sequence and control gate time
;<<Input>>
;	x	Channel * 2
;<<Output>>
;	nothing
;=======================================================================
.proc	nsd_sequence

.rodata

length:	.byte	96
	.byte	72
	.byte	48
	.byte	36
	.byte	32
	.byte	24
	.byte	18
	.byte	16
	.byte	12
	.byte	9
	.byte	8
	.byte	6
	.byte	4
	.byte	3
	.byte	2
	.byte	1

opaddr:	.addr	nsd_op00
	.addr	nsd_op01
	.addr	nsd_op02
	.addr	nsd_op03
	.addr	nsd_op04
	.addr	nsd_op05
	.addr	nsd_op06
	.addr	nsd_op07
	.addr	nsd_op08
	.addr	nsd_op09
	.addr	nsd_op0A
	.addr	nsd_op0B
	.addr	nsd_op0C
	.addr	nsd_op0D
	.addr	nsd_op0E
	.addr	nsd_op0F
	.addr	nsd_op10
	.addr	nsd_op11
	.addr	nsd_op12
	.addr	nsd_op13
	.addr	nsd_op14
	.addr	nsd_op15
	.addr	nsd_op16
	.addr	nsd_op17
	.addr	nsd_op18
	.addr	nsd_op19
	.addr	nsd_op1A
	.addr	nsd_op1B
	.addr	nsd_op1C
	.addr	nsd_op1D
	.addr	nsd_op1E
	.addr	nsd_op1F
	.addr	nsd_op20
	.addr	nsd_op21
	.addr	nsd_op22
	.addr	nsd_op23
	.addr	nsd_op24
	.addr	nsd_op25
	.addr	nsd_op26
	.addr	nsd_op27
	.addr	nsd_op28
	.addr	nsd_op29
	.addr	nsd_op2A
	.addr	nsd_op2B
	.addr	nsd_op2C
	.addr	nsd_op2D
	.addr	nsd_op2E
	.addr	nsd_op2F
	.addr	nsd_op30
	.addr	nsd_op31
	.addr	nsd_op32
	.addr	nsd_op33
	.addr	nsd_op34
	.addr	nsd_op35
	.addr	nsd_op36
	.addr	nsd_op37
	.addr	nsd_op38
	.addr	nsd_op39
	.addr	nsd_op3A
	.addr	nsd_op3B
	.addr	nsd_op3C
	.addr	nsd_op3D
	.addr	nsd_op3E
	.addr	nsd_op3F

.code

	;-------------------------------
	;now play?	(check: Sequence_ptr == 0 ?)	** upper 1 byte only **
	lda	__Sequence_ptr + 1,x
	beq	Exit

	stx	__channel		;channel <- x

	;-------------------------------
	;Gatetime control

	;length == gatetime q ?
	dec	__Length_ctr,x		;length--
	lda	__Length_ctr,x
	cmp	__Gate,x
	bne	GateTime_Exit		; if(__Length_ctr == __Gate){
	jsr	nsd_keyoff		; 	nsd_keyoff();
GateTime_Exit:				; }
	lda	__Length_ctr,x
	bne	Exit		; if(__Length_ctr != 0){ return(); };

	;-------------------------------
	;Sequence		(length == 0)
Sequence:
	jsr	nsd_load_sequence	;[6]

	cmp	#$80			;[2]
	bcc	Control			;[2]	a >= 80 ?

	;-----------------------
	;op-code = 0x80 - 0xFF
Note:
	tay	;save a to y

	;-------
	;bit 4 check (Slur)
Chk_Slur:
	clc
	and	#$10
	beq	@L
	sec
@L:	rol	__tai,x

	;-------
	;bit 5 check (Length )
Chk_Length:
	tya
	and	#$20
	beq	@L
	jsr	nsd_load_sequence
	jmp	@E
@L:	lda	__length,x
@E:	sta	__Length_ctr,x

	;-------
	;bit 6 check (Gate Time)
Chk_GateTime:
	tya
	and	#$40
	beq	@L
	jsr	nsd_load_sequence
	sta	__tmp
	lda	__Length_ctr,x
	sub	__tmp			; a = __Length_ctr - __Gate;
	bcs	@gateset		; if(a < 0){
	lda	#$0			;    a = 0x0; //no gate
	beq	@gateset		; }	// relative jump because "0"
@L:
	lda	__gate_u,x		;if (__gate_u,x == 0) then @q
	beq	@q			;
	lda	__Length_ctr,x
	sub	__gate_u,x		; a = __Length_ctr - __Gate
	bcc	@q			; if (a < 0) then @q
	cmp	__gate_q,x		;
	bcs	@gateset		; if( a < __gate_q){
@q:	lda	__gate_q,x		;    a = __gate_q;
@gateset:				; }
	sta	__Gate,x

Calc_Note_Number:
	tya
	and	#$0F
	cmp	#12
	bcc	NoteSet

@Rest:	and	#$0F
	sub	#$0D
	sta	__tmp
	lda	__tai,x
	and	#$02
	bne	Exit		;If tai then exit
	lda	__chflag,x
	and	#~nsd_chflag::KeyOff
	ora	__tmp
	sta	__chflag,x
Exit:
	rts

NoteSet:
	add	__octave,x
	add	__trans_one,x
	sta	__note,x
	lda	#0
	sta	__trans_one,x	;0 reset
	jmp	nsd_keyon



	;-----------------------
	;op-code = 0x00 - 0x7F
Control:
	cmp	#$40			;[2]
	bcs	Short_Control		;[2]
	;---------------
	;op-code = 0x00 - 0x3F
	asl				;[2]
	tay				;[2]	x <- a * 2
	lda	opaddr,y		;[4]
	sta	__ptr			;[3]
	lda	opaddr + 1,y		;[4]
	sta	__ptr + 1		;[3]
	jmp	(__ptr)			;[5]	jump for each op-code

	;---------------
	;op-code = 0x40 - 0x7F
Short_Control:

	;---------------
	;op-code = 0x40 - 0x7F
	;---------------
	;0x40 - 0x4F
op40:	cmp	#$50
	bcs	op50
	and	#$0F
	;Set default length
	tay
	lda	length,y
	sta	__length,x		;__length = length[a & 0x0F];
	jmp	Sequence
	;---------------
	;0x50 - 0x5F
op50:	cmp	#$60
	bcs	op60
	and	#$0F
	;Set gate time (1)
	sta	__gate_q,x		;__gate_q = a & 0x0F;
	jmp	Sequence
	;---------------
	;0x60 - 0x6F
op60:	cmp	#$70
	bcs	op70
	and	#$0F
	;Set volume
	sta	__tmp
	lda	__volume,x
	and	#$F0
	ora	__tmp
	sta	__volume,x		;__volume = (__volume & 0xF0) | (a & 0x0F);
	jmp	Sequence
	;---------------
	;0x70 - 0x7F
op70:	;Ser release volume
	shl	a, 4
	sta	__tmp
	lda	__volume,x
	and	#$0F
	ora	__tmp
	sta	__volume,x		;__volume = (__volume & 0x0F) | (a << 4);
	jmp	Sequence

;=======================================================================
;		opcode	0x00:	End of Track / End of Subroutine
;-----------------------------------------------------------------------
nsd_op00:
	lda	__subroutine + 1,x
	sta	__Sequence_ptr + 1,x
	beq	@L	;if (a == 0)
	lda	__subroutine,x
	sta	__Sequence_ptr,x	;�߂�Ƃ��͑��
	lda	#0
	sta	__subroutine,x
	sta	__subroutine + 1,x
	jmp	Sequence
@L:
	sta	__Sequence_ptr,x

	lda	__chflag,x
	and	#~nsd_chflag::KeyOff
	sta	__chflag,x
;
;	Sweep�̏�Ԃ����ɖ߂��B
;
@SE1:	;lda	__chflag,x
	and	#nsd_chflag::SE1
	beq	@SE2
	lda	__sweep_ch2
	jsr	_nsd_snd_sweep
	;���g���ݒ��K���ĂԂ悤�ɁB
	lda	#$FF
	sta	__frequency + nsd::TR_BGM2
	sta	__frequency + nsd::TR_BGM2 + 1
	jmp	@Exit

@SE2:	;SE2�͖����B
	and	#nsd_chflag::SE2
	beq	@Exit
	;���g���ݒ��K���ĂԂ悤�ɁB
	lda	#$FF
	sta	__frequency + nsd::TR_BGM4
	sta	__frequency + nsd::TR_BGM4 + 1

@Exit:
	rts

;=======================================================================
;		opcode	0x02:	Sub-routine call
;-----------------------------------------------------------------------
nsd_op02:
	lda	__Sequence_ptr,x
	add	#2
	sta	__subroutine,x
	lda	__Sequence_ptr + 1,x
	adc	#0
	sta	__subroutine + 1,x		;2byte��̃|�C���^���L������B

;=======================================================================
;		opcode	0x01:	Jump (End of Track with loop) 
;-----------------------------------------------------------------------
nsd_op01:
Jump:
	jsr	nsd_load_ptr

	lda	__ptr
	add	__tmp
	sta	__Sequence_ptr,x
	lda	__ptr + 1
	adc	__tmp + 1
	sta	__Sequence_ptr + 1,x	;__Sequence_ptr = __ptr + __tmp

	jmp	Sequence

;=======================================================================
;		opcode	0x03:	Repeat start.
;-----------------------------------------------------------------------
nsd_op03:
	jsr	nsd_load_sequence
	sta	__repeat_ctr,x
	jmp	Sequence

;=======================================================================
;		opcode	0x04:	Repeat break.
;-----------------------------------------------------------------------
nsd_op04:
	lda	__repeat_ctr,x
	cmp	#1
	beq	Jump
	jsr	nsd_load_sequence
	jsr	nsd_load_sequence
	jmp	Sequence

;=======================================================================
;		opcode	0x05:	Repeat end.
;-----------------------------------------------------------------------
nsd_op05:
	dec	__repeat_ctr,x
	bne	Jump
	jsr	nsd_load_sequence
	jsr	nsd_load_sequence
	jmp	Sequence

;=======================================================================
;		opcode	0x06:	Call SE
;-----------------------------------------------------------------------
nsd_op06:
	jsr	nsd_load_ptr

	lda	__ptr
	add	__tmp
	tay
	lda	__ptr + 1
	adc	__tmp + 1
	tax
	tya
	jsr	_nsd_play_se

	ldx	__channel

	jmp	Sequence

;=======================================================================
;		opcode	0x18:	Repeat start.
;-----------------------------------------------------------------------
nsd_op18:
	lda	#0			;counter <= 0
	sta	__repeat_ctr2,x
	jmp	Sequence

;=======================================================================
;		opcode	0x19:	repeat 1 time point
;-----------------------------------------------------------------------
nsd_op19:
	lda	__repeat_ctr2,x
	beq	@exit			;counter == 0 �������牽�����Ȃ��B
	lda	__repeat2,x
	sta	__Sequence_ptr,x
	lda	__repeat2 + 1,x
	sta	__Sequence_ptr + 1,x	;����ȊO�́A :| �̎��ɃW�����v
@exit:
	jmp	Sequence

;=======================================================================
;		opcode	0x1A:	Repeat end.
;-----------------------------------------------------------------------
nsd_op1A:
	inc	__repeat_ctr2,x		;counter ++

	lda	__Sequence_ptr,x
	add	#2
	sta	__repeat2,x
	lda	__Sequence_ptr + 1,x
	adc	#0
	sta	__repeat2 + 1,x		;2byte��̃|�C���^���L������B

	jmp	Jump			;���΃W�����v��

;=======================================================================
;		opcode	0x07:	Write data to memory.
;-----------------------------------------------------------------------
nsd_op07:
	jsr	nsd_load_sequence
	sta	__ptr
	jsr	nsd_load_sequence
	sta	__ptr + 1
	jsr	nsd_load_sequence
	ldy	#0
	sta	(__ptr),y
	jmp	Sequence

;=======================================================================
;		opcode	0x08:	Tempo [BPM]
;-----------------------------------------------------------------------
nsd_op08:
	lda	__chflag,x
	and	#nsd_chflag::SE1 + nsd_chflag::SE2
	bne	Set_Tempo_SE
	jsr	nsd_load_sequence
Set_Tempo:
	sta	__Tempo
	jmp	Sequence
Set_Tempo_SE:
	jsr	nsd_load_sequence
	jmp	Sequence
;=======================================================================
;		opcode	0x0C:	Relative Tempo [BPM]
;-----------------------------------------------------------------------
nsd_op0C:
	lda	__chflag,x
	and	#nsd_chflag::SE1 + nsd_chflag::SE2
	bne	Set_Tempo_SE
	jsr	nsd_load_sequence
	add	__Tempo
	jmp	Set_Tempo
;=======================================================================
;		opcode	0x09:	Note length of �ȗ��� [Ticks] 
;-----------------------------------------------------------------------
nsd_op09:
	jsr	nsd_load_sequence
	sta	__length,x
	jmp	Sequence

;=======================================================================
;		opcode	0x0A:	Gate time (key-off timing from last) 
;-----------------------------------------------------------------------
nsd_op0A:
	jsr	nsd_load_sequence
	sta	__gate_q,x
	jmp	Sequence

;=======================================================================
;		opcode	0x0B:	Gate time (length of ����) 
;-----------------------------------------------------------------------
nsd_op0B:
	jsr	nsd_load_sequence
	sta	__gate_u,x
	jmp	Sequence

;=======================================================================
;		opcode	0x0D:	gate mode	(vol = 0)
;-----------------------------------------------------------------------
nsd_op0D:
	lda	#$00
	sta	__gatemode,x
	jmp	Sequence
;=======================================================================
;		opcode	0x0E:	gate mode
;-----------------------------------------------------------------------
nsd_op0E:
	lda	#$01
	sta	__gatemode,x
	jmp	Sequence
;=======================================================================
;		opcode	0x0F:	gate mode	(release)
;-----------------------------------------------------------------------
nsd_op0F:
	lda	#$02
	sta	__gatemode,x
	jmp	Sequence

;=======================================================================
;		opcode	0x10:	Voice envelop. 
;-----------------------------------------------------------------------
nsd_op10:
	jsr	nsd_load_ptr

	cpx	#nsd::TR_BGM3
	beq	@Exit
	cpx	#nsd::TR_BGM5
	beq	@Exit

	lda	__ptr
	add	__tmp
	sta	__env_voice,x
	lda	__ptr + 1
	adc	__tmp + 1
@Zero:	sta	__env_voice + 1,x	;__env_voice = __ptr + __tmp

	lda	#$01
	sta	__env_voi_ptr,x
@Exit:
	jmp	Sequence

;=======================================================================
;		opcode	0x11:	Volume envelop.
;-----------------------------------------------------------------------
nsd_op11:
	jsr	nsd_load_ptr

	cpx	#nsd::TR_BGM3
	beq	@Exit
	cpx	#nsd::TR_BGM5
	beq	@Exit

	ora	__tmp
	beq	@Zero

	lda	__ptr
	add	__tmp
	sta	__env_volume,x
	lda	__ptr + 1
	adc	__tmp + 1
@Zero:	sta	__env_volume + 1,x

	lda	#$01
	sta	__env_vol_ptr,x
@Exit:
	jmp	Sequence

;=======================================================================
;		opcode	0x12:	Frequency envelop. 
;-----------------------------------------------------------------------
nsd_op12:
	jsr	nsd_load_ptr

	ora	__tmp
	beq	@Zero

	lda	__ptr
	add	__tmp
	sta	__env_frequency,x
	lda	__ptr + 1
	adc	__tmp + 1
@Zero:	sta	__env_frequency + 1,x

	lda	#$01
	sta	__env_freq_ptr,x
@Exit:
	jmp	Sequence

;=======================================================================
;		opcode	0x13:	Note envelop. 
;-----------------------------------------------------------------------
nsd_op13:
	jsr	nsd_load_ptr

	ora	__tmp
	beq	@Zero

	lda	__ptr
	add	__tmp
	sta	__env_note,x
	lda	__ptr + 1
	adc	__tmp + 1
@Zero:	sta	__env_note + 1,x

	lda	#$01
	sta	__env_note_ptr,x
@Exit:
	jmp	Sequence

;=======================================================================
;		opcode	0x14:	Detune (16 = 100 cent)
;-----------------------------------------------------------------------
nsd_op14:
	jsr	nsd_load_sequence
	sta	__detune_cent,x
	jmp	Sequence

;=======================================================================
;		opcode	0x15:	Detune (Resister base) 
;-----------------------------------------------------------------------
nsd_op15:
	jsr	nsd_load_sequence
	sta	__detune_fine,x
	jmp	Sequence

;=======================================================================
;		opcode	0x16:	Sweep (Resister base) 
;-----------------------------------------------------------------------
nsd_op16:
	jsr	nsd_load_sequence
	jsr	_nsd_snd_sweep
	jmp	Sequence

;=======================================================================
;		opcode	0x17:	Portamento (Frequency += n2, every n3 [VBlank]) 
;-----------------------------------------------------------------------
nsd_op17:
	cpx	#nsd::TR_BGM5
	beq	@L

	jsr	nsd_load_sequence	;decay
	sta	__por_ctr,x
	jsr	nsd_load_sequence	;rate
	sta	__por_rate,x
	jsr	nsd_load_sequence	;depth
	sta	__por_depth,x
	jsr	nsd_load_sequence	;target
	sta	__por_target,x

	lda	#0
	sta	__por_now + 0,x
	sta	__por_now + 1,x		;���݂̕ψ�

	jmp	Sequence

@L:
	jsr	nsd_load_ptr
	jsr	nsd_load_ptr
	jmp	Sequence

;=======================================================================
;		opcode	0x1B:	Voice
;-----------------------------------------------------------------------
nsd_op1B:
	lda	#0
	sta	__env_voice + 1,x
	jsr	nsd_load_sequence
	sta	__env_voice,x
	jmp	Sequence
;=======================================================================
;		opcode	0x1C:	VRC7 : Set user instrument 
;-----------------------------------------------------------------------
nsd_op1C:

	jsr	nsd_load_ptr

.if	.defined(VRC7) || .defined(OPLL)
	lda	__ptr
	add	__tmp
	sta	__ptr

	lda	__ptr + 1
	adc	__tmp + 1
	sta	__ptr + 1		;__ptr �e�[�u���̃|�C���^

.ifdef	OPLL
	cpx	#nsd::TR_OPLL
	bcs	@OPLL
.endif

	ldx	#0			;8 byte table
	ldy	#0
@L:
	stx	VRC7_Resister		;��Resister Write
	lda	(__ptr),y		;[5]
	iny				;[2]
	sta	VRC7_Data		;��Data Write

	lda	(__ptr,x)		;[6]
	lda	(__ptr,x)		;[6]
	lda	(__ptr,x)		;[6]
	lda	(__ptr,x)		;[6]
	lda	(__ptr,x)		;[6]
	lda	(__ptr,x)		;[6]	36

	inx				;[2]
	cpx	#8			;[2]
	bne	@L			;[2]	6 + 36 = 42

	ldx	__channel
.endif
	jmp	Sequence


.ifdef	OPLL
@OPLL:
	ldx	#0			;8 byte table
	ldy	#0
@L2:
	stx	OPLL_Resister		;��Resister Write
	lda	(__ptr),y		;[5]
	iny				;[2]
	sta	OPLL_Data		;��Data Write

	lda	(__ptr,x)		;[6]
	lda	(__ptr,x)		;[6]
	lda	(__ptr,x)		;[6]
	lda	(__ptr,x)		;[6]
	lda	(__ptr,x)		;[6]
	lda	(__ptr,x)		;[6]	36

	inx				;[2]
	cpx	#8			;[2]
	bne	@L2			;[2]	6 + 36 = 42

	ldx	__channel

	jmp	Sequence
.endif

;=======================================================================
;		opcode	0x1D:	VRC7 : Set resister
;-----------------------------------------------------------------------
nsd_op1D:

	jsr	nsd_load_sequence

.ifdef	OPLL
	cpx	#nsd::TR_OPLL
	bcs	@OPLL
.endif

.ifdef	VRC7
	sta	VRC7_Resister
.endif
	jsr	nsd_load_sequence
.ifdef	VRC7
	sta	VRC7_Data
.endif
	jmp	Sequence

.ifdef	OPLL
@OPLL:
	sta	OPLL_Resister
	jsr	nsd_load_sequence
	sta	OPLL_Data
	jmp	Sequence
.endif

;=======================================================================
;		opcode	0x1E:	n163 : Set wave table
;-----------------------------------------------------------------------
nsd_op1E:
	jsr	nsd_load_sequence

.ifdef	N163
	shl	a, 1
	ora	#$80
	sta	N163_Resister
.endif

	jsr	nsd_load_ptr

.ifdef	N163
	lda	__ptr
	add	__tmp
	sta	__ptr

	lda	__ptr + 1
	adc	__tmp + 1
	sta	__ptr + 1		;__ptr �e�[�u���̃|�C���^

	ldy	#0
	lda	(__ptr),y
	iny
	tax				;x <- size of table
@L:
	lda	(__ptr),y
	iny
	sta	N163_Data

	dex
	bne	@L

	ldx	__channel

.endif
	jmp	Sequence

;=======================================================================
;		opcode	0x1F:	n163 : Set channel number
;-----------------------------------------------------------------------
nsd_op1F:
	jsr	nsd_load_sequence
.ifdef	N163
	shl	a, 4
	and	#$70
	sta	__n163_num
.endif
	jmp	Sequence

;=======================================================================
;		opcode	0x20:	Volume down (-1) 
;-----------------------------------------------------------------------
nsd_op20:
	lda	__volume,x
	and	#$0F
	beq	@L
	dec	__volume,x
@L:
	jmp	Sequence

;=======================================================================
;		opcode	0x21:	Volume up (+1) 
;-----------------------------------------------------------------------
nsd_op21:
	lda	__volume,x
	and	#$0F
	cmp	#$0F
	beq	@L
	inc	__volume,x
@L:
	jmp	Sequence

;=======================================================================
;		opcode	0x22:	FDS : Set career wave table
;-----------------------------------------------------------------------
nsd_op22:

	jsr	nsd_load_ptr

.ifdef	FDS
	lda	__ptr
	add	__tmp
	sta	__ptr

	lda	__ptr + 1
	adc	__tmp + 1
	sta	__ptr + 1		;__ptr �e�[�u���̃|�C���^

	lda	#$80
	sta	FDS_Write_Enable

	ldy	#0
@L:
	lda	(__ptr),y
	sta	FDS_Wave_Table,y
	iny
	cpy	#64
	bne	@L

	lda	__chflag,x
	and	#nsd_chflag::FDSVOL
	shr	a,2
	sta	FDS_Write_Enable
.endif
	jmp	Sequence

;=======================================================================
;		opcode	0x23:	FDS : Set modulator wave table
;-----------------------------------------------------------------------
nsd_op23:

	jsr	nsd_load_ptr

.ifdef	FDS
	lda	__ptr
	add	__tmp
	sta	__ptr

	lda	__ptr + 1
	adc	__tmp + 1
	sta	__ptr + 1		;__ptr �e�[�u���̃|�C���^

	lda	__fds_frequency
	ora	#$80
	sta	FDS_Mod_CTUNE

	ldy	#0
@L:
	lda	(__ptr),y
	sta	FDS_Mod_Append
	iny
	cpy	#32
	bne	@L

	lda	__fds_frequency
	sta	FDS_Mod_CTUNE
.endif
	jmp	Sequence

;=======================================================================
;		opcode	0x24:	FDS : Modulator frequency
;-----------------------------------------------------------------------
nsd_op24:

	jsr	nsd_load_sequence
.ifdef	FDS
	sta	FDS_Mod_FTUNE		;����
.endif

	jsr	nsd_load_sequence
.ifdef	FDS
	and	#$0F
	sta	FDS_Mod_CTUNE		;���
	sta	__fds_frequency
.endif

	jmp	Sequence

;=======================================================================
;		opcode	0x25:	FDS master volume
;-----------------------------------------------------------------------
nsd_op25:

.ifdef	FDS
	lda	__chflag,x
	and	#~nsd_chflag::FDSVOL
	sta	__tmp
.endif

	jsr	nsd_load_sequence

.ifdef	FDS
	and	#$03
	sta	FDS_Write_Enable
	shl	a,2
	ora	__tmp
	sta	__chflag,x
.endif

	jmp	Sequence

;=======================================================================
;		opcode	0x26:	 FME7: Envelope frequency
;-----------------------------------------------------------------------
nsd_op26:

.ifdef	PSG
	ldy	#PSG_Envelope_Low
	sty	PSG_Register
.endif

	jsr	nsd_load_sequence

.ifdef	PSG
	sta	PSG_Data
	iny
	sty	PSG_Register
.endif

	jsr	nsd_load_sequence
	
.ifdef	PSG
	sta	PSG_Data
.endif

nsd_op27:
	jmp	Sequence

;=======================================================================
;		opcode	0x2A:	Transpose (an absolute value) 
;-----------------------------------------------------------------------
nsd_op2A:
	jsr	nsd_load_sequence
nsd_Set_Trans:
	sta	__trans,x
	jmp	Sequence

;=======================================================================
;		opcode	0x2B:	Transpose (a relative value) 
;-----------------------------------------------------------------------
nsd_op2B:
	jsr	nsd_load_sequence
	add	__trans,x
	jmp	nsd_Set_Trans

;=======================================================================
;		opcode	0x2C:	One time octave down (-1) 
;-----------------------------------------------------------------------
nsd_op2C:
	lda	#-12
	bne	nsd_Set_Trans_One
;=======================================================================
;		opcode	0x2D:	One time octave up (+1) 
;-----------------------------------------------------------------------
nsd_op2D:
	lda	#+12
	bne	nsd_Set_Trans_One
;=======================================================================
;		opcode	0x2E:	One time transpose (a relative value) 
;-----------------------------------------------------------------------
nsd_op2E:
	jsr	nsd_load_sequence
nsd_Set_Trans_One:
	add	__trans_one,x
	sta	__trans_one,x
nsd_op2F:
	jmp	Sequence

;=======================================================================
;		opcode	0x30 - 0x37:	Voice of release (after key-off) 
;-----------------------------------------------------------------------
nsd_op30:
	lda	#$00
nsd_Set_Voice:
	sta	__tmp
	lda	__voice,x
	and	#$0F
	ora	__tmp
	sta	__voice,x
	jmp	Sequence

nsd_op31:
	lda	#$10
	bne	nsd_Set_Voice

nsd_op32:
	lda	#$20
	bne	nsd_Set_Voice

nsd_op33:
	lda	#$30
	bne	nsd_Set_Voice

nsd_op34:
	lda	#$40
	bne	nsd_Set_Voice

nsd_op35:
	lda	#$50
	bne	nsd_Set_Voice

nsd_op36:
	lda	#$60
	bne	nsd_Set_Voice

nsd_op37:
	lda	#$70
	bne	nsd_Set_Voice

;=======================================================================
;		opcode	0x29:	Octave up (+1) 
;-----------------------------------------------------------------------
nsd_op29:
	lda	__octave,x
	add	#12
	bpl	nsd_Set_Octave
	jmp	Sequence

;=======================================================================
;		opcode	0x28:	Octave down (-1) 
;-----------------------------------------------------------------------
nsd_op28:
	lda	__octave,x
	sub	#12
	bmi	nsd_op28_Exit
nsd_Set_Octave:
	sta	__octave,x
nsd_op28_Exit:
	jmp	Sequence

;=======================================================================
;		opcode	0x38 - 0x3F:	Octave
;-----------------------------------------------------------------------
nsd_op38:
	lda	#12
	bne	nsd_Set_Octave

nsd_op39:
	lda	#24
	bne	nsd_Set_Octave

nsd_op3A:
	lda	#36
	bne	nsd_Set_Octave

nsd_op3B:
	lda	#48
	bne	nsd_Set_Octave

nsd_op3C:
	lda	#60
	bne	nsd_Set_Octave

nsd_op3D:
	lda	#72
	bne	nsd_Set_Octave

nsd_op3E:
	lda	#84
	bne	nsd_Set_Octave

nsd_op3F:
	lda	#96
	bne	nsd_Set_Octave

.endproc
