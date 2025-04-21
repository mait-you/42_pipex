# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/08 16:18:55 by mait-you          #+#    #+#              #
#    Updated: 2025/02/12 16:13:58 by mait-you         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Compiler and Flags
CC			:= cc
AR			:= ar rsc
CFLAGS		:= -Wall -Wextra -Werror #-fsanitize=address -g
RM			:= rm -rf

### Executable Name
NAME		:= pipex
LIBFT		:= libft/libft.a

### dirs
SRC_DIR		:= mandatory
LIBFT_DIR	:= libft
OBJS_DIR	:= obj

### Source Files
LIBFT_SRCS	:= $(LIBFT_DIR)/ft_strlen.c $(LIBFT_DIR)/ft_memset.c $(LIBFT_DIR)/ft_strncmp.c $(LIBFT_DIR)/ft_atoi.c \
			$(LIBFT_DIR)/ft_calloc.c $(LIBFT_DIR)/ft_strdup.c $(LIBFT_DIR)/ft_substr.c $(LIBFT_DIR)/ft_split.c \
			$(LIBFT_DIR)/ft_strcspn.c $(LIBFT_DIR)/ft_strchr.c $(LIBFT_DIR)/ft_strjoin.c $(LIBFT_DIR)/ft_putstr_fd.c \
			$(LIBFT_DIR)/ft_putchar_fd.c

SRCS		:= $(SRC_DIR)/pipex.c $(SRC_DIR)/pipex_utils_1.c $(SRC_DIR)/pipex_utils_2.c 

OBJS		:= $(SRCS:%.c=$(OBJS_DIR)/%.o)
LIBFT_OBJS	:= $(LIBFT_SRCS:%.c=$(OBJS_DIR)/%.o)

### Colors and Formatting
RESET		:= \033[0m
BLACK		:= \033[30m
RED			:= \033[31m
GREEN		:= \033[32m
YELLOW		:= \033[33m
BLUE		:= \033[34m
PURPLE		:= \033[35m
CYAN		:= \033[36m
WHITE		:= \033[37m
BOLD		:= \033[1m
UP			:= \033[F

### Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(RED)$(BOLD)$(NAME) $(GREEN)compiled successfully!$(RESET)"

$(LIBFT): $(LIBFT_OBJS)
	@$(AR) $(LIBFT) $(LIBFT_OBJS)
	@echo "$(CYAN)Building libft ...$(RESET)"
	@echo "$(CYAN)╚═ Built $(PURPLE)$(BOLD)$(LIBFT)$(RESET)"

# pipex $(SRC_DIR) Object file compilation rules
$(OBJS_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/pipex.h | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling: $(WHITE)$<$(RESET)"

# libft $(LIB_DIR) Object file compilation rules
$(OBJS_DIR)/$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c $(LIBFT_DIR)/libft.h | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling: $(WHITE)$<$(RESET)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@$(RM) $(OBJS_DIR) $(LIBFT)
	@echo "$(RED)Cleaned object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(UP)Cleaned object files and $(RED)$(BOLD)$(NAME)$(RESET)"

re: fclean all

.PHONY: clean

