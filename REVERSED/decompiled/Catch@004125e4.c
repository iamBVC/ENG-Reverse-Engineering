/* Catch@004125e4 @ 004125e4   82 bytes */

undefined4 Catch_004125e4(void)

{
  char cVar1;
  int iVar2;
  undefined *puVar3;
  int unaff_EBP;
  
  iVar2 = (**(code **)**(undefined4 **)(unaff_EBP + -0x24))(unaff_EBP + -0x34);
  puVar3 = *(undefined **)(iVar2 + 4);
  *(undefined1 *)(unaff_EBP + -4) = 4;
  if (puVar3 == (undefined *)0x0) {
    puVar3 = &DAT_0056e1bc;
  }
  sub_426500(puVar3);
  iVar2 = *(int *)(unaff_EBP + -0x30);
  if (iVar2 != 0) {
    cVar1 = *(char *)(iVar2 + -1);
    if ((cVar1 != '\0') && (cVar1 != -1)) {
      *(char *)(iVar2 + -1) = cVar1 + -1;
      return 0x4125cc;
    }
    sub_562941((char *)(iVar2 + -1));
  }
  return 0x4125cc;
}

