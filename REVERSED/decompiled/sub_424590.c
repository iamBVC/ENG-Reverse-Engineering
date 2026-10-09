/* sub_424590 @ 00424590   227 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_424590(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined **ppuVar3;
  float10 fVar4;
  
  ppuVar3 = &PTR_DAT_00572ee4;
  do {
    if (((*(char *)(ppuVar3 + 2) == '\0') || (DAT_005833e0 != '\0')) &&
       ((*(char *)((int)ppuVar3 + 9) == '\0' || (DAT_005833e0 == '\0')))) {
      puVar1 = ppuVar3[-1];
      if (puVar1 == (undefined *)0x0) {
        sub_4057C0(ppuVar3[1],(float)*(int *)*ppuVar3,0);
        uVar2 = __ftol();
        *(undefined4 *)*ppuVar3 = uVar2;
      }
      else if (puVar1 == (undefined *)0x1) {
        fVar4 = (float10)sub_4057C0(ppuVar3[1],*(undefined4 *)*ppuVar3,0);
        *(float *)*ppuVar3 = (float)fVar4;
      }
      else if (puVar1 == (undefined *)0x2) {
        fVar4 = (float10)sub_4057C0(ppuVar3[1],(float)(byte)**ppuVar3,0);
        if (fVar4 == (float10)_DAT_0056e00c) {
          **ppuVar3 = 0;
        }
        else {
          **ppuVar3 = 1;
        }
      }
    }
    ppuVar3 = ppuVar3 + 4;
  } while ((int)ppuVar3 < 0x573154);
  return;
}

