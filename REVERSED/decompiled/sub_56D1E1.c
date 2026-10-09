/* sub_56D1E1 @ 0056d1e1   93 bytes */

undefined4 * sub_56D1E1(void)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 *extraout_ECX;
  int unaff_EBP;
  
  sub_56D674();
  iVar2 = *(int *)(unaff_EBP + 8);
  *(undefined4 **)(unaff_EBP + -0x10) = extraout_ECX;
  sub_56D605(iVar2);
  uVar1 = *(undefined1 *)(iVar2 + 0xc);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  *(undefined1 *)(extraout_ECX + 3) = uVar1;
  sub_413BF0(0);
  sub_414160(iVar2 + 0xc,0,DAT_0056e1e0);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  *extraout_ECX = &PTR_sub_56D1C5_0056ed68;
  return extraout_ECX;
}

