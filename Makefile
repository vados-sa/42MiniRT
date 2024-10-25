NAME 			= 	minirt

CC 				= 	cc

CCFLAGS 		= 	-Wextra -Wall -Werror
CFLAGS 			+= 	-Iinclude -Isrc -O3 -Wunreachable-code -Ofast

OBJ_DIR			= 	obj/
SRC_DIR			= 	src/
LIBFTDIR 		= 	./lib/libft
LIBMLX			= 	./lib/MLX42

LIBS			=  	$(LIBMLX)/build/libmlx42.a -ldl -L/opt/homebrew/lib -lglfw -pthread -lm #-L/opt/homebrew/lib for mac
LIBS 			+= 	$(LIBFTDIR)/libft.a

INCLUDES		=  	-I./include -I$(LIBMLX)/include -I$(LIBFTDIR)
#INCLUDES		=  	-I./include -I$(LIBMLX)/include -I$(LIBFTDIR) -I/opt/homebrew/opt/glfw/include #petras mac

SRCS 			= $(addprefix $(SRC_DIR), main.c)
OBJS 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
HDRS 			= $(addprefix include/, )

LIBFT 			= $(LIBFTDIR)/libft.a
LIBFT_LIB 		= -Llibft -lft
#LDFLAGS 		= -L/opt/homebrew/opt/glfw/lib #for glfw

all: libmlx $(LIBFT) $(NAME)

libmlx:
	@if [ ! -d "lib/MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42; \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR) all

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)
#$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@rm -rf $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	@# rm -rf $(LIBMLX)/build

re: fclean all

.PHONY: all clean fclean re libmlx $(LIBFT)


