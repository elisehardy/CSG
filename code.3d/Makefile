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

FLAGS = -g -Wpointer-arith -Wall -Wextra -Werror -ansi -O2
IGNORED = -Wno-unused-parameter -Wno-aggressive-loop-optimizations

CFLAGS = $(FLAGS) $(IGNORED)

# assemblage des infos de lib. et inc.
lib =   $(libG3X)$(CCEXT)

# lib.
inc = $(incG3X)

# fichiers *.c locaux
src = src/

# fichiers *.o locaux
bin = bin/



####################################################################################################
# Ne modifier que ces deux lignes :

objet = sphere cube cone cylinder torus matrix object
exec = main
####################################################################################################



# Creer bin si besoin
$(shell mkdir -p $(bin))

object = $(addprefix $(bin),$(addsuffix .o,$(objet)))

all : $(object) $(exec)

# règle générique de création de xxx.o à partir de src/xxx.c
$(bin)%.o : $(src)%.c
	@echo "$< -> $@"
	@$(CC) $(CFLAGS) $(inc) -c $< -o $@

# règle générique de création de l'executable xxx à partir de src/xxx.c (1 seul module)
% : $(object) $(bin)%.o
	@echo "[$^] -> $@"
	@$(CC) $^ $(lib) $(inc) -o $@
	@echo "------------------------"



.PHONY : clean cleanall ?

# informations sur les paramètres de compilation
? :
	@echo "---------compilation informations----------"
	@echo "  processor      : $(PROCBIT)"
	@echo "  compiler       : $(CC)"
	@echo "  options        : $(CFLAGS)"
	@echo "  lib g3x/OpenGl : $(lib)"
	@echo "  headers        : $(inc)"
clean :
	@rm -f $(bin)*.o
cleanall :
	@rm -f $(bin)*.o $(exec) *~ */*~
