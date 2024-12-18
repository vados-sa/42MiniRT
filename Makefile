NAME 			= 	miniRT
NAME_B		= 	miniRT_bonus

CC 				= 	cc

CCFLAGS 		= 	-Wextra -Wall -Werror -g
CFLAGS 			+= 	-Iinclude -Isrc -O3 -Wunreachable-code -Ofast

OBJ_DIR			= 	obj/
SRC_DIR			= 	src/
INIT_DIR 		= 	$(SRC_DIR)/init/
MATH_DIR 		= 	$(SRC_DIR)/math/
PARSE_DIR 		= 	$(SRC_DIR)/parsing/
RENDER_DIR 		= 	$(SRC_DIR)/render/

OBJ_DIR_B			= 	obj_bonus/
SRC_DIR_B			= 	src_bonus/
INIT_DIR_B		= 	$(SRC_DIR_B)/init/
MATH_DIR_B		= 	$(SRC_DIR_B)/math/
PARSE_DIR_B		= 	$(SRC_DIR_B)/parsing/
RENDER_DIR_B 		= 	$(SRC_DIR_B)/render/
BONUS_DIR		= 	$(SRC_DIR_B)/bonus/

LIBFTDIR 		= 	./lib/libft
LIBMLX			= 	./lib/MLX42

LIBS			=  	$(LIBMLX)/build/libmlx42.a -ldl -L/opt/homebrew/lib -lglfw -pthread -lm #-L/opt/homebrew/lib for mac
LIBS 			+= 	$(LIBFTDIR)/libft.a

INCLUDES		=  	-I./incl -I$(LIBMLX)/include -I$(LIBFTDIR)
INCLUDES_B		=  	-I./incl_bonus -I$(LIBMLX)/include -I$(LIBFTDIR)
HDRS 			= $(addprefix incl/, minirt.h macros.h structs.h)
HDRS_B 			= $(addprefix incl_bonus/, minirt_bonus.h macros_bonus.h structs_bonus.h)

SRCS 			=  $(addprefix $(SRC_DIR), main.c  exit.c hooks.c) \
					$(addprefix $(INIT_DIR), init.c light_list.c object_list.c) \
					$(addprefix $(MATH_DIR), vec3_ops.c vec3_ops2.c) \
					$(addprefix $(PARSE_DIR),parsing.c parsing_read_file.c \
						parsing_checks.c number_checks.c parse_utils.c \
						parse_lighting.c parse_camera.c \
						parse_plane.c parse_cylinder.c parse_sphere.c) \
					$(addprefix $(RENDER_DIR), render.c sphere.c plane.c cylinder.c \
						cy_cap.c intersection.c ray.c lights.c)

SRCS_B 			=  $(addprefix $(SRC_DIR_B), main.c  exit.c hooks.c) \
					$(addprefix $(INIT_DIR_B), init.c light_list.c object_list.c) \
					$(addprefix $(MATH_DIR_B), vec3_ops.c vec3_ops2.c) \
					$(addprefix $(PARSE_DIR_B),parsing.c parsing_read_file.c \
						parsing_checks.c number_checks.c parse_utils.c \
						parse_lighting.c parse_camera.c \
						parse_plane.c parse_cylinder.c parse_sphere.c) \
					$(addprefix $(RENDER_DIR_B), render.c sphere.c plane.c cylinder.c \
						cy_cap.c intersection.c ray.c lights.c) \
					$(addprefix $(BONUS_DIR), checkerboard_bonus.c)

OBJS 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
OBJS_B 			= $(patsubst $(SRC_DIR_B)%.c,$(OBJ_DIR_B)%.o,$(SRCS_B))

LIBFT 			= $(LIBFTDIR)/libft.a
LIBFT_LIB 		= -Llibft -lft

all: libmlx $(LIBFT) $(NAME)

bonus: libmlx $(LIBFT) $(NAME_B)

libmlx:
	@if [ ! -d "lib/MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42; \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@make --quiet -C $(LIBMLX)/build -j4

$(LIBFT):
	@$(MAKE) --quiet -C $(LIBFTDIR) all

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDRS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_B)%.o: $(SRC_DIR_B)%.c $(HDRS_B)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES_B) -c $< -o $@

$(NAME): $(OBJS) $(HDRS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[32;1mminiRT is ready\033[5m ✓ ✓ ✓\033[0m"

$(NAME_B): $(OBJS_B) $(HDRS_B)
	@$(CC) $(CFLAGS) $(INCLUDES_B) $(OBJS_B) $(LIBS) -o $(NAME_B)
	@echo "\033[32;1mminiRT_bonus is ready\033[5m ✓ ✓ ✓\033[0m"

clean:
	@rm -f $(OBJS) $(OBJS_B)
	@rm -rf $(OBJ_DIR) $(OBJ_DIR_B)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) clean
	@echo "\033[37;1mObject files removed.\033[0m"

fclean: clean
	@rm -rf $(NAME) $(NAME_B)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) fclean
	@rm -rf $(LIBMLX)/build
	@echo "\033[37;1mExecutable removed.\033[0m"

re: fclean all
re_bonus: fclean bonus

.PHONY: all bonus clean fclean re libmlx $(LIBFT)
