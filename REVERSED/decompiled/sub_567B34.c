/* sub_567B34 @ 00567b34   70 bytes */

void sub_567B34(void)

{
  int unaff_EBX;
  int unaff_EBP;
  int unaff_ESI;
  int *unaff_EDI;
  
  *(undefined4 *)(unaff_ESI + -4) = *(undefined4 *)(unaff_EBP + -0x28);
  DAT_006da420 = *(undefined4 *)(unaff_EBP + -0x1c);
  DAT_006da424 = *(undefined4 *)(unaff_EBP + -0x20);
  if ((((*unaff_EDI == -0x1f928c9d) && (unaff_EDI[4] == 3)) && (unaff_EDI[5] == 0x19930520)) &&
     ((*(int *)(unaff_EBP + -0x24) == unaff_EBX && (*(int *)(unaff_EBP + -0x2c) != unaff_EBX)))) {
    __abnormal_termination();
    sub_567D68();
  }
  return;
}

