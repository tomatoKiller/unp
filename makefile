udpservselect01 : 
	gcc udpcliserv/udpservselect01.c wrapped.c lib/* -o build/udpservselect01

hostent :
	gcc names/hostent.c wrapped.c lib/* -o build/hostent 
	
daytimetcpcli1: names/daytimetcpcli1.c
	gcc names/daytimetcpcli1.c wrapped.c lib/* -o build/daytimetcpcli1

daytimetcpsrv3: inetd/daytimetcpsrv3.c
	gcc inetd/daytimetcpsrv3.c wrapped.c lib/* -o build/daytimetcpsrv3

clean :
	rm build/*
