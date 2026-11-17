/* sub_211066A0 @ 211066a0   170 bytes */

undefined4 __thiscall sub_211066A0(void *this,uint *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = *param_1;
  if (uVar1 < 0x53455171) {
    if (uVar1 == 0x53455170) {
LAB_21106728:
      uVar2 = sub_21106CB0(this,(int *)param_1);
      return uVar2;
    }
    if (uVar1 < 0x42464f54) {
      if (uVar1 == 0x42464f53) {
        *(undefined4 *)((int)this + 0x30) = 0xb;
        return 0;
      }
      if (uVar1 == 0) goto LAB_21106741;
      if (uVar1 == 0x465341) {
        uVar2 = sub_21106750(this,(int)param_1);
        return uVar2;
      }
    }
    else {
      if (uVar1 == 0x42504f53) {
        *(undefined4 *)((int)this + 0x30) = 10;
        return 0;
      }
      if (uVar1 == 0x46464952) {
        uVar2 = sub_21106DB0(this,(int)param_1);
        return uVar2;
      }
    }
LAB_21106738:
    uVar2 = sub_21106900(this,(int *)param_1);
    return uVar2;
  }
  if (uVar1 < 0x6468544e) {
    if (uVar1 == 0x6468544d) goto LAB_21106728;
    if (uVar1 == 0x56414270) {
      uVar2 = sub_21106C90(this,(int)param_1);
      return uVar2;
    }
    if (uVar1 != 0x56414770) {
      uVar2 = sub_21106900(this,(int *)param_1);
      return uVar2;
    }
  }
  else if (uVar1 != 0x70474156) goto LAB_21106738;
LAB_21106741:
  uVar2 = sub_21106AD0(this,(int)param_1);
  return uVar2;
}

