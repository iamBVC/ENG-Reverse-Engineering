/* sub_40E4F0 @ 0040e4f0   199 bytes */

void sub_40E4F0(int param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  undefined1 local_204 [244];
  CHAR aCStack_110 [12];
  int local_104;
  char *pcStack_8;
  
  local_104 = param_1;
  local_204[0] = 0;
  (**(code **)(*DAT_00582a80 + 0x10))(DAT_00582a80,&LAB_0040e5c0,local_204,0xc);
  uVar2 = 0xffffffff;
  pcVar5 = &stack0xfffffdec;
  do {
    pcVar6 = pcVar5;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar5 = pcVar6 + -uVar2;
  pcVar6 = pcStack_8;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  iVar4 = -1;
  pcVar5 = pcStack_8;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  if ((iVar4 != -3) && (iVar4 = _strncmp(pcStack_8,&DAT_005714d8,3), iVar4 != 0)) {
    return;
  }
  GetKeyNameTextA(param_1 << 0x10,aCStack_110,0x100);
  uVar2 = 0xffffffff;
  pcVar5 = aCStack_110;
  do {
    pcVar6 = pcVar5;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar5 = pcVar6 + -uVar2;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcStack_8 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcStack_8 = pcStack_8 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcStack_8 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcStack_8 = pcStack_8 + 1;
  }
  return;
}

