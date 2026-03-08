readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs

# 42 Minishell - Authorized Functions Documentation

## Readline Functions

### readline()
**Description:** Reads a line from user input with history support and editing capabilities.

**Return:** `char *` - pointer to the read line (must be freed), or `NULL` on EOF

**Usage:**
```c
char *line = readline("minishell$ ");
if (line)
    add_history(line);
```

---

### rl_clear_history()
**Description:** Clears the readline history buffer.

**Return:** `void`

**Usage:**
```c
rl_clear_history();
```

---

### rl_on_new_line()
**Description:** Tells readline the cursor is on a new line (used after signals).

**Return:** `int` - 0 on success

**Usage:**
```c
signal(SIGINT, handler);
// In handler:
rl_on_new_line();
```

---

### rl_replace_line()
**Description:** Replaces the current line content with new text.

**Return:** `int` - 0 on success

**Usage:**
```c
rl_replace_line("new content", 0);
```

---

### rl_redisplay()
**Description:** Redisplays the current line in the terminal.

**Return:** `void`

**Usage:**
```c
rl_redisplay();
```

---

### add_history()
**Description:** Adds a line to the readline history.

**Return:** `void`

**Usage:**
```c
add_history("ls -la");
```

---

## Standard I/O & Memory

### printf()
**Description:** Formatted output to stdout.

**Return:** `int` - number of characters printed

**Usage:**
```c
printf("Value: %d\n", 42);
```

---

### malloc()
**Description:** Allocates memory on the heap.

**Return:** `void *` - pointer to allocated memory, or `NULL` on failure

**Usage:**
```c
char *str = malloc(100 * sizeof(char));
```

---

### free()
**Description:** Deallocates previously allocated memory.

**Return:** `void`

**Usage:**
```c
free(str);
str = NULL;
```

---

### write()
**Description:** Writes data to a file descriptor.

**Return:** `ssize_t` - number of bytes written

**Usage:**
```c
write(1, "Hello\n", 6);
```

---

## File Operations

### access()
**Description:** Checks file accessibility (read, write, execute permissions).

**Return:** `int` - 0 if accessible, -1 on error

**Usage:**
```c
if (access("/bin/ls", X_OK) == 0)
    // File is executable
```

---

### open()
**Description:** Opens a file and returns a file descriptor.

**Return:** `int` - file descriptor, or -1 on error

**Usage:**
```c
int fd = open("file.txt", O_RDONLY);
```

---

### read()
**Description:** Reads data from a file descriptor.

**Return:** `ssize_t` - number of bytes read, 0 on EOF, -1 on error

**Usage:**
```c
char buffer[1024];
ssize_t n = read(fd, buffer, sizeof(buffer));
```

---

### close()
**Description:** Closes a file descriptor.

**Return:** `int` - 0 on success, -1 on error

**Usage:**
```c
close(fd);
```

---

### unlink()
**Description:** Deletes a file.

**Return:** `int` - 0 on success, -1 on error

**Usage:**
```c
unlink("temp_file.txt");
```

---

## File Information

### stat() / lstat() / fstat()
**Description:** Gets file information (size, permissions, timestamps).
- `stat()`: follows symlinks
- `lstat()`: doesn't follow symlinks
- `fstat()`: uses file descriptor

**Return:** `int` - 0 on success, -1 on error

**Usage:**
```c
struct stat sb;
stat("file.txt", &sb);
printf("File size: %ld\n", sb.st_size);
```

---

## Process Management

### fork()
**Description:** Creates a child process (duplicates current process).

**Return:** `pid_t` - 0 in child, child PID in parent, -1 on error

**Usage:**
```c
pid_t pid = fork();
if (pid == 0)
    // Child process
else if (pid > 0)
    // Parent process
```

---

### wait() / waitpid() / wait3() / wait4()
**Description:** Waits for child process termination and retrieves status.

**Return:** `pid_t` - PID of terminated child, -1 on error

**Usage:**
```c
int status;
waitpid(pid, &status, 0);
```

---

## Signal Handling

### signal()
**Description:** Sets a signal handler for a specific signal.

**Return:** `sighandler_t` - previous signal handler

**Usage:**
```c
signal(SIGINT, handle_sigint);
```

---

### sigaction()
**Description:** Advanced signal handler setup with more control.

**Return:** `int` - 0 on success, -1 on error

**Usage:**
```c
struct sigaction sa;
sa.sa_handler = handler;
sigaction(SIGINT, &sa, NULL);
```

