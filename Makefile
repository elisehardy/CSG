#
# Les variables d'environnement libG3X, incG3X
# sont definies dans le fichier ~/.bashrc par le script ../install.sh
#
#compilateur
CC = gcc

CCEXT=
ifeq ($(CC),g++) #en mode debug
  CCEXT=++
endif

CFLAGS = -g -Wpointer-arith -Wall -ansi -O2


# assemblage des infos de lib. et inc.
lib =   $(libG3X)$(CCEXT)
# fichiers *.c locaux
src = src/
# fichiers *.h locaux et lib.
inc = -I./include $(incG3X) 

exec = sphere

all : $(exec) clean

# règle générique de création de xxx.o à partir de src/xxx.c
%.o : $(src)%.c
	$(CC) $(CFLAGS) $(inc) -c $< -o $@

# règle générique de création de l'executable xxx à partir de src/xxx.c (1 seul module)
% : %.o
	$(CC) $^ $(lib) -o $@

.PHONY : clean cleanall ?

# informations sur les paramètres de compilation       
? :
	@echo "---------compilation informations----------"
	@echo "  processor      : $(PROCBIT)"
	@echo "  compiler       : $(CC)"
	@echo "  options        : $(CFLAGS)"
	@echo "  lib g3x/OpenGl : $(lib)"
	@echo "  headers        : $(incG3X)"
clean : 
	@rm -f *.o
cleanall :
	@rm -f *.o $(exec) *~ */*~
	
