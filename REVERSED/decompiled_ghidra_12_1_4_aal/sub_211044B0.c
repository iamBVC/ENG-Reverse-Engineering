/* _AAL_CloseFilterProvider@4 @ 211044b0   140 bytes */

void _AAL_CloseFilterProvider_4(uint param_1)

{
  LPVOID pvVar1;
  LPVOID pvVar2;
  LPVOID pvVar3;
  LPVOID pvVar4;
  
                    /* 0x44b0  8  _AAL_CloseFilterProvider@4 */
  if ((((DAT_211155ac != 0) && (DAT_211155b4 != (int *)0x0)) && (param_1 != 0)) &&
     (param_1 <= *(uint *)*DAT_211155b4)) {
    pvVar1 = *(LPVOID *)(((uint *)*DAT_211155b4)[3] + 0x10 + param_1 * 0x30);
    if (pvVar1 != (LPVOID)0x0) {
      if (*(code **)((int)pvVar1 + 0x10) != (code *)0x0) {
        (**(code **)((int)pvVar1 + 0x10))(*(undefined4 *)((int)pvVar1 + 0x38));
        if (*(LPVOID *)(DAT_211155ac + 4) == pvVar1) {
          *(undefined4 *)(DAT_211155ac + 4) = *(undefined4 *)((int)pvVar1 + 0x3c);
        }
        else {
          pvVar4 = *(LPVOID *)(DAT_211155ac + 4);
          pvVar3 = (LPVOID)0x0;
          while (pvVar2 = pvVar4, pvVar2 != pvVar1) {
            pvVar3 = pvVar2;
            pvVar4 = *(LPVOID *)((int)pvVar2 + 0x3c);
          }
          *(undefined4 *)((int)pvVar3 + 0x3c) = *(undefined4 *)((int)pvVar1 + 0x3c);
        }
      }
      sub_2110D4F4(pvVar1);
      *(undefined4 *)(*(int *)(*DAT_211155b4 + 0xc) + 0x10 + param_1 * 0x30) = 0;
    }
  }
  return;
}

