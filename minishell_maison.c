#include "minishell.h"


// A faire = faire la difference entre double quote et single quote
//         = substitution de commande : une string prend le resultat d'une commande  
//         = E0F 




/* MAN MINISHELL 
    TYPE 1 = WORD
    TYPE 2 = ARGUMENTS
    TYPE 3 = DOUBLE QUOTE
    TYPE 4 = SIMPLE QUOTE
    TYPE 5 = EXTENSION  PIPE 6 ou 5? on va dire PIPE 5 du coup je pense a voir
    TYPE 6 = PIPE
    TYPE 7 = INFILE
    TYPE 8 = OUTFILE
    TYPE 9 = &&
    TYPE 10 = ||
    TYPE 11 = (
    TYPE 12 = )
*/



/*If the end of input is recognized, the current token shall be delimited. If there is no current token, the end-of-input indicator shall be returned as the token.

If the previous character was used as part of an operator and the current character is not quoted and can be used with the current characters to form an operator, it shall be used as part of that (operator) token.

If the previous character was used as part of an operator and the current character cannot be used with the current characters to form an operator, the operator containing the previous character shall be delimited.

If the current character is backslash, single-quote, or double-quote ( '\', '", or ' )' and it is not quoted, it shall affect quoting for subsequent characters up to the end of the quoted text. 
The rules for quoting are as described in Quoting. During token recognition no substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input (except for <newline> joining),
unmodified, including any embedded or enclosing quotes or substitution operators, between the quote mark and the end of the quoted text. The token shall not be delimited by the end of the quoted field.

If the current character is an unquoted '$' or '`', the shell shall identify the start of any candidates for parameter expansion ( Parameter Expansion), 
command substitution ( Command Substitution), or arithmetic expansion ( Arithmetic Expansion) from their introductory unquoted character sequences: '$' or "${", "$(" or '`', and "$((", respectively. 
The shell shall read sufficient input to determine the end of the unit to be expanded (as explained in the cited sections). While processing the characters, 
if instances of expansions or quoting are found nested within the substitution, the shell shall recursively process them in the manner specified for the construct that is found. 
The characters found from the beginning of the substitution to its end, allowing for any recursion necessary to recognize embedded constructs, shall be included unmodified in the result token, including any embedded or 
enclosing substitution operators or quotes. The token shall not be delimited by the end of the substitution.

If the current character is not quoted and can be used as the first character of a new operator, the current token (if any) shall be delimited. The current character shall be used as the beginning of the next (operator) token.

If the current character is an unquoted <newline>, the current token shall be delimited.

If the current character is an unquoted <blank>, any token containing the previous character is delimited and the current character shall be discarded.

If the previous character was part of a word, the current character shall be appended to that word.

If the current character is a '#', it and all subsequent characters up to, but excluding, the next <newline> shall be discarded as a comment. The <newline> that ends the line is not considered part of the comment.

The current character is used as the start of a new word.*/

void free_list(t_token *token)
{
    t_token *temp;

    while (token)
    {
        temp = token;
        free(temp);
        token = token->previous;
    }
}

int ft_grammar(t_token **token)
{
    if (*token)
    {
        if ((*token)->type == 1)
        {
            if ((*token)->type == 1 && (!(*token)->previous))
                return (1);
            
            if ((*token)->type == 1 && (*token)->previous->type == 1)
                (*token)->type = 2;

            if ((*token)->type == 1 && (*token)->previous->type == 2)
                (*token)->type = 2;
        }
        
        if ((*token)->type == 5 && ((!(*token)->previous) || (!(*token)->next)))
        {
                printf("bash: syntax error near unexpected token `|'\n");
                return (0);
        }
    }
    return (1);
}

