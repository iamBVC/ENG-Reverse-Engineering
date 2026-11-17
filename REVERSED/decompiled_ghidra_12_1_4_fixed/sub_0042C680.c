/* sub_42C680 @ 0042c680   260 bytes */

void sub_42C680(int param_1,int param_2)

{
  byte *pbVar1;
  int iVar2;
  undefined1 uVar3;
  uint uVar4;
  undefined1 *puVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  uVar4 = (uint)*(byte *)(*(int *)(*(int *)(DAT_00584648 + 0x54) + param_1 * 4) + 3);
  if (uVar4 == 0) {
    uVar4 = 1;
  }
  uVar8 = 0;
  if (uVar4 * param_2 != 0) {
    do {
      iVar2 = uVar8 * 4;
      iVar7 = *(int *)(*(int *)(DAT_00584648 + 0x54) + param_1 * 4);
      puVar5 = (undefined1 *)(iVar7 + iVar2);
      *(uint *)(*(int *)(*(int *)(DAT_00584648 + 0x58) + param_1 * 4) + iVar2) =
           (uint)CONCAT21(CONCAT11(*puVar5,puVar5[1]),*(undefined1 *)(iVar7 + 2 + iVar2));
      if (DAT_006d7c61 == '\0') {
        puVar5 = (undefined1 *)(*(int *)(*(int *)(DAT_00584648 + 0x58) + param_1 * 4) + iVar2);
        uVar3 = __ftol();
        *puVar5 = uVar3;
        puVar5[1] = uVar3;
        puVar5[2] = uVar3;
      }
      iVar7 = 0;
      do {
        pbVar1 = (byte *)(*(int *)(*(int *)(DAT_00584648 + 0x58) + param_1 * 4) + iVar2 + iVar7);
        uVar6 = (uint)*pbVar1 * 2;
        if (0xff < uVar6) {
          uVar6 = 0xff;
        }
        iVar7 = iVar7 + 1;
        *pbVar1 = (byte)uVar6;
      } while (iVar7 < 3);
      uVar8 = uVar8 + 1;
    } while (uVar8 < uVar4 * param_2);
  }
  return;
}

