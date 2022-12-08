# minishell

Simple shell, heavily inspired by bash.

![Screenshot_20221208_152613](https://user-images.githubusercontent.com/82828987/206446231-1049f760-41d4-4e70-891d-bec08caa982a.png)

### We implemented following features:
◦ Working history.<br />
◦ $PATH.<br />
◦ '' and "" (closed single and double quotes).<br />
◦ Redirections (<, <<(DELIM), >, >>).<br />
◦ Pipes ('|' character).<br />
◦ Ctrl-C, Ctrl-D, Ctrl-\ behaving like in bash.<br />

### Builtins:
◦ echo with option -n.<br />
◦ cd with only a relative or absolute path.<br />
◦ pwd with no options.<br />
◦ export with no options.<br />
◦ unset with no options.<br />
◦ env with no options or arguments.<br />
◦ exit with no options.<br />
