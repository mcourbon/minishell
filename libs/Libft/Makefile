SRCS			=	ft_isalnum.c \
					ft_isprint.c \
					ft_memcmp.c \
					ft_putchar_fd.c \
					ft_split.c \
					ft_strlcat.c \
					ft_strcmp.c \
					ft_strncmp.c \
					ft_substr.c \
					ft_atoi.c \
					ft_isalpha.c \
					ft_itoa.c \
					ft_putendl_fd.c \
					ft_strchr.c \
					ft_strlcpy.c \
					ft_memset.c \
					ft_strnstr.c \
					ft_tolower.c \
					ft_bzero.c \
					ft_isascii.c \
					ft_strcpy.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_putnbr_fd.c \
					ft_strdup.c \
					ft_strlen.c \
					ft_strrchr.c \
					ft_toupper.c \
					ft_calloc.c \
					ft_isdigit.c \
					ft_striteri.c \
					ft_memchr.c  \
					ft_putstr_fd.c \
					ft_strjoin.c \
					ft_strmapi.c \
					ft_strtrim.c \
					ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c \
					ft_lstlast.c \
					ft_printf.c \
					ft_display_hexa.c \
					ft_display_number.c \
					ft_display_string.c \
					get_next_line.c \
					get_next_line_utils.c\

OBJS			= $(SRCS:.c=.o)

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -rf
AR				= ar rcs
HEADER			= libft.h
NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS)
				$(AR) $(NAME) $(OBJS)

%.o: 			%.c $(HEADER) Makefile
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re