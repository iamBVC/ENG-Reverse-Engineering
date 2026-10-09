/* sub_41A5E0 @ 0041a5e0   783 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall sub_41A5E0(undefined4 param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  
  DAT_005848d8 = DAT_005848d8 + 1;
  switch(DAT_005846e4) {
  case 2:
    if (DAT_0058470c == 0) {
      sub_426500(DAT_00584958,0);
    }
    else {
      sub_436A50((&PTR_s_Sei_sicuro_che_vuoi_0057bbc4)[DAT_00584f04],0x78);
      sub_436A50((&PTR_s_uscire__0057bbcc)[DAT_00584f04],0x8c);
      sub_4368D0((&PTR_DAT_0057bba8)[DAT_00584f04],0xa0,2,DAT_0058470c,1,0x100);
      sub_4368D0((&PTR_DAT_0057bba4)[DAT_00584f04],0xa0,1,DAT_0058470c,0,0x120);
      sub_4146B0(0x78);
    }
    break;
  case 3:
  case 5:
  case 6:
    break;
  case 4:
    if ((DAT_005848d8 & 0x10) != 0) {
      sub_436A50((&PTR_DAT_0057bbdc)[DAT_00584f04],200);
    }
    break;
  case 7:
    sub_405C50();
    return;
  default:
    goto switchD_0041a607_caseD_8;
  case 0xc:
    sub_41B140();
    return;
  case 0x13:
    sub_41AAF0(param_1);
    return;
  }
  sub_41A480();
  sub_408320();
  if ((DAT_005865cc == 1) && (DAT_006d9e1c != 0)) {
    if (DAT_00581164 == 0) {
      DAT_00581164 = sub_41B8A0(2,0x3f800000,0x3f800000,0x3f800000,0,0,0,
                                (float)_DAT_005865c8 * (float)_DAT_0056e020,
                                (float)DAT_0058658c * (float)_DAT_0056e020,0);
      sub_41BD70(DAT_00581164);
    }
    *(float *)(DAT_00581164 + 0x20) = (float)*(int *)(DAT_006d9e1c + 0x30) * (float)_DAT_0056e020;
    *(float *)(DAT_00581164 + 0x24) =
         (float)(*(int *)(DAT_006d9e1c + 0x34) +
                ((int)(DAT_0058658c + (DAT_0058658c >> 0x1f & 3U)) >> 2)) * (float)_DAT_0056e020;
    *(float *)(DAT_00581164 + 0x28) = -((float)*(int *)(DAT_006d9e1c + 0x38) * (float)_DAT_0056e020)
    ;
    iVar3 = DAT_00581164;
    fVar2 = (float)DAT_0058658c * (float)_DAT_0056e020;
    fVar1 = (float)_DAT_005865c8 * (float)_DAT_0056e020;
    *(float *)(DAT_00581164 + 0x5c) = fVar1;
    *(float *)(iVar3 + 0x58) = fVar2;
    *(float *)(iVar3 + 0x54) = fVar1 * fVar1;
    *(float *)(iVar3 + 0x50) = fVar2 * fVar2;
    if (fVar2 - fVar1 != _DAT_0056e00c) {
      *(float *)(iVar3 + 0x60) = _DAT_0056e008 / (fVar2 - fVar1);
    }
  }
  sub_40DB70();
  if (DAT_0057f8bc != 0) {
    DAT_005790b0 = *(undefined4 *)(DAT_0057f854 + 0x18);
    DAT_005790b4 = *(undefined4 *)(DAT_0057f854 + 0x1c);
    DAT_005790b8 = *(undefined4 *)(DAT_0057f854 + 0x20);
    DAT_006d9d80 = *(undefined4 *)(DAT_0057f854 + 8);
    DAT_006d9d84 = *(undefined4 *)(DAT_0057f854 + 0xc);
    DAT_006d9d88 = *(undefined4 *)(DAT_0057f854 + 0x10);
  }
  sub_41A920(&DAT_005790a0,&DAT_006d9d70,0x800);
  sub_401780(DAT_00584644,&DAT_005790a0);
  if (DAT_0057f8bc != 0) {
    sub_4060C0();
  }
  sub_42BF40(DAT_00584648,DAT_005846ec);
  sub_555140();
  sub_436190();
  sub_42C8C0();
  uVar4 = sub_563C89();
  if (((uVar4 & 1) != 0) && (DAT_00584640 == 0)) {
    DAT_005865d4 = DAT_005865d4 + 1 & 3;
    return;
  }
switchD_0041a607_caseD_8:
  return;
}

