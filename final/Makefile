.SUFFIXES: .$(EXT) .asm .obj .exe
LANG=minor
EXT=minor
LIB=lib
RUN=run
AS=nasm -felf32
ARCH=-DpfARM
CC=gcc
CFLAGS=-g -DYYDEBUG $(ARCH)


$(LANG): $(LANG).y $(LANG).l $(LANG).brg
	make -C lib
	byacc -dv $(LANG).y
	flex -l $(LANG).l
	pburg -T $(LANG).brg
#$(LINK.c) -o $(LANG) -I$(LIB) lex.yy.c y.tab.c yyselect.c -L$(LIB) -lutil
	$(CC) $(CFLAGS) -o $(LANG) -I$(LIB) lex.yy.c y.tab.c yyselect.c $(LIB)/*.o 
clean::
	rm -f *.o $(LANG) lex.yy.c y.tab.c y.tab.h y.output yyselect.c *.asm *~ *.obj *.exe 
	rm -rf *.dSYM
