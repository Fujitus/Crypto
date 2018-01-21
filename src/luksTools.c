//
// Created by costa_d on 25/11/17.
//

#include "pamela.h"

/* int containerHeaderManager(char *path, char *passwd)
 *
 * Créé et set le header du container
 * Return un int : 0 aucune erreur
 *                -1 erreur
 *
 */

int		containerHeaderManager(char *path, char *passwd)
{
  struct 	crypt_device *cd;
  struct 	crypt_params_luks1 params;

  printf("container header | path = %s, passwd = %s\n", path, passwd);
  if (crypt_init(&cd, path) < 0 ) {
      fprintf(stderr, "Error crypt_init\n");
      return (-1);
    }
  params.hash = "sha1";
  params.data_alignment = 0;
  params.data_device = NULL;
  if(crypt_format(cd, CRYPT_LUKS1, "aes", "xts-plain64", NULL, NULL,
		  256 / 8, &params) < 0) {
      crypt_free(cd);
      printf("error crypt_format\n");
      return (-1);
    }
  if (crypt_keyslot_add_by_volume_key(cd, CRYPT_ANY_SLOT, NULL, 0, passwd, 3) < 0) {
      crypt_free(cd);
      printf("error crypt_keyslot\n");
      return (-1);
    }
  crypt_free(cd);
  printf("all good\n");
  return (0);
}

/* int activateContainer(char *path, char *device, char *passwd)
 *
 * Active le container
 * Return un int : 0 aucune erreur
 *                -1 erreur
 *
 */

int 		activateContainer(char *path, char *device, char *passwd)
{
  struct 	crypt_device *cd;
  struct 	crypt_active_device cad;
  char 		*containerPath;

  containerPath = concat(path, device);
  printf("active caontainer | path = %s, device = %s, passwd = %s\n", containerPath, device, passwd);
  if (crypt_init(&cd, containerPath) < 0 ) {
      fprintf(stderr, "Error crypt_init\n");
      free(containerPath);
      return (-1);
    }
  free(containerPath);
  if (crypt_load(cd, CRYPT_LUKS1, NULL) < 0) {
      fprintf(stderr, "Error crypt_load\n");
      crypt_free(cd);
      return (-1);
    }
  if (crypt_activate_by_passphrase(cd, device, CRYPT_ANY_SLOT, passwd, 3, 0) < 0) {
      fprintf(stderr, "Error crypt_active\n");
      crypt_free(cd);
      return (-1);
    }
  crypt_free(cd);
  return (0);
}

/* int changerPasswd(const char *device, char *old_passwd, char* new_passwd)
 *
 * Change le password du container
 * Return un int : 0 aucune erreur
 *                -1 erreur
 *
 */

int 	changerPasswd(const char *device, char *old_passwd, char* new_passwd)
{
  struct crypt_device *cd;

  if (crypt_init_by_name(&cd, device) < 0) {
      return (-1);
    }
  crypt_keyslot_change_by_passphrase(cd, CRYPT_ANY_SLOT, CRYPT_ANY_SLOT, old_passwd,
				     strlen(old_passwd), new_passwd, strlen(new_passwd));
  crypt_free(cd);
  return (0);
}

/* int closeContainer(const char *device)
 *
 * Ferme le container
 * Return un int : 0 aucune erreur
 *                -1 erreur
 *
 */

int 	closeContainer(const char *device)
{
  struct crypt_device *cd;

  if (crypt_deactivate(cd, device) < 0) {
      fprintf(stderr, "Error faild to close container\n");
      crypt_free(cd);
      return (-1);
    }
  crypt_free(cd);
  return (0);
}
