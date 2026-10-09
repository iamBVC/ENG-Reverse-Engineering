/* sub_56D0FA @ 0056d0fa   100 bytes */

undefined4 * sub_56D0FA(void)

{
  undefined1 *puVar1;
  undefined4 *extraout_ECX;
  int unaff_EBP;
  
  sub_56D674();
  *(undefined4 **)(unaff_EBP + -0x14) = extraout_ECX;
  *(undefined **)(unaff_EBP + -0x10) = &DAT_0057f834;
  sub_56D5C8(unaff_EBP + -0x10);
  puVar1 = *(undefined1 **)(unaff_EBP + 8);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  *(undefined1 *)(extraout_ECX + 3) = *puVar1;
  sub_413BF0(0);
  sub_414160(puVar1,0,DAT_0056e1e0);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  *extraout_ECX = &PTR_sub_56D1C5_0056ed68;
  return extraout_ECX;
}

