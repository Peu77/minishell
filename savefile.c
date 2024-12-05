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
            return NULL;
        }
        strcpy(full_path, paths[i]);
        strcat(full_path, "/");
        strcat(full_path, command);
        if (access(full_path, F_OK) == 0) 
        {
            free(paths);
            return full_path;
        }
        free(full_path); 
        i++;
    }
    free(paths);
    return NULL;
}

static void get_path(t_command **command)
{
    t_command *head;
    char **path;
	char *found_path;
    head = (*command);
    while ((*command))
    {
        path = ft_split((*command)->argument, ' ');
        if (!path)
            return;
		((*command)->command_name) = path[0];
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
		(*command)->redirection_token = NULL;
		(*command)->redirection_token = NULL;
        (*command) = (*command)->next;
        free(path);
    }
    (*command) = head;
}

static int create_command_list(char *user_prompt, t_command **command, char **envp)
{
    t_command *new_node;
    int i = 0;

    if (!user_prompt || !command)
        return (0);
    (*command)->command_split = ft_split(user_prompt, '|');
    if (!(*command)->command_split)
		pe(ERROR_SPLIT);
    while ((*command)->command_split[i])
    {
        if ((*command)->command_split[i][0] != '\0')
        {
            new_node = create_node((*command)->command_split[i], envp);
            if (!new_node)
            {
                break;
            }
            add_node_back(command, new_node);
        }
        i++;
    }
    i = 0;
    free_command_split((*command)->command_split);
	return (1);
}

int initialise_command(t_command **command, char *user_prompt, char **envp)
{
	if(!create_command_list(user_prompt, command, envp))
		return (0);
	get_path(command);
	return (1);
}
