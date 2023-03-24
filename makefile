SRCS		= main.c path.c error.c here_doc.c test.c exec.c gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS		= ${SRCS:.c=.o}

LFT			= ./libft/libft.a

HEAD		= pipex.h

NAME		= pipex

CC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

.c.o:		
			${CC} ${CFLAGS} -I${HEAD} -Ilibft -c $< -o ${<:.c=.o}

${NAME}:	${LFT} ${OBJS}
			${CC} ${CFLAGS} ${OBJS} -L ./libft -lft -o ${NAME}

${LFT}:
			make -s -C libft

all:		${NAME}

bonus:		all

clean:
			${RM} ${OBJS} ${OBJS_BONUS}
			make clean -C libft

fclean:		clean
			${RM} ${NAME}
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re
