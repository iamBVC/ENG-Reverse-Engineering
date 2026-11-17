/* Catch@0041063a @ 0041063a   100 bytes */

undefined1 * Catch_0041063a(void)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined *puVar4;
  int unaff_EBP;
  
  sub_4106C0();
  piVar2 = *(int **)(unaff_EBP + -0x14);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 8))(piVar2);
  }
  iVar3 = (**(code **)**(undefined4 **)(unaff_EBP + -0x18))(unaff_EBP + -0x4c);
  puVar4 = *(undefined **)(iVar3 + 4);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  if (puVar4 == (undefined *)0x0) {
    puVar4 = &DAT_0056e1bc;
  }
  sub_426500(puVar4);
  iVar3 = *(int *)(unaff_EBP + -0x48);
  if (iVar3 != 0) {
    cVar1 = *(char *)(iVar3 + -1);
    if ((cVar1 != '\0') && (cVar1 != -1)) {
      *(char *)(iVar3 + -1) = cVar1 + -1;
      return &LAB_0041069e;
    }
    sub_562941((char *)(iVar3 + -1));
  }
  return &LAB_0041069e;
}

