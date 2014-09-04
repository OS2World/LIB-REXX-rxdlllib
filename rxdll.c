//Filename: RXDLL.C
//Rexx DLL template for the C-Challenged
//C-Challenged author: Jan Lambert  2007
//License: Freeware
//Requirements: Open Watcom C/C++ ver 1.6
//Warrentee: If good, i did it; if bad, i deny any knowledge of this package.
//Credits: Jorge Martins article: Building a REXX DLL in C, EDM/2
//         IBM/RexxLA.org: rxMath.c used as an example for Load/DropFuncs

#include <stdio.h>      /*useful stuff*/
#include <string.h>
#include <stdlib.h>

#include <rexxsaa.h>    /*Required!*/
#include "rxdll.h"      /*header file for this module*/


/* ------- Single call Initialization and termination routines --------*/
/* This block can be deleted if individual rxfuncadd/drop calls are used */

#define LFUNC_OK  "0"       /*load/drop returns*/
#define LFUNC_FAILED  "1"

static PCSZ  RxFuncTbl[] = {
	"RxDll",
	"RxDllLoadFuncs",
	"RxDllFunc1",      /*list of user functions*/
	"RxDllDropFuncs"   /*last function dropped*/
};

ULONG RxDllLoadFuncs(CHAR *name,  /* Initialization Routine */
               ULONG numargs,      /* Number of arguments */
               RXSTRING args[],    /* Null-terminated RXSTRINGs array*/
               CHAR *queuename,    /* Current external data queue name */
               RXSTRING *retstr)   /* returning RXSTRING  */
	{
	USHORT    i,j,k;
	USHORT    F,D;
	USHORT    FuncCnt;    /* Num of functions  */

	if (numargs > 0) {             /* check arguments:if any, something bad may be happening */
		strlcpy(retstr->strptr,LFUNC_FAILED,255);
		retstr->strlength = strlen(retstr->strptr);
		return FUNC_FAILED;
	}

	FuncCnt = sizeof(RxFuncTbl)/sizeof(PCSZ);
	for (j = 1; j < FuncCnt; j++) {
		RexxRegisterFunctionDll(RxFuncTbl[j],RxFuncTbl[0], RxFuncTbl[j]);
	}

	/* Put user initialization here : onetime memory allocations etc*/

	strlcpy(retstr->strptr,LFUNC_OK,255);
	retstr->strlength = strlen(retstr->strptr);
	return FUNC_OK;
}

ULONG RxDllDropFuncs(CHAR *name,  /* Termination Routine */
               ULONG numargs,      /* Number of arguments */
               RXSTRING args[],    /* Null-terminated RXSTRINGs array*/
               CHAR *queuename,    /* Current external data queue name */
               RXSTRING *retstr)   /* returning RXSTRING  */
	{
	USHORT    i,j,k;
	USHORT    FuncCnt;             /* Num of functions  */

	if (numargs > 0) {            /* check arguments:if any, something bad may be happening */
		strlcpy(retstr->strptr,LFUNC_FAILED,255);
		retstr->strlength = strlen(retstr->strptr);
		return FUNC_FAILED;
	}

	FuncCnt = sizeof(RxFuncTbl)/sizeof(PCSZ);
	for (j = 1; j < FuncCnt; j++) {
		RexxDeregisterFunction(RxFuncTbl[j]);
	}

	/*put user exit functions here: be sure to release any onetime memory you allocated*/

	strlcpy(retstr->strptr,LFUNC_OK,255);
	retstr->strlength = strlen(retstr->strptr);
	return FUNC_OK;
}

/*-----------  User Functions --------------- */

ULONG RxDllFunc1(CHAR *name,      /* User Routine name */
	ULONG numargs,      /* Number of arguments */
	RXSTRING args[],    /* Null-terminated RXSTRINGs array*/
	CHAR *queuename,    /* Current external data queue name */
	RXSTRING *retstr)   /* return RXSTRING  */
{
	CHAR string[255];    /*local scratch buffers*/
	CHAR buff[255];
	ULONG i,j,k;         /*local counters*/

/* Example Function: accessing arguments */
/* This function returns # of args passed and the length of each argument*/

#ifdef ArgCount1  /*if defined, check for correct # of arguments*/
	if (numargs != ArgCount1) { return FUNC_FAILED;}  /*return error code(40) if bad*/
#endif
	ultoa(numargs,string,10);            /*number of arguments passed*/
	i = 0;
	while (i<numargs){                   /*step thru arguments*/
		strlcat(string," ",sizeof(string));          /*spacer*/
		if (RXNULLSTRING(args[i])) { strcat(string,"N");} /*null arg, return N*/
		else {
			if (RXZEROLENSTRING(args[i])) { strlcat(string,"0",sizeof(string));}              /*null string, return 0*/
			else {                                                                            /*non-null string passed*/

				/*accesse the actual parameter and protects the buffer from overrun*/
				strlcpy(buff,args[i].strptr,min(args[i].strlength+1,sizeof(buff)));       /* copy to buff as a C-string*/

				/*convert the arg length to a string and append to the buffer*/
				utoa(args[i].strlength,buff,10); strlcat(string,buff,sizeof(string));     /*return size: note: buff gets wacked!*/
			}
		}
		i++;    /*next arg*/
	}
	strlcpy(retstr->strptr,string,255);            /*trim string if over default return string length*/
	retstr->strlength = strlen(retstr->strptr);    /*return actual length*/
	return FUNC_OK;                                /*successful return code(0)*/
}
