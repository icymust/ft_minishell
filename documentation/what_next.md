Minishell roadmap

Status legend

- [done] implemented and manually verified at least once
- [partial] implemented in part or still needs mandatory-level validation
- [todo] still missing or clearly incomplete

Current state

- [done] Readline loop is in place.
- [done] Tokenizer and lexer exist.
- [done] Parser builds a command pipeline.
- [done] Basic execution works.
- [partial] Pipes, redirections, and heredoc work in core mandatory cases, but fd/signal/error-path verification is still open.
- [done] Stateful builtins run in the parent when there is no pipeline.
- [done] $? expansion is implemented.
- [done] Generic $VAR expansion is implemented for commands, arguments, and redirection paths.
- [done] Quote-aware normalization is implemented for mandatory cases; shell quotes no longer reach execve as syntax.
- [done] Mandatory builtins are in place for the current project scope.
- [done] Bonus part is deferred for now.

What still remains for mandatory

- [done] Make stateful builtins run in the parent process when there is no pipeline: cd, export, unset, exit.
- [done] Implement export on top of data->envp.
- [done] Implement unset on top of data->envp.
- [done] Implement generic environment variable expansion: $VAR.
- [done] Keep $? expansion, but integrate it into the final quote-aware expansion step.
- [done] Respect quote rules fully for the mandatory parser/executor path:
   single quotes block expansion, double quotes allow expansion, and shell quotes must not reach execve as syntax characters.
- [done] Fix builtin failure statuses where mandatory commands still report success, notably cd.
- [partial] Recheck signal behavior against bash in interactive mode and during child execution.
- [partial] Re-test redirection and heredoc error paths.
- [partial] Re-run the mandatory checklist after expansion and builtin fixes.
- [todo] Re-run memory checks and file descriptor cleanup checks.

High-level flow

user input
   |
   v
[readline]
   |
   v
[Tokenizer / Lexer]
raw tokens: words / operators / quoted segments
   |
   v
[Parser]
cmd_set #1: command + args + redirects
cmd_set #2: command + args + redirects
   |
   v
[Expansion / normalization]
$VAR / $? / quote rules / final argv building
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

Rules we follow

- Mandatory part first.
- No bonus work for now: no &&, no ||, no wildcards.
- We may keep raw token text with quotes while parsing if it helps preserve grouped spaces.
- Before execution, shell syntax must still be normalized into the final argv:
  quotes must not be passed as syntax characters to execve, and expansions must respect single and double quote rules.

Ordered plan

1. Stabilize pipeline behavior
- [done] Re-test simple pipes and redirections.
- [partial] Confirm no debug output pollutes command stdout.
- [partial] Confirm each stage closes the correct file descriptors.

2. Fix exit status flow
- [done] Track the status of the last foreground pipeline.
- [done] Make $? reflect the last executed pipeline correctly.
- [partial] Review child exits in pipeline execution.

Status: core pipe/redirection behavior and mandatory expansion smoke tests passed on March 19, 2026; fd and signal cleanup still need work.

3. Finalize quote handling strategy
- [partial] Keep raw tokens if needed for parsing clarity.
- [done] Define where quote semantics are resolved.
- [done] Build final argv without shell syntax quotes while preserving intended spaces.
- [done] Respect single quotes and double quotes according to the subject.

Current gap: base quote handling is in place for mandatory execution; remaining work is signals, fd cleanup, and final error-path rechecks.

4. Implement variable expansion
- [done] Expand $VAR.
- [done] Expand $?.
- [done] Do not expand inside single quotes.
- [done] Expand inside double quotes.

Current gap: mandatory variable expansion is in place; remaining validation is around signals and redirection/heredoc edge cases.

5. Review and finish redirections
- [done] Input redirection: <
- [done] Output redirection: >
- [done] Append redirection: >>
- [partial] Error handling for open/dup2 failures.

6. Implement heredoc
- [done] Parse << with delimiter.
- [done] Read until delimiter.
- [done] Feed heredoc content to the command stdin.
- [done] Clean heredoc resources correctly without temporary files.

7. Review builtins behavior
- [done] echo -n
- [done] cd
- [done] pwd
- [done] export
- [done] unset
- [done] env
- [done] exit
- [done] Decide which builtins must run in parent when not inside a pipeline.

Current gap: builtin set is stable for mandatory scope; remaining work is now mostly signals, fd cleanup, and final validation.

8. Fix signal behavior
- [partial] Ctrl-C in interactive mode shows a new prompt.
- [done] Ctrl-D exits cleanly.
- [partial] Ctrl-\ does nothing in interactive mode.
- [todo] Child process signal behavior should match command execution expectations.

9. Cleanup and memory safety
- [done] Free tokens.
- [done] Free pipeline structures.
- [partial] Close all used file descriptors.
- [done] Heredoc uses pipe fds instead of temporary files.
- [todo] Recheck for leaks and double frees.

10. Mandatory test checklist
- [done] Simple external command.
- [done] Builtin command.
- [done] Single pipe.
- [done] Multiple pipes.
- [done] Pipe + redirection.
- [done] Invalid command in pipeline.
- [done] Missing file in redirection.
- [done] Quotes with spaces.
- [done] $VAR and $?.
- [done] Heredoc.
- [todo] Signals.

After mandatory is stable

- Only then decide whether bonus is worth doing.
