Minishell roadmap

Current state

- Readline loop is in place.
- Tokenizer and lexer exist.
- Parser builds a command pipeline.
- Basic execution works.
- Basic pipes and redirections are partially working.
- Builtins exist, but parent/child behavior still needs review.
- Bonus part is deferred for now.

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
- Re-test simple pipes and redirections.
- Confirm no debug output pollutes command stdout.
- Confirm each stage closes the correct file descriptors.

2. Fix exit status flow
- Track the status of the last foreground pipeline.
- Make $? reflect the last executed pipeline correctly.
- Review child exits in pipeline execution.

3. Finalize quote handling strategy
- Keep raw tokens if needed for parsing clarity.
- Define where quote semantics are resolved.
- Build final argv without shell syntax quotes while preserving intended spaces.
- Respect single quotes and double quotes according to the subject.

4. Implement variable expansion
- Expand $VAR.
- Expand $?.
- Do not expand inside single quotes.
- Expand inside double quotes.

5. Review and finish redirections
- Input redirection: <
- Output redirection: >
- Append redirection: >>
- Error handling for open/dup2 failures.

6. Implement heredoc
- Parse << with delimiter.
- Read until delimiter.
- Feed heredoc content to the command stdin.
- Clean temporary resources correctly.

7. Review builtins behavior
- echo -n
- cd
- pwd
- export
- unset
- env
- exit
- Decide which builtins must run in parent when not inside a pipeline.

8. Fix signal behavior
- Ctrl-C in interactive mode shows a new prompt.
- Ctrl-D exits cleanly.
- Ctrl-\ does nothing in interactive mode.
- Child process signal behavior should match command execution expectations.

9. Cleanup and memory safety
- Free tokens.
- Free pipeline structures.
- Close all used file descriptors.
- Remove heredoc temporary files.
- Recheck for leaks and double frees.

10. Mandatory test checklist
- Simple external command.
- Builtin command.
- Single pipe.
- Multiple pipes.
- Pipe + redirection.
- Invalid command in pipeline.
- Missing file in redirection.
- Quotes with spaces.
- $VAR and $?.
- Heredoc.
- Signals.

After mandatory is stable

- Only then decide whether bonus is worth doing.