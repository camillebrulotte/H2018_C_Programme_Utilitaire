ASFLAGS = -std=c99

PROGS = info_systeme

all:
	make clean
	make $(PROGS)

clean:
	rm -f $(PROGS) 2> /dev/null

info_systeme:
	gcc $(ASFLAGS) -o info_systeme info_systeme.c utils.c
