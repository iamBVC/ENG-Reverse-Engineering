/* sub_56279D @ 0056279d   156 bytes */

uint sub_56279D(byte *param_1,byte *param_2)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte local_24 [32];
  
  pbVar3 = local_24;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    pbVar3[0] = 0;
    pbVar3[1] = 0;
    pbVar3[2] = 0;
    pbVar3[3] = 0;
    pbVar3 = pbVar3 + 4;
  }
  do {
    bVar1 = *param_2;
    local_24[bVar1 >> 3] = local_24[bVar1 >> 3] | '\x01' << (bVar1 & 7);
    param_2 = param_2 + 1;
  } while (bVar1 != 0);
  if (param_1 == (byte *)0x0) {
    param_1 = DAT_006da360;
  }
  for (; (bVar1 = *param_1, DAT_006da360 = param_1,
         (local_24[bVar1 >> 3] & (byte)(1 << (bVar1 & 7))) != 0 && (bVar1 != 0));
      param_1 = param_1 + 1) {
  }
  do {
    bVar1 = *DAT_006da360;
    if (bVar1 == 0) {
LAB_00562824:
      return -(uint)(param_1 != DAT_006da360) & (uint)param_1;
    }
    if ((local_24[bVar1 >> 3] & (byte)(1 << (bVar1 & 7))) != 0) {
      *DAT_006da360 = 0;
      DAT_006da360 = DAT_006da360 + 1;
      goto LAB_00562824;
    }
    DAT_006da360 = DAT_006da360 + 1;
  } while( true );
}

