
# include <stdio.h>

# define MY_DEBUG
// Type
# define TYPE_INFO 1
# define TYPE_ERROR 1
// Style
# define STYLE_FLAT 0
# define STYLE_LINE 1
# define STYLE_LINE_START 2
# define STYLE_LINE_END 3
# define STYLE_START 4
# define STYLE_END 5

# define VOID do {} while(0);

# if (defined(MY_DEBUG))

    # define DEBUG_PRINT(type, style, arg) \
        do { \
            if (type == 1) \
            { \
                prePrint(style); \
                printf arg; \
                postPrint(style); \
            } \
        } while (0);

    void prePrint(int type);
    void postPrint(int type);

# else // !defined(MY_DEBUG)

    # define DEBUG_PRINT VOID

# endif // (defined(MY_DEBUG))
