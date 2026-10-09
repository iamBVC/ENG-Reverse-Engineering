/* sub_55A6D0 @ 0055a6d0   2250 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_55A6D0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  
  DAT_0057c530 = param_3;
  DAT_0057c528 = param_1;
  DAT_0057c52c = param_2;
  sub_559459();
  _DAT_0057c518 =
       (double)(((float)DAT_0057d850 - _DAT_0057c734) + _DAT_0057c738 +
               (float)DAT_0057d864 * ((float)DAT_0057c558 - _DAT_0057c730));
  _DAT_0057c520 =
       (double)(((float)_DAT_0057d8a8 - _DAT_0057c734) + _DAT_0057c738 +
               ((float)DAT_0057c558 - _DAT_0057c730) * (float)DAT_0057d8bc);
  DAT_0057c594 = DAT_0057c4a0 << 0x10;
  DAT_0057c598 = DAT_0057c4a4 << 0x10;
  if (DAT_0057c55c != 0) {
    iVar5 = DAT_0057c520;
    if (-1 < DAT_0057c59c) {
      do {
        uVar4 = DAT_0057c4a8 >> 0x10;
        DAT_0057c5b8 = DAT_0057c518 + uVar4 * 2;
        iVar5 = iVar5 + uVar4 * 2;
        iVar2 = (DAT_0057c4a0 >> 0x10) - uVar4;
        DAT_0057c560 = DAT_0057c4b8;
        DAT_0057c564 = DAT_0057c4d8;
        DAT_0057c568 = DAT_0057c4e8;
        DAT_0057c56c = DAT_0057c4c8;
        if (uVar4 <= DAT_0057c4a0 >> 0x10) {
          do {
            iVar3 = DAT_0057c5b8;
            if (DAT_0057c560 >> 0x10 <=
                (uint)CONCAT11(*(undefined1 *)(iVar5 + 1 + iVar2 * 2),
                               *(undefined1 *)(iVar5 + iVar2 * 2))) {
              uVar1 = *(undefined2 *)
                       (DAT_0057d8d4 + (uint)CONCAT11(DAT_0057c568._2_1_,DAT_0057c564._2_1_) * 2);
              *(short *)(iVar5 + iVar2 * 2) = (short)(DAT_0057c560 >> 0x10);
              uVar4 = (CONCAT22(uVar1,uVar1) & 0x7e0f81f) * (DAT_0057c56c >> 0x13);
              *(ushort *)(iVar3 + iVar2 * 2) =
                   ((ushort)(uVar4 >> 0x10) & 0xfc1f) >> 5 | (ushort)((uVar4 & 0xfc1f03e0) >> 5);
            }
            DAT_0057c560 = DAT_0057c560 - DAT_0057c4c0;
            DAT_0057c56c = DAT_0057c56c - DAT_0057c4d0;
            DAT_0057c564 = DAT_0057c564 - DAT_0057c4e0;
            DAT_0057c568 = DAT_0057c568 - DAT_0057c4f0;
            bVar6 = 0 < iVar2;
            iVar2 = iVar2 + -1;
          } while (bVar6);
        }
        bVar6 = CARRY4(DAT_0057c594,DAT_0057c598);
        DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
        uVar4 = (uint)bVar6;
        DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
        DAT_0057c4a8 = DAT_0057c4a8 + DAT_0057c4ac;
        DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + uVar4 * -8);
        DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + uVar4 * -8);
        DAT_0057c4b8 = DAT_0057c4b8 + *(int *)(&DAT_0057c4c4 + uVar4 * -8);
        DAT_0057c4c8 = DAT_0057c4c8 + *(int *)(&DAT_0057c4d4 + uVar4 * -8);
        iVar5 = DAT_0057c520 + DAT_0057d8bc;
        _DAT_0057c518 = (double)CONCAT44(DAT_0057c518_4,DAT_0057c518 + DAT_0057d864);
        iVar2 = DAT_0057c59c + -1;
        _DAT_0057c520 = (double)CONCAT44(DAT_0057c520_4,iVar5);
        bVar6 = 0 < DAT_0057c59c;
        DAT_0057c560 = DAT_0057c4b8;
        DAT_0057c564 = DAT_0057c4d8;
        DAT_0057c568 = DAT_0057c4e8;
        DAT_0057c56c = DAT_0057c4c8;
        DAT_0057c59c = iVar2;
      } while (bVar6);
    }
    iVar5 = DAT_0057c520;
    if (-1 < DAT_0057c5a0) {
      do {
        uVar4 = DAT_0057c4b0 >> 0x10;
        DAT_0057c5b8 = DAT_0057c518 + uVar4 * 2;
        iVar5 = iVar5 + uVar4 * 2;
        iVar2 = (DAT_0057c4a0 >> 0x10) - uVar4;
        DAT_0057c560 = DAT_0057c4b8;
        DAT_0057c564 = DAT_0057c4d8;
        DAT_0057c568 = DAT_0057c4e8;
        DAT_0057c56c = DAT_0057c4c8;
        if (uVar4 <= DAT_0057c4a0 >> 0x10) {
          do {
            iVar3 = DAT_0057c5b8;
            if (DAT_0057c560 >> 0x10 <=
                (uint)CONCAT11(*(undefined1 *)(iVar5 + 1 + iVar2 * 2),
                               *(undefined1 *)(iVar5 + iVar2 * 2))) {
              uVar1 = *(undefined2 *)
                       (DAT_0057d8d4 + (uint)CONCAT11(DAT_0057c568._2_1_,DAT_0057c564._2_1_) * 2);
              *(short *)(iVar5 + iVar2 * 2) = (short)(DAT_0057c560 >> 0x10);
              uVar4 = (CONCAT22(uVar1,uVar1) & 0x7e0f81f) * (DAT_0057c56c >> 0x13);
              *(ushort *)(iVar3 + iVar2 * 2) =
                   ((ushort)(uVar4 >> 0x10) & 0xfc1f) >> 5 | (ushort)((uVar4 & 0xfc1f03e0) >> 5);
            }
            DAT_0057c560 = DAT_0057c560 - DAT_0057c4c0;
            DAT_0057c56c = DAT_0057c56c - DAT_0057c4d0;
            DAT_0057c564 = DAT_0057c564 - DAT_0057c4e0;
            DAT_0057c568 = DAT_0057c568 - DAT_0057c4f0;
            bVar6 = 0 < iVar2;
            iVar2 = iVar2 + -1;
          } while (bVar6);
        }
        bVar6 = CARRY4(DAT_0057c594,DAT_0057c598);
        DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
        uVar4 = (uint)bVar6;
        DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
        DAT_0057c4b0 = DAT_0057c4b0 + DAT_0057c4b4;
        DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + uVar4 * -8);
        DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + uVar4 * -8);
        DAT_0057c4b8 = DAT_0057c4b8 + *(int *)(&DAT_0057c4c4 + uVar4 * -8);
        DAT_0057c4c8 = DAT_0057c4c8 + *(int *)(&DAT_0057c4d4 + uVar4 * -8);
        iVar5 = DAT_0057c520 + DAT_0057d8bc;
        _DAT_0057c518 = (double)CONCAT44(DAT_0057c518_4,DAT_0057c518 + DAT_0057d864);
        iVar2 = DAT_0057c5a0 + -1;
        _DAT_0057c520 = (double)CONCAT44(DAT_0057c520_4,iVar5);
        bVar6 = 0 < DAT_0057c5a0;
        DAT_0057c560 = DAT_0057c4b8;
        DAT_0057c564 = DAT_0057c4d8;
        DAT_0057c568 = DAT_0057c4e8;
        DAT_0057c56c = DAT_0057c4c8;
        DAT_0057c5a0 = iVar2;
      } while (bVar6);
    }
    return;
  }
  iVar5 = DAT_0057c520;
  if (-1 < DAT_0057c59c) {
    do {
      uVar4 = DAT_0057c4a8 >> 0x10;
      DAT_0057c5b8 = DAT_0057c518 + uVar4 * 2;
      iVar2 = (DAT_0057c4a0 >> 0x10) - uVar4;
      iVar5 = iVar5 + uVar4 * 2;
      DAT_0057c560 = DAT_0057c4b8;
      DAT_0057c564 = DAT_0057c4d8;
      DAT_0057c568 = DAT_0057c4e8;
      DAT_0057c56c = DAT_0057c4c8;
      if (iVar2 == 0 || DAT_0057c4a0 >> 0x10 < uVar4) {
        do {
          iVar3 = DAT_0057c5b8;
          if (DAT_0057c560 >> 0x10 <=
              (uint)CONCAT11(*(undefined1 *)(iVar5 + 1 + iVar2 * 2),
                             *(undefined1 *)(iVar5 + iVar2 * 2))) {
            uVar1 = *(undefined2 *)
                     (DAT_0057d8d4 + (uint)CONCAT11(DAT_0057c568._2_1_,DAT_0057c564._2_1_) * 2);
            *(short *)(iVar5 + iVar2 * 2) = (short)(DAT_0057c560 >> 0x10);
            uVar4 = (CONCAT22(uVar1,uVar1) & 0x7e0f81f) * (DAT_0057c56c >> 0x13);
            *(ushort *)(iVar3 + iVar2 * 2) =
                 ((ushort)(uVar4 >> 0x10) & 0xfc1f) >> 5 | (ushort)((uVar4 & 0xfc1f03e0) >> 5);
          }
          DAT_0057c560 = DAT_0057c560 + DAT_0057c4c0;
          DAT_0057c56c = DAT_0057c56c + DAT_0057c4d0;
          DAT_0057c564 = DAT_0057c564 + DAT_0057c4e0;
          DAT_0057c568 = DAT_0057c568 + DAT_0057c4f0;
          iVar3 = iVar2 + 1;
          bVar6 = iVar2 < -1;
          iVar2 = iVar3;
        } while (iVar3 == 0 || bVar6);
      }
      bVar6 = CARRY4(DAT_0057c594,DAT_0057c598);
      DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
      uVar4 = (uint)bVar6;
      DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
      DAT_0057c4a8 = DAT_0057c4a8 + DAT_0057c4ac;
      DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + uVar4 * -8);
      DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + uVar4 * -8);
      DAT_0057c4b8 = DAT_0057c4b8 + *(int *)(&DAT_0057c4c4 + uVar4 * -8);
      DAT_0057c4c8 = DAT_0057c4c8 + *(int *)(&DAT_0057c4d4 + uVar4 * -8);
      iVar5 = DAT_0057c520 + DAT_0057d8bc;
      _DAT_0057c518 = (double)CONCAT44(DAT_0057c518_4,DAT_0057c518 + DAT_0057d864);
      iVar2 = DAT_0057c59c + -1;
      _DAT_0057c520 = (double)CONCAT44(DAT_0057c520_4,iVar5);
      bVar6 = 0 < DAT_0057c59c;
      DAT_0057c560 = DAT_0057c4b8;
      DAT_0057c564 = DAT_0057c4d8;
      DAT_0057c568 = DAT_0057c4e8;
      DAT_0057c56c = DAT_0057c4c8;
      DAT_0057c59c = iVar2;
    } while (bVar6);
  }
  iVar5 = DAT_0057c520;
  if (-1 < DAT_0057c5a0) {
    do {
      uVar4 = DAT_0057c4b0 >> 0x10;
      DAT_0057c5b8 = DAT_0057c518 + uVar4 * 2;
      iVar2 = (DAT_0057c4a0 >> 0x10) - uVar4;
      iVar5 = iVar5 + uVar4 * 2;
      DAT_0057c560 = DAT_0057c4b8;
      DAT_0057c564 = DAT_0057c4d8;
      DAT_0057c568 = DAT_0057c4e8;
      DAT_0057c56c = DAT_0057c4c8;
      if (iVar2 == 0 || DAT_0057c4a0 >> 0x10 < uVar4) {
        do {
          iVar3 = DAT_0057c5b8;
          if (DAT_0057c560 >> 0x10 <=
              (uint)CONCAT11(*(undefined1 *)(iVar5 + 1 + iVar2 * 2),
                             *(undefined1 *)(iVar5 + iVar2 * 2))) {
            uVar1 = *(undefined2 *)
                     (DAT_0057d8d4 + (uint)CONCAT11(DAT_0057c568._2_1_,DAT_0057c564._2_1_) * 2);
            *(short *)(iVar5 + iVar2 * 2) = (short)(DAT_0057c560 >> 0x10);
            uVar4 = (CONCAT22(uVar1,uVar1) & 0x7e0f81f) * (DAT_0057c56c >> 0x13);
            *(ushort *)(iVar3 + iVar2 * 2) =
                 ((ushort)(uVar4 >> 0x10) & 0xfc1f) >> 5 | (ushort)((uVar4 & 0xfc1f03e0) >> 5);
          }
          DAT_0057c560 = DAT_0057c560 + DAT_0057c4c0;
          DAT_0057c56c = DAT_0057c56c + DAT_0057c4d0;
          DAT_0057c564 = DAT_0057c564 + DAT_0057c4e0;
          DAT_0057c568 = DAT_0057c568 + DAT_0057c4f0;
          iVar3 = iVar2 + 1;
          bVar6 = iVar2 < -1;
          iVar2 = iVar3;
        } while (iVar3 == 0 || bVar6);
      }
      bVar6 = CARRY4(DAT_0057c594,DAT_0057c598);
      DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
      uVar4 = (uint)bVar6;
      DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
      DAT_0057c4b0 = DAT_0057c4b0 + DAT_0057c4b4;
      DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + uVar4 * -8);
      DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + uVar4 * -8);
      DAT_0057c4b8 = DAT_0057c4b8 + *(int *)(&DAT_0057c4c4 + uVar4 * -8);
      DAT_0057c4c8 = DAT_0057c4c8 + *(int *)(&DAT_0057c4d4 + uVar4 * -8);
      iVar5 = DAT_0057c520 + DAT_0057d8bc;
      _DAT_0057c518 = (double)CONCAT44(DAT_0057c518_4,DAT_0057c518 + DAT_0057d864);
      iVar2 = DAT_0057c5a0 + -1;
      _DAT_0057c520 = (double)CONCAT44(DAT_0057c520_4,iVar5);
      bVar6 = 0 < DAT_0057c5a0;
      DAT_0057c560 = DAT_0057c4b8;
      DAT_0057c564 = DAT_0057c4d8;
      DAT_0057c568 = DAT_0057c4e8;
      DAT_0057c56c = DAT_0057c4c8;
      DAT_0057c5a0 = iVar2;
    } while (bVar6);
  }
  return;
}

