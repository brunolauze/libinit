
#ifndef __GLOBAL_DEFINED_H
#define __GLOBAL_DEFINED_H
#include "util.h"
#endif

#ifndef PROVIDE
#error "PROVIDE is not defined"
#endif

#ifndef NAME
#define NAME S(PROVIDE)
#endif

#ifndef REQUIRE 
#error "REQUIRE is not defined"
#endif

#ifndef BEFORE 
#define BEFORE { NULL }
#endif

#ifndef KEYWORD
#define KEYWORD { NULL }
#endif

#if 0

#else
#define CANSTART_SUFFIX canstart
#define PRESTART_SUFFIX prestart
#define START_SUFFIX start
#define STOP_SUFFIX stop
#define STATUS_SUFFIX status
#define RELOAD_SUFFIX reload
#define PROVIDE_SUFFIX provide
#define REQUIRE_SUFFIX require
#define BEFORE_SUFFIX before
#define KEYWORD_SUFFIX keyword
#define SANITY_SUFFIX sanity
#define LISTCMD_SUFFIX listcmd
#define PROVIDE_FUNC CAT3(PROVIDE, _, PROVIDE_SUFFIX)
#define REQUIRE_FUNC CAT3(PROVIDE, _, REQUIRE_SUFFIX)
#define BEFORE_FUNC CAT3(PROVIDE, _, BEFORE_SUFFIX)
#define KEYWORD_FUNC CAT3(PROVIDE, _, KEYWORD_SUFFIX)
#define CANSTART_FUNC CAT3(PROVIDE, _, CANSTART_SUFFIX)
#define PRESTART_FUNC CAT3(PROVIDE, _, PRESTART_SUFFIX)
#define START_FUNC CAT3(PROVIDE, _, START_SUFFIX)
#define STOP_FUNC CAT3(PROVIDE, _, STOP_SUFFIX)
#define STATUS_FUNC CAT3(PROVIDE, _, STATUS_SUFFIX)
#define RELOAD_FUNC CAT3(PROVIDE, _, RELOAD_SUFFIX)
#define SANITY_FUNC CAT3(PROVIDE, _, SANITY_SUFFIX)
#define LISTCMD_FUNC CAT3(PROVIDE, _, LISTCMD_SUFFIX)


#define ENABLE_SUFFIX _enable
#define DEFAULT_START_VARIABLE	S(CAT2(PROVIDE,ENABLE_SUFFIX))
#endif

const char * 	PROVIDE_FUNC();
char **		 	REQUIRE_FUNC();
char ** 		BEFORE_FUNC();
char ** 		KEYWORD_FUNC();
int 			CANSTART_FUNC();
int 			PRESTART_FUNC();
int 			START_FUNC();
int 			STOP_FUNC();
int 			STATUS_FUNC();
int 			RELOAD_FUNC();
int 			SANITY_FUNC();
int				LISTCMD_FUNC();





