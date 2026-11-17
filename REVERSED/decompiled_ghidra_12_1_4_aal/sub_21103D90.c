/* _AAL_Get3DAttributes@8 @ 21103d90   52 bytes */

void _AAL_Get3DAttributes_8(uint param_1,undefined4 param_2)

{
  int iVar1;
  
                    /* 0x3d90  12  _AAL_Get3DAttributes@8 */
  if ((((DAT_211155b4 != (undefined4 *)0x0) && (param_1 != 0)) &&
      (param_1 <= *(uint *)*DAT_211155b4)) &&
     (iVar1 = *(int *)(((uint *)*DAT_211155b4)[3] + 0x10 + param_1 * 0x30), iVar1 != 0)) {
    (**(code **)(iVar1 + 0x14))(param_2);
  }
  return;
}

