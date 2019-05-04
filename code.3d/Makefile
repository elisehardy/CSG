# compilateur
CC = gcc

FLAGS = -g -Wpointer-arith -Wall -Wextra -Werror -O2
IGNORED =
CFLAGS = $(FLAGS) $(IGNORED)

# assemblage des infos de lib. et inc.
libg3x = ../libg3x/
lib = $(libG3X)$(CCEXT)
inc = $(incG3X)



####################################################################################################
# Ne modifier que ces lignes :

# fichiers *.c locaux
src = src/

# fichiers *.o locaux
bin = bin/


objet = sphere cube cone cylinder torus matrix stack file object tree main
exec = csg
####################################################################################################



# Cree bin si besoin
$(shell mkdir -p $(bin))

object = $(addprefix $(bin),$(addsuffix .o,$(objet)))

all : $(object) $(exec)


.PHONY: clean cleanall doc all info


$(bin)%.o: $(src)%.c
	@echo "$< -> $@"
	@$(CC) $(CFLAGS) $(inc) -c $< -o $@


$(exec): $(object) $(bin)main.o
	@echo "[$^] -> $@"
	@$(CC) $^ $(lib) $(inc) -o $@
	@echo "------------------------"


info:
	@echo "---------compilation informations----------"
	@echo "  processor      : $(PROCBIT)"
	@echo "  compiler       : $(CC)"
	@echo "  options        : $(CFLAGS)"
	@echo "  lib g3x/OpenGl : $(lib)"
	@echo "  headers        : $(inc)"


doc:
	rm docs/html docs/index.html -rf
	doxygen
	ln -s html/files.html docs/index.html


clean:
	@rm -f $(bin)*.o


cleanall:
	@rm -rf $(bin)*.o $(exec) *~ */*~ docs/html docs/index.html
