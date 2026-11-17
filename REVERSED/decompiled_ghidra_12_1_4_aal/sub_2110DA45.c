/* sub_2110DA45 @ 2110da45   90 bytes */

void __thiscall sub_2110DA45(void *this,char *param_1)

{
  char cVar1;
  char cVar2;
  undefined *this_00;
  uint uVar3;
  undefined *puVar4;
  
  this_00 = (undefined *)(int)*param_1;
  uVar3 = sub_2110F202(this,(uint)this_00);
  if (uVar3 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if (DAT_21114ecc < 2) {
        uVar3 = (byte)PTR_DAT_21114ed8[*param_1 * 2] & 4;
        this_00 = PTR_DAT_21114ed8;
      }
      else {
        puVar4 = (undefined *)0x4;
        uVar3 = sub_2110F18D(this_00,(int)*param_1,4);
        this_00 = puVar4;
      }
    } while (uVar3 != 0);
  }
  cVar2 = *param_1;
  *param_1 = DAT_21114ed0;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = cVar2;
    cVar2 = cVar1;
  } while (*param_1 != '\0');
  return;
}

