#pragma once
#include "trackset.h"

/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class BGM :
	public TrackSet
{
public:
	BGM(MMLfile* MML, unsigned int _id, const wchar_t _strName[] = L"BGM");
	~BGM(void);
	void	getAsm(MusicFile* MUS);
};
