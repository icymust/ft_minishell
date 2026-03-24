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
martin@ubuntu22:~/Desktop/github/ft_minishell/minishell$ ./minishell 
Minishell>$ 

## 02. Empty Enter
Action: Press `Enter` on an empty prompt

Your output:
Minishell>$ 
Minishell>$ 

## 03. Spaces only
Command:
```sh
    
```

Your output:
Minishell>$       [spaces]
Minishell>$ 

## 04. Ctrl+D on empty prompt
Action: Press `Ctrl+D` on an empty prompt

Your output:
Minishell>$ 
martin@ubuntu22:~/Desktop/github/ft_minishell/minishell$ 

## 05. Ctrl+C on empty prompt
Action: Press `Ctrl+C` on an empty prompt

Your output:
Minishell>$ ^C
Minishell>$ 

## 06. Ctrl+\ on empty prompt
Action: Press `Ctrl+\` on an empty prompt

Your output:
Minishell>$ 

## 07. Relative executable with slash
Command:
```sh
./minishell
```

Your output:
Minishell>$ ./minishell 
Minishell>$ 

## 08. Absolute executable path
Command:
```sh
/bin/echo hello
```

Your output:
Minishell>$ /bin/echo hello
hello
Minishell>$ 

## 09. PATH command
Command:
```sh
ls
```

Your output:
Minishell>$ ls
includes  libft  Makefile  Makefile.local  minishell  src

## 10. PATH command with args
Command:
```sh
wc -l Makefile
```

Your output:
Minishell>$ wc -l Makefile
65 Makefile

## 11. Command not found
Command:
```sh
idontexist
```

Your output:
Minishell>$ idontexist
Command not found: idontexist

## 12. Directory as command
Command:
```sh
/bin
```

Your output:
Minishell>$ /bin
Command not found: /bin

## 13. `echo` without args
Command:
```sh
echo
```

Your output:
Minishell>$ echo

Minishell>$ 

## 14. `echo` simple text
Command:
```sh
echo hello
```

Your output:
Minishell>$ echo hello
hello

## 15. `echo -n`
Command:
```sh
echo -n hello
```

Your output:
Minishell>$ echo -n hello
helloMinishell>$ 

## 16. `echo -nnnn`
Command:
```sh
echo -nnnn hello
```

Your output:
Minishell>$ echo -nnnn hello
helloMinishell>$ 

## 17. `echo` multiple args
Command:
```sh
echo hello world 42
```

Your output:
Minishell>$ echo hello world 42
hello world 42
Minishell>$ 

## 18. `echo` single quotes
Command:
```sh
echo 'hello world'
```

Your output:
Minishell>$ echo 'hello world'
hello world
Minishell>$ 

## 19. `echo` double quotes
Command:
```sh
echo "hello world"
```

Your output:
Minishell>$ echo "hello world"
hello world
Minishell>$ 

## 20. `echo` mixed quotes
Command:
```sh
echo "hi" 'there'
```

Your output:
Minishell>$ echo "hi" 'there'
hi there
Minishell>$ 

## 21. `echo` adjacent quoted parts
Command:
```sh
echo "ab""cd"
```

Your output:
Minishell>$ echo "ab""cd"
abcd
Minishell>$ 

## 22. `pwd`
Command:
```sh
pwd
```

Your output:
Minishell>$ pwd
/home/martin/Desktop/github/ft_minishell/minishell
Minishell>$ 

## 23. `cd` relative path
Command:
```sh
cd src
pwd
```

Your output:
Minishell>$ cd src
Minishell>$ pwd
/home/martin/Desktop/github/ft_minishell/minishell/src
Minishell>$ 

## 24. `cd ..`
Command:
```sh
cd ..
pwd
```

Your output:
Minishell>$ cd ..
Minishell>$ pwd
/home/martin/Desktop/github/ft_minishell/minishell
Minishell>$ 

## 25. `cd` absolute path
Command:
```sh
cd /tmp
pwd
```

Your output:
Minishell>$ cd /tmp
Minishell>$ pwd
/tmp
Minishell>$ 

## 26. `cd` home
Command:
```sh
cd
pwd
```

Your output:
Minishell>$ cd
Minishell>$ pwd
/home/martin
Minishell>$ 

## 27. `cd` invalid path
Command:
```sh
cd /this/path/does/not/exist
```

Your output:
Minishell>$ cd /this/path/does/not/exist
cd: No such file or directory
Minishell>$ 

## 28. `cd` too many args
Command:
```sh
cd src libft
```

Your output:
Minishell>$ cd src libft
cd: too many arguments
Minishell>$ 

## 29. `env`
Command:
```sh
env
```

Your output:
Minishell>$ env
SHELL=/bin/bash
COLORTERM=truecolor
TERM_PROGRAM_VERSION=1.112.0
LANGUAGE=en_US:
LC_ADDRESS=ru_RU.UTF-8
LC_NAME=ru_RU.UTF-8
LC_MONETARY=ru_RU.UTF-8
PWD=/home/martin/Desktop/github/ft_minishell/minishell
LOGNAME=martin
XDG_SESSION_TYPE=tty
VSCODE_GIT_ASKPASS_NODE=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/node
MOTD_SHOWN=pam
HOME=/home/martin
LC_PAPER=ru_RU.UTF-8
LANG=en_US.UTF-8
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
GIT_ASKPASS=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/extensions/git/dist/askpass.sh
SSH_CONNECTION=192.168.1.111 59029 192.168.1.116 22
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_PYTHON_AUTOACTIVATE_GUARD=1
LESSCLOSE=/usr/bin/lesspipe %s %s
XDG_SESSION_CLASS=user
TERM=xterm-256color
LC_IDENTIFICATION=ru_RU.UTF-8
LESSOPEN=| /usr/bin/lesspipe %s
USER=martin
VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-8668239cfb.sock
SHLVL=2
LC_TELEPHONE=ru_RU.UTF-8
LC_MEASUREMENT=ru_RU.UTF-8
XDG_SESSION_ID=17
XDG_RUNTIME_DIR=/run/user/1000
SSH_CLIENT=192.168.1.111 59029 22
LC_TIME=ru_RU.UTF-8
VSCODE_GIT_ASKPASS_MAIN=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/extensions/git/dist/askpass-main.js
XDG_DATA_DIRS=/usr/share/gnome:/usr/local/share:/usr/share:/var/lib/snapd/desktop
BROWSER=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/helpers/browser.sh
PATH=/home/martin/.local/bin:/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/remote-cli:/home/martin/.local/bin:/home/martin/.local/bin:/home/martin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
LC_NUMERIC=ru_RU.UTF-8
OLDPWD=/home/martin/Desktop/github/ft_minishell
TERM_PROGRAM=vscode
VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-a9b06bae-4ff5-4eca-97a0-b158b061f681.sock
_=./minishell
Minishell>$ 

## 30. `export` without args
Command:
```sh
export
```

Your output:
Minishell>$ export
SHELL=/bin/bash
COLORTERM=truecolor
TERM_PROGRAM_VERSION=1.112.0
LANGUAGE=en_US:
LC_ADDRESS=ru_RU.UTF-8
LC_NAME=ru_RU.UTF-8
LC_MONETARY=ru_RU.UTF-8
PWD=/home/martin/Desktop/github/ft_minishell/minishell
LOGNAME=martin
XDG_SESSION_TYPE=tty
VSCODE_GIT_ASKPASS_NODE=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/node
MOTD_SHOWN=pam
HOME=/home/martin
LC_PAPER=ru_RU.UTF-8
LANG=en_US.UTF-8
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
GIT_ASKPASS=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/extensions/git/dist/askpass.sh
SSH_CONNECTION=192.168.1.111 59029 192.168.1.116 22
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_PYTHON_AUTOACTIVATE_GUARD=1
LESSCLOSE=/usr/bin/lesspipe %s %s
XDG_SESSION_CLASS=user
TERM=xterm-256color
LC_IDENTIFICATION=ru_RU.UTF-8
LESSOPEN=| /usr/bin/lesspipe %s
USER=martin
VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-8668239cfb.sock
SHLVL=2
LC_TELEPHONE=ru_RU.UTF-8
LC_MEASUREMENT=ru_RU.UTF-8
XDG_SESSION_ID=17
XDG_RUNTIME_DIR=/run/user/1000
SSH_CLIENT=192.168.1.111 59029 22
LC_TIME=ru_RU.UTF-8
VSCODE_GIT_ASKPASS_MAIN=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/extensions/git/dist/askpass-main.js
XDG_DATA_DIRS=/usr/share/gnome:/usr/local/share:/usr/share:/var/lib/snapd/desktop
BROWSER=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/helpers/browser.sh
PATH=/home/martin/.local/bin:/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/remote-cli:/home/martin/.local/bin:/home/martin/.local/bin:/home/martin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
LC_NUMERIC=ru_RU.UTF-8
OLDPWD=/home/martin/Desktop/github/ft_minishell
TERM_PROGRAM=vscode
VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-a9b06bae-4ff5-4eca-97a0-b158b061f681.sock
_=./minishell
Minishell>$ 

## 31. `export NAME=value`
Command:
```sh
export TESTVAR=hello
env
```

Your output:
Minishell>$ export TESTVAR=hello
Minishell>$ env
SHELL=/bin/bash
COLORTERM=truecolor
TERM_PROGRAM_VERSION=1.112.0
LANGUAGE=en_US:
LC_ADDRESS=ru_RU.UTF-8
LC_NAME=ru_RU.UTF-8
LC_MONETARY=ru_RU.UTF-8
PWD=/home/martin/Desktop/github/ft_minishell/minishell
LOGNAME=martin
XDG_SESSION_TYPE=tty
VSCODE_GIT_ASKPASS_NODE=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/node
MOTD_SHOWN=pam
HOME=/home/martin
LC_PAPER=ru_RU.UTF-8
LANG=en_US.UTF-8
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
GIT_ASKPASS=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/extensions/git/dist/askpass.sh
SSH_CONNECTION=192.168.1.111 59029 192.168.1.116 22
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_PYTHON_AUTOACTIVATE_GUARD=1
LESSCLOSE=/usr/bin/lesspipe %s %s
XDG_SESSION_CLASS=user
TERM=xterm-256color
LC_IDENTIFICATION=ru_RU.UTF-8
LESSOPEN=| /usr/bin/lesspipe %s
USER=martin
VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-8668239cfb.sock
SHLVL=2
LC_TELEPHONE=ru_RU.UTF-8
LC_MEASUREMENT=ru_RU.UTF-8
XDG_SESSION_ID=17
XDG_RUNTIME_DIR=/run/user/1000
SSH_CLIENT=192.168.1.111 59029 22
LC_TIME=ru_RU.UTF-8
VSCODE_GIT_ASKPASS_MAIN=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/extensions/git/dist/askpass-main.js
XDG_DATA_DIRS=/usr/share/gnome:/usr/local/share:/usr/share:/var/lib/snapd/desktop
BROWSER=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/helpers/browser.sh
PATH=/home/martin/.local/bin:/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/remote-cli:/home/martin/.local/bin:/home/martin/.local/bin:/home/martin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
LC_NUMERIC=ru_RU.UTF-8
OLDPWD=/home/martin/Desktop/github/ft_minishell
TERM_PROGRAM=vscode
VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-a9b06bae-4ff5-4eca-97a0-b158b061f681.sock
_=./minishell
TESTVAR=hello
Minishell>$ 

## 32. `export` overwrite existing
Command:
```sh
export TESTVAR=one
export TESTVAR=two
env
```

Your output:
Minishell>$ export TESTVAR=one
Minishell>$ export TESTVAR=two
Minishell>$ env
SHELL=/bin/bash
COLORTERM=truecolor
TERM_PROGRAM_VERSION=1.112.0
LANGUAGE=en_US:
LC_ADDRESS=ru_RU.UTF-8
LC_NAME=ru_RU.UTF-8
LC_MONETARY=ru_RU.UTF-8
PWD=/home/martin/Desktop/github/ft_minishell/minishell
LOGNAME=martin
XDG_SESSION_TYPE=tty
VSCODE_GIT_ASKPASS_NODE=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/node
MOTD_SHOWN=pam
HOME=/home/martin
LC_PAPER=ru_RU.UTF-8
LANG=en_US.UTF-8
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
GIT_ASKPASS=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/extensions/git/dist/askpass.sh
SSH_CONNECTION=192.168.1.111 59029 192.168.1.116 22
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_PYTHON_AUTOACTIVATE_GUARD=1
LESSCLOSE=/usr/bin/lesspipe %s %s
XDG_SESSION_CLASS=user
TERM=xterm-256color
LC_IDENTIFICATION=ru_RU.UTF-8
LESSOPEN=| /usr/bin/lesspipe %s
USER=martin
VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-8668239cfb.sock
SHLVL=2
LC_TELEPHONE=ru_RU.UTF-8
LC_MEASUREMENT=ru_RU.UTF-8
XDG_SESSION_ID=17
XDG_RUNTIME_DIR=/run/user/1000
SSH_CLIENT=192.168.1.111 59029 22
LC_TIME=ru_RU.UTF-8
VSCODE_GIT_ASKPASS_MAIN=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/extensions/git/dist/askpass-main.js
XDG_DATA_DIRS=/usr/share/gnome:/usr/local/share:/usr/share:/var/lib/snapd/desktop
BROWSER=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/helpers/browser.sh
PATH=/home/martin/.local/bin:/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/remote-cli:/home/martin/.local/bin:/home/martin/.local/bin:/home/martin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
LC_NUMERIC=ru_RU.UTF-8
OLDPWD=/home/martin/Desktop/github/ft_minishell
TERM_PROGRAM=vscode
VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-a9b06bae-4ff5-4eca-97a0-b158b061f681.sock
_=./minishell
TESTVAR=two
Minishell>$ 

## 33. `unset`
Command:
```sh
export TESTVAR=hello
unset TESTVAR
env
```

Your output:
Minishell>$ export TESTVAR=hello
Minishell>$ unset TESTVAR
Minishell>$ env
SHELL=/bin/bash
COLORTERM=truecolor
TERM_PROGRAM_VERSION=1.112.0
LANGUAGE=en_US:
LC_ADDRESS=ru_RU.UTF-8
LC_NAME=ru_RU.UTF-8
LC_MONETARY=ru_RU.UTF-8
PWD=/home/martin/Desktop/github/ft_minishell/minishell
LOGNAME=martin
XDG_SESSION_TYPE=tty
VSCODE_GIT_ASKPASS_NODE=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/node
MOTD_SHOWN=pam
HOME=/home/martin
LC_PAPER=ru_RU.UTF-8
LANG=en_US.UTF-8
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
GIT_ASKPASS=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/extensions/git/dist/askpass.sh
SSH_CONNECTION=192.168.1.111 59029 192.168.1.116 22
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_PYTHON_AUTOACTIVATE_GUARD=1
LESSCLOSE=/usr/bin/lesspipe %s %s
XDG_SESSION_CLASS=user
TERM=xterm-256color
LC_IDENTIFICATION=ru_RU.UTF-8
LESSOPEN=| /usr/bin/lesspipe %s
USER=martin
VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-8668239cfb.sock
SHLVL=2
LC_TELEPHONE=ru_RU.UTF-8
LC_MEASUREMENT=ru_RU.UTF-8
XDG_SESSION_ID=17
XDG_RUNTIME_DIR=/run/user/1000
SSH_CLIENT=192.168.1.111 59029 22
LC_TIME=ru_RU.UTF-8
VSCODE_GIT_ASKPASS_MAIN=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/extensions/git/dist/askpass-main.js
XDG_DATA_DIRS=/usr/share/gnome:/usr/local/share:/usr/share:/var/lib/snapd/desktop
BROWSER=/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/helpers/browser.sh
PATH=/home/martin/.local/bin:/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/remote-cli:/home/martin/.local/bin:/home/martin/.local/bin:/home/martin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
LC_NUMERIC=ru_RU.UTF-8
OLDPWD=/home/martin/Desktop/github/ft_minishell
TERM_PROGRAM=vscode
VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-a9b06bae-4ff5-4eca-97a0-b158b061f681.sock
_=./minishell
Minishell>$ 

## 34. `unset` missing name
Command:
```sh
unset NOT_EXIST
```

Your output:
Minishell>$ unset NOT_EXIST
Minishell>$ 

## 35. `exit`
Command:
```sh
exit
```

Your output:
Minishell>$ exit
martin@ubuntu22:~/Desktop/github/ft_minishell/minishell$ 

## 36. `$HOME`
Command:
```sh
echo $HOME
```

Your output:
Minishell>$ echo $HOME
/home/martin
Minishell>$ 

## 37. `$PATH`
Command:
```sh
echo $PATH
```

Your output:
Minishell>$ echo $PATH
/home/martin/.local/bin:/home/martin/.vscode-server/cli/servers/Stable-07ff9d6178ede9a1bd12ad3399074d726ebe6e43/server/bin/remote-cli:/home/martin/.local/bin:/home/martin/.local/bin:/home/martin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
Minishell>$ 

## 38. `$?` after success
Command:
```sh
/usr/bin/true
echo $?
```

Your output:
Minishell>$ /usr/bin/true
Minishell>$ echo $?
0
Minishell>$ 

## 39. `$?` after failure
Command:
```sh
/usr/bin/false
echo $?
```

Your output:
Minishell>$ /usr/bin/false
Minishell>$ echo $?
1
Minishell>$ 

## 40. `$?` after command not found
Command:
```sh
idontexist
echo $?
```

Your output:
Minishell>$ idontexist
Command not found: idontexist
Minishell>$ echo $?
127
Minishell>$ 

## 41. Expansion in double quotes
Command:
```sh
echo "home=$HOME"
```

Your output:
Minishell>$ echo "home=$HOME"
home=/home/martin
Minishell>$ 

## 42. No expansion in single quotes
Command:
```sh
echo '$HOME'
```

Your output:
Minishell>$ echo '$HOME'
$HOME
Minishell>$ 

## 43. Empty variable
Command:
```sh
echo $VARIABLE_THAT_DOES_NOT_EXIST
```

Your output:
Minishell>$ echo $VARIABLE_THAT_DOES_NOT_EXIST

Minishell>$ 

## 44. Input redirection
Command:
```sh
cat < Makefile
```

Your output:
Minishell>$ cat < Makefile
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
        src/builtin/builtin.c \
        src/builtin/builtin_export.c \
        src/builtin/builtin_export_utils.c \
        src/builtin/builtin_unset.c \
        src/builtin/builtin_env.c \
        src/builtin/builtin_echo.c  \
        src/builtin/builtin_cd.c \
        src/builtin/builtin_pwd.c \
        src/data/data.c \
        src/data/envp.c \
        src/execution/execution.c \
        src/execution/execution_external_utils.c \
        src/execution/exec_utils.c \
        src/execution/pipeline_free.c \
        src/serialize/tokenizer.c \
        src/serialize/token_list.c \
        src/serialize/lexer.c \
        src/serialize/cmd_set.c \
        src/serialize/cmd_redirect.c \
        src/utils/utils.c \
        src/utils/exit.c \
        src/minishell.c \
        src/serialize/pipeline_build.c \
        src/execution/pipeline_exec.c \
        src/execution/pipeline_heredoc.c \
        src/execution/pipeline_parent_builtin.c \
        src/execution/pipeline_parent_utils.c \
        src/execution/pipeline_parent_redir.c \
        src/core/signals.c \
        src/expand/expand.c \
        src/expand/expand_len.c \
        src/expand/expand_build.c \
        src/expand/expand_utils.c \
        src/execution/pipeline_child.c

HEADERS = includes/minishell.h

INCLUDE = -I ./includes -I ./libft/includes

LIBFT = -Llibft -lft

all: libft $(NAME)

$(NAME): ${SRCS} ${HEADERS}
        @$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) $(LIBFT) -lreadline -o $(NAME)

libft:
        @$(MAKE) -C ./libft

re: fclean all

clean:
        $(MAKE) clean -C ./libft

fclean: clean
        $(MAKE) fclean -C ./libft
        rm -f $(NAME)
        rm -rf $(NAME).dSYM

.PHONY: all libft clean fclean re $(NAME) 
Minishell>$ 

## 45. Output redirection truncate
Command:
```sh
echo hello > out.txt
cat out.txt
```

Your output:
Minishell>$ echo hello > out.txt
Minishell>$ cat out.txt
hello
Minishell>$ 

## 46. Output redirection append
Command:
```sh
echo one > out.txt
echo two >> out.txt
cat out.txt
```

Your output:
Minishell>$ echo one > out.txt
Minishell>$ echo two >> out.txt
Minishell>$ cat out.txt
one
two
Minishell>$ 

## 47. Input redirection missing file
Command:
```sh
cat < no_such_file
```

Your output:
Minishell>$ cat < no_such_file
minishell: infile: No such file or directory
Minishell>$ 

## 48. Redirection without command
Command:
```sh
> out.txt
```

Your output:
Minishell>$ > out.txt
Syntax error: missing redirection target
Pipeline creation failed
martin@ubuntu22:~/Desktop/github/ft_minishell/minishell$ 

## 49. Output redirection on builtin
Command:
```sh
echo hello > builtout.txt
cat builtout.txt
```

Your output:
Minishell>$ echo hello > builtout.txt
Minishell>$ cat builtout.txt
hello
Minishell>$ 

## 50. `pwd` with redirection
Command:
```sh
pwd > pwdout.txt
cat pwdout.txt
```

Your output:
Minishell>$ pwd > pwdout.txt
Minishell>$ cat pwdout.txt
/home/martin/Desktop/github/ft_minishell/minishell
Minishell>$ 

## 51. Simple pipe
Command:
```sh
echo hello | cat
```

Your output:
Minishell>$ echo hello | cat
hello
Minishell>$ 

## 52. Pipe with external commands
Command:
```sh
ls | wc -l
```

Your output:
Minishell>$ ls | wc -l
10
Minishell>$ 

## 53. Multiple pipes
Command:
```sh
echo hello world | cat | wc -w
```

Your output:
Minishell>$ echo hello world | cat | wc -w
2
Minishell>$ 

## 54. Pipe with builtin on left
Command:
```sh
echo hello | wc -c
```

Your output:
Minishell>$ echo hello | wc -c
6
Minishell>$ 

## 55. Pipe with builtin on right
Command:
```sh
echo hello | pwd
```

Your output:
Minishell>$ echo hello | pwd
/home/martin/Desktop/github/ft_minishell/minishell
Minishell>$ 

## 56. `cd` inside pipeline
Command:
```sh
pwd
echo hello | cd src
pwd
```

Your output:
Minishell>$ pwd
/home/martin/Desktop/github/ft_minishell/minishell
Minishell>$ echo hello | cd src
Minishell>$ pwd
/home/martin/Desktop/github/ft_minishell/minishell
Minishell>$ 

## 57. Output redirection with pipe
Command:
```sh
echo hello | cat > pipeout.txt
cat pipeout.txt
```

Your output:
Minishell>$ echo hello | cat > pipeout.txt
Minishell>$ cat pipeout.txt
hello
Minishell>$ 

## 58. Input redirection with pipe
Command:
```sh
cat < Makefile | wc -l
```

Your output:
Minishell>$ cat < Makefile | wc -l
65
Minishell>$ 

## 59. Heredoc basic
Command:
```sh
cat << EOF
hello
world
EOF
```

Your output:
Minishell>$ cat << EOF
heredoc> hello
heredoc> world
heredoc> EOF
hello
world
Minishell>$ 

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
Minishell>$ wc -l << EOF
heredoc> one
heredoc> two
heredoc> three
heredoc> EOF
3
Minishell>$ 

## 61. Heredoc with pipe
Command:
```sh
cat << EOF | wc -l
a
b
EOF
```

Your output:
Minishell>$ cat << EOF | wc -l
heredoc> a
heredoc> b
heredoc> EOF
2
Minishell>$ 

## 62. Ctrl+C during heredoc
Action:
```sh
cat << EOF
```
Then press `Ctrl+C`

Your output:
Minishell>$ cat << EOF
heredoc> ^C
heredoc> 

## 63. Ctrl+D during heredoc
Action:
```sh
cat << EOF
```
Then press `Ctrl+D`

Your output:
Minishell>$ cat << EOF
heredoc> 
Minishell>$ 

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
Minishell>$ echo 'hello

Minishell>$ 

## 66. Syntax error: leading pipe
Command:
```sh
| ls
```

Your output:
Minishell>$ | ls
'$'   builtout.txt   includes   libft   Makefile   Makefile.local   minishell   out.txt   pipeout.txt   pwdout.txt   src
Minishell>$ 

## 67. Syntax error: trailing pipe
Command:
```sh
ls |
```

Your output:
Minishell>$ ls |
'$'   builtout.txt   includes   libft   Makefile   Makefile.local   minishell   out.txt   pipeout.txt   pwdout.txt   src
Minishell>$ 

## 68. Syntax error: double pipe unsupported
Command:
```sh
ls || wc
```

Your output:
Minishell>$ ls || wc
Lexer error: unsupported operator '||'
Syntax error: unexpected token after redirection path

Minishell>$ '$'   builtout.txt   includes   libft   Makefile   Makefile.local   minishell   out.txt   pipeout.txt   pwdout.txt   src
Minishell>$ 

## 69. Syntax error: `&&` unsupported
Command:
```sh
ls && pwd
```

Your output:
Minishell>$ ls && pwd
Lexer error: unsupported operator '&&'
Syntax error: unexpected token after redirection path

Minishell>$ '$'   builtout.txt   includes   libft   Makefile   Makefile.local   minishell   out.txt   pipeout.txt   pwdout.txt   src
Minishell>$ 

## 70. Syntax error: missing redirect target
Command:
```sh
echo hello >
```

Your output:
Minishell>$ echo hello >
Syntax error: missing redirection target
Pipeline creation failed
martin@ubuntu22:~/Desktop/github/ft_minishell/minishell$ 

## 71. Syntax error: missing input target
Command:
```sh
cat <
```

Your output:
Minishell>$ cat <
Syntax error: missing redirection target
Pipeline creation failed
martin@ubuntu22:~/Desktop/github/ft_minishell/minishell$ 

## 72. Unsupported semicolon
Command:
```sh
echo one ; echo two
```

Your output:
Minishell>$ echo one ; echo two
one ; echo two
Minishell>$ 

## 73. Unsupported backslash behavior
Command:
```sh
echo hello\ world
```

Your output:
Minishell>$ echo hello\ world
hello\ world
Minishell>$ 

## 74. History check
Action: Run several commands, then press `Arrow Up`

Your output:
`Arrow Up`
Minishell>$ echo hello\ world
`Arrow Up`
Minishell>$ echo one ; echo two

## 75. Ctrl+C during foreground external command
Action:
```sh
cat
```
Then press `Ctrl+C`

Your output:
Minishell>$ cat
^CMinishell>$ 

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
Minishell>$ cat
^CMinishell>$ echo $?
130
Minishell>$ 

## 77. Ctrl+\ during foreground external command
Action:
```sh
cat
```
Then press `Ctrl+\`

Your output:
Minishell>$ cat
^\Minishell>$ 

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
Minishell>$ cat
^\Minishell>echo $?
131
Minishell>$ 

## 79. `exit` after previous error
Command:
```sh
idontexist
exit
```

Your output:
Minishell>$ idontexist
Command not found: idontexist
Minishell>$ exit
martin@ubuntu22:~/Desktop/github/ft_minishell/minishell$ 

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

Minishell>$ echo hi
hi
Minishell>$ pwd
/home/martin/Desktop/github/ft_minishell/minishell
Minishell>$ ls
'$'   builtout.txt   includes   libft   Makefile   Makefile.local   minishell   out.txt   pipeout.txt   pwdout.txt   src
Minishell>$ echo hello | wc -c
6
Minishell>$ cat < Makefile | wc -l
65
Minishell>$ 



## Fix Queue
Work through these one by one.

Priority 1: syntax errors must not exit minishell
- [x] 48. `> out.txt` should not kill the shell. It currently reports a syntax error and exits.
- [x] 70. `echo hello >` should report syntax error and stay in minishell.
- [x] 71. `cat <` should report syntax error and stay in minishell.

Priority 2: unclosed quotes
- [x] 64. Unclosed single quote is not handled correctly.
- [x] 65. Unclosed double quote is not handled correctly.

Priority 3: pipe syntax validation
- [x] 66. `| ls` should be a syntax error, but `ls` is executed.
- [x] 67. `ls |` should be a syntax error, but `ls` is executed.
- [x] 68. `ls || wc` prints an error but still executes `ls`.
- [x] 69. `ls && pwd` prints an error but still executes `ls`.

Priority 4: heredoc signal handling
- [x] 62. `Ctrl+C` during heredoc should abort heredoc and return to the main prompt.

Priority 5: signal output formatting
- [x] 75. `Ctrl+C` during foreground external command prints prompt on the same line.
- [x] 77. `Ctrl+\\` during foreground external command prints wrong output/prompt behavior.
- [x] 78. `$?` after `Ctrl+\\` is correct, but prompt/output formatting is still wrong.

Optional cleanup
- [x] 12. Running a directory as a command should not say `Command not found`.
