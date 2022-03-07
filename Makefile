CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g
NAME		=	minishell

SRC			=	minishell.c			\
				minishell_utils.c	\

FT_PRINTF_PATH	=	./ft_printf/

OBJ_PATH	=	./objects/
SRC_PATH	=	./src/
INC_PATH	=	./include/
HEADERS		=	minishell.h		\

FT_PRINTF 	=	src/libftprintf.a 

HEAD_DEP	=	${HEADERS:%.h=${INC_PATH}%.h}

OBJ			=	${SRC:%.c=${OBJ_PATH}%.o}

.PHONY	:	all re clean fclean ${FT_PRINTF}

all : ${NAME}

${FT_PRINTF}:
	@echo "Making the library."
	@${MAKE} -s -C ${FT_PRINTF_PATH}

${OBJ_PATH}:
	@mkdir ${OBJ_PATH}

${OBJ_PATH}%.o : ${SRC_PATH}%.c ${HEAD_DEP} | ${OBJ_PATH}
	@${CC} ${CFLAGS} -o $@ -c $< -I${INC_PATH} -I${FT_PRINTF_PATH}

${NAME} : ${FT_PRINTF} ${OBJ}
	@${CC} ${CFLAGS} -o $@  $^ ${FT_PRINTF} -lreadline
	@echo "✅ Your ${NAME} is ready to fly."

clean :
	@rm -rf ${OBJ_PATH}
	@echo "Making the project nice and clean."

fclean : clean
	@rm -f ${NAME}
	@echo "The executable has got to go..."

re:
	@echo "Rebuilding..."
	@${MAKE} -s fclean all