SRCS_printf = ft_printf.c ft_file1.c ft_file2.c
SRCS_bonus = ft_split_bonus.c main_bonus.c pipex_utils1_bonus.c gnl_utils_bonus.c gnl_bonus.c pipex_utils2_bonus.c pipex_utils3_bonus.c
SRCS_mandatory = main.c pipex_utils1.c ft_split.c pipex_utils2.c ft_substr.c pipex_utils3.c

b_SRCS = $(addprefix bonus/,$(SRCS_bonus))
P_SRCS = $(addprefix ft_printf/,$(SRCS_printf))
SRCS = $(addprefix Mandatory/,$(SRCS_mandatory))

B_OBJ = $(addprefix object_files2/,$(notdir $(b_SRCS:.c=.o)))
P_OBJ = $(addprefix printf_objs/,$(notdir $(P_SRCS:.c=.o)))
OBJ_mandatory = $(addprefix object_files1/,$(notdir $(SRCS:.c=.o)))

PRINTF_NAME = libftprintf.a
NAME = pipex
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_mandatory) $(PRINTF_NAME)
	cc $(CFLAGS) $(OBJ_mandatory) $(PRINTF_NAME) -I ./includes -o $(NAME)

object_files1/%.o: Mandatory/%.c includes/pipex.h
	mkdir -p object_files1
	cc $(CFLAGS) -I ./includes -c $< -o $@

object_files2/%.o: bonus/%.c includes/pipex_bonus.h
	mkdir -p object_files2
	cc $(CFLAGS) -I ./includes -c $< -o $@

bonus: $(B_OBJ) $(PRINTF_NAME)
	cc $(CFLAGS) $(B_OBJ) $(PRINTF_NAME) -I ./includes -o pipex

$(PRINTF_NAME): $(P_OBJ)
	ar -rc $(PRINTF_NAME) $(P_OBJ)

printf_objs/%.o: ft_printf/%.c
	mkdir -p printf_objs
	$(CC) $(CFLAGS) -I ./includes -c $< -o $@

clean:
	rm -rf printf_objs object_files1 object_files2

fclean: clean
	rm -rf $(NAME) $(PRINTF_NAME)

re: fclean all

