/*
** entryPoints.c for pamela in /home/costa_d/Documents/TEK3/pamela
**
** Made by Arnaud Costa
** Login   <costa_d@epitech.net>
**
** Started on  Wed Nov 22 13:50:50 2017 Arnaud Costa
** Last update Wed Nov 22 13:50:51 2017 Arnaud Costa
*/

#include "pamela.h"

/* PAM_EXTERN int	pam_sm_authenticate(pam_handle_t *pamh, int flags,int ac, const char **av)
 *
 * Fonction qui manage l'évènement de connection
 * return un PAM_EXTERN int : PAM_IGNORE dans tous les cas
 *
 */

PAM_EXTERN int	pam_sm_authenticate(pam_handle_t *pamh, int flags,int ac, const char **av)
{
  char 		*username;
  char 		*password;
  int		res;

  username = getUserInfo(pamh, PAM_USER);
  password = getUserInfo(pamh, PAM_AUTHTOK);
  printf("Info username =  %s | passwd  = %s\n", username, password);
  if (username == NULL || password == NULL || strcmp(username, "root") == 0)
    return (PAM_IGNORE);
  if (isSaveZone("/root/.pamela_containers") == -1)
    return (PAM_IGNORE);
  res = isContainer("/root/.pamela_containers/", username);
  if (res == -1) {
      return (PAM_IGNORE);
    }
  else if (res == 2)
    {
      if (initContainer("/root/.pamela_containers/", username, password) == -1)
	return (PAM_IGNORE);
      //return (PAM_IGNORE);
    }
  activateContainer("/root/.pamela_containers/", username, password);
  return (PAM_IGNORE);
}

/* PAM_EXTERN int	pam_sm_open_session(pam_handle_t *pamh, int flags,int ac, const char **av)
 *
 * Fonction qui manage l'évènement de connection
 * return un PAM_EXTERN int : PAM_IGNORE dans tous les cas
 *
 */

PAM_EXTERN int	pam_sm_open_session(pam_handle_t *pamh, int flags,int ac, const char **av)
{
  char		*mountPath;
  char		*mountPointPath;
  char 		*username;
  char		*tmp;

  username = getUserInfo(pamh, PAM_USER);
  mountPath = concat("/dev/mapper/", username);
  tmp = concat("/home/", username);
  if (tmp == NULL || strcmp(username, "root") == 0)
    return (PAM_IGNORE);
  mountPointPath = concat(tmp, "/secure_data-rw");
  if (mountPath == NULL || mountPointPath == NULL)
    return (PAM_IGNORE);
  mountSecurePoint(mountPath, mountPointPath, username);
  return (PAM_IGNORE);
}

/* PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags,int ac, const char **av)
 *
 * Fonction qui manage l'évènement de fermeture de session
 * return un PAM_EXTERN int : PAM_IGNORE dans tous les cas
 *
 */

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags,int ac, const char **av)
{
  char		*mountPath;
  char		*mountPointPath;
  char 		*username;
  char		*tmp;

  username = getUserInfo(pamh, PAM_USER);
  mountPath = concat("/dev/mapper/", username);
  tmp = concat("/home/", username);
  if (tmp == NULL)
    return (PAM_IGNORE);
  mountPointPath = concat(tmp, "/secure_data-rw");
  free(tmp);
  if (mountPath == NULL || mountPointPath == NULL)
    return (PAM_IGNORE);
  if (umountSecurePoint(mountPath, mountPointPath) == -1)
    return (PAM_IGNORE);
  sleep(1);
  closeContainer(username);
  sleep(5);
  return (PAM_IGNORE);
}

/* PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int ac, const char **av
 *
 * Fonction qui manage l'évènement de changement de mot de passe
 * return un PAM_EXTERN int : PAM_IGNORE dans tous les cas
 *
 */

PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int ac, const char **av)
{
  char 		*username;
  char 		*password;
  char 		*oldpassword;

  username = getUserInfo(pamh, PAM_USER);
  password = getUserInfo(pamh, PAM_AUTHTOK);
  oldpassword = getUserInfo(pamh, PAM_OLDAUTHTOK);
  if (username == NULL || password == NULL || oldpassword == NULL || strcmp(username, "root") == 0)
    return (PAM_IGNORE);
  changerPasswd(username, oldpassword, password);
  activateContainer("/root/.pamela_containers/", username, password);
  return (PAM_IGNORE);
}
