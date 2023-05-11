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

HEADERS_LIST	=

SRCS_LIST		=	main.c \
					second_parsing.c	\ #arg_init.c

HEADERS			=	${HEADERS_LIST:%.h=${DIR_HEADERS}%.h}

OBJS			=	${SRCS_LIST:%.c=${DIR_OBJS}%.o}

# ---- Compilation ---- #

CC				=	cc

CFLAGS			=	 -Wall -Werror -Wextra -g3

FRAMEWORKS		=	-Llib/libft -lft


# ---- Commands ---- #

RM				=	rm -rf

MKDIR			=	mkdir -p

# ********* RULES ******** #

init			:
					git submodule update --init --recursive
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

# ---- Usual Rules ---- #

clean			:
					make -C lib/libft clean
					${RM} ${OBJS}

fclean			:
					make clean
					${RM} ${NAME}
					make -C lib/libft fclean

re				:
					make fclean
					make all

.PHONY:	all clean fclean re
