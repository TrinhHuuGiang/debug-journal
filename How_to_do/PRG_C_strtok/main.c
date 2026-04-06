// Refer: https://cplusplus.com/reference/cstring/strtok/

/**
 * 
 * (strtok)
 * char * strtok ( char * str, const char * delimiters );
 * 
 * 
 * - Browse through the `str`, stop after found a delimiter.
 *  + modify the delim to `\0` then point `pch` to next position, start new token
 * - If multiple delim as `abc,.,.cd` and delimiters is `,.` => token: "abc","cd"
 * 
 */

/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
{
    char str[] ="- This, a ,, - sample string.";
    char * pch;
    printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok (str," ,.-");
    while (pch != NULL)
    {
        printf ("%s\n",pch);
        pch = strtok (NULL, " ,.-");
    }

    printf ("String after parse \"%s\"\n",str);

    return 0;
}