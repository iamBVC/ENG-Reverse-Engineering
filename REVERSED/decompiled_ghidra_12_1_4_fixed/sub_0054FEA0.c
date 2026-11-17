/* sub_54FEA0 @ 0054fea0   62 bytes */

void sub_54FEA0(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(char *)(param_1 + 0x135) = (char)(iVar1 >> 0xc);
  iVar1 = sub_54BC00(param_1);
  *(char *)(param_1 + 0x134) = (char)(iVar1 >> 0xc);
  iVar1 = sub_54BC00(param_1);
  *(undefined1 *)(param_1 + 0x136) = 1;
  *(char *)(param_1 + 0x133) = (char)(iVar1 >> 0xc);
  return;
}

