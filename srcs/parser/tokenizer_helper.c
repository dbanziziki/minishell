#include "tokenizer.h"

char *token_to_str(int token)
{
	if (token == WORD_TOKEN)
		return "WORD";
	else if (token == GREATER_THAN_TOKEN)
		return "GREATER THAN";
	else if (token == LESS_THAN_TOKEN)
		return "LESS THAN";
	else if (token == HEREDOC_TOKEN)
		return "HEREDOC";
	else if (token == EOF_TOKEN)
		return "EOF";
	else if (token == PIPE)
		return "PIPE";
	else if (token == DOUBLE_QUOTE_TOKEN)
		return "DOUBLE QUOTE";
	else if (token == SIMPLE_QUOTE_TOKEN)
		return "SIMPLE QUOTE";
	else if (token == DOLLARSIGN_TOKEN)
		return "DOLLARSIGN";
	else
		return "UNKNOWN";
}
