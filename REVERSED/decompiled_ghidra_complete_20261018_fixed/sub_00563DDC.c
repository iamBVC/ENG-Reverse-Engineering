/* sub_563DDC @ 00563ddc   34 bytes */

undefined4 sub_563DDC(undefined4 param_1,uint *param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  uVar2 = sub_568A4A(param_1);
  *(undefined8 *)param_2 = uVar2;
  uVar1 = 0xffffffff;
  if ((*param_2 & param_2[1]) != 0xffffffff) {
    uVar1 = 0;
  }
  return uVar1;
}