---

### sigemptyset() / sigaddset()
**Description:** Manages signal sets for blocking/unblocking.

**Return:** `int` - 0 on success, -1 on error

**Usage:**
```c
sigset_t set;
sigemptyset(&set);
sigaddset(&set, SIGINT);
```

---

### kill()
**Description:** Sends a signal to a process.

**Return:** `int` - 0 on success, -1 on error

**Usage:**
```c
kill(pid, SIGTERM);
```

---

### exit()
**Description:** Terminates the program with exit status.

**Return:** `void` (never returns)

**Usage:**
```c
exit(0);  // Success
```

---

## Directory Management

### getcwd()
**Description:** Gets the current working directory path.

**Return:** `char *` - pointer to buffer with path, or `NULL` on error

**Usage:**
```c
char cwd[PATH_MAX];
getcwd(cwd, sizeof(cwd));
```

---

### chdir()
**Description:** Changes the current working directory.

**Return:** `int` - 0 on success, -1 on error

**Usage:**
```c
chdir("/home/user");
```

---

### opendir() / readdir() / closedir()
**Description:** Opens, reads, and closes directories.

**Return:** `DIR *` / `struct dirent *` / `int`

**Usage:**
```c
DIR *dir = opendir(".");
struct dirent *entry;
while ((entry = readdir(dir)) != NULL)
    printf("%s\n", entry->d_name);
closedir(dir);
```

---

## Process Execution

### execve()
**Description:** Replaces current process with a new program.

