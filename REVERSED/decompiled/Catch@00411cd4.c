/* Catch@00411cd4 @ 00411cd4   140 bytes */

undefined4 Catch_00411cd4(void)

{
  int *piVar1;
  int iVar2;
  undefined *puVar3;
  int unaff_EBP;
  
  piVar1 = *(int **)(unaff_EBP + -0x24);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  piVar1 = *(int **)(unaff_EBP + -0x28);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  piVar1 = *(int **)(unaff_EBP + -0x18);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  iVar2 = *(int *)(unaff_EBP + -0x1c);
  if (iVar2 != 0) {
    sub_413170();
    sub_562941(iVar2);
  }
  iVar2 = (**(code **)**(undefined4 **)(unaff_EBP + -0x80))(unaff_EBP + -0x90);
  puVar3 = *(undefined **)(iVar2 + 4);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  if (puVar3 == (undefined *)0x0) {
    puVar3 = &DAT_0056e1bc;
  }
  sub_426500(puVar3);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  sub_413BF0(1);
  sub_40FBE0(3,0,0,0);
  return 0x411cbc;
}

