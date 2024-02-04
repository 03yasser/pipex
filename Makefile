SRCS = main.c pipex_utils1.c ft_split.c
SRCS_printf = ft_printf.c ft_file1.c ft_file2.c
P_SRCS = $(addprefix ft_printf/,$(SRCS_printf))
P_OBJ = $(addprefix printf_objs/,$(notdir $(P_SRCS:.c=.o)))

PRINTF_NAME = libftprintf.a
NAME = pipex
CFLAGS =
all: $(NAME) $(PRINTF_NAME)

$(NAME): $(SRCS) $(PRINTF_NAME)
	cc  $(SRCS) $(PRINTF_NAME) -I. -o $(NAME)
$(PRINTF_NAME): $(P_OBJ)
	ar -rc $(PRINTF_NAME) $(P_OBJ)
printf_objs/%.o:ft_printf/%.c
	mkdir -p printf_objs
	$(CC) $(CFLAGS) -I ./includes -c $< -o $@
clean:
	rm -rf printf_objs
fclean:
	rm -rf $(PRINTF_NAME)
	rm -rf $(NAME)
re: fclean all