#ifndef PAMELA_H
# define PAMELA_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <unistd.h>
#include <inttypes.h>
#include <libcryptsetup.h>
#include <sys/mount.h>
#include <pwd.h>

int		findContainer(const char *);
char	*getInitCmd(char *path);
char    *getUserInfo(pam_handle_t *pamh, int value);
char	*getCreatCmd(char *path);
int		isSaveZone(char *path);
int		isContainer(char *container_path, char *devices_name);
int		initContainer(char *container_path, char *device_name, char *);
int 	setContainerHeader(char *device_name, char *passwd);
int		activateContainer(char *path, char *device_name, char *passwd);
int		mountSecurePoint(char *mountPath, char *mountPointPath, char *);
int		umountSecurePoint(char *mountPath, char *mountPointPath);
char	*concat(char *one, char *two);
int		creatDir(char *dirpath);
int 	ontainerStatus(const char *device_name);
int 	closeContainer(const char *device_name);
int 	changerPasswd(const char *device, char *old_passwd, char* new_passwd);

#endif /* !PAMELA_H */