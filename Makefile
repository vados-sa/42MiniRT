NAME 			= 	miniRT

CC 				= 	cc

CCFLAGS 		= 	-Wextra -Wall -Werror -g
CFLAGS 			+= 	-Iinclude -Isrc -O3 -Wunreachable-code -Ofast

OBJ_DIR			= 	obj/
SRC_DIR			= 	src/
INIT_DIR 		= 	$(SRC_DIR)/init/
MATH_DIR 		= 	$(SRC_DIR)/math/
PARSE_DIR 		= 	$(SRC_DIR)/parsing/
RENDER_DIR 		= 	$(SRC_DIR)/render/
BONUS_DIR 		= 	$(SRC_DIR)/bonus/
LIBFTDIR 		= 	./lib/libft
LIBMLX			= 	./lib/MLX42


LIBS			=  	$(LIBMLX)/build/libmlx42.a -ldl -L/opt/homebrew/lib -lglfw -pthread -lm #-L/opt/homebrew/lib for mac
LIBS 			+= 	$(LIBFTDIR)/libft.a

INCLUDES		=  	-I./incl -I$(LIBMLX)/include -I$(LIBFTDIR)

SRCS 			=  $(addprefix $(SRC_DIR), main.c  exit.c hooks.c) \
					$(addprefix $(INIT_DIR), init.c light_list.c object_list.c) \
					$(addprefix $(MATH_DIR), vec3_ops.c vec3_ops2.c) \
					$(addprefix $(PARSE_DIR),parsing.c parsing_read_file.c \
						parsing_checks.c number_checks.c parse_utils.c \
						parse_lighting.c parse_camera.c \
						parse_plane.c parse_cylinder.c parse_sphere.c) \
					$(addprefix $(RENDER_DIR), render.c sphere.c plane.c cylinder.c \
						cy_cap.c intersection.c ray.c lights.c)
OBJS 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
HDRS 			= $(addprefix incl/, minirt.h macros.h structs.h)

LIBFT 			= $(LIBFTDIR)/libft.a
LIBFT_LIB 		= -Llibft -lft

ifdef BONUS
CFLAGS += -DBONUS=1
NAME = miniRT_bonus
SRCS += $(addprefix $(BONUS_DIR), checkerboard_bonus.c render_bonus.c lights_bonus.c)
SRCS := $(filter-out $(addprefix $(RENDER_DIR), render.c lights.c), $(SRCS))
HDRS += $(addprefix incl/, minirt_bonus.h)
else
CFLAGS += -DBONUS=0
endif

all: libmlx $(LIBFT) $(NAME)

bonus:
	@$(MAKE) BONUS=1

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

$(NAME): $(OBJS) $(HDRS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[32;1mminiRT is ready\033[5m ✓ ✓ ✓\033[0m"

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) clean
	@echo "\033[37;1mObject files removed.\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@if [ -f miniRT_bonus ]; then \
		rm miniRT_bonus; \
	fi
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) fclean
	@rm -rf $(LIBMLX)/build
	@echo "\033[37;1mExecutable removed.\033[0m"

re: fclean all
re_bonus: fclean bonus

.PHONY: all bonus clean fclean re libmlx $(LIBFT)
