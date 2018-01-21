//
// Created by costa_d on 25/11/17.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* char *getCreatCmd(char *)
 *
 * Créé la commande "dd if=/dev/zero of=<path> bs=1 count=0 seek=10G" qui permet de générer un block mémoire
 * Return : aucune erreur,un pointeur vers cette nouvelle chaine de caractères
 *          NULL si erreur
 *
 */

char	*getCreatCmd(char *path)
{
  char 	*res;

  if ((res = calloc(strlen("dd if=/dev/zero of= bs=1 count=0 seek=10G") + strlen(path) + 1, sizeof(char))) == NULL)
    return (NULL);
  res = strcpy(res, "dd if=/dev/zero of=");
  res = strcat(res, path);
  res = strcat(res, " bs=1 count=0 seek=10G");
  return (res);
}

/* char *getInitCmd(char *)
 *
 * Créé la commande "/sbin/mkfs.ext4 /dev/mapper/<path>" qui formate le block mémoire
 * Return : aucune erreur,un pointeur vers cette nouvelle chaine de caractères
 *          NULL si erreur
 *
 */

char	*getInitCmd(char *path)
{
  char 	*res;

  if ((res = calloc(strlen("/sbin/mkfs.ext4 /dev/mapper/") + strlen(path) + 1, sizeof(char))) == NULL)
    return (NULL);
  res = strcpy(res, "/sbin/mkfs.ext4 /dev/mapper/");
  res = strcat(res, path);
  return (res);
}

/* char *concat(char *, char *)
 *
 * Permet d'assebler deux chaines de caractères de l'acclocation de la mémoire à la copie
 * Return : aucune erreur,un pointeur vers cette nouvelle chaine de caractères
 *          NULL si erreur
 *
 */

char	*concat(char *one, char *two)
{
  char 	*res;

  if ((res = calloc(strlen(one) + strlen(two) + 1, sizeof(char))) == NULL)
    return (NULL);
  res = strcpy(res, one);
  res = strcat(res, two);
  return (res);
}
