all: dirinfo.c
	gcc dirinfo.c

run: all
	./a.out

clean:
	rm a.out
