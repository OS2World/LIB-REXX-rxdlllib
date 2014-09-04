#define  FUNC_FAILED   40            /*Rexx internal return codes*/
#define  FUNC_OK        0

RexxFunctionHandler RxDllLoadFuncs;  /*Block function registration for multifuncion dlls*/
RexxFunctionHandler RxDllDropFuncs;  /*Delete if not used*/

//#define  ArgCount1       5           /*OPTIONAL: Func1 number of arguments expected*/
RexxFunctionHandler RxDllFunc1;      /*User functions: add to RxFuncTbl in RxDll.c  */
                                     /* add to EXPORTs in RxDll.lnk*/

