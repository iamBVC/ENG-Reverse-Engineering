/* sub_56D0A0 @ 0056d0a0   89 bytes */

void sub_56D0A0(void)

{
  size_t sVar1;
  int unaff_EBP;
  
  sub_56D674();
  *(undefined1 *)(unaff_EBP + -0x20) = *(undefined1 *)(unaff_EBP + -0xd);
  sub_413BF0(0);
  sVar1 = _strlen("string too long");
  sub_56D3B4("string too long",sVar1);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  sub_56D0FA(unaff_EBP + -0x20);
  *(undefined ***)(unaff_EBP + -0x3c) = &PTR_LAB_0056ed48;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(unaff_EBP + -0x3c,&DAT_0056f5d8);
}

