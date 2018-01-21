/*
** userManager.c for pamela in /home/costa_d/Documents/TEK3/pamela
**
** Made by Arnaud Costa
** Login   <costa_d@epitech.net>
**
** Started on  Wed Nov 22 13:50:36 2017 Arnaud Costa
** Last update Wed Nov 22 13:50:37 2017 Arnaud Costa
*/

#include "pamela.h"

/* char *getUserInfo(pam_handle_t *pamh, int value)
 *
 * Donne les infos du user en fonction du flag value passé en paramètre
 * Return une chaine de caractère : valueget qui est l'info voulue
 *                                  NULL en cas d'erreur
 *
 */

char            *getUserInfo(pam_handle_t *pamh, int value)
{
  char		*valueget;
  int           ret;

  valueget = malloc(sizeof(char) * 1024);
  ret = pam_get_item(pamh, value, (const void **)&valueget);
  if (ret != PAM_SUCCESS || valueget == NULL) {
      return (NULL);
    }
  return (valueget);
}