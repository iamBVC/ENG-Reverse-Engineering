/* sub_418EE0 @ 00418ee0   729 bytes */

undefined4 sub_418EE0(int param_1)

{
  code *pcVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  
  if (DAT_00583a68 == -1) {
    iVar2 = param_1;
    if ((DAT_005fcf08 & 0x10) != 0) {
      sub_4170E0();
      sub_546170(0,0xffffff80,8);
      if ((0 < *(int *)(param_1 + 0xc)) && (iVar2 = *(int *)(param_1 + 0xc) + -1, -1 < iVar2)) {
        piVar8 = (int *)(*(int *)(param_1 + 0x10) + 4 + iVar2 * 0x18);
        do {
          if (*piVar8 != 0) {
            *(int *)(param_1 + 0xc) = iVar2;
            break;
          }
          iVar2 = iVar2 + -1;
          piVar8 = piVar8 + -6;
        } while (-1 < iVar2);
      }
      if ((*(int *)(param_1 + 0xc) != iVar2) && (iVar2 = *(int *)(param_1 + 8) + -1, -1 < iVar2)) {
        piVar8 = (int *)(*(int *)(param_1 + 0x10) + 4 + iVar2 * 0x18);
        do {
          if (*piVar8 != 0) {
            *(int *)(param_1 + 0xc) = iVar2;
            break;
          }
          iVar2 = iVar2 + -1;
          piVar8 = piVar8 + -6;
        } while (-1 < iVar2);
      }
    }
    if ((DAT_005fcf08 & 0x40) != 0) {
      sub_4170E0();
      sub_546170(0,0xffffff80,8);
      iVar4 = *(int *)(param_1 + 8);
      iVar7 = *(int *)(param_1 + 0xc) + 1;
      if ((iVar7 < iVar4) && (iVar2 = iVar7, iVar7 < iVar4)) {
        piVar8 = (int *)(*(int *)(param_1 + 0x10) + 4 + iVar7 * 0x18);
        do {
          if (*piVar8 != 0) {
            *(int *)(param_1 + 0xc) = iVar7;
            iVar2 = iVar7;
            break;
          }
          iVar7 = iVar7 + 1;
          piVar8 = piVar8 + 6;
          iVar2 = iVar7;
        } while (iVar7 < iVar4);
      }
      if ((*(int *)(param_1 + 0xc) != iVar2) && (iVar2 = 0, 0 < iVar4)) {
        piVar8 = (int *)(*(int *)(param_1 + 0x10) + 4);
        do {
          if (*piVar8 != 0) {
            *(int *)(param_1 + 0xc) = iVar2;
            break;
          }
          iVar2 = iVar2 + 1;
          piVar8 = piVar8 + 6;
        } while (iVar2 < iVar4);
      }
    }
    sub_417150();
    if (*(code **)(param_1 + 0x14) != (code *)0x0) {
      (**(code **)(param_1 + 0x14))
                (*(undefined4 *)(*(int *)(param_1 + 0x10) + 0xc + *(int *)(param_1 + 0xc) * 0x18));
    }
    uVar6 = *(uint *)(*(int *)(param_1 + 0x10) + 0x14 + *(int *)(param_1 + 0xc) * 0x18) &
            DAT_005fcf08;
    if (uVar6 != 0) {
      if ((uVar6 & 0x4000) != 0) {
        sub_546170(0,0xffffff81,8);
      }
      pcVar1 = *(code **)(*(int *)(param_1 + 0x10) + 8 + *(int *)(param_1 + 0xc) * 0x18);
      if (pcVar1 != (code *)0x0) {
        uVar5 = (*pcVar1)(*(undefined4 *)
                           (*(int *)(param_1 + 0x10) + *(int *)(param_1 + 0xc) * 0x18 + 0xc));
        return uVar5;
      }
    }
  }
  else {
    if (DAT_00583a68 != -2) {
      DAT_00583a24 = DAT_00583a24 + 1;
      piVar8 = (int *)(param_1 + 0xc);
      if ((DAT_00583a24 & 8) == 0) {
        puVar3 = (uint *)(*(int *)(param_1 + 0x10) + 0x28 + *piVar8 * 0x18);
        uVar6 = *(uint *)(*(int *)(param_1 + 0x10) + 0x28 + *piVar8 * 0x18) & 0xfffffff7;
      }
      else {
        puVar3 = (uint *)(*(int *)(param_1 + 0x10) + 0x28 + *piVar8 * 0x18);
        uVar6 = *puVar3 | 8;
      }
      *puVar3 = uVar6;
      if (DAT_00583984 == 0) {
        iVar2 = sub_40E630();
        if (iVar2 == 0) {
          DAT_00583984 = 1;
        }
      }
      else if (DAT_00583a6c == 1) {
        iVar2 = sub_40E630();
        if (((iVar2 != -1) && (iVar2 != 0)) && (iVar4 = sub_40E690(iVar2), iVar4 != -1)) {
          sub_546170(0,0xffffff81,8);
          sub_4199F0(iVar2,DAT_00583a68,iVar4);
          DAT_00583a68 = 0xfffffffe;
          sub_418C10();
          puVar3 = (uint *)(*(int *)(param_1 + 0x10) + 0x28 + *piVar8 * 0x18);
          *puVar3 = *puVar3 & 0xfffffff7;
          sub_419A60(iVar2);
          DAT_00583a6c = 0;
          return 0;
        }
      }
      else {
        iVar2 = sub_40E630();
        if ((iVar2 == -1) && (iVar2 = sub_40E690(0), iVar2 != -1)) {
          sub_546170(0,0xffffff81,8);
          sub_4199F0(0,DAT_00583a68,iVar2);
          DAT_00583a68 = 0xfffffffe;
          sub_418AA0();
          puVar3 = (uint *)(*(int *)(param_1 + 0x10) + 0x28 + *piVar8 * 0x18);
          *puVar3 = *puVar3 & 0xfffffff7;
          sub_419A60(0);
          return 0;
        }
      }
      return 0;
    }
    iVar2 = sub_40E630();
    if (iVar2 == 0) {
      DAT_00583a68 = -1;
    }
  }
  return 0;
}

