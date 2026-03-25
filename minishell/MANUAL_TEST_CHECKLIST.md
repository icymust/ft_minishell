# Minishell Manual Test Checklist

Use this file to test your `minishell` manually.

How to use:
- Run `./minishell`
- Execute the command or action from each case
- Paste your minishell output under `Your output`
- For `Ctrl+C`, `Ctrl+D`, `Ctrl+\`, describe exactly what happened
- If one test exits the shell, restart `./minishell` and continue
- If a feature is not implemented yet, write `NOT IMPLEMENTED`

## 01. Startup prompt
Action: Start `./minishell`

Your output:

## 02. Empty Enter
Action: Press `Enter` on an empty prompt

Your output:

## 03. Spaces only
Command:
```sh
    
```

Your output:

## 04. Ctrl+D on empty prompt
Action: Press `Ctrl+D` on an empty prompt

Your output:

## 05. Ctrl+C on empty prompt
Action: Press `Ctrl+C` on an empty prompt

Your output:

## 06. Ctrl+\ on empty prompt
Action: Press `Ctrl+\` on an empty prompt

Your output:

## 07. Relative executable with slash
Command:
```sh
./minishell
```

Your output:

## 08. Absolute executable path
Command:
```sh
/bin/echo hello
```

Your output:

## 09. PATH command
Command:
```sh
ls
```

Your output:

## 10. PATH command with args
Command:
```sh
wc -l Makefile
```

Your output:

## 11. Command not found
Command:
```sh
idontexist
```

Your output:

## 12. Directory as command
Command:
```sh
/bin
```

Your output:

## 13. `echo` without args
Command:
```sh
echo
```

Your output:

## 14. `echo` simple text
Command:
```sh
echo hello
```

Your output:

## 15. `echo -n`
Command:
```sh
echo -n hello
```

Your output:

## 16. `echo -nnnn`
Command:
```sh
echo -nnnn hello
```

Your output:

## 17. `echo` multiple args
Command:
```sh
echo hello world 42
```

Your output:

## 18. `echo` single quotes
Command:
```sh
echo 'hello world'
```

Your output:

## 19. `echo` double quotes
Command:
```sh
echo "hello world"
```

Your output:

## 20. `echo` mixed quotes
Command:
```sh
echo "hi" 'there'
```

Your output:

## 21. `echo` adjacent quoted parts
Command:
```sh
echo "ab""cd"
```

Your output:

## 22. `pwd`
Command:
```sh
pwd
```

Your output:

## 23. `cd` relative path
Command:
```sh
cd src
pwd
```

Your output:

## 24. `cd ..`
Command:
```sh
cd ..
pwd
```

Your output:

## 25. `cd` absolute path
Command:
```sh
cd /tmp
pwd
```

Your output:

## 26. `cd` home
Command:
```sh
cd
pwd
```

Your output:

## 27. `cd` invalid path
Command:
```sh
cd /this/path/does/not/exist
```

Your output:

## 28. `cd` too many args
Command:
```sh
cd src libft
```

Your output:

## 29. `env`
Command:
```sh
env
```

Your output:

## 30. `export` without args
Command:
```sh
export
```

Your output:

## 31. `export NAME=value`
Command:
```sh
export TESTVAR=hello
env
```

Your output:

## 32. `export` overwrite existing
Command:
```sh
export TESTVAR=one
export TESTVAR=two
env
```

Your output:

## 33. `unset`
Command:
```sh
export TESTVAR=hello
unset TESTVAR
env
```

Your output:

## 34. `unset` missing name
Command:
```sh
unset NOT_EXIST
```

Your output:

## 35. `exit`
Command:
```sh
exit
```

Your output:

## 36. `$HOME`
Command:
```sh
echo $HOME
```

Your output:

## 37. `$PATH`
Command:
```sh
echo $PATH
```

Your output:

## 38. `$?` after success
Command:
```sh
/usr/bin/true
echo $?
```

Your output:

## 39. `$?` after failure
Command:
```sh
/usr/bin/false
echo $?
```

Your output:

## 40. `$?` after command not found
Command:
```sh
idontexist
echo $?
```

Your output:

## 41. Expansion in double quotes
Command:
```sh
echo "home=$HOME"
```

Your output:

## 42. No expansion in single quotes
Command:
```sh
echo '$HOME'
```

Your output:

## 43. Empty variable
Command:
```sh
echo $VARIABLE_THAT_DOES_NOT_EXIST
```

Your output:

## 44. Input redirection
Command:
```sh
cat < Makefile
```

Your output:

## 45. Output redirection truncate
Command:
```sh
echo hello > out.txt
cat out.txt
```

Your output:

## 46. Output redirection append
Command:
```sh
echo one > out.txt
echo two >> out.txt
cat out.txt
```

Your output:

## 47. Input redirection missing file
Command:
```sh
cat < no_such_file
```

Your output:

## 48. Redirection without command
Command:
```sh
> out.txt
```

Your output: (создался файл)
Minishell>$ > out.txt
Minishell>$ 


## 49. Output redirection on builtin
Command:
```sh
echo hello > builtout.txt
cat builtout.txt
```

Your output:

## 50. `pwd` with redirection
Command:
```sh
pwd > pwdout.txt
cat pwdout.txt
```

Your output:

## 51. Simple pipe
Command:
```sh
echo hello | cat
```

Your output:

## 52. Pipe with external commands
Command:
```sh
ls | wc -l
```

Your output:

## 53. Multiple pipes
Command:
```sh
echo hello world | cat | wc -w
```

Your output:

## 54. Pipe with builtin on left
Command:
```sh
echo hello | wc -c
```

Your output:

## 55. Pipe with builtin on right
Command:
```sh
echo hello | pwd
```

Your output:

## 56. `cd` inside pipeline
Command:
```sh
pwd
echo hello | cd src
pwd
```

Your output:

## 57. Output redirection with pipe
Command:
```sh
echo hello | cat > pipeout.txt
cat pipeout.txt
```

Your output:

## 58. Input redirection with pipe
Command:
```sh
cat < Makefile | wc -l
```

Your output:

## 59. Heredoc basic
Command:
```sh
cat << EOF
hello
world
EOF
```

Your output:

## 60. Heredoc into command
Command:
```sh
wc -l << EOF
one
two
three
EOF
```

Your output:

## 61. Heredoc with pipe
Command:
```sh
cat << EOF | wc -l
a
b
EOF
```

Your output:

## 62. Ctrl+C during heredoc
Action:
```sh
cat << EOF
```
Then press `Ctrl+C`

Your output:

## 63. Ctrl+D during heredoc
Action:
```sh
cat << EOF
```
Then press `Ctrl+D`

Your output:

## 64. Unclosed single quote
Command:
```sh
echo 'hello
```

Your output:

## 65. Unclosed double quote
Command:
```sh
echo "hello
```

Your output:

## 66. Syntax error: leading pipe
Command:
```sh
| ls
```

Your output:

## 67. Syntax error: trailing pipe
Command:
```sh
ls |
```

Your output:

## 68. Syntax error: double pipe unsupported
Command:
```sh
ls || wc
```

Your output:

## 69. Syntax error: `&&` unsupported
Command:
```sh
ls && pwd
```

Your output:

## 70. Syntax error: missing redirect target
Command:
```sh
echo hello >
```

Your output:

## 71. Syntax error: missing input target
Command:
```sh
cat <
```

Your output:

## 72. Unsupported semicolon
Command:
```sh
echo one ; echo two
```

Your output:

## 73. Unsupported backslash behavior
Command:
```sh
echo hello\ world
```

Your output:

## 74. History check
Action: Run several commands, then press `Arrow Up`

Your output:

## 75. Ctrl+C during foreground external command
Action:
```sh
cat
```
Then press `Ctrl+C`

Your output:

## 76. `$?` after Ctrl+C
Command sequence:
```sh
cat
```
Press `Ctrl+C`, then:
```sh
echo $?
```

Your output:

## 77. Ctrl+\ during foreground external command
Action:
```sh
cat
```
Then press `Ctrl+\`

Your output:

## 78. `$?` after Ctrl+\
Command sequence:
```sh
cat
```
Press `Ctrl+\`, then:
```sh
echo $?
```

Your output:

## 79. `exit` after previous error
Command:
```sh
idontexist
exit
```

Your output:

## 80. Memory and fd sanity
Action:
- Run many commands in a row:
```sh
echo hi
pwd
ls
echo hello | wc -c
cat < Makefile | wc -l
```
- Confirm shell still works after all of them

Your output:

## 81. Directory status code
Command:
```sh
/bin
echo $?
```

Your output:

## 82. Heredoc Ctrl+C status
Action:
- Run `cat << EOF`
- Press `Ctrl+C`
- Then run:
```sh
echo $?
```

Your output:

## 83. Foreground external Ctrl+C status
Action:
- Run `cat`
- Press `Ctrl+C`
- Then run:
```sh
echo $?
```

Your output:

## 84. Foreground external Ctrl+\ status
Action:
- Run `cat`
- Press `Ctrl+\`
- Then run:
```sh
echo $?
```

Your output:

## 85. `$?` after Ctrl+C on empty prompt
Action:
- Press `Ctrl+C` on an empty prompt
- Then run:
```sh
echo $?
```

Your output:

## 86. Heredoc line count via `readline`
Command:
```sh
wc -l << EOF
hello
world
EOF
```

Your output:

## 87. Heredoc empty body
Command:
```sh
wc -l << EOF
EOF
```

Your output:

## 88. Heredoc should not print `^M`
Action:
- Run:
```sh
cat << EOF
```
- Type one normal line and press `Enter`
- Confirm the prompt/input does not show `^M`
- Finish with:
```sh
EOF
```

Your output:

## 89. `Ctrl+C` in heredoc after readline change
Action:
- Run `cat << EOF`
- Press `Ctrl+C`
- Then run:
```sh
echo $?
```

Your output:
