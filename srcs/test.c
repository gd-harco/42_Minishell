/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:50:01 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/11 12:42:45 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int main() {
//     pid_t pid = getpid();
// 	kill(pid, SIGINT);
// 	printf("Signal SIGINT envoyé au processus %d\n", pid);
// 	return (0);
// }

char    *is_cmd(char *str)
{
    if (str[0] == 'e' && str[1] == 'c' && str[2] == 'h' && str[3] == 'o')
    {
        if (str[4] == '\0')
            return ("\n");
        else if (str[4] == '-' && str[5] == 'n')
            return (ft_substr(str, 6, ft_strlen(str - 6)));
        else
            return (ft_strjoin(ft_substr(str, 4, ft_strlen(str - 4)), "\n"));
    }
    return ("error\n");
}





// int echo_cmd(char *str)
// {
//     char    **cmd;
//     char    *new;
//     int     i;
    
//     i = 1;
//     cmd = ft_split(str, ' '); 
//     if (cmd == NULL)
//         return (-1);
//     new = ft_strjoin(cmd[0], cmd[1]);
//     while (cmd[i] != NULL)
//     {
//         new = ft_strjoin( new, cmd[i + 1]);
//         i++;
//     }
//     printf("%s", is_cmd(new));
//     if (is_cmd(new) == 0)
//         return (0);
//     else if (ft_strncmp(new, "echo", ft_strlen(new)) == 0)
//         return (1);
//     else
//         return (-1);
// }

static int  echo_compare(char **str)
{
    if (str[0][0] == 'e' && str[0][1] == 'c' && str[0][2] == 'h' && str[0][3] == 'o' && str[0][4] == '\0')
    {
        if (str[1][0] == '-' && str[1][1] == 'n' && str[1][2] == '\0')
            return (0);
        else
            return (1);
    }
    else
        return (-1);
}

int echo_cmd(char *str)
{
    char    **cmd;
    int i;
    int j;

    i = 0;
    cmd = ft_split(str, ' '); 
    if (cmd == NULL)
        return (-1);
    while (cmd[i] != NULL)
        i++;
    if (echo_compare(cmd) == 0)
        j = 2;
    else if (echo_compare(cmd) == 1)
        j = 1;
    else
        return (-1);
    while (j <  i)
        printf("%s", cmd[j++]);
    if (echo_compare(cmd) == 1)
        printf("\n");
    return (0);
    

}

int cd_cmd(char *str)
{
    char    **cmd;
    int i;

    i = 0;
    cmd = ft_split(str, ' '); 
    if (cmd == NULL)
        return (-1);
    while (cmd[i] != NULL)
        i++;
    if (cmd[0][0] == 'c' && cmd[0][1] == 'd' && cmd[0][2] == '\0')
    {
        if (chdir(cmd[1]) == -1 )
        fprintf(stderr, "Error : %s\n", strerror(errno));
    }
    return (0);
}


t_token *cmd_init(char *str, char **envp)
{
    t_token *t_new;
    char **s;
    char **path;
    char *s_p;

    s = ft_split(str, ' ');
    t_new = malloc(sizeof(t_token));
    if (!t_new)
        return(NULL);
    t_new->next = NULL;
    if (s[0][0] != '<')
    {
        path = get_path(envp);
        s_p = process(str, path);
        if (!s_p)
            return(NULL);
        t_new->content = malloc(sizeof (char *) * 2);
        t_new->content[0] = malloc(sizeof(char *) * (ft_strlen(s_p) + 1));
        t_new->content[0] = ft_strdup(s_p);
        t_new->content[1] = NULL;
    }
    printf("%s\n", s_p);
    
    return (t_new);
}


int main(int argc, char **argv, char **envp)
{
    char    *str;
    int     i;

    (void)argc;
    (void)argv;
    i = 0;
    str = readline("");
    while (i < 5 ) //detect SIGINT ou SIGTERM ?
    {
        add_history(str);
        cmd_init(str, envp);
        echo_cmd(str);
        cd_cmd(str);
        i++;
        printf("Minishell$ ");
        str = readline("");
    }
    return (0);
}

// int main()
// {
//     char    *str;
//     str = readline("");
//     add_history(str);
//     if (echo_cmd(str) == 0)
//         printf("%s", str);
//     else if (echo_cmd(str) == 1)
//         printf("%s\n", str);
//     return (0);
// }

// int main() {
//     DIR *rep = opendir(".");
//     if (rep == NULL) {
//         perror("Erreur lors de l'ouverture du répertoire");
//         exit(EXIT_FAILURE);
//     }
//     struct dirent *entree;
//     while ((entree = readdir(rep)) != NULL) {
//         printf("%s\n", entree->d_name);
//     }
//     closedir(rep);
//     return 0;
// }

// int main() {
//     if (unlink("wa") == -1) {
//         perror("Erreur lors de la suppression du fichier");
//         exit(EXIT_FAILURE);
//     }
//     printf("Le fichier a été supprimé avec succès\n");
//     return 0;
// }

// int main() {
//     struct stat file_stat;
//     char *file_path = "/nfs/homes/tdutel/Documents/Cursus-42/Cercle3/Minishell/srcs/test.c";
//     if (lstat(file_path, &file_stat) == -1) {
//         perror("Erreur lors de l'appel à la fonction stat");
//         return 1;
//     }
//     printf("Le fichier %s a une taille de %ld octets\n", file_path, file_stat.st_size);
//     printf("Les permissions du fichier sont : %o\n", file_stat.st_mode & 0777);
//     return 0;
// }

// int main() {
//     printf("Le répertoire courant est : %s\n", getcwd(NULL, 0));
//     chdir("/tmp");
//     printf("Le répertoire courant est maintenant : %s\n", getcwd(NULL, 0));

//     return 0;
// }


//     if (kill(pid, SIGINT) == 0) {
//         printf("Signal SIGINT envoyé au processus %d\n", pid);
//     } else {
//         perror("kill() a échoué");
//         return -1;
//     }
//     return 0;
// }
// */
// int main() {
//     char buf[1024];
// 	getcwd(buf, sizeof(buf));
// 	printf("buf : %s", buf);
// 	return (0);
// }

/*
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd() a échoué");
        exit(EXIT_FAILURE);
    }
    return 0;
}*/

// void gestionnaire_signal(int signal) {
//     printf("Signal %d reçu\n", signal);
//     exit(EXIT_SUCCESS);
// }

// int main() {
//     struct sigaction action;
//     action.sa_handler = gestionnaire_signal;
//     sigemptyset(&action.sa_mask);
//     action.sa_flags = 0;
//     if (sigaction(SIGINT, &action, NULL) == -1) {
//         perror("Erreur lors de la définition du gestionnaire de signal");
//         exit(EXIT_FAILURE);
//     }
//     while (1) {
//         printf("En attente de signal...\n");
//         sleep(1);
//     }
//     return 0;
// }

// int	main(void)
// {
// 	char	*ligne_saisie;


// 	ligne_saisie = readline("Entrez une ligne de texte : ");
// 	add_history(ligne_saisie);
// 	rl_clear_history();
//     printf("Vous avez saisi : %s\n", ligne_saisie);
// 	ligne_saisie = readline("Entrez une ligne de texte : ");
// 	add_history(ligne_saisie);
	
// 	ligne_saisie = readline("Entrez une ligne de texte : ");
// 	add_history(ligne_saisie);
// 	ligne_saisie = readline("Entrez une ligne de texte : ");
// 	add_history(ligne_saisie);
// 	printf("OK");
//     free(ligne_saisie);
//     return 0;
// }

// int main() {
//     char* saisie_utilisateur = readline("Entrez une ligne de texte : ");
//     add_history(saisie_utilisateur);
// 	rl_replace_line("bonjour", 7); // Efface la ligne de commande courante
//     rl_redisplay();
// 	printf("La saisie de l'utilisateur est : %s\n", saisie_utilisateur);
//     free(saisie_utilisateur);
//     return 0;
// }


// int main() {
//     char* saisie_utilisateur = readline("Entrez une ligne de texte : ");
//     rl_on_new_line(); // Déplace le curseur à la ligne suivante
//     rl_message("Vous avez saisi : %s\n", saisie_utilisateur);
//     free(saisie_utilisateur);
//     return 0;
// }

// int main() {
//     char* saisie_utilisateur = readline("Entrez une ligne de texte : ");
//     rl_replace_line("", 0); // Efface la ligne de commande courante
//     printf("La saisie de l'utilisateur est : %s\n", saisie_utilisateur);
//     free(saisie_utilisateur);
//     return 0;
// }
