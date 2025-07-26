# Problem
- [->](#mean-of-binbash-in-shell-script) mean of `#!/bin/bash` in shell script
- [->](#mean-of-export-in-bash-shell) mean of `export` in bash shell


## mean of `#!/bin/bash` in shell script
- Imagine the any shell script require `!/bin/bash`, it like a tell with bash  
    that i need new independent bash shell for work  
    - So independent bash similar with create new `process`, it is not inherit  
        any `Variable` from parent
- `#!/` is called a `shebang`.
## mean of `export` in bash shell
- Because program call by bash can runing at `background` independent by `&` or 
    `#!/bin/bash` with script
    - So `export` is a tag tell OS that these `Variable` grown up to `Environment variable`  
    - With `export` any child `process` of this bash with know what `Variable` is this
    ```bash
        quyet@quyet:~/CODE/note-for-future/Some_bugs/Shell_and_export$ ./parent_has_export.sh
        vvv---child print---vvv
        Hello from parent export hẹllo
        ^^^---print  done---^^^
        quyet@quyet:~/CODE/note-for-future/Some_bugs/Shell_and_export$ ./parent_no_export.sh
        vvv---child print---vvv

        ^^^---print  done---^^^
    ```