/* sub_56D4ED @ 0056d4ed   43 bytes */

undefined4 sub_56D4ED(char *param_1)

{
  size_t sVar1;
  void *pvVar2;
  undefined4 uVar3;
  
  if (param_1 != (char *)0x0) {
    sVar1 = _strlen(param_1);
    pvVar2 = _malloc(sVar1 + 1);
    if (pvVar2 != (void *)0x0) {
      uVar3 = sub_569990(pvVar2,param_1);
      return uVar3;
    }
  }
  return 0;
}

