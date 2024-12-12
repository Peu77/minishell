#include "../../includes/minishell.h"

int get_user_prompt(char **user_prompt)
{
    *user_prompt = readline(">>>> Minishell>$ ");

    if (*user_prompt == NULL) 
    {
        clear_history();
        printf("exit\n");
        free(*user_prompt);  // Free memory allocated by readline
        return 0;  // Return 0 to signal exit
    }

    add_history(*user_prompt);
    remove_newline(*user_prompt);

    return 1;
}
