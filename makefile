udpservselect01 : 
	gcc udpcliserv/udpservselect01.c wrapped.c lib/* -o build/udpservselect01

hostent :
	gcc names/hostent.c wrapped.c lib/* -o build/hostent 
	
daytimetcpcli1: names/daytimetcpcli1.c
	gcc names/daytimetcpcli1.c wrapped.c lib/* -o build/daytimetcpcli1

daytimetcpsrv3: inetd/daytimetcpsrv3.c
	gcc inetd/daytimetcpsrv3.c wrapped.c lib/* -o build/daytimetcpsrv3

unixbind: unixdomain/unixbind.c
	gcc unixdomain/unixbind.c wrapped.c lib/* -o build/unixbind
	
openfile: unixdomain/openfile.c
	gcc unixdomain/openfile.c wrapped.c lib/* -o build/openfile

mycat: unixdomain/mycat.c
	gcc unixdomain/mycat.c unixdomain/myopen.c wrapped.c lib/* -o build/mycat

strclinonb: nonblock/strclinonb.c
	gcc nonblock/strclinonb.c  wrapped.c lib/* -o build/strclinonb
clean :
	rm build/*
