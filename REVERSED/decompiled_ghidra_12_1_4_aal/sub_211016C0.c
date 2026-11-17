/* _AAL_SetVoiceAttr@4 @ 211016c0   477 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _AAL_SetVoiceAttr_4(uint *param_1)

{
  undefined4 *puVar1;
  void *this;
  uint uVar2;
  int iVar3;
  uint uVar4;
  float fVar5;
  
                    /* 0x16c0  69  _AAL_SetVoiceAttr@4 */
  if (((DAT_211155ac == 0) || (param_1 == (uint *)0x0)) ||
     (this = (void *)param_1[1], this == (void *)0x0)) {
    AAL_SetError(s_AAL_is_not_initialised_2111408c);
  }
  else {
    uVar2 = *(uint *)((int)this + 8);
    if (uVar2 == 0) {
      uVar2 = *param_1;
      if ((uVar2 & 1) != 0) {
        sub_2110A040(this,param_1[2]);
      }
      if ((uVar2 & 2) != 0) {
        sub_2110A000(this,(short *)(param_1 + 3));
      }
      if ((uVar2 & 4) != 0) {
        *(uint *)((int)this + 100) = param_1[0x2f];
      }
      if ((uVar2 & 0x10) != 0) {
        uVar4 = param_1[0x2e];
        puVar1 = (undefined4 *)((int)this + 0x70);
        if (uVar4 == 0) {
          *puVar1 = 1;
        }
        else {
          *puVar1 = 0;
          *(uint *)((int)this + 0x6c) = uVar4;
        }
        if (*(int *)((int)this + 0x90) != 0) {
          (**(code **)((int)this + 0xa4))(*(undefined4 *)((int)this + 0xac),0,puVar1);
        }
      }
      if ((uVar2 & 8) != 0) {
        uVar4 = param_1[0x2d];
        *(uint *)((int)this + 0x108) = param_1[0x2c];
        *(uint *)((int)this + 0xfc) = uVar4;
      }
      if ((uVar2 & 0x200) != 0) {
        fVar5 = _DAT_2111232c;
        if ((_DAT_2111232c <= (float)param_1[0x33]) &&
           (fVar5 = _DAT_21112328, (float)param_1[0x33] <= _DAT_21112328)) {
          fVar5 = (float)param_1[0x33];
        }
        *(float *)((int)this + 0x24) = fVar5;
      }
      if ((uVar2 & 0x400) != 0) {
        fVar5 = _DAT_2111232c;
        if ((_DAT_2111232c <= (float)param_1[0x34]) &&
           (fVar5 = _DAT_21112328, (float)param_1[0x34] <= _DAT_21112328)) {
          fVar5 = (float)param_1[0x34];
        }
        *(float *)((int)this + 0x20) = fVar5;
      }
      if ((uVar2 & 0x800) != 0) {
        fVar5 = _DAT_2111232c;
        if ((_DAT_2111232c <= (float)param_1[0x35]) &&
           (fVar5 = _DAT_21112328, (float)param_1[0x35] <= _DAT_21112328)) {
          fVar5 = (float)param_1[0x35];
        }
        *(float *)((int)this + 0x1c) = fVar5;
      }
      if ((uVar2 & 0x8000) != 0) {
        sub_2110A170(this,0,param_1 + 0x18);
        return;
      }
    }
    else if ((uVar2 <= *(uint *)*DAT_211155b4) &&
            (iVar3 = *(int *)(((uint *)*DAT_211155b4)[3] + 0x10 + uVar2 * 0x30), iVar3 != 0)) {
      (**(code **)(iVar3 + 0x3c))(this,param_1);
      return;
    }
  }
  return;
}

