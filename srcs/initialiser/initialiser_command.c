#include "../../includes/minishell.h"

static char *construct_full_path(char *path, const char *command)
{
    char *full_path;
    
    full_path = malloc(ft_strlen(path) + ft_strlen(command) + 2);
    if (!full_path)
        return (pev(ERROR_MALLOC), NULL);
    ft_strlcpy(full_path, path, ft_strlen(path) + 1);
    ft_strlcat(full_path, "/", ft_strlen(path) + ft_strlen(command) + 2);
    ft_strlcat(full_path, command, ft_strlen(path) + ft_strlen(command) + 2);  // Append command
    return (full_path);
}

char *find_command_in_path(const char *command)
{
    char *env_path;
    char **paths;
    char *full_path;
    int i = -1;

    env_path = getenv("PATH");
    if (!env_path)
        return (pev(ERROR_FIND_ENV), NULL);
    paths = ft_split(env_path, ':');
    if (!paths)
        return (pev(ERROR_SPLIT), NULL);
    while (paths[++i])
    {
        full_path = construct_full_path(paths[i], command);
        if (!full_path)
            return (free_command_split(paths), NULL);
        if (access(full_path, F_OK) == 0) 
            return (free_command_split(paths), full_path);
        free(full_path);
        full_path = NULL;
    }
    free_command_split(paths);
    return NULL;
}

static int get_path(t_command **command)
{
    t_command *head = (*command);
    char *found_path;

    while ((*command))
    {
        found_path = find_command_in_path((*command)->command_name);
        if (found_path)
        {
            (*command)->path = found_path;
            printf("Command '%s' found at: %s\n", (*command)->command_name, found_path);
        }
        else
        {
            (*command)->path = NULL;
            printf("Command '%s' not found in PATH.\n", (*command)->command_name );
        }
        (*command) = (*command)->next;
    }
    *command = head;
    return (1);
}

static int create_command_list(char *user_prompt, t_command **command, char **envp)
{
    char **command_split;
    t_command *new_node;
    int i = 0;

    if (!user_prompt || !command)
        return 0;
    command_split = ft_split(user_prompt, '|');
    if (!command_split)
        perror(ERROR_SPLIT);
    while (command_split[i])
    {
        if (command_split[i][0] != '\0')
        {
            new_node = create_node(command_split[i], envp);
            if (!new_node)
                pe(ERROR_NODE);
            add_node_back(command, new_node);
        }
        i++;
    }
    free_command_split(command_split);
	return (1);
}

int initialise_command(t_command **command, char *user_prompt, char **envp)
{
	if(!create_command_list(user_prompt, command, envp))
		return (0);
	get_path(command);
	
	return (1);
}


