//
// Created by costa_d on 25/11/17.
//

#include "pamela.h"

int	main()
{
  printf("Testing 1\n");
  if (isSaveZone("./pamela_containers") == -1)
    return (0);
  if (isContainer("./pamela_containers/", "test") == -1)
    return (0);
  return (0);
}