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

	Sub(MMLfile* MML, char _strName[] = "==== [ Sub ]====");

	~Sub();

};// END CLASS DEFINITION Sub

#endif // __SUB__
