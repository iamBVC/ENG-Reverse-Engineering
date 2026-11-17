/* sub_40D890 @ 0040d890   50 bytes */

uint sub_40D890(char *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0;
  while( true ) {
    uVar3 = (uint)*param_1;
    iVar1 = sub_562E4E(uVar3);
    if (iVar1 == 0) break;
    uVar2 = uVar3 - 0x37;
    if (uVar3 < 0x3a) {
      uVar2 = uVar3 - 0x30;
    }
    uVar4 = uVar4 << 4 | uVar2;
    param_1 = param_1 + 1;
  }
  return uVar4;
}

