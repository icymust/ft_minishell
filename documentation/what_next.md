Parsing done
execution and piping and forks

user input
   |
   v
[readline]
   |
   v
[Tokenizer / Lexer]
"echo" "|" "wc" ">" "out.txt"
   |
   v
[Parser]
cmd_set #1: echo ...
cmd_set #2: wc ... > out.txt
   |
   v
[Executor]
fork / pipe / dup2 / builtin / execve
   |
   v
[waitpid + $?]
   |
   v
[cleanup]