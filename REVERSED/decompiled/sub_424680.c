/* sub_424680 @ 00424680   132 bytes */

void sub_424680(void)

{
  undefined *puVar1;
  uint uVar2;
  undefined **ppuVar3;
  
  sub_545F90(DAT_00584ea0,0x80);
  ppuVar3 = &PTR_DAT_00572ee4;
  do {
    if (((*(char *)(ppuVar3 + 2) == '\0') || (DAT_005833e0 != '\0')) &&
       ((*(char *)((int)ppuVar3 + 9) == '\0' || (DAT_005833e0 == '\0')))) {
      puVar1 = ppuVar3[-1];
      if (puVar1 == (undefined *)0x0) {
        uVar2 = *(uint *)*ppuVar3;
LAB_004246ea:
        sub_405870(ppuVar3[1],uVar2,0);
      }
      else if (puVar1 == (undefined *)0x1) {
        sub_405830(ppuVar3[1],*(undefined4 *)*ppuVar3,0);
      }
      else if (puVar1 == (undefined *)0x2) {
        uVar2 = (uint)(byte)**ppuVar3;
        goto LAB_004246ea;
      }
    }
    ppuVar3 = ppuVar3 + 4;
    if (0x573153 < (int)ppuVar3) {
      return;
    }
  } while( true );
}

