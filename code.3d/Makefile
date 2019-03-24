# Ce makefile n'utilise pas de variable d'environnement.

# compilateur
CC = gcc

FLAGS = -g -Wpointer-arith -Wall -Wextra -Werror -ansi -O2
IGNORED = -Wno-unused-parameter
CFLAGS = $(FLAGS) $(IGNORED)

# assemblage des infos de lib. et inc.
libGL = $(dir $(dir $(shell find /usr/lib/ -name libGL.so | head -n 1)))
libg3x = ../libg3x/
lib = -L$(libGL) -L$(libg3x) -lm -lGL -lGLU -lglut -lg3x.64b
inc = -I$(libg3x)include/ -I$(libGL)include/



####################################################################################################
# Ne modifier que ces lignes :

# fichiers *.c locaux
src = src/

# fichiers *.o locaux
bin = bin/


objet = sphere cube cone cylinder torus matrix object
exec = main
####################################################################################################



# Cree bin si besoin
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
