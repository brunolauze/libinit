
#ifndef __MAIN_H__
#define __MAIN_H__

#define SPACE " "

#define INIT_PROVIDE "init"

#define ABI 				"abi"
#define ACCOUNTING 			"accounting"


#define GLOBAL_DEFINE { ABI, \
						ACCOUNTING, \
						NULL }

char **provide();

#endif

