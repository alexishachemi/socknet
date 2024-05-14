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

INCLIBS	=	linked clogger

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

fclean: clean
	rm -f $(LNAME)
	rm -f $(NAME)

re: fclean all

$(NAME):	$(LNAME)
	gcc -o $(NAME) tests/main.c $(LDFLAGS) $(CFLAGS) -L. -l$(NAME)

debug:	$(NAME)

$(OBJDIR)/%.o:	%.c
	@mkdir -p $(@D)
	gcc -o $@ -c $< $(CFLAGS) $(LDFLAGS)

.PHONY: all clean fclean re debug $(NAME)
