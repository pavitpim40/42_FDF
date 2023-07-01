# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 10:34:59 by ppimchan          #+#    #+#              #
#    Updated: 2023/07/01 15:52:26 by ppimchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME					= fdf
CC						= gcc
FLAGS					= -Wall -Wextra -Werror -O3
ALL_HEADERS				= -I$(FDF_HEADERS_DIRECTORY)  -I$(LIBFT_DIRECTORY) -I$(MINI_LIBX_DIRECTORY)
ALL_LIBS 				= -lmlx -lm -lft -L$(LIBFT_DIRECTORY) -L$(MINI_LIBX_DIRECTORY) -framework OpenGL -framework AppKit

# LIBFT
LIBFT_DIRECTORY			= ./libft/
LIBFT_HEADERS			= $(LIBFT_DIRECTORY)libft.h
LIBFT					= $(LIBFT_DIRECTORY)libft.a

# MINI_LIBX
MINI_LIBX_DIRECTORY		= ./minilibx_macos/
MINI_LIBX_HEADERS		= $(MINI_LIBX_DIRECTORY)mlx.h
MINI_LIBX				= $(MINI_LIBX_DIRECTORY)libmlx.a

# FDF_HEADERS
FDF_HEADERS_DIRECTORY	= ./includes/
FDF_HEADERS_FILES		= fdf.h
FDF_HEADERS				= $(addprefix $(FDF_HEADERS_DIRECTORY), $(FDF_HEADERS_FILES))

# SOURCE
SRCS_DIRECTORY			= ./srcs/
SRCS_FILES				= main.c error.c 
SRCS					= $(addprefix $(SRCS_DIRECTORY) $(SRCS_FILES))

# OBJECT
OBJECTS_DIRECTORY		= ./objects/
OBJECTS_FILES			= $(patsubst %.c, %.o, $(SRCS_FILES))
OBJECTS					= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_FILES))


# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# RULES

all: $(NAME)

$(NAME) : $(LIBFT) $(MINI_LIBX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	$(CC) $(FLAGS) $(ALL_LIBS) $(ALL_HEADERS) $(OBJECTS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

# create ./object/
$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

# Compile All .c to .o 
$(OBJECTS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(FDF_HEADERS)
	$(CC) $(FLAGS) -c $(ALL_HEADERS) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	$(MAKE) -sC $(LIBFT_DIRECTORY)

$(MINI_LIBX):
	@echo "$(NAME): $(GREEN)Creating $(MINI_LIBX)...$(RESET)"
	$(MAKE) -sC $(MINI_LIBX_DIRECTORY)

clean:
	$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	$(MAKE) -sC $(MINI_LIBX_DIRECTORY) clean
	rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	rm -f $(MINI_LIBX)
	@echo "$(NAME): $(RED)$(MINI_LIBX) was deleted!$(RESET)"
	rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re