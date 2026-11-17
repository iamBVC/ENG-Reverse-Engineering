/* sub_2110E1FF @ 2110e1ff   185 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_2110E1FF(void)

{
  char cVar1;
  size_t sVar2;
  undefined4 *puVar3;
  void *pvVar4;
  int iVar5;
  uint *puVar6;
  
  if (DAT_21115b4c == 0) {
    sub_21110138();
  }
  iVar5 = 0;
  for (puVar6 = DAT_21115600; (char)*puVar6 != '\0'; puVar6 = (uint *)((int)puVar6 + sVar2 + 1)) {
    if ((char)*puVar6 != '=') {
      iVar5 = iVar5 + 1;
    }
    sVar2 = _strlen((char *)puVar6);
  }
  puVar3 = _malloc(iVar5 * 4 + 4);
  _DAT_21115648 = puVar3;
  if (puVar3 == (undefined4 *)0x0) {
    __amsg_exit(9);
  }
  cVar1 = (char)*DAT_21115600;
  puVar6 = DAT_21115600;
  while (cVar1 != '\0') {
    sVar2 = _strlen((char *)puVar6);
    if ((char)*puVar6 != '=') {
      pvVar4 = _malloc(sVar2 + 1);
      *puVar3 = pvVar4;
      if (pvVar4 == (void *)0x0) {
        __amsg_exit(9);
      }
      sub_2110F6C0((uint *)*puVar3,puVar6);
      puVar3 = puVar3 + 1;
    }
    puVar6 = (uint *)((int)puVar6 + sVar2 + 1);
    cVar1 = (char)*puVar6;
  }
  sub_2110D99D(DAT_21115600);
  DAT_21115600 = (uint *)0x0;
  *puVar3 = 0;
  _DAT_21115b48 = 1;
  return;
}

