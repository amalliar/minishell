#ifndef LEXER_H
# define LEXER_H

enum					e_lexer_states
{
	LS_NORMAL,
	LS_IN_QUOTES,
	LS_IN_DQUOTES,
};

enum					e_token_types
{
	TT_SEMICOLON = ';',
	TT_PIPE = '|',
	TT_LEFT_AB = '<',
	TT_RIGHT_AB = '>',
	TT_RIGHT_DAB,
	TT_DOLLAR = '$',
	TT_WORD,
	TT_NULL = 0
};

typedef struct 			s_token
{
	char				*data;
	int					type;
	struct s_token		*next;
}						t_token;

t_token		*lexer_proc(char *line);
void		lexer_clear(t_token **token_list);

#endif
