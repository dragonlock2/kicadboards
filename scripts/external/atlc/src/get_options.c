/* atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either package_version 2
of the License, or (at your option) any later package_version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
USA.

Dr. David Kirkby, e-mail drkirkby at gmail.com 

*/


/*
 * Here's something you've all been waiting for:  the AT&T public domain
 * source for getopt(3).  It is the code which was given out at the 1985
 * UNIFORUM conference in Dallas.  I obtained it by electronic mail
 * directly from AT&T.  The people there assure me that it is indeed
 * in the public domain.
 * 
 * There is no manual page.  That is because the one they gave out at
 * UNIFORUM was slightly different from the current System V Release 2
 * manual page.  The difference apparently involved a note about the
 * famous rules 5 and 6, recommending using white space between an option
 * and its first argument, and not grouping options that have arguments.
 * Getopt itself is currently lenient about both of these things White
 * space is allowed, but not mandatory, and the last option in a group can
 * have an argument.  That particular package_version of the man page evidently
 * has no official existence, and my source at AT&T did not send a copy.
 * The current SVR2 man page reflects the actual behavor of this getopt.
 * However, I am not about to post a copy of anything licensed by AT&T.
 */

#include "config.h"

#include "definitions.h"

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

/*LINTLIBRARY*/
#ifndef NULL
#define NULL    0
#endif
#define EOF     (-1)


int     my_opterr = 1;
int     my_optind = 1;
int     my_optopt;
char    *my_optarg;

void ERR(const char *s, char c, char **argv)  
{
	if(my_opterr)
	{
		char errbuf[2];
		errbuf[0] = c;
		errbuf[1] = '\n';
		/* (void) write(2, argv[0], (unsigned)strlen(argv[0]));
		(void) write(2, s, (unsigned)strlen(s));
		(void) write(2, errbuf, 2); */
		(void) fwrite(argv[0], (unsigned)strlen(argv[0]),1,stderr);
		(void) fwrite(s, (unsigned)strlen(s),1,stderr);
		(void) fwrite(errbuf, 2, 1,stderr); 
	}
}

char *index2(const char *str, char c)
{
	char *ret;
	ret=strchr((char *) str,c);
	return(ret);
}


int get_options(int argc, char **argv, const char *opts)
{
	static int sp = 1;
	/* register int c;
	 register char *cp; */
        int c;
        char tmp;
	char *cp;
        cp=&tmp;

	if(sp == 1)
	{
		if(my_optind >= argc ||
		   argv[my_optind][0] != '-' || argv[my_optind][1] == '\0')
			return(EOF);
		else if(strcmp(argv[my_optind], "--") == 0) {
			my_optind++;
			return(EOF);
		}
        }
	my_optopt = c = argv[my_optind][sp];
	if(c == ':' || (cp=index2((char *) opts, c)) == NULL) {
		ERR(": illegal option -- ", c,argv);
		if(argv[my_optind][++sp] == '\0') {
			my_optind++;
			sp = 1;
		}
		return('?');
	}
	if(*++cp == ':') {
		if(argv[my_optind][sp+1] != '\0')
			my_optarg = &argv[my_optind++][sp+1];
		else if(++my_optind >= argc) {
			ERR(": option requires an argument -- ", c,argv);
			sp = 1;
			return('?');
		} else
			my_optarg = argv[my_optind++];
		sp = 1;
	} else {
		if(argv[my_optind][++sp] == '\0') {
			sp = 1;
			my_optind++;
		}
		my_optarg = NULL;
	}
	return(c);
}
