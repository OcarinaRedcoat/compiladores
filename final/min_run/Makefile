.SUFFIXES: .$(EXT) .asm
COMP=../minor # compiler
EXT=min # file extension: .$(EXT)
LIB=minor # runtime library: lib$(LIB).a
RUN=../run # runtime directory
AS=nasm -felf32 # assembler command
LD=ld -melf_i386 # loader command

RUNTIME=lib$(LIB).a # stand-alone runtime
SRC=exemplo.min
EXE=$(SRC:%.min=%)

all:: compiler $(EXE) cp_run

compiler::
	make -C ..

%:%.$(EXT)
	$(COMP) -trace $<
	$(AS) $*.asm -o $*.o

cp_run::
	cp *.o $(RUN)

clean::
	rm -f *.o *.asm *.s *~ $(EXE)
