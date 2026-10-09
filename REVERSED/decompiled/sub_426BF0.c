/* sub_426BF0 @ 00426bf0   2997 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_426BF0(void)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  undefined4 uVar4;
  
  sub_4264B0(&DAT_00573410);
  sub_4264B0(&DAT_00573450);
  sub_4264B0(&DAT_00573610);
  sub_4264B0(&DAT_00573690);
  sub_4264B0(&DAT_00573710);
  sub_4264B0(&DAT_005736d0);
  sub_4264B0(&DAT_00573490);
  sub_4264B0(&DAT_005734d0);
  sub_4264B0(&DAT_00573510);
  sub_4264B0(&DAT_00573550);
  sub_4264B0(&DAT_00573590);
  sub_4264B0(&DAT_005735d0);
  sub_4264B0(&DAT_00573650);
  sub_4264B0(&DAT_00573750);
  sub_4264B0(&DAT_00573790);
  sub_426BB0();
  _DAT_00573650 = 0x7f;
  DAT_00573653 = 1;
  _DAT_00573610 = 0x7f;
  DAT_00573613 = 1;
  _DAT_00573690 = 0x7f;
  DAT_00573693 = 1;
  _DAT_00573710 = 0x7f;
  DAT_00573713 = 1;
  _DAT_005736d0 = 0x7f;
  DAT_005736d3 = 1;
  _DAT_00573790 = 0x7f;
  DAT_00573793 = 1;
  if (DAT_00585218 != '\0') {
    sub_426890();
  }
  if (DAT_006d94e8 != '\0') {
    return;
  }
  if (DAT_005fd090 != 0) {
    return;
  }
  if (DAT_005fd08c != 0) {
    return;
  }
  DAT_005fd0b4 = DAT_005fd0b4 + 1 & 0x1f;
  if ((DAT_005fcf74 != (uint)(&DAT_00584f1c)[DAT_00584ebc + DAT_00584eb8 * 6] >> 0xc) ||
     (DAT_00584640 != 0)) {
    DAT_005fd020 = 0x96;
    DAT_005fcf74 = (uint)(&DAT_00584f1c)[DAT_00584ebc + DAT_00584eb8 * 6] >> 0xc;
    sub_426500(0x10,DAT_00573664,DAT_00573668,0x28,0x20);
  }
  if (DAT_005fd020 == 0) {
    if (DAT_005fd054 != 0) {
      iVar2 = DAT_005fd054 * 4;
      DAT_005fd054 = DAT_005fd054 - 1;
      DAT_00573668 = *(int *)(&DAT_0057387c + iVar2) + -0x40;
    }
  }
  else {
    DAT_005fd020 = DAT_005fd020 + -1;
    if (DAT_005fd054 < 0x10) {
      DAT_00573668 = *(int *)(&DAT_00573880 + DAT_005fd054 * 4) + -0x40;
      DAT_005fd054 = DAT_005fd054 + 1;
    }
  }
  if ((-0x20 < DAT_00573668) &&
     ((((&DAT_00584f1c)[DAT_00584ebc + DAT_00584eb8 * 6] != 0 || (DAT_00584640 != 0)) &&
      ((DAT_006da2e0 & 0x4000) != 0)))) {
    uVar1 = (int)DAT_005fd0b4 >> 1 & 7;
    _DAT_0057365c = uVar1 + 10;
    DAT_00573664 = (byte)(&DAT_00573810)[uVar1] + 0x1b8;
    uVar1 = (uint)(&DAT_00584f1c)[DAT_00584ebc + DAT_00584eb8 * 6] >> 0xc;
    DAT_0057366d = DAT_005ff070 <= uVar1;
    sub_426740(0x1b8,DAT_00573668 + 0x12,uVar1,0x7f);
    if (DAT_00584640 != 0) {
      if (DAT_005ff070 < 100) {
        uVar4 = 0x58;
      }
      else {
        uVar4 = 0x59;
      }
      sub_425CB0(0x1b6,DAT_00573668 + 0x1e,uVar4,0x7f,1,1);
      sub_426740(0x1b8,DAT_00573668 + 0x22,DAT_005ff070,0x7f);
    }
    sub_425D40(&DAT_00573650,0);
  }
  if ((DAT_005fcf80 != DAT_00584ff4 >> 0xc) || (DAT_006da2dc != 0)) {
    DAT_005fd02c = 0x96;
    DAT_005fcf80 = DAT_00584ff4 >> 0xc;
    sub_426500(0x10,DAT_00573624,DAT_00573628,0x28,0x20);
  }
  if (DAT_005fd02c == 0) {
    if (DAT_005fd060 != 0) {
      iVar2 = DAT_005fd060 * 4;
      DAT_005fd060 = DAT_005fd060 - 1;
      DAT_00573628 = *(int *)(&DAT_0057387c + iVar2) + -0x40;
    }
  }
  else {
    DAT_005fd02c = DAT_005fd02c + -1;
    if (DAT_005fd060 < 0x10) {
      DAT_00573628 = *(int *)(&DAT_00573880 + DAT_005fd060 * 4) + -0x40;
      DAT_005fd060 = DAT_005fd060 + 1;
    }
  }
  if (((-0x20 < DAT_00573628) && (DAT_00584ff4 != 0)) && ((DAT_006da2e0 & 0x8000) != 0)) {
    uVar1 = (int)DAT_005fd0b4 >> 1;
    _DAT_0057361c = uVar1 + 0x13;
    DAT_00573624 = (byte)(&DAT_00573828)[uVar1 & 0xf] + 0x184;
    if ((DAT_00584ff4 & 0xfffff000) < 0x3e8000) {
      sub_426740(0x184,DAT_00573628 + 0x12,DAT_00584ff4 >> 0xc,0x7f);
    }
    else {
      sub_425CB0(0x17c,DAT_00573628,(uVar1 & 7) + 0x5a,0x7f,1,1);
    }
    sub_425D40(&DAT_00573610,0);
  }
  if (DAT_005fcf84 != DAT_00584e60 >> 0xc) {
    if (DAT_005fcf84 < DAT_00584e60 >> 0xc) {
      (&DAT_00584ec8)[DAT_00584eb8 * 6 + DAT_00584ebc] =
           (&DAT_00584ec8)[DAT_00584eb8 * 6 + DAT_00584ebc] | 1;
    }
    DAT_005fcf84 = DAT_00584e60 >> 0xc;
    DAT_005fd030 = 0x96;
    sub_426500(0x10,DAT_005736a4,DAT_005736a8,0x28,0x20);
  }
  if (DAT_005fd030 == 0) {
    if (DAT_005fd064 != 0) {
      DAT_005fd064 = DAT_005fd064 - 1;
      DAT_005736a8 = *(int *)(&DAT_00573880 + DAT_005fd064 * 4) + -0x40;
    }
  }
  else {
    DAT_005fd030 = DAT_005fd030 + -1;
    if (DAT_005fd064 < 0x10) {
      DAT_005736a8 = *(int *)(&DAT_00573880 + DAT_005fd064 * 4) + -0x40;
      DAT_005fd064 = DAT_005fd064 + 1;
    }
  }
  if ((((-0x20 < DAT_005736a8) && (DAT_00584e60 != 0)) && ((DAT_006da2e0 & 0x20000) != 0)) &&
     (((DAT_006d9e74 & 0x8000) == 0 || (DAT_00584640 != 0)))) {
    _DAT_0057369c = (byte)(&DAT_00573838)[(int)DAT_005fd0b4 >> 1 & 7] + 0x41;
    sub_426740(0x11c,DAT_005736a8 + 0x12,DAT_00584e60 >> 0xc,0x7f);
    sub_425D40(&DAT_00573690,0);
  }
  if (DAT_005fcf7c != DAT_00584ffc >> 0xc) {
    DAT_005fd028 = 0x96;
    DAT_005fcf7c = DAT_00584ffc >> 0xc;
    sub_426500(0x10,DAT_00573724,DAT_00573728,0x28,0x20);
  }
  if (DAT_005fd028 == 0) {
    if (DAT_005fd05c != 0) {
      iVar2 = DAT_005fd05c * 4;
      DAT_005fd05c = DAT_005fd05c - 1;
      DAT_00573728 = *(int *)(&DAT_0057387c + iVar2) + -0x40;
    }
  }
  else {
    DAT_005fd028 = DAT_005fd028 + -1;
    if (DAT_005fd05c < 0x10) {
      DAT_00573728 = *(int *)(&DAT_00573880 + DAT_005fd05c * 4) + -0x40;
      DAT_005fd05c = DAT_005fd05c + 1;
    }
  }
  if (((-0x20 < DAT_00573728) && ((DAT_00584ffc & 0xfffff000) != 0)) &&
     ((DAT_006da2e0 & 0x10000) != 0)) {
    if ((DAT_006d9e74 & 0x2000) == 0) {
      _DAT_0057371c = (int)DAT_005fd0b4 / 2 + 0x23;
    }
    else {
      _DAT_0057371c = (int)DAT_005fd0b4 / 2 + 0x5a;
    }
    DAT_00573724 = (byte)(&DAT_00573818)[(int)DAT_005fd0b4 >> 1 & 0xf] + 0x150;
    sub_426740(0x150,DAT_00573728 + 0x12,DAT_00584ffc >> 0xc,0x7f);
    sub_425D40(&DAT_00573710,0);
  }
  if ((0 < DAT_006da290) || ((DAT_006da2e0 & 0x40000) != 0)) {
    DAT_005fd038 = 0x96;
  }
  iVar2 = DAT_006da304 >> 0xc;
  if (DAT_005fcf8c == iVar2) {
    if (DAT_005fd038 != 0) goto LAB_004272ea;
    if (DAT_005fd06c != 0) {
      DAT_005fd06c = DAT_005fd06c - 1;
      DAT_005734a8 = *(int *)(&DAT_00573880 + DAT_005fd06c * 4) + -0x40;
    }
  }
  else {
    DAT_005fd038 = 0x96;
    DAT_005fcf8c = iVar2;
LAB_004272ea:
    DAT_005fd038 = DAT_005fd038 + -1;
    if (DAT_005fd06c < 0x10) {
      DAT_005734a8 = *(int *)(&DAT_00573880 + DAT_005fd06c * 4) + -0x40;
      DAT_005fd06c = DAT_005fd06c + 1;
    }
  }
  if (((-0x20 < DAT_005734a8) && (0 < DAT_006da304)) && ((DAT_006da2e0 & 0x2000) != 0)) {
    _DAT_005734e4 = 0xd5;
    _DAT_00573538 = 0xd5;
    _DAT_00573578 = iVar2 + 0x30;
    _DAT_005735b8 = (DAT_006da290 >> 0xc) + 0x30;
    _DAT_005735e4 = iVar2 + 0x2e;
    DAT_0057352d = 0;
    DAT_0057356d = 0;
    DAT_005735ad = 0;
    DAT_005735ed = 0;
    DAT_005734ad = 0;
    DAT_005734ed = 0;
    if ((DAT_006d9e74 & 0x80000) == 0) {
      if ((DAT_006d9e74 & 0x100000) == 0) {
        _DAT_0057355c = 3;
        _DAT_0057359c = 2;
      }
      else {
        _DAT_0057355c = 9;
        _DAT_0057359c = 8;
      }
    }
    else {
      _DAT_0057355c = 7;
      _DAT_0057359c = 6;
    }
    _DAT_005734e8 = DAT_005734a8;
    _DAT_00573528 = DAT_005734a8;
    _DAT_00573568 = DAT_005734a8;
    _DAT_005735a8 = DAT_005734a8;
    _DAT_005735e8 = DAT_005734a8;
    sub_425D40(&DAT_005735d0,0);
    sub_425D40(&DAT_00573590,0);
    sub_425D40(&DAT_00573550,0);
    sub_425D40(&DAT_00573510,0);
    sub_425D40(&DAT_00573490,0);
    sub_425D40(&DAT_005734d0,0);
  }
  if ((DAT_00584e70 < 0x5000) || (DAT_005fcf88 != DAT_00584e70)) {
    DAT_005fd034 = 0x96;
LAB_00427497:
    DAT_005fd034 = DAT_005fd034 + -1;
    if (DAT_005fd068 < 0x10) {
      DAT_00573428 = *(int *)(&DAT_00573880 + DAT_005fd068 * 4) + -0x40;
      DAT_005fd068 = DAT_005fd068 + 1;
    }
  }
  else {
    if (DAT_005fd034 != 0) goto LAB_00427497;
    if (DAT_005fd068 != 0) {
      iVar2 = DAT_005fd068 * 4;
      DAT_005fd068 = DAT_005fd068 - 1;
      DAT_00573428 = *(int *)(&DAT_0057387c + iVar2) + -0x40;
    }
  }
  if ((-0x20 < DAT_00573428) && ((DAT_006da2e0 & 0x1000) != 0)) {
    if (((DAT_005fcf88 == DAT_00584e70) && (DAT_0057341c == 0x33)) || (0x3a < DAT_0057341c)) {
LAB_00427570:
      if (DAT_0057341c != 0x37) {
        _DAT_00573468 = DAT_00573428;
        sub_425D40(&DAT_00573450,1);
      }
    }
    else {
      DAT_0057341c = DAT_0057341c + 1;
      if (DAT_0057341c != 0x37) {
        if (0x3a < DAT_0057341c) {
          DAT_0057341c = 0x33;
        }
        _DAT_00573464 =
             (*(int *)(DAT_0057341c * 4 + 0x573704) - (&DAT_00573724)[DAT_0057341c] / 2) + 0x100;
        _DAT_00573478 = (&DAT_00573724)[DAT_0057341c] + _DAT_00573464;
        goto LAB_00427570;
      }
      DAT_005fcf88 = DAT_00584e70;
      _DAT_0057345c = (DAT_00584e70 >> 0xc) + 0x3b;
    }
    sub_425D40(&DAT_00573410,1);
  }
  if (((DAT_006d9e74 & 0x1000) != 0) && (DAT_00584640 == 0)) {
    sub_436C60(s_Kuzco_0057394c,0x20,0x50);
    uVar1 = DAT_006da300 >> 0xc;
    if (uVar1 != 0) {
      iVar2 = (uVar1 - 1) * 0x10 + 0x58;
      do {
        sub_425CB0(0x20,iVar2,0x5a,0x7f,1,1);
        uVar1 = uVar1 - 1;
        iVar2 = iVar2 + -0x10;
      } while (uVar1 != 0);
    }
    sub_436C60(s_Kronk_00573944,0x1a8,0x50);
    uVar1 = DAT_006da2f8 >> 0xc;
    if (uVar1 != 0) {
      iVar2 = (uVar1 - 1) * 0x10 + 0x58;
      do {
        sub_425CB0(0x1c8,iVar2,0x5a,0x7f,1,1);
        uVar1 = uVar1 - 1;
        iVar2 = iVar2 + -0x10;
      } while (uVar1 != 0);
    }
  }
  if ((DAT_006d9e74 & 0x4000) == 0) goto LAB_00427704;
  uVar1 = DAT_006da300 >> 0xc;
  if (DAT_005fcf78 == uVar1) {
    if (DAT_005fd024 != 0) goto LAB_00427688;
    if (DAT_005736e8 < -0x1f) goto LAB_00427704;
    DAT_005736e8 = DAT_005736e8 + -1;
LAB_004276bc:
    if (DAT_005736e8 < -0x1f) goto LAB_00427704;
  }
  else {
    DAT_005fd024 = 0x96;
    DAT_005fcf78 = uVar1;
LAB_00427688:
    DAT_005fd024 = DAT_005fd024 + -1;
    bVar3 = false;
    if (DAT_005736e8 < 0) {
      DAT_005736e8 = DAT_005736e8 + 8;
      bVar3 = DAT_005736e8 < 0;
    }
    if (DAT_005736e8 == 0 || bVar3) goto LAB_004276bc;
    DAT_005736e8 = 0;
  }
  if ((DAT_006da300 != 0) && ((DAT_006da2e0 & 0x10000) != 0)) {
    _DAT_005736dc = ((int)DAT_005fd0b4 >> 1 & 0xfU) + 0x5a;
    sub_426740(0x150,DAT_005736e8 + 0x12,uVar1,0x7f);
    sub_425D40(&DAT_005736d0,0);
  }
LAB_00427704:
  if ((DAT_006d9e74 & 0x8000) == 0) {
    if (DAT_005fd074 != 0) {
      DAT_005fd074 = DAT_005fd074 - 1;
      DAT_005737a8 = *(int *)(&DAT_00573880 + DAT_005fd074 * 4) + -0x40;
    }
  }
  else if (DAT_005fd074 < 0x10) {
    DAT_005737a8 = *(int *)(&DAT_00573880 + DAT_005fd074 * 4) + -0x40;
    DAT_005fd074 = DAT_005fd074 + 1;
  }
  if ((-0x20 < DAT_005737a8) && (DAT_00584640 == 0)) {
    _DAT_0057379c = ((int)DAT_005fd0b4 >> 1 & 7U) + 0x45;
    sub_425D40(&DAT_00573790,1);
  }
  if ((DAT_006da2dc != 0) && (DAT_00584640 == 0)) {
    sub_425D40(&DAT_00573750,1);
  }
  return;
}

