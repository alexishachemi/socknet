##
## EPITECH PROJECT, 2024
## socknet
## File description:
## Makefile
##

OBJDIR	=	tmp

SRCDIR	=	src

# prod

NAME	=	socknet

LNAME	=	lib${NAME}.a

SRC		=	$(shell find src -type f -name '*.c')

OBJ		=	$(SRC:%.c=$(OBJDIR)/%.o)

# flags

INCDIRS	=	include

INCLIBS	=	clogger linked

CFLAGS	+=	-Wall -Wextra

CFLAGS	+=	$(addprefix -I,$(INCDIRS))

LDFLAGS	+=	$(addprefix -l,$(INCLIBS))

# rules

$(LNAME):	$(OBJ)
	ar rc $(LNAME) $(OBJ)

all: $(LNAME)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(shell find . -type f -name '*.gcda')
	rm -rf $(shell find . -type f -name '*.gcno')

dclean:
	@rm -rf docs/html/

fclean: clean dclean
	rm -f $(LNAME)
	rm -f $(NAME)_client
	rm -f $(NAME)_server

re: fclean all

debug: $(LNAME)
	gcc -o $(NAME)_server tests/server.c $(CFLAGS) -L. -l$(NAME) $(LDFLAGS)
	gcc -o $(NAME)_client tests/client.c $(CFLAGS) -L. -l$(NAME) $(LDFLAGS)

docs: dclean
	(cd docs; doxygen)

$(OBJDIR)/%.o:	%.c
	@mkdir -p $(@D)
	gcc -o $@ -c $< $(CFLAGS) $(LDFLAGS)

.PHONY: all clean dclean fclean re debug docs
