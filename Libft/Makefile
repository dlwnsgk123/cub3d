NAME = libft.a
SRCS = ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_memccpy.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strncmp.c \
		ft_strchr.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_memcmp.c \
		ft_strdup.c \
		ft_memmove.c \
		ft_strrchr.c \
		ft_substr.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strjoin.c \
		ft_strmapi.c \
		ft_strtrim.c \
		ft_split.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_atol.c \
		ft_strndup.c \
		ft_strcmp.c \
		ft_strtrim_back.c \
		get_next_line.c \

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

OBJ		= ${SRCS:.c=.o}

$(NAME)	: ${OBJ}
			ar rcs ${NAME} ${OBJ}

all : ${NAME}

clean :
			rm -rf $(OBJ)

fclean : clean
			rm -rf ${NAME}

re : fclean all

.PHONY : all bonus clean fclean re
