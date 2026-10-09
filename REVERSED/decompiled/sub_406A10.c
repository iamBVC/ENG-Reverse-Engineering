/* sub_406A10 @ 00406a10   158 bytes */

void sub_406A10(int param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined2 *puVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined2 *puVar10;
  
  iVar8 = 0;
  uVar7 = 0;
  if (param_3 * param_4 != 1) {
    do {
      sVar1 = *(short *)(param_1 + iVar8 * 2);
      if (sVar1 < 0) {
        uVar4 = uVar7 - (int)sVar1;
        uVar2 = *(undefined2 *)(param_1 + 2 + iVar8 * 2);
        iVar8 = iVar8 + 1;
        if (uVar7 < uVar4) {
          uVar4 = uVar4 - uVar7;
          puVar9 = (undefined4 *)(param_2 + uVar7 * 2);
          for (uVar5 = uVar4 >> 1; uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar9 = CONCAT22(uVar2,uVar2);
            puVar9 = puVar9 + 1;
          }
          uVar7 = uVar7 + uVar4;
          for (uVar4 = (uint)((uVar4 & 1) != 0); uVar4 != 0; uVar4 = uVar4 - 1) {
            *(undefined2 *)puVar9 = uVar2;
            puVar9 = (undefined4 *)((int)puVar9 + 2);
          }
        }
      }
      else {
        uVar4 = (int)sVar1 + uVar7;
        iVar8 = iVar8 + 1;
        if (uVar7 < uVar4) {
          iVar3 = uVar4 - uVar7;
          puVar10 = (undefined2 *)(param_1 + iVar8 * 2);
          puVar6 = (undefined2 *)(param_2 + uVar7 * 2);
          iVar8 = iVar8 + iVar3;
          uVar7 = uVar7 + iVar3;
          do {
            uVar2 = *puVar10;
            puVar10 = puVar10 + 1;
            *puVar6 = uVar2;
            puVar6 = puVar6 + 1;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
        }
        iVar8 = iVar8 + -1;
      }
      iVar8 = iVar8 + 1;
    } while (uVar7 < param_3 * param_4 - 1U);
  }
  return;
}

