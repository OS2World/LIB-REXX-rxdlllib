/* Test REXX DLL Kit Jan Lambert*/
num=''
tt='ABCDEFGHIJKLMNOPQRSTUVWXYZ'

parse arg num      /*get the number of arguments to pass*/
num=strip(num)
if num='' | \datatype(num,'w') then do
	say 'Usage: ckrxdll #'
	say '# is the number of arguments to pass to the DLL'
	say 'Default arguments are the argument# raised to the 6th power'
	say 'The template expects 5 arguments. eg. ckrxdll 5'
	say 'It returns the # of arguments followed by the length of each argument'
	exit
end


single=0

say "single=default, 1=loadfuncs call  ?"
nl=linein()
if strip(nl)='' then single =1

/* Register the external function */
if single then do
	if \rxfuncquery("RxDllFunc1") then  rc= rxfuncdrop("RxDllFunc1") /*get rid of old versions*/
	if rxfuncquery("RxDllFunc1") then rc= rxfuncadd( "RxDllFunc1", "RXDLL", "RxDllFunc1")
end
else do
	if \rxfuncquery("RxDllDropFuncs") then  rc= rxDllDropfuncs() /*get rid of old versions*/
	if rxfuncquery("RxDllFunc1") then do
		rc= rxfuncadd( "RxDllLoadFuncs", "RXDLL","RxDllLoadFuncs")
		rc=RxDllLoadFuncs()
	end
end

cmd='rc= RxDllFunc1('
do i=1 to num             /*make some arguments*/
	cmd=cmd||i**6||','
end
cmd=strip(cmd,'t',',')||')'
say 'Call:' cmd
interpret cmd
say 'Return length='length(rc)
say 'Return=' rc
say 'Waiting: Funcion(s) still loaded'
nl=linein()
if single then rc= rxfuncdrop("RxDllFunc1")
else rc=RxDllDropFuncs()

exit

