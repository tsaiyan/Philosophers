# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

HEADER = ./sources/header.h

SOURCE = ./sources

OBJTS =  $(SOURCE)/main.c $(SOURCE)/parcer.c $(SOURCE)/utils.c  $(SOURCE)/philos_life.c $(SOURCE)/logic_utils.c $(SOURCE)/init.c $(SOURCE)/hara_kiri.c $(SOURCE)/check_all_ate.c

NAME = philo_two

RM = rm -f

CC = gcc -Wall -Wextra -Werror

.PHONY:		all clean fclean re

all: $(NAME)

$(NAME): $(OBJTS) $(HEADER)
	@$(CC) $(OBJTS) -o $(NAME)
	@echo "$(GREEN)Comliled.$(RESET)"
clean:
	@$ rm -rf $(NAME)
	@echo "$(RED)$(NAME) deleted.$(RESET)"
fclean: clean
re: fclean all
