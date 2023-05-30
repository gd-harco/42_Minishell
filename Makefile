# ******** VARIABLES ******** #

# ---- Final Executable --- #

NAME			=	minishell

# ---- Directories ---- #

DIR_OBJS		=	bin/

DIR_SRCS		=	srcs/

DIR_HEADERS		=	includes/

# ---- Libs variables ---- #

LIBFT			=	lib/libft/libft.a

# ---- Files ---- #

HEADERS_LIST	=	builtins.h\
					exec.h		\
					minishell.h	\
					struct.h	\
					parsing.h

SRCS_LIST		=	main2.c			\
					prompt.c		\
\
					builtins/echo.c		\
					builtins/env.c		\
					builtins/exit.c		\
					builtins/pwd.c		\
					builtins/unset.c	\
\
					exec/execution.c		\
					exec/get_item_nb.c		\
					exec/here_doc.c			\
					exec/translate.c		\
					exec/translate_utils.c	\
\
					parsing/path.c				\
					parsing/token.c				\
					parsing/token_check.c		\
					parsing/token_cmd_fct.c		\
					parsing/token_fct.c			\
					parsing/token_env_var.c		\
					parsing/token_redirect.c	\
					parsing/utils.c


HEADERS			=	${HEADERS_LIST:%.h=${DIR_HEADERS}%.h}

OBJS			=	${SRCS_LIST:%.c=${DIR_OBJS}%.o}

# ---- Compilation ---- #

CC				=	cc

CFLAGS			=	 -Wall -Werror -Wextra -g3 #-fsanitize=address

FRAMEWORKS		=	-Llib/libft -lft


# ---- Commands ---- #

RM				=	rm -rf

MKDIR			=	mkdir -p

# ********* RULES ******** #

init			:
					make all

all				:	${OBJS} ${HEADERS}
					make -C lib/libft
					make ${NAME}

# ---- Variables Rules ---- #

${NAME}			:	${OBJS} ${HEADERS} ${LIBFT}
					${CC} ${CFLAGS} -I ${DIR_HEADERS} ${OBJS} ${FRAMEWORKS} -o ${NAME} -lreadline

# ---- Compiled Rules ---- #

${OBJS}			:	| ${DIR_OBJS}

${DIR_OBJS}%.o	:	${DIR_SRCS}%.c ${HEADERS}
					${CC} ${CFLAGS} -I ${DIR_HEADERS} -c $< -o $@

${DIR_OBJS}		:
					${MKDIR} ${DIR_OBJS}
					${MKDIR} ${DIR_OBJS}builtins
					${MKDIR} ${DIR_OBJS}parsing
					${MKDIR} ${DIR_OBJS}exec

# ---- Usual Rules ---- #

clean			:
					make -C lib/libft clean
					${RM} ${OBJS}
					${RM} ${DIR_OBJS}

fclean			:
					make clean
					${RM} ${NAME}
					make -C lib/libft fclean

re				:
					make fclean
					make all

.PHONY:	all clean fclean re
