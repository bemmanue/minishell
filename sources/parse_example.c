#include "minishell.h"

struct s_out
{
	char			*command;
	char			**args;
	char			**redir;
	struct s_out	*next;
};

int	main(void)
{
	struct s_out	*input;

	input = malloc(sizeof (struct s_out *));
	input->command = ft_strdup("cat");
	input->args = malloc(sizeof (char *) * 3);
	input->args[1] = ft_strdup("file1");
	input->args[0] = ft_strdup("file0");
	input->args[2] = NULL;
	input->redir = malloc(sizeof (char *) * 3);
	input->redir[0] = ft_strdup("kamil>");
	input->redir[1] = ft_strdup(">yulya");
	input->redir[2] = NULL;
	input->next = NULL;
	return (0);
}
