/* sub_56814E @ 0056814e   114 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined5 __fastcall sub_56814E(undefined4 param_1,undefined1 param_2)

{
  undefined4 uVar1;
  undefined4 in_EAX;
  undefined1 extraout_DL;
  int unaff_EBP;
  float10 in_ST0;
  float10 fVar2;
  float10 fVar3;
  undefined4 unaff_retaddr;
  
  fVar2 = ABS(in_ST0);
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)(_DAT_0057ccee < fVar2) << 8 | (ushort)(NAN(_DAT_0057ccee) || NAN(fVar2)) << 10 |
       (ushort)(_DAT_0057ccee == fVar2) << 0xe;
  if ((*(byte *)(unaff_EBP + -0x9f) & 0x41) == 0) {
    fVar3 = ROUND(in_ST0);
    fVar2 = (float10)0;
    *(ushort *)(unaff_EBP + -0xa0) =
         (ushort)(fVar3 < fVar2) << 8 | (ushort)(NAN(fVar3) || NAN(fVar2)) << 10 |
         (ushort)(fVar3 == fVar2) << 0xe;
    fVar3 = in_ST0 - fVar3;
    fVar2 = (float10)0;
    *(ushort *)(unaff_EBP + -0xa0) =
         (ushort)(fVar3 < fVar2) << 8 | (ushort)(NAN(fVar3) || NAN(fVar2)) << 10 |
         (ushort)(fVar3 == fVar2) << 0xe;
    f2xm1(ABS(fVar3));
    return CONCAT14(*(undefined1 *)(unaff_EBP + -0x9f),in_EAX);
  }
  fVar2 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)(in_ST0 < fVar2) << 8 | (ushort)(NAN(in_ST0) || NAN(fVar2)) << 10 |
       (ushort)(in_ST0 == fVar2) << 0xe;
  if ((*(byte *)(unaff_EBP + -0x9f) & 1) == 0) {
    return CONCAT14(param_2,unaff_retaddr);
  }
  *(undefined1 *)(unaff_EBP + -0x90) = 4;
  uVar1 = sub_568306();
  return CONCAT14(extraout_DL,uVar1);
}

