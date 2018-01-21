//
// Created by costa_d on 25/11/17.
//

#include "pamela.h"

/* int mountSecurePoint(char *mountPath, char *mountPointPath, char *user)
 *
 * Monte le conteneur
 * Return un int : 0 aucune erreur
 *                -1 erreur
 *
 */

int	mountSecurePoint(char *mountPath, char *mountPointPath, char *user)
{
  struct passwd *uid;

  printf("user %s | mountPath = %s | mountPointPath = %s\n", user, mountPath, mountPointPath);
  if (creatDir(mountPointPath) == -1) {
      fprintf(stderr, "Fail to create secure_data\n");
      return (-1);
    }
  if (mount(mountPath, mountPointPath, "ext4", 0, "") != 0) {
      fprintf(stderr, "Fail to mont secure data\n");
      if (rmdir(mountPointPath) == -1) {
          fprintf(stderr, "Fail to rm secure_data\n");
          sleep(5);
          return (-1);
        }
      return (-1);
    }
  if ((uid = getpwnam(user)) == NULL) {
      fprintf(stderr, "Fail to get user info\n");
      return (-1);
    }
  if (chown(mountPointPath, uid->pw_uid, uid->pw_gid) == -1) {
      fprintf(stderr, "Fail to chown secure_data\n");
      return (-1);
    }
  return (0);
}

/* int umountSecurePoint(char *mountPath, char *mountPointPath)
 *
 * Démonte le conteneur
 * Return un int : 0 aucune erreur
 *                -1 erreur à la suppression du dossier
 *
 */

int	umountSecurePoint(char *mountPath, char *mountPointPath)
{
  printf("mountPath = %s, mountPointPath = %s\n", mountPath, mountPointPath);
  if (umount(mountPointPath) == -1) {
      fprintf(stderr, "Fail to umont secure_data\n");
      sleep(5);
      return (-1);
    }
  sleep(5);
  if (rmdir(mountPointPath) == -1) {
      fprintf(stderr, "Fail to rm secure_data\n");
      sleep(5);
      return (-1);
    }
  printf("Umont ok\n");
  sleep(5);
  return (0);
}