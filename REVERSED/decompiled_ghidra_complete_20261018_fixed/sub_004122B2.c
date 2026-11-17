/* Catch@004122b2 @ 004122b2   95 bytes */

undefined4 Catch_004122b2(void)

{
  int iVar1;
  undefined *puVar2;
  int unaff_EBP;
  
  iVar1 = *(int *)(unaff_EBP + -0x20);
  if (iVar1 != 0) {
    sub_413390();
    sub_562941(iVar1);
  }
  iVar1 = (**(code **)**(undefined4 **)(unaff_EBP + 0xc))(unaff_EBP + -0x50);
  puVar2 = *(undefined **)(iVar1 + 4);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  if (puVar2 == (undefined *)0x0) {
    puVar2 = &DAT_0056e1bc;
  }
  sub_426500(puVar2);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  sub_413BF0(1);
  sub_40FBE0(3,0,0,0);
  return 0x41229a;
}

