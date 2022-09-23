# minishell
This project is about creating a simple shell.

Handles single and double quotes, does not support unclosed quotes.

Does not support semicolon ( ; )

Supports <, <<, >, >> redirections, pipes, enviroment variables.

Handles ctrl-C, ctrl-D, ctrl-\ like in bash.

Has following built-ins: echo, cd, pwd, export, unset, env, exit.

Supports && and || with parenthesis for priorities.

Wildcard * works for current working directory.

For more information see [subject](https://github.com/y-grab/minishell/blob/main/subject/minishell_subject.pdf)
