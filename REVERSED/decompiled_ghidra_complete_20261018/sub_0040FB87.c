/* Catch@0040fb87 @ 0040fb87   67 bytes */

undefined1 * Catch_0040fb87(void)

{
  int iVar1;
  undefined *puVar2;
  int unaff_EBP;
  
  iVar1 = (**(code **)**(undefined4 **)(unaff_EBP + -0x48))(unaff_EBP + -0x58);
  puVar2 = *(undefined **)(iVar1 + 4);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  if (puVar2 == (undefined *)0x0) {
    puVar2 = &DAT_0056e1bc;
  }
  sub_40FBE0(1,puVar2,0,0);
  *(undefined1 *)(unaff_EBP + -4) = 1;
  sub_413BF0(1);
  sub_40FC50();
  return &LAB_0040fbca;
}

