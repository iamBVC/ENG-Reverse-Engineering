/* Catch@004113fb @ 004113fb   98 bytes */

undefined1 * Catch_004113fb(void)

{
  char cVar1;
  int iVar2;
  undefined *puVar3;
  int unaff_EBP;
  
  sub_4114A0();
  iVar2 = (**(code **)**(undefined4 **)(unaff_EBP + -0x98))(unaff_EBP + -0xb4);
  puVar3 = *(undefined **)(iVar2 + 4);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  if (puVar3 == (undefined *)0x0) {
    puVar3 = &DAT_0056e1bc;
  }
  sub_426500(puVar3);
  iVar2 = *(int *)(unaff_EBP + -0xb0);
  if (iVar2 != 0) {
    cVar1 = *(char *)(iVar2 + -1);
    if ((cVar1 != '\0') && (cVar1 != -1)) {
      *(char *)(iVar2 + -1) = cVar1 + -1;
      return &LAB_0041145d;
    }
    sub_562941((char *)(iVar2 + -1));
  }
  return &LAB_0041145d;
}

