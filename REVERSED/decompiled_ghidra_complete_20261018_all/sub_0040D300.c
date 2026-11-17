/* sub_40D300 @ 0040d300   166 bytes */

undefined4 sub_40D300(int param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint local_4;
  
  iVar6 = 0;
  iVar7 = 0;
  if (0 < param_3) {
    do {
      bVar1 = *(byte *)(iVar6 + param_1);
      local_4 = (uint)bVar1;
      iVar3 = iVar6 + 1;
      if ((bVar1 & 0x80) == 0) {
        for (; iVar6 = iVar3, local_4 != 0; local_4 = local_4 - 1) {
          *(undefined1 *)(iVar7 + param_2) = *(undefined1 *)(iVar6 + param_1);
          iVar7 = iVar7 + 1;
          iVar3 = iVar6 + 1;
        }
      }
      else {
        iVar5 = 0;
        uVar2 = *(undefined1 *)(iVar6 + 1 + param_1);
        iVar6 = iVar6 + 2;
        iVar3 = (bVar1 >> 4 & 7) + 3;
        if (iVar3 != 0) {
          do {
            iVar4 = iVar5 - (CONCAT11(bVar1,uVar2) & 0xfff);
            iVar5 = iVar5 + 1;
            *(undefined1 *)(iVar7 + param_2 + -1 + iVar5) = *(undefined1 *)(iVar4 + iVar7 + param_2)
            ;
          } while (iVar5 < iVar3);
        }
        iVar7 = iVar7 + iVar3;
      }
    } while (iVar7 < param_3);
    return 0;
  }
  return 0;
}

