/* sub_407140 @ 00407140   130 bytes */

void sub_407140(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_00581138 == 0) {
    DAT_00581134 = 0;
    return;
  }
  iVar5 = 0;
  iVar3 = DAT_00581138;
  if (0 < DAT_00581134) {
    iVar4 = 0;
    do {
      bVar1 = *(byte *)(iVar4 + 2 + iVar3);
      if (bVar1 == 8) {
        iVar2 = *(int *)(iVar4 + 0xc + iVar3);
joined_r0x00407179:
        if (iVar2 != 0) {
          sub_562941(iVar2);
          iVar3 = DAT_00581138;
        }
      }
      else if ((9 < bVar1) && (bVar1 < 0xc)) {
        iVar2 = *(int *)(iVar4 + 0xc + iVar3);
        goto joined_r0x00407179;
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x10;
    } while (iVar5 < DAT_00581134);
  }
  sub_562941(iVar3);
  DAT_00581138 = 0;
  DAT_00581134 = 0;
  return;
}

