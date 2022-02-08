NAME = minishell

SRCS = srcs/minishell.c \
		srcs/built_ins/env.c \
		srcs/built_ins/exit.c \
		srcs/built_ins/export/export.c \
		srcs/alloc/struct_init.c \
		srcs/utils/utils_1.c \
		srcs/utils/utils_2.c \
		srcs/built_ins/pwd.c \
		srcs/built_ins/cd.c \
		srcs/built_ins/export/check_export_args_new.c \
		srcs/built_ins/export/if_double_new.c \
		srcs/built_ins/unset/unset.c \
		srcs/built_ins/unset/unset_check_args.c \
		srcs/parsing/split_command.c \
		srcs/alloc/exit_free.c \
		srcs/parsing/lexer.c \
		srcs/execution/execution.c \
		srcs/parsing/expansion.c

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${SRCBONUS:.c=.o}

PATH_LIBFT = 42_libft

INCLUDES = -I/includes/minishell.h

CFLAGS = -g #-fsanitize=address #-Werror -Wall -Wextra

CC = clang 

LIB = 42_libft/libft.a -I./usr/include

RM = rm -f

all: ${NAME}

${NAME}: ${OBJS}
		make -C $(PATH_LIBFT)
		${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${LIB} -o ${NAME} -lreadline

clean:
		make -C $(PATH_LIBFT) clean
		${RM} ${OBJS} ${OBJSBONUS}

fclean: clean
		make -C $(PATH_LIBFT) clean
		${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re
