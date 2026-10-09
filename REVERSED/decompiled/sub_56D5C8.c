/* sub_56D5C8 @ 0056d5c8   61 bytes */

undefined4 * __thiscall sub_56D5C8(undefined4 *param_1,undefined4 *param_2)

{
  size_t sVar1;
  void *pvVar2;
  
  *param_1 = &PTR_sub_56D5AC_0056eda0;
  sVar1 = _strlen((char *)*param_2);
  pvVar2 = operator_new(sVar1 + 1);
  param_1[1] = pvVar2;
  if (pvVar2 != (void *)0x0) {
    sub_569990(pvVar2,*param_2);
  }
  param_1[2] = 1;
  return param_1;
}

