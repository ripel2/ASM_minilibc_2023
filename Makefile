##
## EPITECH PROJECT, 2023
## ASM_minilibc_2023
## File description:
## Makefile
##

RM			=	-rm -f

NASM		=	nasm
GCC			=	gcc

LD			=	ld

SRC			=	src/strlen.asm	\
				src/strchr.asm	\
				src/strcmp.asm	\
				src/strncmp.asm	\
				src/memset.asm	\
				src/memcpy.asm

OBJ			=	$(SRC:.asm=.o)

NAME		=	libasm.so

NASMFLAGS	=	-f elf64

TESTS_SRC	=	tests/tests_strlen.c	\
				tests/tests_strchr.c	\
				tests/tests_strcmp.c	\
				tests/tests_strncmp.c	\
				tests/tests_memset.c	\
				tests/tests_memcpy.c
TESTS_OBJ	=	$(TESTS_SRC:.c=.o)

TESTS_FLAGS	=	-lcriterion -ldl
COVERAGE	=	--coverage -fprofile-arcs -ftest-coverage

all:		$(NAME)

%.o:		%.asm
	$(NASM) $< -o $@ $(NASMFLAGS)

%.o:		%.c
	$(GCC) -c $< -o $@ $(CFLAGS)

$(NAME):	$(OBJ)
	$(LD) -shared -o $(NAME) $(OBJ)

clean:
	find . -name "*.o" -delete
	find . -name "*~" -delete -or -name "#*#" -delete
	find . -name "*.gcda" -delete -or -name "*.gcno" -delete

fclean:		clean
	$(RM) -f $(NAME)

re:			fclean all

tests_run:	CFLAGS += $(COVERAGE)
tests_run:	clean $(NAME) $(TESTS_OBJ)
	$(GCC) -o unit_tests $(TESTS_OBJ) $(CFLAGS) $(TESTS_FLAGS)
	./unit_tests
	$(RM) unit_tests

.PHONY:	all clean fclean re
