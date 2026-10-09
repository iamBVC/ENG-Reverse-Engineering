/* sub_56D2CC @ 0056d2cc   89 bytes */

void sub_56D2CC(void)

{
  size_t sVar1;
  int unaff_EBP;
  
  sub_56D674();
  *(undefined1 *)(unaff_EBP + -0x20) = *(undefined1 *)(unaff_EBP + -0xd);
  sub_413BF0(0);
  sVar1 = _strlen("invalid string position");
  sub_56D3B4("invalid string position",sVar1);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  sub_56D0FA(unaff_EBP + -0x20);
  *(undefined ***)(unaff_EBP + -0x3c) = &PTR_LAB_0056ed78;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(unaff_EBP + -0x3c,&DAT_0056f700);
}

