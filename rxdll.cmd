/* Test second access to REXX DLL Kit Jan Lambert*/
num=''
tt='ABCDEFGHIJKLMNOPQRSTUVWXYZ'
f.=''
f.0=3
f.1="RxDllLoadFuncs"
f.2="RxDllDropFuncs"
f.3="RxDllFunc1"
do i=1 to f.0
	if rxfuncquery(f.i) then say f.i "not loaded"
	else say f.i "is loaded"
end
if \rxfuncquery(f.3) then do
	parse arg num
	mum=strip(num)
	if num='' then num=5
	cmd='rc= RxDllFunc1('
	do i=1 to num             /*make some arguments*/
		cmd=cmd||i**7||','
	end
	cmd=strip(cmd,'t',',')||')'
	say 'Call:' cmd
	say "Execute? Y/N"
	nl=translate(strip(linein()))
	if pos('Y',nl)=0 then exit
	interpret cmd
	say 'Returned:' rc
end

exit

