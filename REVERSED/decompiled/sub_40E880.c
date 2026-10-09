/* sub_40E880 @ 0040e880   219 bytes */

undefined1 sub_40E880(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  int *piVar7;
  undefined4 *puVar8;
  undefined1 local_4 [4];
  
  puVar8 = (undefined4 *)&DAT_0056e61c;
  iVar2 = (**(code **)(*DAT_00582a74 + 0xc))(DAT_00582a74,&DAT_0056e61c,local_4,0);
  if (iVar2 != 0) {
    return 0;
  }
  piVar7 = (int *)&DAT_0056e6bc;
  iVar2 = (**(code **)*puVar8)(puVar8,&DAT_0056e6bc,&DAT_00582a80);
  if (piVar7 != (int *)0x0) {
    (**(code **)(*piVar7 + 8))(piVar7);
  }
  if (iVar2 != 0) {
    return 0;
  }
  iVar2 = (**(code **)(*DAT_00582a80 + 0x2c))(DAT_00582a80,&DAT_0056e72c,puVar8,0);
  if (iVar2 != 0) {
    if (DAT_00582a80 != (int *)0x0) {
      (**(code **)(*DAT_00582a80 + 8))(DAT_00582a80);
      DAT_00582a80 = (int *)0x0;
    }
    return 0;
  }
  cVar1 = sub_40E7F0(1);
  if (cVar1 == '\0') {
    return 0;
  }
  uVar3 = 0xffffffff;
  pcVar5 = s_Keyboard_005714e8;
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  pcVar6 = (char *)&DAT_00582b50;
  for (uVar4 = uVar3 >> 2; piVar7 = DAT_00582a74, uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  (**(code **)(*piVar7 + 0x10))(piVar7,3,&LAB_0040e960,0,1);
  return 1;
}

