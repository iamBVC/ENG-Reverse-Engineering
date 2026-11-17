/* sub_21108320 @ 21108320   106 bytes */

int __thiscall sub_21108320(void *this,undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = *(int **)((int)this + 0x14);
  if (piVar1 == (int *)0x0) {
    return 0;
  }
  iVar2 = piVar1[4];
  iVar3 = 0;
  if (0 < *piVar1) {
    do {
      if (param_1 == *(undefined4 **)(iVar2 + 8)) {
        if (*(int *)(iVar2 + 0xc) == 0) {
          _AAL_Lock_0();
          (**(code **)*param_1)(param_1,&DAT_211122e8,(int *)(iVar2 + 0xc));
          _AAL_Unlock_0();
        }
        iVar2 = *(int *)(iVar2 + 0xc);
        if (iVar2 != 0) {
          return iVar2;
        }
        break;
      }
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + piVar1[1];
    } while (iVar3 < *piVar1);
  }
  AAL_SetError(s_Could_not_create_sound_property_s_211145f0);
  return 0;
}

