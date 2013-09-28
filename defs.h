#ifndef _DEFS_H_
#define _DEFS_H_

#define F_VERBOSE 0001 
#define F_DEBUG   0002
#define F_QUIET   0004

#define VERBOSE (f_flags & F_VERBOSE)
#define DEBUG   (f_flags & F_DEBUG)
#define QUIET   (f_flags & F_QUIET)

#endif
