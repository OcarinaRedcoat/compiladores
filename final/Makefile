.SUFFIXES: .$(EXT) .asm .obj .exe
LANG=minor
EXT=minor
LIB=lib
RUN=run
AS=nasm -felf32
ARCH=-DpfI386
CC=gcc
CFLAGS=-g -DYYDEBUG $(ARCH)
LD=ld -m elf_i386

$(LANG): $(LANG).y $(LANG).l $(LANG).brg
	make -C lib
	byacc -dv $(LANG).y
	flex -l $(LANG).l
	pburg -T $(LANG).brg
	$(CC) $(CFLAGS) -o $(LANG) -I$(LIB) lex.yy.c y.tab.c yyselect.c $(LIB)/*.o 
	make -C $(RUN)
	-cp $(RUN)/libminor.a libminor.a


run: run.asm $(LANG)
	$(AS) run.asm -o run.o
	$(LD) run.o libminor.a -o run
	./run


clean::
	rm -f *.o $(LANG) lex.yy.c y.tab.c y.tab.h y.output yyselect.c exs/*.asm *~ *.obj *.exe 
	rm -rf *.dSYM
