#pragma once

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class MusicHeader
{
//�����o�[�ϐ�
public:
	unsigned	char	iBGM;
	unsigned	char	iSE;
	unsigned	int		offsetPCM;
				bool	op_code;		//option �� code �w�肳�ꂽ�H
				string	Label;
				string	title;
				string	copyright;
				string	composer;
				string	segmentSEQ;
				string	segmentPCM;
				string	romcode;
//�����o�[�֐�
public:
				MusicHeader(MMLfile* MML, string _code);
				~MusicHeader(void);
		void	Set_Title(MMLfile* MML);
		void	Set_Copyright(MMLfile* MML);
		void	Set_Composer(MMLfile* MML);
		void	Set_SegmentSEQ(MMLfile* MML);
		void	Set_SegmentPCM(MMLfile* MML);
		void	Set_Label(MMLfile* MML);
		void	Set_OffsetPCM(MMLfile* MML);
		void	Set_RomCode(MMLfile* MML);
		void	Set_Number_BGM(MMLfile* MML);
		void	Set_Number_SE(MMLfile* MML);
};
