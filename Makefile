sandbox: ccsandbox
	./Sandbox
sort: ccSort
	./Sort
hw: cchw
	./HelloWorld
collatz: ccCollatz
	./Collatz
maxOccurences: ccmaxOccurences
	./MaxOccurences

ccsandbox:
	gcc Sandbox.c -o Sandbox
ccSort:
	gcc Sort.c -o Sort
cchw:
	gcc HelloWorld.c -o HelloWorld
ccCollatz:
	gcc Collatz.c -o Collatz
ccmaxOccurences:
	gcc MaxOccurences.c -o MaxOccurences
