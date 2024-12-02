
#ifndef MACROS_H
# define MACROS_H

//error messages
# define ALLOC_ERR "Error\nAllocation error."
# define ARGV_ERR "Error\nUsage: ./minirt *.rt"
# define OPEN_ERR "Error\nFile does not exist or cannot be opened."
# define EXTENSION_ERR "Error\nFormat *.rt required."
# define EMPTY_ERR "Error\nEmpty file."
# define TYPE_ID_ERR "Error\nType identifier is not valid, or is declared \
more than once, or space at the beginning of the line."
# define SPACE_ERR "Error\nSpace at the end of the line."
# define LEN_ERR "Error\nElement doesn't contain the right amount of \
information."
# define RATIO_ERR "Error\nLight ratio invalid or out of bounds."
# define FOV_ERR "Error\nFOV invalid or out of bounds."
# define GEN_INFO_ERR "Error\nWrong amount of information."
# define COL_RANGE_ERR "Error\nR,G,B color values are out of bounds."
# define NORMAL_RANGE_ERR "Error\n3d normalized orientation vector's \
values are out of bounds."
# define NUM_ERR "Error\nNumber contains invalid characters."
# define DIMENSION_ERR "Error\nObject dimensions have to be positive values."

//macros
# define IMAGE_WIDTH 1200.0
# define IMAGE_HEIGHT 675.0
# define PI 3.1415926535897932385
# define FOCAL_LENGTH 1.0
//if t_float is double
# define EPSILON 1e-6
//if t_float is float
//# define EPSILON 0.0005

# if BONUS == 1
#  define MAX_LIGHT 100
# else
#  define MAX_LIGHT 1
# endif

#endif
