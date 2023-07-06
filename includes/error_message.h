#ifndef ERROR_MESSAGE_H
# define ERROR_MESSAGE_H

//#################### HERE-DOC RELATED ####################//
# define HERE_DOC_EOF "minishell: warning: here-document delimited by end-of-file"

//#################### SYNTAX RELATED ####################//
# define NL_SYNTAX_ERR "minishell: syntax error near unexpected token `newline'"
# define PIPE_SYNTAX_ERR "minishell: syntax error near unexpected token `|'"
# define PIPE2_SYNTAX_ERR "minishell: syntax error near unexpected token `||'"
# define IN_SYNTAX_ERR "minishell: syntax error near unexpected token `<'"
# define IN2_SYNTAX_ERR "minishell: syntax error near unexpected token `<<'"
# define OUT_SYNTAX_ERR "minishell: syntax error near unexpected token `>'"
# define OUT2_SYNTAX_ERR "minishell: syntax error near unexpected token `>>'"
# define IN3_SYNTAX_ERR "minishell: syntax error near unexpected token `<<<'"
# define IO_SYNTAX_ERR "minishell: syntax error near unexpected token `<>'"

#endif
