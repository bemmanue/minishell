
# include "parser.h"

int main(void)
{
	t_command	*command;
	char 		*str;
	int 		i;

	str = readline("hello$ ");
	command = parse_string(str);
	while (command)
	{
		printf("s = %s\n", command->name);
		i = 0;
		while (command->argv && command->argv[i])
		{
			printf("argv = %s\n", command->argv[i]);
			i++;
		}
		i = 0;
		while (command->rdrct && command->rdrct[i])
		{
			printf("rdrct = %s\n", command->rdrct[i]);
			i++;
		}
		command = command->next;
	}
	while (1)
		NULL;
	return (0);
}
