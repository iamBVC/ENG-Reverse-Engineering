/* sub_4015F0 @ 004015f0   387 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1
sub_4015F0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 *param_6,byte *param_7)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  
  _DAT_0057d798 = 0;
  _DAT_0057d828 = 0;
  _DAT_0057d738 = 0;
  _DAT_0057d708 = 0;
  _DAT_0057d768 = 0;
  _DAT_0057d7c8 = 0;
  puVar3 = param_6;
  if ((*param_7 & 0x10) != 0) {
    cVar1 = sub_401430(4,param_1,param_2,param_3,param_4,param_6,&DAT_0057d770,param_5);
    if (cVar1 == '\0') {
      return 0;
    }
    puVar3 = (undefined4 *)&DAT_0057d770;
  }
  if ((*param_7 & 0x20) != 0) {
    cVar1 = sub_401430(5,param_1,param_2,param_3,param_4,puVar3,&DAT_0057d800,param_5);
    if (cVar1 == '\0') {
      return 0;
    }
    puVar3 = (undefined4 *)&DAT_0057d800;
  }
  if ((*param_7 & 1) != 0) {
    cVar1 = sub_401430(0,param_1,param_2,param_3,param_4,puVar3,&DAT_0057d710,param_5);
    if (cVar1 == '\0') {
      return 0;
    }
    puVar3 = (undefined4 *)&DAT_0057d710;
  }
  if ((*param_7 & 2) != 0) {
    cVar1 = sub_401430(1,param_1,param_2,param_3,param_4,puVar3,&DAT_0057d6e0,param_5);
    if (cVar1 == '\0') {
      return 0;
    }
    puVar3 = (undefined4 *)&DAT_0057d6e0;
  }
  if ((*param_7 & 8) != 0) {
    cVar1 = sub_401430(3,param_1,param_2,param_3,param_4,puVar3,&DAT_0057d740,param_5);
    if (cVar1 == '\0') {
      return 0;
    }
    puVar3 = &DAT_0057d740;
  }
  if ((*param_7 & 4) != 0) {
    cVar1 = sub_401430(2,param_1,param_2,param_3,param_4,puVar3,&DAT_0057d7a0,param_5);
    if (cVar1 == '\0') {
      return 0;
    }
    puVar3 = &DAT_0057d7a0;
  }
  for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_6 = *puVar3;
    puVar3 = puVar3 + 1;
    param_6 = param_6 + 1;
  }
  return 1;
}

