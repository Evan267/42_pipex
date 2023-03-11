SRCS		= main.c test.c exec.c

OBJS		= ${SRCS:.c=.o}

LFT			= ./libft/libft.a

HEAD		= pipex.h

NAME		= pipex

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

.c.o:		
			${CC} ${CFLAGS} -I${HEAD} -Ilibft -c $< -o ${<:.c=.o}

${NAME}:	${LFT} ${OBJS}
			${CC} ${OBJS} -L ./libft -lft -o ${NAME}

${LFT}:
			make -s -C libft

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJS_BONUS}
			make clean -C libft

fclean:		clean
			${RM} ${NAME}
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re
