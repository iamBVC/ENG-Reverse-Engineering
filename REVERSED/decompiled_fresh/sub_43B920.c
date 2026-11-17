/* sub_43B920 @ 0043b920   103 bytes */

undefined4 sub_43B920(undefined4 *param_1,undefined4 param_2)

{
  void *pvVar1;
  void *pvVar2;
  
  pvVar1 = _malloc(0x218);
  sub_5629E6(pvVar1,0x218,1,param_2);
  pvVar2 = _malloc((int)*(short *)((int)pvVar1 + 0xe) * (int)*(short *)((int)pvVar1 + 0xc) * 3);
  *(void **)((int)pvVar1 + 0x214) = pvVar2;
  if (pvVar2 != (void *)0x0) {
    sub_5629E6(pvVar2,(int)*(short *)((int)pvVar1 + 0xe) * (int)*(short *)((int)pvVar1 + 0xc) * 3,1,
               param_2);
    *param_1 = pvVar1;
  }
  return 0;
}

