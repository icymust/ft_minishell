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
- [partial] Pipes, redirections, and heredoc exist, but still need full mandatory verification.
- [done] $? expansion is implemented.
- [todo] Generic $VAR expansion is still missing.
- [todo] Quote-aware normalization is still incomplete.
- [partial] Builtins exist, but export is still incomplete and parent/child behavior still needs review.
- [done] Bonus part is deferred for now.

What still remains for mandatory

- [todo] Make stateful builtins run in the parent process when there is no pipeline: cd, export, unset, exit.
- [todo] Implement export on top of data->envp.
- [done] Implement unset on top of data->envp.
- [todo] Implement generic environment variable expansion: $VAR.
- [partial] Keep $? expansion, but integrate it into the final quote-aware expansion step.
- [todo] Respect quote rules fully:
   single quotes block expansion, double quotes allow expansion, and shell quotes must not reach execve as syntax characters.
- [partial] Recheck signal behavior against bash in interactive mode and during child execution.
- [partial] Re-test redirection and heredoc error paths.
- [todo] Re-run the mandatory checklist after expansion and builtin fixes.
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
- [partial] Re-test simple pipes and redirections.
- [partial] Confirm no debug output pollutes command stdout.
- [partial] Confirm each stage closes the correct file descriptors.

2. Fix exit status flow
- [done] Track the status of the last foreground pipeline.
- [done] Make $? reflect the last executed pipeline correctly.
- [partial] Review child exits in pipeline execution.

Status: mostly in place, but should be revalidated after builtin parent/child fixes.

3. Finalize quote handling strategy
- [partial] Keep raw tokens if needed for parsing clarity.
- [todo] Define where quote semantics are resolved.
- [todo] Build final argv without shell syntax quotes while preserving intended spaces.
- [todo] Respect single quotes and double quotes according to the subject.

Current gap: quotes are still preserved in tokens, and quote removal/expansion rules are not finalized globally.

4. Implement variable expansion
- [todo] Expand $VAR.
- [done] Expand $?.
- [todo] Do not expand inside single quotes.
- [todo] Expand inside double quotes.

Current gap: only $? is implemented right now.

5. Review and finish redirections
- [partial] Input redirection: <
- [partial] Output redirection: >
- [partial] Append redirection: >>
- [partial] Error handling for open/dup2 failures.

6. Implement heredoc
- [done] Parse << with delimiter.
- [done] Read until delimiter.
- [done] Feed heredoc content to the command stdin.
- [partial] Clean temporary resources correctly.

7. Review builtins behavior
- [done] echo -n
- [partial] cd
- [done] pwd
- [todo] export
- [done] unset
- [done] env
- [partial] exit
- [todo] Decide which builtins must run in parent when not inside a pipeline.

Current gap: export is still TODO, and stateful builtin parent/child behavior should be revalidated after the latest fixes.

8. Fix signal behavior
- [partial] Ctrl-C in interactive mode shows a new prompt.
- [done] Ctrl-D exits cleanly.
- [partial] Ctrl-\ does nothing in interactive mode.
- [todo] Child process signal behavior should match command execution expectations.

9. Cleanup and memory safety
- [done] Free tokens.
- [done] Free pipeline structures.
- [partial] Close all used file descriptors.
- [done] Remove heredoc temporary files.
- [todo] Recheck for leaks and double frees.

10. Mandatory test checklist
- [partial] Simple external command.
- [partial] Builtin command.
- [partial] Single pipe.
- [todo] Multiple pipes.
- [partial] Pipe + redirection.
- [partial] Invalid command in pipeline.
- [partial] Missing file in redirection.
- [todo] Quotes with spaces.
- [partial] $VAR and $?.
- [partial] Heredoc.
- [todo] Signals.

After mandatory is stable

- Only then decide whether bonus is worth doing.
