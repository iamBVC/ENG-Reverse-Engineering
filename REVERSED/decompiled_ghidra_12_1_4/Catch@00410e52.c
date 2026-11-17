/* Catch@00410e52 @ 00410e52   101 bytes */

undefined1 * Catch_00410e52(void)

{
  char cVar1;
  int iVar2;
  undefined *puVar3;
  int unaff_EBP;
  
  *(undefined1 *)(unaff_EBP + -4) = 2;
  sub_410ED0();
  iVar2 = sub_413B20(unaff_EBP + -0x154);
  puVar3 = *(undefined **)(iVar2 + 4);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  if (puVar3 == (undefined *)0x0) {
    puVar3 = &DAT_0056e1bc;
  }
  sub_426500(puVar3);
  iVar2 = *(int *)(unaff_EBP + -0x150);
  if (iVar2 != 0) {
    cVar1 = *(char *)(iVar2 + -1);
    if ((cVar1 != '\0') && (cVar1 != -1)) {
      *(char *)(iVar2 + -1) = cVar1 + -1;
      return &LAB_00410eb7;
    }
    sub_562941((char *)(iVar2 + -1));
  }
  return &LAB_00410eb7;
}

