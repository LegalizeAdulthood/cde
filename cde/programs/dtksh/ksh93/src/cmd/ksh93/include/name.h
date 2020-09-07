/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these libraries and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* $XConsortium: name.h /main/3 1995/11/01 16:41:17 rswiston $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*        THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF        *
*                    AT&T BELL LABORATORIES                    *
*         AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN         *
*            ACCORDANCE WITH APPLICABLE AGREEMENTS             *
*                                                              *
*                Copyright (c) 1995 AT&T Corp.                 *
*              Unpublished & Not for Publication               *
*                     All Rights Reserved                      *
*                                                              *
*       The copyright notice above does not evidence any       *
*      actual or intended publication of such source code      *
*                                                              *
*               This software was created by the               *
*           Advanced Software Technology Department            *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                    {research,attmail}!dgk                    *
*                                                              *
***************************************************************/

/* : : generated by proto : : */
                  
#ifndef _NV_PRIVATE
#if !defined(__PROTO__)
#if defined(__STDC__) || defined(__cplusplus) || defined(_proto) || defined(c_plusplus)
#if defined(__cplusplus)
#define __MANGLE__	"C"
#else
#define __MANGLE__
#endif
#define __STDARG__
#define __PROTO__(x)	x
#define __OTORP__(x)
#define __PARAM__(n,o)	n
#if !defined(__STDC__) && !defined(__cplusplus)
#if !defined(c_plusplus)
#define const
#endif
#define signed
#define void		int
#define volatile
#define __V_		char
#else
#define __V_		void
#endif
#else
#define __PROTO__(x)	()
#define __OTORP__(x)	x
#define __PARAM__(n,o)	o
#define __MANGLE__
#define __V_		char
#define const
#define signed
#define void		int
#define volatile
#endif
#if defined(__cplusplus) || defined(c_plusplus)
#define __VARARG__	...
#else
#define __VARARG__
#endif
#if defined(__STDARG__)
#define __VA_START__(p,a)	va_start(p,a)
#else
#define __VA_START__(p,a)	va_start(p)
#endif
#endif

/*
 * This is the implementation header file for name-value pairs
 */

#define _NV_PRIVATE	\
	union Value	nvalue; 	/* value field */ \
	char		*nvenv;		/* pointer to environment name */ \
	Namfun_t	*nvfun;		/* pointer to trap functions */

#include	<ast.h>
#include	"shtable.h"

/* Nodes can have all kinds of values */
union Value
{
	const char	*cp;
	int		*ip;
	char		c;
	int		i;
	unsigned	u;
	long		*lp;
	short		s;
	double		*dp;	/* for floating point arithmetic */
	struct Namarray	*array;	/* for array node */
	struct Namval	*np;	/* for Namval_t node */
	union Value	*up;	/* for indirect node */
	struct Ufunction *rp;	/* shell user defined functions */
	int (*bfp) __PROTO__((int,char*[],__V_*));/* builtin entry point function pointer */
};

#include	"nval.h"

/* used for arrays */
#define ARRAY_MASK	((1L<<ARRAY_BITS)-1)	/* For index values */

#define ARRAY_MAX 	4096	/* maximum number of elements in an array
				   This must be less than ARRAY_MASK */
#define ARRAY_INCR	16	/* number of elements to grow when array 
				   bound exceeded.  Must be a power of 2 */

/* These flags are used as options to array_get() */
#define ARRAY_ASSIGN	0
#define ARRAY_LOOKUP	1
#define ARRAY_DELETE	2


/* This describes a user shell function node */
struct Ufunction
{
	int	*ptree;			/* address of parse tree */
	int	lineno;			/* line number of function start */
	off_t	hoffset;		/* offset into history file */
};

/* attributes of Namval_t items */

/* The following attributes are for internal use */
#define NV_IMPORT	NV_NOADD	/* value imported from environment */
#define NV_FUNCT	NV_IDENT	/* node value points to function */
#define NV_NOCHANGE	(NV_EXPORT|NV_IMPORT|NV_RDONLY|NV_TAGGED|NV_NOFREE)
#define NV_ATTRIBUTES	(~(NV_NOSCOPE|NV_ARRAY|NV_IDENT|NV_ASSIGN|NV_REF|NV_VARNAME))
#define NV_HOST		(NV_RJUST|NV_LJUST)
#define NV_PARAM	(1<<12)		/* expansion use positional params */