t_extension *set_extension(char *str, t_extension *extension)
{
    int i;
    int a; 
    int b;
    int c;

    i = 0;
    a = 0;
    b = 0;
    c = 0;
    t_extension *new_element;
    new_element = malloc(sizeof(t_extension));
    if (!new_element)
        perror ("MALLOC CREATE VALUE");
    while (str[i])
    {
        while (str[i] && str[i] != '=')
            i++;
        a = i;
        i++;
        while (str[i])
            i++;
        b = (i - a - 1);
    }
    new_element->ancient = malloc(sizeof(char *) * a + 1);
    new_element->new = malloc(sizeof(char *) * b + 1);
    if (!new_element->ancient || !new_element->new)
        perror ("MALLOC CREATE STRING VALUE");
    while (c < a)
    {
        new_element->ancient[c] = str[c];
        c++;
    }
    c++;
    a = 0;
    while (str[c])
    {
        new_element->new[a] = str[c];  //integrer integration dans integration a=test -> b=ert$a --->>> A FAIRE
        c++;
        a++;
    }
    str[c] = '\0';
    new_element->previous = extension;
    return (new_element);
}

char *check_extension(char *str, t_extension *extension)
{
    int i;

    i = 0;
    while (extension)
    {
        if(!strcmp((const char *)extension->ancient, (const char *)str))
            return(extension->new);
        extension = extension->previous;
    }
    return (str);
}

t_token *push_empty_list (t_db_list *info, t_token *token, char *str, int type)
{
    t_token *new_element;
    new_element = malloc(sizeof(t_token));
    if (!new_element)
        perror ("MALLOC CREATE LIST");
    new_element->next = NULL;
    new_element->previous = NULL;
    new_element->str = str;
    new_element->type = type;
    info->first = new_element;
    info->last = new_element;
    info->lenght = 1;
    return (new_element);
}


t_token *push_full_list (t_db_list *info, t_token *token, char *str, int type)
{
    t_token *new_element;
    new_element = malloc(sizeof(t_token));
    if (!new_element)
        perror ("MALLOC CREATE LIST");
    new_element->str = str;
    new_element->type = type;
    new_element->next = NULL;
    info->last->next = new_element;
    new_element->previous = info->last;
    info->last = new_element;
    info->lenght = info->lenght + 1;

    return (new_element);
}

t_token *push_list(t_db_list *info, t_token *token, char *str, int type)
{
    if (info->lenght == 0)
        return (push_empty_list (info, token, str, type));

    if (info->lenght > 0)
        return (push_full_list(info, token, str, type));
    return (0);
}

t_db_list *init_list(t_db_list *info)
{
    info = malloc(sizeof(t_db_list));
    if (!info)
        perror ("MALLOC CREATE LIST");
    info->first = NULL;
    info->last = NULL;
    info->lenght = 0;

    return (info);
}

void determine_pipe_num(t_token *token, t_pipe_exec *pipe_exec)
{
    t_token *tmp;

    tmp = token;
    pipe_exec->cmds_nbr = 1;
    while (tmp && !(tmp->type == 9 || tmp->type == 10))
    {
        if (tmp->type == 5)
            pipe_exec->cmds_nbr++;
        tmp = tmp->next;
    }
}

void    determine_in_out(t_token *token, t_pipe_exec *pipe_exec)
{
    t_token *tmp;

    tmp = token;
    pipe_exec->infile = NULL;
    pipe_exec->outfile = NULL;
    while (tmp && !(tmp->type == 9 || tmp->type == 10))
    {
        if (tmp->type == 7)
            pipe_exec->infile = tmp->str;
        if (tmp->type == 8)
            pipe_exec->outfile = tmp->str;
        tmp = tmp->next;
    }
}

void    handle_cmd(t_token **token, t_pipe_exec *pipe_exec)
{
    pipe_exec->cmd = NULL;
    while (*token && !((*token)->type == 9 || (*token)->type == 10))
    {
        if ((*token)->type == 1)
        {
            pipe_exec->cmd = (*token)->str;
            if ((*token)->next)
                *token = (*token)->next;
        }
        if (!(*token)->next || pipe_exec->cmd)
            break;
        *token = (*token)->next;
    }
}


