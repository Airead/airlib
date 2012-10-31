#ifndef _DEBUG_H_
#define _DEBUG_H_

/*
 * Macros to help debugging
 */

#ifdef _AIR_DEBUG_
#  define DEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#else
#  define DEBUG(fmt, args...) /* not debugging: nothing */
#endif

#endif /* _DEBUG_H_ */
