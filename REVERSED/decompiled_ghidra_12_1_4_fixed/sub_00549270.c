/* sub_549270 @ 00549270   944 bytes */

void __thiscall sub_549270(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  undefined4 *puVar2;
  byte bVar3;
  undefined2 uVar4;
  undefined3 uVar8;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  byte bVar9;
  uint uVar10;
  undefined4 extraout_ECX;
  undefined2 extraout_var;
  int *piVar11;
  int local_4;
  
  bVar1 = *(byte *)(param_4 + 10);
  uVar10 = CONCAT31((int3)((uint)param_1 >> 8),bVar1) & 0xffffff0f;
  bVar9 = (byte)uVar10;
  bVar3 = bVar1 & 0xf;
  if (bVar9 < 0x10) {
    local_4 = param_1;
    switch(bVar1 & 0xf0) {
    case 0x90:
      uVar8 = (undefined3)((bVar1 & 0xf0) - 0x80 >> 8);
      if (*(char *)(param_4 + 0xc) != '\0') {
        local_4 = 0;
        iVar6 = sub_549830(param_3,CONCAT31(uVar8,*(undefined1 *)(param_4 + 0xb)),
                           CONCAT31(uVar8,*(char *)(param_4 + 0xc)),bVar3);
        if (iVar6 == 0) {
          return;
        }
        iVar5 = sub_549710(param_2,*(undefined1 *)(param_4 + 0xb),*(undefined1 *)(param_4 + 0xc),
                           bVar3);
        if (iVar5 == 0) {
          return;
        }
        *(undefined4 *)(iVar5 + 0x94) = 0;
        sub_547750(*(undefined4 *)(param_2 + 0x10),iVar5 + 0x80,
                   *(undefined1 *)(param_3 + 0x53 + (bVar1 & 0xf) * 0xc),0);
        if (*(int *)(iVar5 + 0x88) == 0) {
          return;
        }
        uVar4 = sub_5498C0(*(undefined1 *)(param_4 + 0xb),
                           (short)*(char *)(param_3 + (bVar1 & 0xf) * 0xc + 0x57),
                           *(undefined1 *)(iVar6 + 4),*(undefined1 *)(iVar6 + 5));
        *(undefined2 *)(iVar5 + 0x6c) = uVar4;
        *(int *)(iVar5 + 8) = iVar6;
        *(int *)(iVar5 + 0xc) = param_3;
        *(undefined4 *)(iVar5 + 0x10) = 2;
        sub_5479B0(*(undefined4 *)(iVar5 + 0x88),*(byte *)(iVar6 + 1) & 4);
        sub_547900(*(undefined4 *)(iVar5 + 0x88),
                   CONCAT22(extraout_var,*(undefined2 *)(iVar5 + 0x6c)));
        uVar7 = sub_5490C0(param_2,param_3,iVar5);
        sub_5478C0(*(undefined4 *)(iVar5 + 0x88),uVar7);
        uVar7 = sub_5497B0(param_3,iVar5,&local_4);
        sub_547950(*(undefined4 *)(iVar5 + 0x88),uVar7);
        sub_426500(*(undefined4 *)(iVar5 + 0x88),*(undefined2 *)(iVar6 + 0x10),
                   *(undefined2 *)(iVar6 + 0x12));
        if (local_4 != 0) {
          sub_547970(*(undefined4 *)(iVar5 + 0x88),local_4);
        }
        sub_547840(*(undefined4 *)(param_2 + 0x10),*(undefined4 *)(iVar5 + 0x88));
        return;
      }
    case 0x80:
      iVar6 = sub_549880(param_2,param_3,
                         CONCAT31((int3)(uVar10 >> 8),*(undefined1 *)(param_4 + 0xb)),bVar3);
      if (iVar6 != 0) {
        sub_549760(param_2,iVar6 + 0x80,0);
        return;
      }
      break;
    case 0xb0:
      switch(*(undefined1 *)(param_4 + 0xb)) {
      case 6:
      case 99:
        if (*(char *)(param_4 + 0xc) == '\x1e') {
          *(undefined4 *)(param_3 + 0x34) = *(undefined4 *)(param_3 + 0x14);
          *(undefined2 *)(param_3 + 0x48) = *(undefined2 *)(param_3 + 0x20);
          *(undefined4 *)(param_3 + 0x44) = *(undefined4 *)(param_3 + 0x18);
          return;
        }
        break;
      case 7:
      case 0xb:
        *(undefined1 *)(param_3 + ((bVar1 & 0xf) + 7) * 0xc) = *(undefined1 *)(param_4 + 0xc);
        piVar11 = *(int **)(param_2 + 0x74);
        if (piVar11 != (int *)0x0) {
          do {
            if ((piVar11[3] == param_3) && (*(char *)((int)piVar11 + 0x7d) == (char)uVar10)) {
              uVar7 = sub_5490C0(param_2,param_3,piVar11);
              sub_5478C0(piVar11[0x22],uVar7);
              uVar10 = bVar1 & 0xf;
            }
            piVar11 = (int *)*piVar11;
          } while (piVar11 != (int *)0x0);
          return;
        }
        break;
      case 10:
        *(undefined1 *)(param_3 + 0x52 + (bVar1 & 0xf) * 0xc) = *(undefined1 *)(param_4 + 0xc);
        piVar11 = *(int **)(param_2 + 0x74);
        if (piVar11 != (int *)0x0) {
          do {
            if ((piVar11[3] == param_3) && (*(char *)((int)piVar11 + 0x7d) == (char)uVar10)) {
              uVar7 = sub_5490C0(param_2,param_3,piVar11);
              sub_5478C0(piVar11[0x22],uVar7);
              uVar10 = bVar1 & 0xf;
            }
            piVar11 = (int *)*piVar11;
          } while (piVar11 != (int *)0x0);
          return;
        }
        break;
      case 0x10:
        *(undefined1 *)(param_3 + 0x53 + (bVar1 & 0xf) * 0xc) = *(undefined1 *)(param_4 + 0xc);
        return;
      }
      break;
    case 0xc0:
      sub_5497F0(param_3,(uint)*(byte *)(param_4 + 0xb) * 0x10 +
                         *(int *)(*(int *)(param_3 + 0x38) + 4),bVar1 & 0xf);
      return;
    case 0xe0:
      iVar6 = ((*(byte *)(param_4 + 0xc) - 0x40) * 0x80 + (uint)*(byte *)(param_4 + 0xb)) * 0x960;
      iVar6 = (int)(iVar6 + (iVar6 >> 0x1f & 0x1fffU)) >> 0xd;
      *(char *)(param_3 + 0x57 + (bVar1 & 0xf) * 0xc) = (char)iVar6;
      for (puVar2 = *(undefined4 **)(param_2 + 0x74); puVar2 != (undefined4 *)0x0;
          puVar2 = (undefined4 *)*puVar2) {
        if ((puVar2[3] == param_3) && (*(char *)((int)puVar2 + 0x7d) == (char)uVar10)) {
          iVar5 = puVar2[2];
          uVar7 = sub_5498C0(CONCAT22((short)((uint)iVar5 >> 0x10),(ushort)*(byte *)(puVar2 + 0x1f))
                             ,iVar6,*(undefined1 *)(iVar5 + 4),
                             CONCAT31((int3)(uVar10 >> 8),*(undefined1 *)(iVar5 + 5)));
          *(short *)(puVar2 + 0x1b) = (short)uVar7;
          sub_547900(puVar2[0x22],uVar7);
          uVar10 = CONCAT31((int3)((uint)extraout_ECX >> 8),bVar9);
        }
      }
    }
  }
  return;
}

