NAME 			= 	minirt

CC 				= 	cc

CCFLAGS 		= 	-Wextra -Wall -Werror -g
CFLAGS 			+= 	-Iinclude -Isrc -O3 -Wunreachable-code -Ofast

OBJ_DIR			= 	obj/
SRC_DIR			= 	src/
PARSE_DIR 		= 	$(SRC_DIR)/parsing/
LIBFTDIR 		= 	./lib/libft
LIBMLX			= 	./lib/MLX42

LIBS			=  	$(LIBMLX)/build/libmlx42.a -ldl -L/opt/homebrew/lib -lglfw -pthread -lm #-L/opt/homebrew/lib for mac
LIBS 			+= 	$(LIBFTDIR)/libft.a

INCLUDES		=  	-I./incl -I$(LIBMLX)/include -I$(LIBFTDIR)
#INCLUDES		=  	-I./include -I$(LIBMLX)/include -I$(LIBFTDIR) -I/opt/homebrew/opt/glfw/include #petras mac

SRCS 			=  $(SRC_DIR)/main.c $(SRC_DIR)/init.c $(SRC_DIR)/exit.c $(SRC_DIR)/light_list.c \
					 $(SRC_DIR)/object_list.c $(SRC_DIR)/render.c $(SRC_DIR)/vec3_ops.c $(SRC_DIR)/vec3_products.c \
					 $(SRC_DIR)/plane.c $(SRC_DIR)/intersection.c $(SRC_DIR)/ray.c\
					 $(PARSE_DIR)/parsing.c $(PARSE_DIR)/parsing_read_file.c \
					 $(PARSE_DIR)/parsing_checks.c $(PARSE_DIR)/number_checks.c \
					 $(PARSE_DIR)/parse_amb_light.c $(PARSE_DIR)/parse_light.c $(PARSE_DIR)/parse_camera.c \
					 $(PARSE_DIR)/parse_plane.c $(PARSE_DIR)/parse_cylinder.c $(PARSE_DIR)/parse_sphere.c
OBJS 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
HDRS 			= $(addprefix incl/, minirt.h macros.h structs.h)

LIBFT 			= $(LIBFTDIR)/libft.a
LIBFT_LIB 		= -Llibft -lft
#LDFLAGS 		= -L/opt/homebrew/opt/glfw/lib #for glfw
#DEBUG 			= 1

all: libmlx $(LIBFT) $(NAME)

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
#$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	@echo "\033[32;1mminiRT is ready\033[5m ✓ ✓ ✓\033[0m"

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) clean
	@echo "\033[37;1mObject files removed.\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) fclean
	@# rm -rf $(LIBMLX)/build
	@echo "\033[37;1mExecutable removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re libmlx $(LIBFT)


