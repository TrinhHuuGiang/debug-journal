- Result:
```bash
    giangtrinh@giangtrinhLU:~/Documents/test_code/Test_include$ gcc -o test.run a.c b.c c.c
    In file included from a.c:2:
    b.h:6: warning: "MACRO_INCLUDE" redefined
        6 | #define MACRO_INCLUDE 10
        | 
    In file included from b.h:4:
    c.h:4: note: this is the location of the previous definition
        4 | #define MACRO_INCLUDE 1000
        | 
    In file included from b.c:1:
    b.h:6: warning: "MACRO_INCLUDE" redefined
        6 | #define MACRO_INCLUDE 10
        | 
    In file included from b.h:4:
    c.h:4: note: this is the location of the previous definition
        4 | #define MACRO_INCLUDE 1000
        | 

        
    ~/Documents/test_code/Test_include$ ./test.run 
    this is B function. MACRO VALUE: 10
    this is C function. MACRO VALUE: 1000
```

## Comment
- Macro will be use in the file it is defined
- The same macro can reuse but value will fix at compile time:
    - `MACRO_INCLUDE 1000` still be 1000 with `c.h` function
    - `MACRO_INCLUDE 10` still be 10 with `c.h` function
- 2 file has same function can't include together or include the remaining one