**Return:** `int` - -1 on error (doesn't return on success)

**Usage:**
```c
char *argv[] = {"ls", "-la", NULL};
execve("/bin/ls", argv, envp);
```

---

## File Descriptor Duplication

### dup() / dup2()
**Description:** Duplicates file descriptors (for redirection).
- `dup()`: creates new descriptor pointing to same file
- `dup2()`: redirects `oldfd` to `newfd`

**Return:** `int` - new file descriptor, or -1 on error

**Usage:**
```c
dup2(fd, STDOUT_FILENO);  // Redirect stdout to fd
```

---

### pipe()
**Description:** Creates a pipe for inter-process communication.

**Return:** `int` - 0 on success, -1 on error

**Usage:**
```c
int pipefd[2];
pipe(pipefd);
// pipefd[0] = read end, pipefd[1] = write end
```

---

## Error Handling

### strerror()
**Description:** Returns human-readable error message for errno.

**Return:** `char *` - error message string

**Usage:**
```c
char *msg = strerror(errno);
printf("Error: %s\n", msg);
```

---

### perror()
**Description:** Prints error message to stderr with custom prefix and errno description.

**Return:** `void`

**Usage:**
```c
if (fd == -1)
    perror("open");  // Prints: "open: No such file or directory"
```

---

## Terminal Control

### isatty()
**Description:** Checks if file descriptor is associated with a terminal.

**Return:** `int` - 1 if terminal, 0 if not

**Usage:**
```c
if (isatty(STDIN_FILENO))
    // Running in interactive mode
```

---

### ttyname()
**Description:** Returns name of terminal device associated with file descriptor.

**Return:** `char *` - terminal name, or `NULL` on error

**Usage:**
```c
char *term = ttyname(STDIN_FILENO);
printf("Terminal: %s\n", term);
```

---

### ttyslot()
**Description:** Returns the index of the current user's entry in the utmp file (largely obsolete).

**Return:** `int` - slot number, or 0 on error

**Usage:**
```c
int slot = ttyslot();
```

---

### ioctl()
**Description:** Device-specific input/output control operations.

**Return:** `int` - usually 0 on success, -1 on error

**Usage:**
```c
struct winsize ws;
ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
printf("Terminal size: %dx%d\n", ws.ws_col, ws.ws_row);
```

---

### tcgetattr() / tcsetattr()
**Description:** Gets/sets terminal attributes (raw mode, echo, etc.).

**Return:** `int` - 0 on success, -1 on error

**Usage:**
```c
struct termios term;
tcgetattr(STDIN_FILENO, &term);
term.c_lflag &= ~(ECHO);  // Disable echo
tcsetattr(STDIN_FILENO, TCSANOW, &term);
```

---

## Terminal Capability (Termcap)

### tgetent()
**Description:** Loads terminal capability database for specified terminal type.

**Return:** `int` - 1 on success, 0 if not found, -1 on error

**Usage:**
```c
char buffer[2048];
if (tgetent(buffer, getenv("TERM")) == 1)
    // Terminal capabilities loaded
```

---

### tgetflag()
**Description:** Gets boolean terminal capability.

**Return:** `int` - 1 if capability exists, 0 if not

**Usage:**
```c
if (tgetflag("am"))  // Auto margin capability
    // Terminal has auto margins
```

---

### tgetnum()
**Description:** Gets numeric terminal capability.

**Return:** `int` - capability value, or -1 if not found

**Usage:**
```c
int cols = tgetnum("co");  // Number of columns
```

---

### tgetstr()
**Description:** Gets string terminal capability.

**Return:** `char *` - capability string, or `NULL` if not found

**Usage:**
```c
char *area = buffer;
char *clear_seq = tgetstr("cl", &area);  // Clear screen sequence
```

---

### tgoto()
**Description:** Instantiates cursor movement string with parameters.

**Return:** `char *` - formatted capability string

**Usage:**
```c
char *cm = tgetstr("cm", &area);  // Cursor move capability
char *move_str = tgoto(cm, col, row);
```

---

### tputs()
**Description:** Outputs terminal capability string with padding.

**Return:** `int` - 0 on success

**Usage:**
```c
int outchar(int c) { return write(1, &c, 1); }
tputs(clear_seq, 1, outchar);
```

---

## Summary

These functions enable you to build a functional shell with:
- User input handling (readline)
- Process control (fork, execve, wait)
- Signal management (signal, sigaction)
- File I/O and redirection (open, pipe, dup2)
- Directory navigation (chdir, opendir)
- Error handling (strerror, perror)
- Terminal control (termcap, tcgetattr, ioctl)

---

## Required Header Files

Add these includes to your minishell header file:

```c
/* Standard libraries */
#include <stdio.h>          // printf, perror
#include <stdlib.h>         // malloc, free, exit, getenv
#include <unistd.h>         // write, read, close, access, fork, execve, dup, dup2, pipe
                            // getcwd, chdir, isatty, ttyname, ttyslot
#include <string.h>         // strerror
#include <errno.h>          // errno

/* File operations */
#include <fcntl.h>          // open, O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_APPEND
#include <sys/stat.h>       // stat, lstat, fstat, struct stat

/* Process management */
#include <sys/types.h>      // pid_t, size_t, ssize_t
#include <sys/wait.h>       // wait, waitpid, wait3, wait4, WIFEXITED, WEXITSTATUS

/* Signal handling */
#include <signal.h>         // signal, sigaction, kill, sigemptyset, sigaddset
                            // SIGINT, SIGQUIT, struct sigaction

/* Directory operations */
#include <dirent.h>         // opendir, readdir, closedir, DIR, struct dirent

/* Terminal control */
#include <termios.h>        // tcgetattr, tcsetattr, struct termios
#include <sys/ioctl.h>      // ioctl, TIOCGWINSZ, struct winsize

/* Readline */
#include <readline/readline.h>  // readline, rl_clear_history, rl_on_new_line
                                // rl_replace_line, rl_redisplay
#include <readline/history.h>   // add_history

/* Terminal capabilities (termcap) - for bonus */
#include <curses.h>         // Or #include <term.h> depending on system
#include <term.h>           // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

/* Other useful headers */
#include <limits.h>         // PATH_MAX
#include <stdbool.h>        // bool, true, false
```

### Compilation Flags

When compiling your minishell, use these flags:

```bash
# Basic compilation
gcc -Wall -Wextra -Werror -lreadline -o minishell *.c

# With readline in custom location (e.g., Homebrew on macOS)
gcc -Wall -Wextra -Werror -I/usr/local/opt/readline/include \
    -L/usr/local/opt/readline/lib -lreadline -o minishell *.c

# With termcap library (if needed)
gcc -Wall -Wextra -Werror -lreadline -ltermcap -o minishell *.c

# Or with ncurses (modern alternative to termcap)
gcc -Wall -Wextra -Werror -lreadline -lncurses -o minishell *.c
```

### Important Notes

1. **Readline Library**: Must link with `-lreadline`
2. **Termcap**: May need `-ltermcap` or `-lncurses` depending on system
3. **Signal Handling**: Use `sigaction()` instead of `signal()` for better portability
4. **Memory Management**: Always free memory allocated by `readline()`
5. **Error Checking**: Always check return values, especially for system calls
6. **File Descriptors**: Remember to close all opened file descriptors
7. **Child Processes**: Always wait for child processes to avoid zombies
