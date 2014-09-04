Rexx DLL Kit for the C-Challenged   18:22:16Z  27 Jan 2007

This is a simple template to create OS/2 rexx/Object Rexx extension
functions using the Open Watcom C compiler. The basic outline is from
Jorge Martins' EDM/2 article: Building a REXX DLL in C. The multifunction
rxDllLoad/Drop functions are modeled on the IBM/OORexx rxMath.c source.
It is buildable under version 1.6 and has been tested on Warp 4.5 with
Object Rexx. Error checking is not rigorous!

It ain't pretty. I was hopeing to get thru life without writing a
program in C, but i need a faster way to do some complex math,
so this was the easiest route. There is a simple function to return
the number of arguments and the length of each.

compile:  wcc386 -bd rxdll
link:     wlink @rxdll

ckrxdll.cmd is a simple developement test for the enclosed dll.
rxdll.cmd checks if the functions have been loaded, and calls
rxDllFunc1 if desired. This was for debugging the linker
global vs instance init options.

test:
chkrxdll #(small number)
asks if single(load only Func1) or multi(use LoadFuncs)
prints: (with #=5)
	Return length=11
	Return= 5 1 2 3 4 5
	Waiting: Funcion(s) still loaded

rxdll.cmd # can now be used to check multi-instance execution.



jan lambert
snapdrgn@cruzio.com  SUBJECT: rxdll.kit

