### References
- [g++ cheat seat](https://bytes.usc.edu/cs104/wiki/gcc/)

### Sumary cheatsheet table 
- Syntax compile
    ```bash
        # gcc --help or reference at header
        [gcc/g++] [-option] [execute output file] [input files ...]
    ```
- using `gcc` for C and `g++` for C++ or object file `.o`

|option|purpose|
|-|-|
|`gcc file1.c file2.c ...`|only executable and default name, no debug inform, no optimize|
|`gcc -o execute_name file1.c file2.c ...`|only executable with rename and extension, no debug inform, no optimize|
|`gcc -c file1.c file2.c ...`|only compile to object file `.o`|
|`gcc -o execute_name file1.o file2.o ...`|only executable with rename and extension, no debug inform, no optimize|
|<hr>|<hr>|
|`gcc -g ...`| executable with debug info, no optimize|
|`gcc -g0 ...`| like normal executable, no optimize |
|<hr>|<hr>|
|`gcc -O0 ...`| like normal executable, no optimize|
|`gcc [-O1/.../-O3] ...`| optimize faster but file larger|
|`gcc [Os] ...`| optimizest size|
|<hr>|<hr>|
|`gcc -Wall ...`|show all common warning|
|`gcc -Wextra ...`|  show extra warn |
|`gcc -pedantic ...`| show warn ISO C++ rules if you want to be extra safe |
|`gcc -Werror ...`| all warn above become error |

