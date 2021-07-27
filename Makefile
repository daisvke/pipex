CC			=	clang $(FLAGS)
FLAGS		=	-Wall -Wextra -Werror -g $(MEM)
MEM			=	-fsanitize=address

RM			=	rm -rf

NAME		=	pipex

SRC_DIR		=	src/
SRC_FILES	=	exit.c \
				get_next_line.c \
				get_next_line_utils.c \
				heredoc.c \
				main.c \
				path.c \
				split.c \
				system_calls.c \
				utils_fd.c \
				utils_str.c
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		=	obj/
OBJ_FILES	=	$(SRC_FILES:.c=.o)
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	@echo -n "\n"
	@echo -n "NOW GENERATING PIPEX..."
	@$(CC) $(OBJ) -o $(NAME)
	@echo "\033[32m\t\t[OK]\033[0m\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@$(CC) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
