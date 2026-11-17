/* sub_211082A0 @ 211082a0   119 bytes */

int __thiscall sub_211082A0(void *this,undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  
  piVar1 = *(int **)((int)this + 0x14);
  iVar5 = 0;
  if (piVar1 == (int *)0x0) {
    return 0;
  }
  iVar3 = 0;
  puVar2 = (undefined4 *)piVar1[4];
  puVar4 = param_1;
  if (0 < *piVar1) {
    do {
      puVar4 = puVar2;
      if (param_1 == (undefined4 *)puVar4[1]) {
        piVar1 = puVar4 + 2;
        if (*piVar1 == 0) {
          _AAL_Lock_0();
          (**(code **)*param_1)(param_1,&DAT_211122a8,piVar1);
          _AAL_Unlock_0();
        }
        iVar5 = *piVar1;
        if (iVar5 != 0) goto LAB_2110830b;
        break;
      }
      iVar3 = iVar3 + 1;
      puVar2 = (undefined4 *)((int)puVar4 + piVar1[1]);
    } while (iVar3 < *piVar1);
  }
  AAL_SetError(s_Could_not_create_3d_sound_interf_211145cc);
LAB_2110830b:
  puVar4[2] = iVar5;
  return iVar5;
}