/* This following are for use with nodes which are not name-values */
#define NV_FUNCTION	(NV_RJUST|NV_FUNCT)	/* value is shell function */
#define NV_FPOSIX	NV_LJUST		/* posix function semantics */

#define NV_NOPRINT	(NV_LTOU|NV_UTOL)	/* do not print */
#define NV_NOALIAS	(NV_NOPRINT|NV_IMPORT)
#define NV_NOEXPAND	NV_RJUST		/* do not expand alias */
#define NV_BLTIN	(NV_NOPRINT|NV_EXPORT)
#define BLT_ENV		(NV_RDONLY)		/* non-stoppable,
						 * can modify environment */
#define BLT_SPC		(NV_LJUST)		/* special built-ins */
#define BLT_EXIT	(NV_RJUST)		/* exit value can be > 255 */
#define BLT_DCL		(NV_TAGGED)		/* declaration command */
#define is_abuiltin(n)	(nv_isattr(n,NV_BLTIN)==NV_BLTIN)
#define is_afunction(n)	(nv_isattr(n,NV_FUNCTION)==NV_FUNCTION)
#define	nv_funtree(n)	((n)->nvalue.rp->ptree)
#define	funptr(n)	((n)->nvalue.bfp)


/* NAMNOD MACROS */
#define nv_link(root,n)		hashlook((Hashtab_t*)(root),(char*)(n),\
					HASH_INSTALL,(char*)sizeof(Namval_t))
/* ... for attributes */

#define nv_onattr(n,f)	((n)->nvflag |= (f))
#define nv_setattr(n,f)	((n)->nvflag = (f))
#define nv_offattr(n,f)	((n)->nvflag &= ~(f))
/* ... etc */

#define nv_setsize(n,s)	((n)->nvsize = ((s)&0xfff))

/* ...	for arrays */

#define nv_arrayptr(np)	(nv_isattr(np,NV_ARRAY)?(np)->nvalue.array:(Namarr_t*)0)
#define array_elem(ap)	((ap)->nelem&ARRAY_MASK)
#define array_assoc(ap)	((ap)->fun)

extern __MANGLE__ void		array_check __PROTO__((Namval_t*, int));
extern __MANGLE__ union Value	*array_find __PROTO__((Namval_t*, int));
extern __MANGLE__ char 		*nv_endsubscript __PROTO__((Namval_t*, char*, int));
extern __MANGLE__ Namfun_t 	*nv_cover __PROTO__((Namval_t*));
struct argnod;		/* struct not declared yet */
extern __MANGLE__ void		nv_setlist __PROTO__((struct argnod*, int));
extern __MANGLE__ void 		nv_scope __PROTO__((struct argnod*));

extern __MANGLE__ const char	e_subscript[];
extern __MANGLE__ const char	e_nullset[];
extern __MANGLE__ const char	e_notset[];
extern __MANGLE__ const char	e_noparent[];
extern __MANGLE__ const char	e_readonly[];
extern __MANGLE__ const char	e_badfield[];
extern __MANGLE__ const char	e_restricted[];
extern __MANGLE__ const char	e_ident[];
extern __MANGLE__ const char	e_varname[];
extern __MANGLE__ const char	e_funname[];
extern __MANGLE__ const char	e_intbase[];
extern __MANGLE__ const char	e_noalias[];
extern __MANGLE__ const char	e_aliname[];
extern __MANGLE__ const char	e_badexport[];
extern __MANGLE__ const char	e_badref[];
extern __MANGLE__ const char	e_noref[];
extern __MANGLE__ const char	e_selfref[];
extern __MANGLE__ const char	e_envmarker[];
extern __MANGLE__ const char	e_badlocale[];
extern __MANGLE__ const char	e_loop[];
#endif /* _NV_PRIVATE */