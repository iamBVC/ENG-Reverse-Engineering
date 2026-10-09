/* sub_562640 @ 00562640   109 bytes */

void sub_562640(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = sub_5645F3(DAT_006db930);
  if (uVar1 < (uint)((int)DAT_006db92c + (4 - DAT_006db930))) {
    iVar2 = sub_5645F3(DAT_006db930);
    iVar2 = sub_5644D3(DAT_006db930,iVar2 + 0x10);
    if (iVar2 == 0) {
      return;
    }
    DAT_006db92c = (undefined4 *)(iVar2 + ((int)DAT_006db92c - DAT_006db930 >> 2) * 4);
    DAT_006db930 = iVar2;
  }
  *DAT_006db92c = param_1;
  DAT_006db92c = DAT_006db92c + 1;
  return;
}

