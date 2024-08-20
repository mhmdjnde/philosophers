SRCS			= philo/main.c \
				philo/ini_destroy.c \
				philo/monitor.c \
				philo/routine_case_1.c \
				philo/routine_case_2.c \
				philo/routine.c \
				philo/utils.c \
				philo/val_in.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.
LIBS			= -lpthread

NAME			= philo2

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
