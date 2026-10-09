/* sub_418C10 @ 00418c10   182 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_418C10(void)

{
  int iVar1;
  
  iVar1 = DAT_00582260;
  if (*(int *)(DAT_00582260 + 0x70) != 0) {
    sub_40E610(*(undefined4 *)(*(int *)(DAT_00582260 + 0x70) + 0x1c),&DAT_00583a70);
    _DAT_005841b0 = &DAT_00583a70;
    sub_40E610(*(undefined4 *)(*(int *)(iVar1 + 0x70) + 0x30),&DAT_00583850);
    _DAT_005841e0 = &DAT_00583850;
    sub_40E610(*(undefined4 *)(*(int *)(iVar1 + 0x70) + 0x18),&DAT_00583918);
    _DAT_00584210 = &DAT_00583918;
    sub_40E610(*(undefined4 *)(*(int *)(iVar1 + 0x70) + 0x20),&DAT_00583ab0);
    _DAT_00584240 = &DAT_00583ab0;
    sub_40E610(*(undefined4 *)(*(int *)(iVar1 + 0x70) + 0x10),&DAT_005838d0);
    _DAT_00584270 = &DAT_005838d0;
    sub_40E610(*(undefined4 *)(*(int *)(iVar1 + 0x70) + 0x14),&DAT_00583b30);
    _DAT_005842a0 = &DAT_00583b30;
  }
  return;
}

