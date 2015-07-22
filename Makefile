
cmdline.o: cmdline.c cmdline.h
	gcc -Wall -W -ggdb -c cmdline.c

stub: stub.c cmdline.o
	gcc -Wall -W -o $@ $^

fstub: fstub.c cmdline.o
	gcc -Wall -W -o $@ $^

test: stub
	./pace
	echo ok

clean:
	rm -f cmdline.o stub stub.o tests/pace.out
