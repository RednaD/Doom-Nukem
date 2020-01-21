# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 13:08:42 by vtouffet          #+#    #+#              #
#    Updated: 2019/08/22 15:50:05 by cfargere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_GAME_PATH=./srcs/game/
SRCS_GAME_FILES=main.c					\
                struct.c				\
				render.c				\
                draw_wall.c				\
				draw_floor_ceiling.c	\
				draw_gui.c				\
				draw_sprite.c			\
				draw_sprite2.c			\
				init_sprite.c			\
                parser.c				\
                data.c					\
                get_texture.c			\
				load_texture.c			\
                hook_mouse.c			\
				hook_keyboard.c			\
                raycast.c				\
				utils.c					\
				move_xy_axis.c			\
				move_z_axis.c			\
				color.c					\
				enemy.c					\
				object.c				\
				hud.c					\
				gui.c					\
				door.c					\
				decal.c                 \
				loader_xpm.c            \
				loader_utils.c
SRCS_GAME=$(addprefix $(SRCS_GAME_PATH), $(SRCS_GAME_FILES))

SRCS_EDITOR_PATH=./srcs/editor/
SRCS_EDITOR_FILES=cli.c display.c events.c file.c init.c texture.c resize.c utils.c \
				  display_ui.c free.c ../game/loader_xpm.c ../game/loader_utils.c
SRCS_EDITOR=$(addprefix $(SRCS_EDITOR_PATH), $(SRCS_EDITOR_FILES))

OBJECTS_GAME_PATH=./objs/game/
OBJECTS_GAME_FILES=$(SRCS_GAME_FILES:.c=.o)
OBJECTS_GAME=$(addprefix $(OBJECTS_GAME_PATH), $(OBJECTS_GAME_FILES))

OBJECTS_EDITOR_PATH=./objs/editor/
OBJECTS_EDITOR_FILES=$(SRCS_EDITOR_FILES:.c=.o)
OBJECTS_EDITOR=$(addprefix $(OBJECTS_EDITOR_PATH), $(OBJECTS_EDITOR_FILES))

COMPILE=gcc -Wall -Wextra -Werror

INCLUDES=-I./libs/libft -I./libs/minilibx
HEADER_GAME=./inc/doomnukem.h ./inc/game/xpm_parser_struct.h
HEADER_EDITOR=./inc/editor/doomnukem.h ./inc/editor/prototypes.h ./inc/editor/structs.h \
			  ./inc/game/xpm_parser_struct.h

MLX=./libs/minilibx/libmlx.a -framework OpenGL -framework AppKit

LIB_NAME=libft.a
LIB_PATH=./libs/libft/
LIB=$(LIB_PATH)$(LIB_NAME)

COLOR_RESET=\033[0m
COLOR_PENDING=\033[0;33m
COLOR_SUCCESS=\033[0;32m
COLOR_DEFAULT=\033[1;34m

all: libft minilibx doom-nukem editor
	@echo "        [$(COLOR_SUCCESS)DONE$(COLOR_RESET)]"

libft:
	@echo "$(LIB_NAME)     [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@make -C $(LIB_PATH) > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "$(LIB_NAME) [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"

minilibx:
	@echo "mlx.a      [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@make -C ./libs/minilibx > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "mlx.a   [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"

doom-nukem: $(OBJECTS_GAME) ./libs/minilibx/libmlx.a $(LIB)
	@echo "game	[$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@$(COMPILE) $(OBJECTS_GAME) $(MLX) $(LIB) -o doom-nukem > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "game	[$(COLOR_SUCCESS)OK$(COLOR_RESET)]"

$(OBJECTS_GAME_PATH)%.o: $(SRCS_GAME_PATH)%.c $(HEADER_GAME)
	@mkdir -p $(OBJECTS_GAME_PATH) 2>/dev/null || echo "" > /dev/null
	@$(COMPILE) $(INCLUDES) -I./inc/doomnukem.h -c $< -o $@
	@echo "Compiled $@" > /dev/null

editor: $(OBJECTS_EDITOR) ./libs/minilibx/libmlx.a $(LIB)
	@echo "editor     [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@$(COMPILE) $(OBJECTS_EDITOR) $(MLX) $(LIB) -o editor > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "editor  [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"

$(OBJECTS_EDITOR_PATH)%.o: $(SRCS_EDITOR_PATH)%.c $(HEADER_EDITOR)
	@mkdir -p $(OBJECTS_EDITOR_PATH) 2>/dev/null || echo "" > /dev/null
	@$(COMPILE) $(INCLUDES) -I./inc/editor -c $< -o $@
	@echo "Compiled $@" > /dev/null

clean:
	@make -C $(LIB_PATH) clean
	@make -C ./libs/minilibx/ clean
	@/bin/rm -Rf ./objs

fclean: clean
	@make -C $(LIB_PATH) fclean
	@/bin/rm -Rf doom-nukem
	@/bin/rm -Rf editor

re: fclean all
