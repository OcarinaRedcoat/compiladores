LANG=minor
EXT=min# file extension: .$(EXT)
LIB=lib# compiler library directory
UTIL=util# compiler library: lib$(LIB).a
MINRUN=min_run# runtime directory
RUN=run# runtime directory
EXS=exs# examples directory
CC=gcc
CFLAGS= -g -DYYDEBUG -DpfI386
AS=nasm -felf32
LD=ld -m elf_i386
LDLIBS=lib$(LANG).a

$(LANG): $(LANG).y $(LANG).l $(LANG).brg
	make -C $(LIB)
	byacc -dv $(LANG).y
	flex -dl $(LANG).l
	pburg -T $(LANG).brg
	$(LINK.c) -w -g -o $(LANG) $(ARCH) -I$(LIB) lex.yy.c y.tab.c yyselect.c -L$(LIB) -l$(UTIL)
	make -C $(MINRUN)
	make -C $(RUN)
	-cp $(RUN)/libminor.a $(LDLIBS)

out: out.asm $(LANG)
	$(AS) out.asm -o out.o
	$(LD) out.o $(LDLIBS) -o out
	./out

examples:: $(LANG)
	make -C $(EXS)

clean::
	make -C $(LIB) clean
	make -C $(RUN) clean
	make -C $(EXS) clean
	make -C $(MINRUN) clean
	rm -f *.o exs/*.o $(LANG) $(LDLIBS) lex.yy.c y.tab.c y.tab.h y.output yyselect.c exs/*.asm *~ a.out *.o *.asm
