/* sub_40D130 @ 0040d130   249 bytes */

uint sub_40D130(int *param_1,COLORREF param_2)

{
  int iVar1;
  HDC pHVar2;
  uint uVar3;
  HDC__ *hdc;
  HDC local_80;
  HDC__ local_7c [4];
  uint *puStack_6c;
  uint uStack_3c;
  
  uVar3 = 0xffffffff;
  if ((param_2 != 0xffffffff) && (iVar1 = (**(code **)(*param_1 + 0x44))(param_1), iVar1 == 0)) {
    pHVar2 = (HDC)GetPixel(local_80,0,0);
    SetPixel(local_80,0,0,param_2);
    (**(code **)(*param_1 + 0x68))(param_1);
    local_80 = pHVar2;
  }
  hdc = local_7c;
  local_7c[0].unused = 0x7c;
  iVar1 = (**(code **)(*param_1 + 100))(param_1,0,hdc,0);
  while (iVar1 == -0x7789fde4) {
    iVar1 = (**(code **)(*param_1 + 100))(param_1,0,&stack0xffffff70,0,0);
  }
  if (iVar1 == 0) {
    uVar3 = *puStack_6c;
    if (uStack_3c < 0x20) {
      uVar3 = uVar3 & (1 << ((byte)uStack_3c & 0x1f)) - 1U;
    }
    (**(code **)(*param_1 + 0x80))(param_1,0);
  }
  if ((param_2 != 0xffffffff) &&
     (iVar1 = (**(code **)(*param_1 + 0x44))(param_1,&stack0xffffff6c), iVar1 == 0)) {
    SetPixel(hdc,0,0,(COLORREF)local_80);
    (**(code **)(*param_1 + 0x68))(param_1,hdc);
  }
  return uVar3;
}

