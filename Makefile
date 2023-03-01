RM = rm -f
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
INCLUDES = includes/minishell.h
SRCS_DIR = srcs/
SRCS = builtin_1.c\
       builtin_2.c\
	   builtin_3.c\
	   builtin_execution1.c\
	   builtin_execution2.c\
	   builtin_execution3.c\
	   determine_cmd.c\
	   determine_cmd2.c\
	   error.c\
	   execution.c\
	   execution2.c\
	   execution3.c\
	   execution4.c\
	   fonction_supplier_3.c\
	   fonction_supplier_2.c\
	   fonction_supplier.c\
	   handle_here_doc.c\
	   handle_here_doc2.c\
	   handle_parsing.c\
	   handle_spe.c\
	   handle_tokens.c\
	   handlers.c\
	   list_1.c\
	   list_2.c\
	   main_extended.c\
	   main.c\
	   operators.c\
	   pipes.c\
	   redirection.c\
	   redirection2.c\
	   utils_1.c\
	   utils_2.c\
	   utils_3.c\
	   utils_4.c\
	   utils_5.c\
	   wild_match.c\
	   wild_match2.c\
	   wildcard.c\
	   wildcard2.c\
	   wildcard3.c
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(SRCS:.c=.o)

%.o: %.c
	${CC} -c ${CFLAGS} ${INCLUDES} $< -o $@ -lreadline

all: $(NAME)

$(NAME) : $(OBJS)
		gcc -g -o $(NAME) $(OBJS) -lreadline 

$(OBJS): $(SRCS_PATH)
	gcc -c ${CFLAGS} ${CFLAGS} ${INCLUDES} ${SRCS_PATH}

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: fclean re all clean