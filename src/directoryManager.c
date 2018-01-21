//
// Created by costa_d on 20/11/17.
//

#include "pamela.h"

/* int creaDir(char *dirpath)
 *
 * Créé un dossier au path donné en paramètre
 * Return un int : 0 si tout s'est bien passé
 *                -1 le dossier n'a pas pu etre créé
 *
 */

int	creatDir(char *dirpath)
{
  int dit_status;

  dit_status = mkdir(dirpath, 0700);
  if (dit_status == -1)
    return (-1);
  return (0);
}

/* int creatContainer(char *container_path, char *device_name)
 *
 * Créé un device au path donné en paramètre
 * Return un int : 0 si tout s'est bien passé
 *                -1 le device n'a pas pu etre créé
 *
 */

int	creatContainer(char *container_path, char *device_name)
{
  char *cmd;
  FILE *fd;

  cmd = getCreatCmd(container_path);
  fd = popen(cmd,"w");
  free(cmd);
  if (fd == NULL)
    return (-1);
  pclose(fd);
  return (0);
}


/* int initContainer(char *container_path, char *device_name, char *passwd)
 *
 * Initialise le device
 * Return un int : 0 si tout s'est bien passé
 *                -1 le device n'a pas pu etre initialisé
 *
 */

int	initContainer(char *container_path, char *device_name, char *passwd)
{
  char	*cmd;
  char	*tmp;

  printf("InitContainer | Info device_name =  %s | passwd  = %s | container_path = %s\n", device_name, passwd, container_path);
//  tmp = malloc(strlen(device_name) + strlen(container_path) + 1);
//  strcpy(tmp, container_path);
//  tmp = strcat(tmp, device_name);
//  container_path = tmp;
  tmp = concat(container_path, device_name);
  printf("tmp = %s\n", tmp);
  //return (-1);
  //free(tmp);
  if (tmp == NULL)
    return (-1);
  if (containerHeaderManager(tmp, passwd) == -1) {
      fprintf(stderr, "Fail to set secure data header | %s, %s\n", tmp, passwd);
      free(tmp);
      return (-1);
    }
  free(tmp);
  if (activateContainer(container_path, device_name, passwd) == -1)
    {
      fprintf(stderr, "Fail to active secure_data\n");
      return (-1);
    }
  cmd = getInitCmd(device_name);
  printf("Cmd = %s\n", cmd);
  if (cmd == NULL)
    return (-1);
  if (system(cmd) == -1) {
      free(cmd);
      fprintf(stderr, "Fail to %s\n", cmd);
      return (-1);
    }
  free(cmd);
  return (0);
}


/* int isContainer(char *container_path, char *devices_name)
 *
 * Check si le container passé en paramètre existe puis le créé si besoin
 * Return un int : 0 le container existait déjà, aucune erreur
 *                 2 le container a été créé, aucune erreur
 *                -1 erreur
 *
 */

int	isContainer(char *container_path, char *device_name)
{
  struct stat 	container;
  char		*tmp;

//  tmp = malloc(strlen(devices_name) + strlen(container_path) + 1);
//  strcpy(tmp, container_path);
//  tmp = strcat(tmp, devices_name);
//  container_path = tmp;
  tmp = concat(container_path, device_name);
  printf("isContainer | Info device_name =  %s | container_path = %s\n", device_name, tmp);
  if (tmp == NULL)
    return (-1);
  if (stat(tmp, &container) == -1) {
      if (creatContainer(tmp, device_name) == -1) {
	  fprintf(stderr, "Error fail to create Container\n");
	  free(tmp);
	  return (-1);
	}
      free(tmp);
      return (2);
    }
  free(tmp);
  return (0);
}


/* int isSaveZone(char *path)
 *
 * Check si le dossier passé en paramètre existe puis le créé si besoin
 * Return un int : 0 le dossier existait déjà, aucune erreur
 *                 2 le dossier a été créé, aucune erreur
 *                -1 erreur sur la création du dossier
 *
 */

int	isSaveZone(char *path)
{
  struct stat dir;

  if (stat(path, &dir) == -1) {
      if (creatDir(path) == -1) {
	  fprintf(stderr, "Error fail to create folder\n");
	  return (-1);
	}
      return (2);
    }
  return (0);
}