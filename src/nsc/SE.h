// �ÓI���f��


#ifndef __SE__
#define __SE__


// Include files
#include "MMLfile.h"
#include "TrackSet.h"
/****************************************************************/
/*																*/
/*			�N���X��`											*/
/*																*/
/****************************************************************/
class SE : public TrackSet
{

public:

	SE(MMLfile* MML,	 char _strName[] = "==== [ SE ]====");

	~SE();

};// END CLASS DEFINITION SE

#endif // __SE__
