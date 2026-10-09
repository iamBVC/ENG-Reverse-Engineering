/* sub_41DB40 @ 0041db40   193 bytes */

undefined4 sub_41DB40(int param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  BOOL BVar3;
  uint uVar4;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  iVar1 = sub_41D9C0();
  if (iVar1 != 0) {
    uVar2 = (*DAT_005863dc)(param_1,param_2);
    return uVar2;
  }
  if (((param_1 == 0x12340042) && (param_2 != (uint *)0x0)) && (0x27 < *param_2)) {
    BVar3 = SystemParametersInfoA(0x30,0,&local_10,0);
    if (BVar3 != 0) {
      param_2[1] = 0;
      param_2[2] = 0;
      uVar4 = GetSystemMetrics(0);
      param_2[3] = uVar4;
      uVar4 = GetSystemMetrics(1);
      param_2[4] = uVar4;
      param_2[5] = local_10;
      param_2[9] = 1;
      param_2[6] = local_c;
      param_2[7] = local_8;
      param_2[8] = local_4;
      if (0x47 < *param_2) {
        lstrcpyA((LPSTR)(param_2 + 10),s_DISPLAY_005725f8);
      }
      return 1;
    }
  }
  return 0;
}

