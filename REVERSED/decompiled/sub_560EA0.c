/* sub_560EA0 @ 00560ea0   1131 bytes */

void sub_560EA0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  bool bVar10;
  
  DAT_0057c530 = param_3;
  DAT_0057c528 = param_1;
  DAT_0057c52c = param_2;
  sub_558FF0();
  iVar1 = DAT_0057c4f0;
  DAT_0057c518 = DAT_0057d850 + DAT_0057d864 * (DAT_0057c558 + -1) + -2;
  DAT_0057c594 = DAT_0057c4a0 << 0x10;
  DAT_0057c598 = DAT_0057c4a4 << 0x10;
  DAT_0057c5b8 = DAT_0057c4e0 << 0x10;
  uVar8 = DAT_0057c4f0 * 0x10000;
  if (DAT_0057c55c != 0) {
    if (-1 < DAT_0057c59c) {
      do {
        iVar3 = DAT_0057d8d4;
        uVar5 = DAT_0057c4a8 >> 0x10;
        iVar9 = DAT_0057c518 + uVar5 * 2;
        if (uVar5 <= DAT_0057c4a0 >> 0x10) {
          uVar6 = (uint)CONCAT11(DAT_0057c4e8._2_1_,DAT_0057c4d8._2_1_);
          uVar2 = CONCAT22((short)DAT_0057c4d8,CONCAT11(DAT_0057c4f0._2_1_,DAT_0057c4e0._2_1_));
          uVar7 = CONCAT22((short)DAT_0057c4e8,*(undefined2 *)(DAT_0057d8d4 + uVar6 * 2));
          iVar4 = (DAT_0057c4a0 >> 0x10) - uVar5;
          do {
            *(short *)(iVar9 + iVar4 * 2) = (short)uVar7;
            bVar10 = uVar2 < DAT_0057c5b8;
            uVar2 = uVar2 - DAT_0057c5b8;
            uVar6 = (uint)CONCAT11(((char)(uVar6 >> 8) - (char)(uVar2 >> 8)) - (uVar7 < uVar8),
                                   ((char)uVar6 - (char)uVar2) - bVar10);
            uVar7 = CONCAT22((short)(uVar7 + iVar1 * -0x10000 >> 0x10),
                             *(undefined2 *)(iVar3 + uVar6 * 2));
            bVar10 = 0 < iVar4;
            iVar4 = iVar4 + -1;
          } while (bVar10);
        }
        DAT_0057c4a8 = DAT_0057c4a8 + DAT_0057c4ac;
        bVar10 = CARRY4(DAT_0057c594,DAT_0057c598);
        DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
        DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + (uint)bVar10 * -8);
        DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + (uint)bVar10 * -8);
        DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
        DAT_0057c518 = DAT_0057c518 + DAT_0057d864;
        iVar3 = DAT_0057c59c + -1;
        bVar10 = 0 < DAT_0057c59c;
        DAT_0057c59c = iVar3;
      } while (bVar10);
    }
    if (-1 < DAT_0057c5a0) {
      do {
        iVar3 = DAT_0057d8d4;
        uVar5 = DAT_0057c4b0 >> 0x10;
        iVar9 = DAT_0057c518 + uVar5 * 2;
        if (uVar5 <= DAT_0057c4a0 >> 0x10) {
          uVar6 = (uint)CONCAT11(DAT_0057c4e8._2_1_,DAT_0057c4d8._2_1_);
          uVar2 = CONCAT22((short)DAT_0057c4d8,CONCAT11(DAT_0057c4f0._2_1_,DAT_0057c4e0._2_1_));
          uVar7 = CONCAT22((short)DAT_0057c4e8,*(undefined2 *)(DAT_0057d8d4 + uVar6 * 2));
          iVar4 = (DAT_0057c4a0 >> 0x10) - uVar5;
          do {
            *(short *)(iVar9 + iVar4 * 2) = (short)uVar7;
            bVar10 = uVar2 < DAT_0057c5b8;
            uVar2 = uVar2 - DAT_0057c5b8;
            uVar6 = (uint)CONCAT11(((char)(uVar6 >> 8) - (char)(uVar2 >> 8)) - (uVar7 < uVar8),
                                   ((char)uVar6 - (char)uVar2) - bVar10);
            uVar7 = CONCAT22((short)(uVar7 + iVar1 * -0x10000 >> 0x10),
                             *(undefined2 *)(iVar3 + uVar6 * 2));
            bVar10 = 0 < iVar4;
            iVar4 = iVar4 + -1;
          } while (bVar10);
        }
        DAT_0057c4b0 = DAT_0057c4b0 + DAT_0057c4b4;
        bVar10 = CARRY4(DAT_0057c594,DAT_0057c598);
        DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
        DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + (uint)bVar10 * -8);
        DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + (uint)bVar10 * -8);
        DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
        DAT_0057c518 = DAT_0057c518 + DAT_0057d864;
        iVar3 = DAT_0057c5a0 + -1;
        bVar10 = 0 < DAT_0057c5a0;
        DAT_0057c5a0 = iVar3;
      } while (bVar10);
    }
    return;
  }
  if (-1 < DAT_0057c59c) {
    do {
      iVar1 = DAT_0057d8d4;
      uVar5 = DAT_0057c4a8 >> 0x10;
      iVar9 = DAT_0057c518 + uVar5 * 2;
      iVar3 = (DAT_0057c4a0 >> 0x10) - uVar5;
      if (iVar3 == 0 || DAT_0057c4a0 >> 0x10 < uVar5) {
        uVar2 = (uint)CONCAT11(DAT_0057c4e8._2_1_,DAT_0057c4d8._2_1_);
        uVar5 = CONCAT22((short)DAT_0057c4d8,CONCAT11(DAT_0057c4f0._2_1_,DAT_0057c4e0._2_1_));
        uVar6 = CONCAT22((short)DAT_0057c4e8,*(undefined2 *)(DAT_0057d8d4 + uVar2 * 2));
        do {
          *(short *)(iVar9 + iVar3 * 2) = (short)uVar6;
          bVar10 = CARRY4(uVar5,DAT_0057c5b8);
          uVar5 = uVar5 + DAT_0057c5b8;
          uVar2 = (uint)CONCAT11((char)(uVar2 >> 8) + (char)(uVar5 >> 8) + CARRY4(uVar6,uVar8),
                                 (char)uVar2 + (char)uVar5 + bVar10);
          iVar4 = iVar3 + 1;
          uVar6 = CONCAT22((short)(uVar6 + uVar8 >> 0x10),*(undefined2 *)(iVar1 + uVar2 * 2));
          bVar10 = iVar3 < -1;
          iVar3 = iVar4;
        } while (iVar4 == 0 || bVar10);
      }
      DAT_0057c4a8 = DAT_0057c4a8 + DAT_0057c4ac;
      bVar10 = CARRY4(DAT_0057c594,DAT_0057c598);
      DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
      DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + (uint)bVar10 * -8);
      DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + (uint)bVar10 * -8);
      DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
      DAT_0057c518 = DAT_0057c518 + DAT_0057d864;
      iVar1 = DAT_0057c59c + -1;
      bVar10 = 0 < DAT_0057c59c;
      DAT_0057c59c = iVar1;
    } while (bVar10);
  }
  if (-1 < DAT_0057c5a0) {
    do {
      iVar1 = DAT_0057d8d4;
      uVar5 = DAT_0057c4b0 >> 0x10;
      iVar9 = DAT_0057c518 + uVar5 * 2;
      iVar3 = (DAT_0057c4a0 >> 0x10) - uVar5;
      if (iVar3 == 0 || DAT_0057c4a0 >> 0x10 < uVar5) {
        uVar2 = (uint)CONCAT11(DAT_0057c4e8._2_1_,DAT_0057c4d8._2_1_);
        uVar5 = CONCAT22((short)DAT_0057c4d8,CONCAT11(DAT_0057c4f0._2_1_,DAT_0057c4e0._2_1_));
        uVar6 = CONCAT22((short)DAT_0057c4e8,*(undefined2 *)(DAT_0057d8d4 + uVar2 * 2));
        do {
          *(short *)(iVar9 + iVar3 * 2) = (short)uVar6;
          bVar10 = CARRY4(uVar5,DAT_0057c5b8);
          uVar5 = uVar5 + DAT_0057c5b8;
          uVar2 = (uint)CONCAT11((char)(uVar2 >> 8) + (char)(uVar5 >> 8) + CARRY4(uVar6,uVar8),
                                 (char)uVar2 + (char)uVar5 + bVar10);
          iVar4 = iVar3 + 1;
          uVar6 = CONCAT22((short)(uVar6 + uVar8 >> 0x10),*(undefined2 *)(iVar1 + uVar2 * 2));
          bVar10 = iVar3 < -1;
          iVar3 = iVar4;
        } while (iVar4 == 0 || bVar10);
      }
      DAT_0057c4b0 = DAT_0057c4b0 + DAT_0057c4b4;
      bVar10 = CARRY4(DAT_0057c594,DAT_0057c598);
      DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
      DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + (uint)bVar10 * -8);
      DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + (uint)bVar10 * -8);
      DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
      DAT_0057c518 = DAT_0057c518 + DAT_0057d864;
      iVar1 = DAT_0057c5a0 + -1;
      bVar10 = 0 < DAT_0057c5a0;
      DAT_0057c5a0 = iVar1;
    } while (bVar10);
  }
  return;
}

