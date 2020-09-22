sandbox: ccsandbox
	./Sandbox
hw: cchw
	./HelloWorld
collatz: ccCollatz
	./Collatz

ccsandbox:
	gcc Sandbox.c -o Sandbox
cchw:
	gcc HelloWorld.c -o HelloWorld
ccCollatz:
	gcc Collatz.c -o Collatz
