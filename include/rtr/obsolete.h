
#ifdef RTDEBUG
#ifdef RTR_OBSOLETE
#include  <stream.h>

#ifndef _RDEV_NO_STL_
#define RTROBSOLETE(s) cout<<"Warning:Call to obsolete method at line "\
						   <<__LINE__<<" in "<<__FILE__\
						   <<".\n\tUse method "<<s<<" instead."\
						   <<endl
#endif
#else

#define RTROBSOLETE(s)

#endif

#else

#define RTROBSOLETE(s)

#endif
