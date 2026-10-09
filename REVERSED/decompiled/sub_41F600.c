/* sub_41F600 @ 0041f600   45 bytes */

undefined4 sub_41F600(char *param_1,char *param_2)

{
  char *pcVar1;
  
  if (*param_1 == *param_2) {
    do {
      pcVar1 = param_2 + 1;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
      if ((*pcVar1 == '\0') || (*param_1 == '\0')) {
        return 0;
      }
    } while (*param_1 == *pcVar1);
  }
  return 1;
}

