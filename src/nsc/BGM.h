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
	BGM(MMLfile* MML, const char _strName[] = "==== [ BGM ]====");
	~BGM(void);
};
