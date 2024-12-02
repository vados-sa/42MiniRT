
#ifndef MACROS_H
# define MACROS_H

//error messages
# define ALLOC_ERR "Error\nerror on allocation"
# define ARGV_ERR "Error\nusage: ./minirt *.rt"
# define OPEN_ERR "Error\nfile does not exist or cannot be opened"
# define EXTENSION_ERR "Error\nformat *.rt required"
# define EMPTY_ERR "Error\nempty file"
# define TYPE_ID_ERR "Error\nspace at the beginning of the line or \
type identifier is not valid or is declared more than once"
# define SPACE_ERR "Error\nspace at the end of the line"
# define LEN_ERR "Error\nelement doesn't contain the right amount of information"
# define RATIO_ERR "Error\nlight ratio invalid or out of bounds"
# define FOV_ERR "Error\nfov invalid or out of bounds"
# define GEN_INFO_ERR "Error\nwrong amount of information"
# define COL_RANGE_ERR "Error\nrgba values are out of bounds"
# define NORMAL_RANGE_ERR "Error\nnormal values are out of bounds"
# define NUM_ERR "Error\nnumber contains invalid characters"
# define DIMENSION_ERR "Error\nobject dimensions have to be positive values"

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
