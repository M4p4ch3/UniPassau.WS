
# include "debug.h"

# if (defined(MY_DEBUG))

    int indent = 0;
    
    void prePrint(int style)
    {
        // End of a Section
        if (style == STYLE_END)
        {
            // Decrease Ident Level
            indent = indent - 1;
        }

        // No prePrint for style FLAT and LINE_END
        if (style != STYLE_FLAT && style != STYLE_LINE_END)
        {
            // Prints Tabs to match Indent Level
            int iIndent = 0;
            while (iIndent < indent)
            {
                printf("\t");
                iIndent = iIndent + 1;
            }

            // End of a Section
            if (style == STYLE_END)
            {
                printf("-- ");
            }
            // Normal Line
            else // (style != END)
            {
                printf("// ");
            }
        }
    }

    void postPrint(int style)
    {
        // No postPrint for style FLAT and LINE_START
        if (style != STYLE_FLAT && style != STYLE_LINE_START)
        {
            // Start of a Section
            if (style == STYLE_START)
            {
                printf(" --");
            }
            // Normal Line
            else // (style != START)
            {
                printf(" //");
            }

            printf("\r\n");
        }

        // Start of a Section
        if (style == STYLE_START)
        {
            // Increase Ident Level
            indent = indent + 1;
        }
    }

# endif // (defined(MY_DEBUG))
