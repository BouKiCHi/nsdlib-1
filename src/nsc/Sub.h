// �ÓI���f��

#ifndef __SUB__
#define __SUB__

// Include files
#include "MMLfile.h"
#include "TrackSet.h"
/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class Sub : public TrackSet
{

public:

	Sub(MMLfile* MML, unsigned int _id, char _strName[] = "==== [ Sub ]====");
	~Sub();
	void	getAsm(MusicFile* MUS);

};// END CLASS DEFINITION Sub

#endif // __SUB__
