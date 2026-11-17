/* sub_55F55C @ 0055f55c   3222 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_55F55C(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  
  DAT_0057c530 = param_3;
  DAT_0057c528 = param_1;
  DAT_0057c52c = param_2;
  sub_559A46();
  _DAT_0057c518 =
       (double)(((float)DAT_0057d850 - _DAT_0057c744) + _DAT_0057c748 +
               (float)DAT_0057d864 * ((float)DAT_0057c558 - _DAT_0057c740));
  _DAT_0057c520 =
       (double)(((float)_DAT_0057d8a8 - _DAT_0057c744) + _DAT_0057c748 +
               ((float)DAT_0057c558 - _DAT_0057c740) * (float)DAT_0057d8bc);
  DAT_0057c594 = DAT_0057c4a0 << 0x10;
  DAT_0057c598 = DAT_0057c4a4 << 0x10;
  if (DAT_0057c55c != 0) {
    if (DAT_0057c59c < 0) {
LAB_0055fef5:
      if (DAT_0057c5a0 < 0) {
        return;
      }
      DAT_0057c5c0 = DAT_0057c4e0 << 8 | DAT_0057c4f0 >> 0x10;
      DAT_0057c5c4 = (DAT_0057c4f0 & 0xfffe) << 0x10 | DAT_0057c4d0 >> 7;
      uVar6 = DAT_0057c4d8 << 8 | DAT_0057c4e8 >> 0x10;
      uVar1 = (DAT_0057c4e8 & 0xfffe) << 0x10 | DAT_0057c4c8 >> 7;
      uVar3 = DAT_0057c4b0 >> 0x10;
      DAT_0057c5bc = DAT_0057c520 + uVar3 * 2;
      DAT_0057c5b8 = DAT_0057c518 + uVar3 * 2;
      if (DAT_0057c4a0 >> 0x10 < uVar3) goto LAB_00560091;
      DAT_0057c560 = DAT_0057c4b8;
      uVar4 = DAT_0057c4b8 >> 0x10;
      DAT_0057c570 = DAT_0057c508;
      iVar2 = (DAT_0057c4a0 >> 0x10) - uVar3;
      do {
        do {
          if (uVar4 <= *(ushort *)(DAT_0057c5bc + iVar2 * 2)) {
            uVar5 = (uint)*(ushort *)(DAT_0057d8d4 + (uVar6 >> 0x18 | (uVar6 & 0xff) << 8) * 2);
            *(short *)(DAT_0057c5bc + iVar2 * 2) = (short)uVar4;
            uVar3 = (uint)*(ushort *)(DAT_0057c5b8 + iVar2 * 2);
            uVar3 = (DAT_0057c570 >> 0x13) * ((uVar3 & 0x3e0) << 0x10 | uVar3 & 0x3e07c1f) +
                    (uVar1 >> 0xc & 0x1f) * (uVar5 & 0x3e07c1f | (uVar5 & 0x3e0) << 0x10);
            *(ushort *)(DAT_0057c5b8 + iVar2 * 2) =
                 ((ushort)(uVar3 >> 0x10) & 0x7c0f) >> 5 | (ushort)((uVar3 & 0x7c0f83e0) >> 5);
          }
          bVar9 = uVar1 < DAT_0057c5c4;
          uVar1 = uVar1 - DAT_0057c5c4;
          uVar6 = (uVar6 - DAT_0057c5c0) - (uint)bVar9;
          DAT_0057c570 = DAT_0057c570 - DAT_0057c510;
          DAT_0057c560 = DAT_0057c560 - DAT_0057c4c0;
          uVar4 = DAT_0057c560 >> 0x10;
          bVar9 = 0 < iVar2;
          iVar2 = iVar2 + -1;
        } while (bVar9);
LAB_00560091:
        do {
          bVar9 = CARRY4(DAT_0057c594,DAT_0057c598);
          DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
          uVar1 = (uint)bVar9;
          DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
          DAT_0057c4b0 = DAT_0057c4b0 + DAT_0057c4b4;
          DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + uVar1 * -8);
          DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + uVar1 * -8);
          DAT_0057c4b8 = DAT_0057c4b8 + *(int *)(&DAT_0057c4c4 + uVar1 * -8);
          DAT_0057c4c8 = DAT_0057c4c8 + *(int *)(&DAT_0057c4d4 + uVar1 * -8);
          iVar8 = DAT_0057c520 + DAT_0057d8bc;
          iVar2 = DAT_0057c518 + DAT_0057d864;
          _DAT_0057c520 = (double)CONCAT44(DAT_0057c520_4,iVar8);
          _DAT_0057c518 = (double)CONCAT44(DAT_0057c518_4,iVar2);
          DAT_0057c570 = DAT_0057c508 + *(int *)(&DAT_0057c514 + uVar1 * -8);
          iVar7 = DAT_0057c5a0 + -1;
          if (DAT_0057c5a0 < 1) {
            DAT_0057c508 = DAT_0057c570;
            DAT_0057c560 = DAT_0057c4b8;
            DAT_0057c5a0 = iVar7;
            return;
          }
          uVar6 = DAT_0057c4d8 * 0x100 | DAT_0057c4e8 >> 0x10;
          uVar1 = (DAT_0057c4e8 & 0xfffe) << 0x10 | DAT_0057c4c8 >> 7;
          uVar3 = DAT_0057c4b0 >> 0x10;
          DAT_0057c5b8 = iVar2 + uVar3 * 2;
          iVar2 = (DAT_0057c4a0 >> 0x10) - uVar3;
          DAT_0057c508 = DAT_0057c570;
          DAT_0057c5a0 = iVar7;
        } while (DAT_0057c4a0 >> 0x10 < uVar3);
        uVar4 = DAT_0057c4b8 >> 0x10;
        DAT_0057c560 = DAT_0057c4b8;
        DAT_0057c5bc = iVar8 + uVar3 * 2;
      } while( true );
    }
    DAT_0057c5c0 = DAT_0057c4e0 << 8 | DAT_0057c4f0 >> 0x10;
    DAT_0057c5c4 = (DAT_0057c4f0 & 0xfffe) << 0x10 | DAT_0057c4d0 >> 7;
    uVar6 = DAT_0057c4d8 << 8 | DAT_0057c4e8 >> 0x10;
    uVar1 = (DAT_0057c4e8 & 0xfffe) << 0x10 | DAT_0057c4c8 >> 7;
    uVar3 = DAT_0057c4a8 >> 0x10;
    DAT_0057c5bc = DAT_0057c520 + uVar3 * 2;
    DAT_0057c5b8 = DAT_0057c518 + uVar3 * 2;
    if (DAT_0057c4a0 >> 0x10 < uVar3) goto LAB_0055fd99;
    DAT_0057c560 = DAT_0057c4b8;
    uVar4 = DAT_0057c4b8 >> 0x10;
    DAT_0057c570 = DAT_0057c508;
    iVar2 = (DAT_0057c4a0 >> 0x10) - uVar3;
    do {
      do {
        if (uVar4 <= *(ushort *)(DAT_0057c5bc + iVar2 * 2)) {
          uVar5 = (uint)*(ushort *)(DAT_0057d8d4 + (uVar6 >> 0x18 | (uVar6 & 0xff) << 8) * 2);
          *(short *)(DAT_0057c5bc + iVar2 * 2) = (short)uVar4;
          uVar3 = (uint)*(ushort *)(DAT_0057c5b8 + iVar2 * 2);
          uVar3 = (DAT_0057c570 >> 0x13) * ((uVar3 & 0x3e0) << 0x10 | uVar3 & 0x3e07c1f) +
                  (uVar1 >> 0xc & 0x1f) * (uVar5 & 0x3e07c1f | (uVar5 & 0x3e0) << 0x10);
          *(ushort *)(DAT_0057c5b8 + iVar2 * 2) =
               ((ushort)(uVar3 >> 0x10) & 0x7c0f) >> 5 | (ushort)((uVar3 & 0x7c0f83e0) >> 5);
        }
        bVar9 = uVar1 < DAT_0057c5c4;
        uVar1 = uVar1 - DAT_0057c5c4;
        uVar6 = (uVar6 - DAT_0057c5c0) - (uint)bVar9;
        DAT_0057c570 = DAT_0057c570 - DAT_0057c510;
        DAT_0057c560 = DAT_0057c560 - DAT_0057c4c0;
        uVar4 = DAT_0057c560 >> 0x10;
        bVar9 = 0 < iVar2;
        iVar2 = iVar2 + -1;
      } while (bVar9);
LAB_0055fd99:
      do {
        bVar9 = CARRY4(DAT_0057c594,DAT_0057c598);
        DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
        uVar1 = (uint)bVar9;
        DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
        DAT_0057c4a8 = DAT_0057c4a8 + DAT_0057c4ac;
        DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + uVar1 * -8);
        DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + uVar1 * -8);
        DAT_0057c4b8 = DAT_0057c4b8 + *(int *)(&DAT_0057c4c4 + uVar1 * -8);
        DAT_0057c4c8 = DAT_0057c4c8 + *(int *)(&DAT_0057c4d4 + uVar1 * -8);
        iVar7 = DAT_0057c520 + DAT_0057d8bc;
        iVar8 = DAT_0057c518 + DAT_0057d864;
        _DAT_0057c520 = (double)CONCAT44(DAT_0057c520_4,iVar7);
        _DAT_0057c518 = (double)CONCAT44(DAT_0057c518_4,iVar8);
        DAT_0057c570 = DAT_0057c508 + *(int *)(&DAT_0057c514 + uVar1 * -8);
        iVar2 = DAT_0057c59c + -1;
        bVar9 = DAT_0057c59c < 1;
        DAT_0057c508 = DAT_0057c570;
        DAT_0057c560 = DAT_0057c4b8;
        DAT_0057c59c = iVar2;
        if (bVar9) goto LAB_0055fef5;
        uVar6 = DAT_0057c4d8 * 0x100 | DAT_0057c4e8 >> 0x10;
        uVar1 = (DAT_0057c4e8 & 0xfffe) << 0x10 | DAT_0057c4c8 >> 7;
        uVar3 = DAT_0057c4a8 >> 0x10;
        DAT_0057c5b8 = iVar8 + uVar3 * 2;
        iVar2 = (DAT_0057c4a0 >> 0x10) - uVar3;
      } while (DAT_0057c4a0 >> 0x10 < uVar3);
      uVar4 = DAT_0057c4b8 >> 0x10;
      DAT_0057c5bc = iVar7 + uVar3 * 2;
    } while( true );
  }
  if (DAT_0057c59c < 0) {
LAB_0055f900:
    if (DAT_0057c5a0 < 0) {
      return;
    }
    DAT_0057c5c0 = DAT_0057c4e0 << 8 | DAT_0057c4f0 >> 0x10;
    DAT_0057c5c4 = (DAT_0057c4f0 & 0xfffe) << 0x10 | DAT_0057c4d0 >> 7;
    uVar6 = DAT_0057c4d8 << 8 | DAT_0057c4e8 >> 0x10;
    uVar1 = (DAT_0057c4e8 & 0xfffe) << 0x10 | DAT_0057c4c8 >> 7;
    uVar3 = DAT_0057c4b0 >> 0x10;
    DAT_0057c5bc = DAT_0057c520 + uVar3 * 2;
    DAT_0057c5b8 = DAT_0057c518 + uVar3 * 2;
    iVar2 = (DAT_0057c4a0 >> 0x10) - uVar3;
    if (iVar2 != 0 && uVar3 <= DAT_0057c4a0 >> 0x10) goto LAB_0055fa9c;
    DAT_0057c560 = DAT_0057c4b8;
    uVar3 = DAT_0057c4b8 >> 0x10;
    DAT_0057c570 = DAT_0057c508;
    do {
      do {
        if (uVar3 <= *(ushort *)(DAT_0057c5bc + iVar2 * 2)) {
          uVar4 = (uint)*(ushort *)(DAT_0057d8d4 + (uVar6 >> 0x18 | (uVar6 & 0xff) << 8) * 2);
          *(short *)(DAT_0057c5bc + iVar2 * 2) = (short)uVar3;
          uVar3 = (uint)*(ushort *)(DAT_0057c5b8 + iVar2 * 2);
          uVar3 = (DAT_0057c570 >> 0x13) * ((uVar3 & 0x3e0) << 0x10 | uVar3 & 0x3e07c1f) +
                  (uVar1 >> 0xc & 0x1f) * (uVar4 & 0x3e07c1f | (uVar4 & 0x3e0) << 0x10);
          *(ushort *)(DAT_0057c5b8 + iVar2 * 2) =
               ((ushort)(uVar3 >> 0x10) & 0x7c0f) >> 5 | (ushort)((uVar3 & 0x7c0f83e0) >> 5);
        }
        bVar9 = CARRY4(uVar1,DAT_0057c5c4);
        uVar1 = uVar1 + DAT_0057c5c4;
        uVar6 = uVar6 + DAT_0057c5c0 + (uint)bVar9;
        DAT_0057c570 = DAT_0057c570 + DAT_0057c510;
        DAT_0057c560 = DAT_0057c560 + DAT_0057c4c0;
        uVar3 = DAT_0057c560 >> 0x10;
        iVar7 = iVar2 + 1;
        bVar9 = iVar2 < -1;
        iVar2 = iVar7;
      } while (iVar7 == 0 || bVar9);
LAB_0055fa9c:
      do {
        bVar9 = CARRY4(DAT_0057c594,DAT_0057c598);
        DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
        uVar1 = (uint)bVar9;
        DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
        DAT_0057c4b0 = DAT_0057c4b0 + DAT_0057c4b4;
        DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + uVar1 * -8);
        DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + uVar1 * -8);
        DAT_0057c4b8 = DAT_0057c4b8 + *(int *)(&DAT_0057c4c4 + uVar1 * -8);
        DAT_0057c4c8 = DAT_0057c4c8 + *(int *)(&DAT_0057c4d4 + uVar1 * -8);
        iVar8 = DAT_0057c520 + DAT_0057d8bc;
        iVar2 = DAT_0057c518 + DAT_0057d864;
        _DAT_0057c520 = (double)CONCAT44(DAT_0057c520_4,iVar8);
        _DAT_0057c518 = (double)CONCAT44(DAT_0057c518_4,iVar2);
        DAT_0057c570 = DAT_0057c508 + *(int *)(&DAT_0057c514 + uVar1 * -8);
        iVar7 = DAT_0057c5a0 + -1;
        if (DAT_0057c5a0 < 1) {
          DAT_0057c508 = DAT_0057c570;
          DAT_0057c560 = DAT_0057c4b8;
          DAT_0057c5a0 = iVar7;
          return;
        }
        uVar6 = DAT_0057c4d8 * 0x100 | DAT_0057c4e8 >> 0x10;
        uVar1 = (DAT_0057c4e8 & 0xfffe) << 0x10 | DAT_0057c4c8 >> 7;
        uVar4 = DAT_0057c4b0 >> 0x10;
        DAT_0057c5b8 = iVar2 + uVar4 * 2;
        iVar2 = (DAT_0057c4a0 >> 0x10) - uVar4;
        DAT_0057c508 = DAT_0057c570;
        DAT_0057c5a0 = iVar7;
      } while (iVar2 != 0 && uVar4 <= DAT_0057c4a0 >> 0x10);
      uVar3 = DAT_0057c4b8 >> 0x10;
      DAT_0057c560 = DAT_0057c4b8;
      DAT_0057c5bc = iVar8 + uVar4 * 2;
    } while( true );
  }
  DAT_0057c5c0 = DAT_0057c4e0 << 8 | DAT_0057c4f0 >> 0x10;
  DAT_0057c5c4 = (DAT_0057c4f0 & 0xfffe) << 0x10 | DAT_0057c4d0 >> 7;
  uVar6 = DAT_0057c4d8 << 8 | DAT_0057c4e8 >> 0x10;
  uVar1 = (DAT_0057c4e8 & 0xfffe) << 0x10 | DAT_0057c4c8 >> 7;
  uVar3 = DAT_0057c4a8 >> 0x10;
  DAT_0057c5bc = DAT_0057c520 + uVar3 * 2;
  DAT_0057c5b8 = DAT_0057c518 + uVar3 * 2;
  iVar2 = (DAT_0057c4a0 >> 0x10) - uVar3;
  if (iVar2 != 0 && uVar3 <= DAT_0057c4a0 >> 0x10) goto LAB_0055f7a4;
  DAT_0057c560 = DAT_0057c4b8;
  uVar3 = DAT_0057c4b8 >> 0x10;
  DAT_0057c570 = DAT_0057c508;
  do {
    do {
      if (uVar3 <= *(ushort *)(DAT_0057c5bc + iVar2 * 2)) {
        uVar4 = (uint)*(ushort *)(DAT_0057d8d4 + (uVar6 >> 0x18 | (uVar6 & 0xff) << 8) * 2);
        *(short *)(DAT_0057c5bc + iVar2 * 2) = (short)uVar3;
        uVar3 = (uint)*(ushort *)(DAT_0057c5b8 + iVar2 * 2);
        uVar3 = (DAT_0057c570 >> 0x13) * ((uVar3 & 0x3e0) << 0x10 | uVar3 & 0x3e07c1f) +
                (uVar1 >> 0xc & 0x1f) * (uVar4 & 0x3e07c1f | (uVar4 & 0x3e0) << 0x10);
        *(ushort *)(DAT_0057c5b8 + iVar2 * 2) =
             ((ushort)(uVar3 >> 0x10) & 0x7c0f) >> 5 | (ushort)((uVar3 & 0x7c0f83e0) >> 5);
      }
      bVar9 = CARRY4(uVar1,DAT_0057c5c4);
      uVar1 = uVar1 + DAT_0057c5c4;
      uVar6 = uVar6 + DAT_0057c5c0 + (uint)bVar9;
      DAT_0057c570 = DAT_0057c570 + DAT_0057c510;
      DAT_0057c560 = DAT_0057c560 + DAT_0057c4c0;
      uVar3 = DAT_0057c560 >> 0x10;
      iVar7 = iVar2 + 1;
      bVar9 = iVar2 < -1;
      iVar2 = iVar7;
    } while (iVar7 == 0 || bVar9);
LAB_0055f7a4:
    do {
      bVar9 = CARRY4(DAT_0057c594,DAT_0057c598);
      DAT_0057c594 = DAT_0057c594 + DAT_0057c598;
      uVar1 = (uint)bVar9;
      DAT_0057c4a0 = DAT_0057c4a0 + DAT_0057c4a4;
      DAT_0057c4a8 = DAT_0057c4a8 + DAT_0057c4ac;
      DAT_0057c4d8 = DAT_0057c4d8 + *(int *)(&DAT_0057c4e4 + uVar1 * -8);
      DAT_0057c4e8 = DAT_0057c4e8 + *(int *)(&DAT_0057c4f4 + uVar1 * -8);
      DAT_0057c4b8 = DAT_0057c4b8 + *(int *)(&DAT_0057c4c4 + uVar1 * -8);
      DAT_0057c4c8 = DAT_0057c4c8 + *(int *)(&DAT_0057c4d4 + uVar1 * -8);
      iVar7 = DAT_0057c520 + DAT_0057d8bc;
      iVar8 = DAT_0057c518 + DAT_0057d864;
      _DAT_0057c520 = (double)CONCAT44(DAT_0057c520_4,iVar7);
      _DAT_0057c518 = (double)CONCAT44(DAT_0057c518_4,iVar8);
      DAT_0057c570 = DAT_0057c508 + *(int *)(&DAT_0057c514 + uVar1 * -8);
      iVar2 = DAT_0057c59c + -1;
      bVar9 = DAT_0057c59c < 1;
      DAT_0057c508 = DAT_0057c570;
      DAT_0057c560 = DAT_0057c4b8;
      DAT_0057c59c = iVar2;
      if (bVar9) goto LAB_0055f900;
      uVar6 = DAT_0057c4d8 * 0x100 | DAT_0057c4e8 >> 0x10;
      uVar1 = (DAT_0057c4e8 & 0xfffe) << 0x10 | DAT_0057c4c8 >> 7;
      uVar4 = DAT_0057c4a8 >> 0x10;
      DAT_0057c5b8 = iVar8 + uVar4 * 2;
      iVar2 = (DAT_0057c4a0 >> 0x10) - uVar4;
    } while (iVar2 != 0 && uVar4 <= DAT_0057c4a0 >> 0x10);
    uVar3 = DAT_0057c4b8 >> 0x10;
    DAT_0057c5bc = iVar7 + uVar4 * 2;
  } while( true );
}

