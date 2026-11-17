/* _AAL_Close3DProvider@4 @ 21103cf0   81 bytes */

void _AAL_Close3DProvider_4(uint param_1)

{
  LPVOID pvVar1;
  
                    /* 0x3cf0  7  _AAL_Close3DProvider@4 */
  if (((DAT_211155b4 != (int *)0x0) && (param_1 != 0)) && (param_1 <= *(uint *)*DAT_211155b4)) {
    pvVar1 = *(LPVOID *)(((uint *)*DAT_211155b4)[3] + 0x10 + param_1 * 0x30);
    if (pvVar1 != (LPVOID)0x0) {
      (**(code **)((int)pvVar1 + 0x1c))(0);
      sub_2110D4F4(pvVar1);
      *(undefined4 *)(*(int *)(*DAT_211155b4 + 0xc) + 0x10 + param_1 * 0x30) = 0;
    }
  }
  return;
}