void    handle_args(t_token **token, t_pipe_exec *pipe_exec)
{
    t_token *tmp;
    int i;

    tmp = *token;
    pipe_exec->args_nbr = 0;
    i = -1;
    while (tmp && !(tmp->type == 9 || tmp->type == 10 || tmp->type == 5))
    {
        if (tmp->type == 2)
            pipe_exec->args_nbr++;
        tmp = tmp->next;
    }
    pipe_exec->newargs = malloc((pipe_exec->args_nbr + 2) * sizeof(char *));
    pipe_exec->newargs[++i] = pipe_exec->cmd;
    while (*token && (*token)->type == 2)
    {
        pipe_exec->newargs[++i] = (*token)->str;
        if (!(*token)->next)
            break;
        *token = (*token)->next;
    }
    pipe_exec->newargs[i + 1] = NULL;
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;
	int		i;

	new_s = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

void    determine_path(char *cmd, char **path, char **env)
{
    int i;

    if (cmd[0] == '/')
    {
        *path = NULL;
        return ;
    }
    i = -1;
    while (env[++i])
    {
        if (!strncmp(env[i], "PATH=", 5))
            break;
    }
    *path = env[i];
}

int determine_cmd_no_path(char **bin, char *cmd, char *path)
{
    int fd;

    *bin = ft_strdup(cmd);
    if (!(*bin))
        return (1);
    fd = access(*bin, F_OK & W_OK);
    if (fd == -1)
        return (1);
    return (0);
}


int determine_cmd_path(char **bin, char *cmd, char *path)
{
    int fd;
    int i;
    char    *tmp;

    fd = -1;
    path += 5;
    while (fd == -1 && path[i])
    {
        i = 0;
        while (path[i] && path[i] != ':')
            i++;
        path[i] = 0;
        tmp = ft_strjoin(path, "/");
        *bin = ft_strjoin(tmp, cmd);
        if (!tmp || !(*bin))
            return (1);
        free(tmp);
        fd = access(*bin, F_OK & W_OK);
        i++;
        path = path + i;
    }
    if (fd == -1)
        return (1);
    else
        return (0);
}

int handle_cmd_args(t_token **token, t_pipe_exec *pipe_exec)
{
    int found;
    
    handle_cmd(token, pipe_exec);
    handle_args(token, pipe_exec);
    determine_path(pipe_exec->cmd, &pipe_exec->path, pipe_exec->env);
    if (!pipe_exec->path)
        found = determine_cmd_no_path(&pipe_exec->bin, pipe_exec->cmd, pipe_exec->path);
    else
        found = determine_cmd_path(&pipe_exec->bin, pipe_exec->cmd, pipe_exec->path);
    if (found)
        return (1);
    return (0);
}
// SEGFAULT SI AUCUNE ENTREE
// GERER les >> correctement (e.g creer fichier si existe pas)
// CHECKER les leaks de la partie exec des que ce sera possible
// GERER les wildcards
// GERER les parentheses
// GERER ./a.out

/*
int    execute_commands(t_token *token, t_pipe_exec *pipe_exec)
{
    int id;

    pipe_exec->save_input = dup(STDIN_FILENO);
    pipe_exec->save_output = dup(STDOUT_FILENO);
    if (pipe_exec->infile)
    {
        pipe_exec->input = open(pipe_exec->infile, O_RDONLY);
        if (pipe_exec->input == -1)
            return (1);
    }
    else
        pipe_exec->input = dup(pipe_exec->save_input);
    while (pipe_exec->cmds_nbr > 0)
    {
        if (handle_cmd_args(&token, pipe_exec))
            return (1);
        dup2(pipe_exec->input, STDIN_FILENO);
        close(pipe_exec->input);
        if (pipe_exec->cmds_nbr == 1)
        {
            if (pipe_exec->outfile)
            {
                pipe_exec->output = open(pipe_exec->outfile, O_RDONLY);
                if (pipe_exec->output == -1)
                    return (1);
            }
            else
                pipe_exec->output = dup(pipe_exec->save_output);
        
        }
        else
        {
            pipe(pipe_exec->pipe_fd);
            pipe_exec->input = pipe_exec->pipe_fd[0];
            pipe_exec->output = pipe_exec->pipe_fd[1];    
        }
        dup2(pipe_exec->output, STDOUT_FILENO);
        close(pipe_exec->output);
        id = fork();
        if (!id)
        {
            execve(pipe_exec->bin, pipe_exec->newargs, pipe_exec->env);
            exit(1);
        } 
        pipe_exec->cmds_nbr--;            

    }
    dup2(pipe_exec->save_input, STDIN_FILENO);
    dup2(pipe_exec->save_output, STDOUT_FILENO);
    close(pipe_exec->save_input);
    close(pipe_exec->save_output);
    waitpid(id, &pipe_exec->status, 0);
    free(pipe_exec->newargs);
    return (0);
}
*/

int    input_redirection(char  *infile, int   *input, int save_input)
{
    if (infile)
    {
        *input = open(infile, O_RDONLY);
        if (*input == -1)
            return (1);
    }
    else
        *input = dup(save_input);
    return (0);
}

int    output_redirection(char  *outfile, int   *output, int save_output)
{
    if (outfile)
    {
        *output = open(outfile, O_CREAT | O_WRONLY, 0664);
        if (*output == -1)
            return (1);
    }
    else
        *output = dup(save_output);
    return (0);
}

int pipe_redirections(int   pipe_fd[2], int *input, int *output)
{
    if (pipe(pipe_fd) == -1)
        return (1);
    *input = pipe_fd[0];
    *output = pipe_fd[1];
    return (0);
}

void    restore_fd(int save_input, int save_output)
{
    dup2(save_input, STDIN_FILENO);
    dup2(save_output, STDOUT_FILENO);
    close(save_input);
    close(save_output);
}

int handle_execution(t_token **token, t_pipe_exec **pipe_exec, int *id)
{
    if (handle_cmd_args(token, *pipe_exec))
        return (1);
    dup2((*pipe_exec)->input, STDIN_FILENO);
    close((*pipe_exec)->input);
    if ((*pipe_exec)->cmds_nbr == 1)
        output_redirection((*pipe_exec)->outfile, &(*pipe_exec)->output, (*pipe_exec)->save_output);
    else
        pipe_redirections((*pipe_exec)->pipe_fd, &(*pipe_exec)->input, &(*pipe_exec)->output);  
    dup2((*pipe_exec)->output, STDOUT_FILENO);
    close((*pipe_exec)->output);
    *id = fork();
    if (!(*id))
    {
        printf("TEST0\n");
        execve((*pipe_exec)->bin, (*pipe_exec)->newargs, (*pipe_exec)->env);
        printf("TEST1\n");
        exit(1);
    }
}

int    execute_commands(t_token *token, t_pipe_exec *pipe_exec)
{
    int id;

    pipe_exec->save_input = dup(STDIN_FILENO);
    pipe_exec->save_output = dup(STDOUT_FILENO);
    input_redirection(pipe_exec->infile, &pipe_exec->input, pipe_exec->save_input);
    while (pipe_exec->cmds_nbr > 0)
    {
        handle_execution(&token, &pipe_exec, &id);
        pipe_exec->cmds_nbr--;            
    }
    restore_fd(pipe_exec->save_input, pipe_exec->save_output);
    waitpid(id, &pipe_exec->status, 0);
    free(pipe_exec->newargs);
    return (0);
}

void    test(void)
{
    printf("OKAY MDR LOL LMAO VRAIMENT MOFO\n");
}

int move_next_cmds(t_token **token)
{
    while (*token)
    {
        if ((*token)->type == 9)
        {
            *token = (*token)->next;
            return (1);
        }
        if ((*token)->type == 10)
        {
            *token = (*token)->next;
            return (2);
        }
        if (!(*token)->next)
            break ;
        *token = (*token)->next;
    }
    return (-1);
}
/*
int    execute_line(t_token *token, char **env)
{
    t_pipe_exec pipe_exec;
    int continue_exec;
    int found_cmd;

    continue_exec = 0;
    while (continue_exec != -1)
    {
        determine_in_out(token, &pipe_exec);
        determine_pipe_num(token, &pipe_exec);
        pipe_exec.env = env;
        if (!continue_exec)
            found_cmd = execute_commands(token, &pipe_exec);
        else
        {
            if (continue_exec == 1 && !pipe_exec.status)
                found_cmd = execute_commands(token, &pipe_exec);
            if (continue_exec == 2 && (pipe_exec.status != 0 || found_cmd))
                found_cmd = execute_commands(token, &pipe_exec);
        }
        continue_exec = move_next_cmds(&token);
    } 
    return (0);
}
*/

int    execute_line(t_token *token, char **env)
{
    t_pipe_exec pipe_exec;
    int continue_exec;
    int found_cmd;

    continue_exec = 0;
    while (continue_exec != -1)
    {
        determine_in_out(token, &pipe_exec);
        determine_pipe_num(token, &pipe_exec);
        pipe_exec.env = env;
        if (!continue_exec)
            found_cmd = execute_commands(token, &pipe_exec);
        else
        {
            if (continue_exec == 1 && !pipe_exec.status)
                found_cmd = execute_commands(token, &pipe_exec);
            if (continue_exec == 2 && (pipe_exec.status != 0 || found_cmd))
                found_cmd = execute_commands(token, &pipe_exec);
        }
        continue_exec = move_next_cmds(&token);
    } 
    return (0);
}

/*
t_db_list *init_minishell(t_token **token, t_extension **extension, char *env[], t_db_list *info)
{

    *token = NULL;
    *extension = NULL;
    info = init_list(info);
    return (info);
}
*/

t_db_list *init_minishell(t_minishell *minishell, char *env[])
{
    minishell->env = env;
    minishell->token = NULL;
    minishell->extension = NULL;
    minishell->info = init_list(minishell->info);
    return (minishell->info);
}

int main(int argc, char *argv[], char *env[])
{
    t_minishell minishell;

    minishell.info = init_minishell(&minishell, env);
    while ((minishell.line = readline("minishell$ ")))
    {
        parse_line(minishell.line, &minishell.token, &minishell.extension, 0, &minishell.info);
        while (minishell.token && minishell.token->previous)                 //utilise ce while pour te balader;
            minishell.token = minishell.token->previous;

        if (!strcmp(minishell.token->str, "exit"))
        {
            free_list(minishell.token);                      //fermeture programme          
            free(minishell.line);
            break;
        }                 

        while (minishell.token)
        {
            if (!(ft_grammar(&minishell.token)))          
                break;

            add_history(minishell.line);

            printf("token = %s\ntype = %d\n\n", minishell.token->str, minishell.token->type);
            if (!minishell.token->next)
                break;
            minishell.token = minishell.token->next;

        }

        while (minishell.token && minishell.token->previous)                 //utilise ce while pour te balader;
            minishell.token = minishell.token->previous;
        //printf("minishell.token->str: %s\n", minishell.token->str);
        if (execute_line(minishell.token, minishell.env))
            return (1);
        free_list(minishell.token);
        //minishell.info = init_list(minishell.token, minishell.extension, minishell.info);                //je free la structure de controle de la liste
        minishell.info = init_list(minishell.info);
        free(minishell.line);
    }

    free(minishell.extension);

}


            //FAIRE ATTENTION AU STRNCMP