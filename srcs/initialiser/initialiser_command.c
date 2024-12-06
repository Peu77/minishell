#include "../../includes/minishell.h"

char *find_command_in_path(const char *command)
{
    char *env_path;
    char **paths;
    char *full_path;
    int i = 0;

    env_path = getenv("PATH");
    if (!env_path)
    {
        printf("No PATH environment variable found.\n");
        return NULL;
    }
    paths = ft_split(env_path, ':');
    if (!paths)
    {
        printf("Error splitting PATH.\n");
        return NULL;
    }
    while (paths[i])
    {
        full_path = malloc(ft_strlen(paths[i]) + ft_strlen(command) + 2);
        if (!full_path)
        {
            printf("Memory allocation error.\n");
            free_command_split(paths);
            return NULL;
        }
		ft_strlcpy(full_path, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(paths[i]) + ft_strlen(command) + 2);
		ft_strlcat(full_path, command, ft_strlen(paths[i]) + ft_strlen(command) + 2); // full_path_size
        if (access(full_path, F_OK) == 0) 
        {
            free_command_split(paths);
            return full_path;
        }
        free(full_path);
        full_path = NULL;
        i++;
    }
    free_command_split(paths);
    return (NULL);
}

static int get_path(t_command **command)
{
    t_command *head = (*command);
    char **path;
    char *found_path;

    while ((*command))
    {
        path = ft_split((*command)->argument, ' ');
        if (!path)
            return pe(ERROR_SPLIT);
        (*command)->command_name = ft_strdup(path[0]);
        found_path = find_command_in_path((*command)->command_name);
        if (found_path)
        {
            (*command)->path = found_path;
            printf("Command '%s' found at: %s\n", path[0], found_path);
        }
        else
        {
            (*command)->path = NULL;
            printf("Command '%s' not found in PATH.\n", path[0]);
        }
        free_command_split(path);
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
	if(!get_path(command))
		return (0);
	
	return (1);
}


