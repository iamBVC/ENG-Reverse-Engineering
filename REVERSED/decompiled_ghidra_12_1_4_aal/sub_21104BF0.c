/* sub_21104BF0 @ 21104bf0   1187 bytes */

int __fastcall sub_21104BF0(void *param_1)

{
  ulonglong uVar1;
  int iVar2;
  void *pvVar3;
  undefined4 *puVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  int *piVar9;
  uint *puVar10;
  undefined8 uVar11;
  uint local_4c [4];
  int local_3c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int *local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  iVar2 = *(int *)((int)param_1 + 0x48);
  if (iVar2 == 0) {
    _AAL_Lock_0();
    LOCK();
    DAT_211155e0 = DAT_211155e0 + 1;
    UNLOCK();
    *(uint *)((int)param_1 + 0xcc) = *(uint *)((int)param_1 + 0xcc) & 0xffffffdf;
    iVar2 = sub_211050B0((int)param_1);
    if (iVar2 == 0) {
      sub_211053E0((int)param_1);
      _AAL_Unlock_0();
      LOCK();
      DAT_211155e0 = DAT_211155e0 + -1;
      UNLOCK();
      return 1;
    }
    uVar6 = *(uint *)((int)param_1 + 0xcc);
    if (((uVar6 & 0x20000) == 0) && ((uVar6 & 0x10000) != 0)) {
      piVar5 = *(int **)((int)param_1 + 0xb4);
      local_24 = 0;
      local_20 = 0;
      local_1c = 0;
      local_18 = 0;
      *(int **)((int)param_1 + 0x88) = piVar5;
      local_28 = 0x14;
      (**(code **)(*piVar5 + 0xc))(piVar5,&local_28);
      uVar6 = (uint)(*(int *)((int)param_1 + 0x28) << 3) / 1000;
      iVar2 = local_20 / (int)uVar6;
      *(int *)((int)param_1 + 0x94) = local_20;
      *(uint *)((int)param_1 + 0x90) = uVar6;
      *(int *)((int)param_1 + 0x8c) = iVar2;
      if (1 < iVar2) {
        do {
          iVar2 = *(int *)((int)param_1 + 0x8c);
          uVar6 = *(int *)((int)param_1 + 0x94) / iVar2;
          *(uint *)((int)param_1 + 0x90) = uVar6;
          if (((uVar6 & *(ushort *)((int)param_1 + 0x2c) - 1) == 0) &&
             (uVar6 * iVar2 - *(int *)((int)param_1 + 0x94) == 0)) break;
          *(int *)((int)param_1 + 0x8c) = iVar2 + -1;
        } while (1 < iVar2 + -1);
      }
      if (*(int *)((int)param_1 + 0x8c) < 2) {
        *(undefined4 *)((int)param_1 + 0x8c) = 2;
        *(int *)((int)param_1 + 0x90) = *(int *)((int)param_1 + 0x94) / 2;
      }
    }
    else {
      uVar7 = (uint)(*(int *)((int)param_1 + 0x28) << 3) / 1000;
      *(undefined4 *)((int)param_1 + 0x8c) = 0x60;
      *(uint *)((int)param_1 + 0x90) = uVar7;
      if ((uVar6 & 0x20000) != 0) {
        *(uint *)((int)param_1 + 0x90) = uVar7 * 2;
      }
      uVar7 = *(int *)((int)param_1 + 0x90) + 0xfU & 0xfffffff0;
      *(uint *)((int)param_1 + 0x90) = uVar7;
      puVar10 = local_4c;
      for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar10 = 0;
        puVar10 = puVar10 + 1;
      }
      local_3c = (int)param_1 + 0x20;
      local_4c[2] = uVar7 * 0x60;
      local_4c[1] = (uVar6 & 0x80000 | 0x100e00) >> 4;
      *(uint *)((int)param_1 + 0x94) = local_4c[2];
      local_4c[0] = 0x24;
      iVar2 = (**(code **)(**(int **)((int)param_1 + 0xb8) + 0xc))
                        (*(int **)((int)param_1 + 0xb8),local_4c,(undefined4 *)((int)param_1 + 0x84)
                         ,0);
      if (iVar2 < 0) {
        sub_211053E0((int)param_1);
        AAL_SetError(s_Could_not_create_secondary_buffe_211143b8);
        _AAL_Unlock_0();
        LOCK();
        DAT_211155e0 = DAT_211155e0 + -1;
        UNLOCK();
        return 1;
      }
      *(undefined4 *)((int)param_1 + 0x88) = *(undefined4 *)((int)param_1 + 0x84);
      sub_21105480((int)param_1);
    }
    iVar2 = (**(code **)(**(int **)((int)param_1 + 0x88) + 0x10))
                      (*(int **)((int)param_1 + 0x88),&local_c,&local_8);
    if (iVar2 < 0) {
      sub_211053E0((int)param_1);
      AAL_SetError(s_Could_not_get_buffer_position_21114398);
      _AAL_Unlock_0();
      LOCK();
      DAT_211155e0 = DAT_211155e0 + -1;
      UNLOCK();
      return 1;
    }
    *(undefined4 *)((int)param_1 + 0xa0) = 0x300;
    iVar2 = local_8 / *(uint *)((int)param_1 + 0x90) + 1;
    *(int *)((int)param_1 + 0x98) = iVar2;
    *(int *)((int)param_1 + 0x9c) = iVar2;
    uVar11 = sub_211010C0(1);
    *(int *)((int)param_1 + 0xa4) = (int)uVar11;
    _AAL_Unlock_0();
    *(uint *)((int)param_1 + 0x4c) = *(uint *)((int)param_1 + 0x90);
    uVar1 = (ulonglong)*(uint *)((int)param_1 + 0x90) /
            (ulonglong)(*(ushort *)((int)param_1 + 0x2e) >> 3);
    iVar2 = (int)uVar1;
    *(int *)((int)param_1 + 0x50) = iVar2;
    *(int *)((int)param_1 + 0x54) = (int)(uVar1 / *(ushort *)((int)param_1 + 0x22));
    iVar2 = iVar2 * 4;
    *(int *)((int)param_1 + 0x5c) = iVar2;
    pvVar3 = operator_new(((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2) << 2);
    *(void **)((int)param_1 + 0x60) = pvVar3;
    *(int *)((int)param_1 + 100) = *(int *)((int)param_1 + 0x5c);
    iVar2 = *(int *)((int)param_1 + 0x5c) + 0x20;
    pvVar3 = operator_new(((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2) << 2);
    *(void **)((int)param_1 + 0x68) = pvVar3;
    *(undefined4 *)((int)param_1 + 0x6c) = 0;
    *(undefined4 *)((int)param_1 + 0x70) = 0;
    *(undefined4 *)((int)param_1 + 0x74) = 0;
    if (*(int *)((int)param_1 + 0xb0) == 0) {
      puVar4 = operator_new(0x94);
      if (puVar4 == (undefined4 *)0x0) {
        puVar8 = (undefined4 *)0x0;
      }
      else {
        puVar8 = puVar4 + 1;
        *puVar4 = 4;
        iVar2 = 4;
        puVar4 = puVar8;
        do {
          *puVar4 = 0;
          puVar4[1] = 0;
          puVar4 = puVar4 + 9;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      *(undefined4 **)((int)param_1 + 0xb0) = puVar8;
    }
    if (*(int *)((int)param_1 + 0x7c) == 0) {
      iVar2 = *(int *)((int)param_1 + 0x78);
      piVar5 = operator_new(iVar2 * 0x11c + 4);
      if (piVar5 == (int *)0x0) {
        piVar9 = (int *)0x0;
      }
      else {
        piVar9 = piVar5 + 1;
        *piVar5 = iVar2;
        local_14 = piVar9;
        if (-1 < iVar2 + -1) {
          piVar5 = piVar5 + 0x25;
          local_10 = iVar2;
          do {
            *piVar9 = 0;
            piVar5[-0x23] = 0;
            sub_211035E0(piVar5,0x24,3,sub_211089D0);
            piVar5[-0xe] = 0;
            piVar5[-0x22] = 0;
            piVar5[-0x21] = 0;
            piVar9 = piVar9 + 0x47;
            piVar5 = piVar5 + 0x47;
            local_10 = local_10 + -1;
          } while (local_10 != 0);
          local_10 = 0;
          piVar9 = local_14;
        }
      }
      *(int **)((int)param_1 + 0x7c) = piVar9;
      local_c = 0;
      if (*(int *)((int)param_1 + 0x78) != 0) {
        do {
          piVar5 = (int *)(*(int *)((int)param_1 + 0x7c) + local_c * 0x11c);
          piVar9 = *(int **)((int)param_1 + 0x10);
          if (*piVar9 != 0) {
            if (*piVar5 != 0) {
              *(int *)(*piVar5 + 4) = piVar5[1];
              *(int *)piVar5[1] = *piVar5;
              *piVar5 = 0;
              piVar5[1] = 0;
            }
            iVar2 = *piVar9;
            piVar5[1] = (int)piVar9;
            *piVar5 = iVar2;
            *(int **)(iVar2 + 4) = piVar5;
            *(int **)piVar5[1] = piVar5;
          }
          local_c = local_c + 1;
        } while (local_c < *(uint *)((int)param_1 + 0x78));
      }
    }
    sub_21109660(DAT_211155b4,s_AAL_Mixer_21114134,(uint *)0x0,&local_8);
    sub_211056A0(param_1,1,0);
    sub_211056A0(param_1,2,local_8);
    sub_211056A0(param_1,0,local_8);
    sub_211056A0(param_1,3,local_8);
    iVar2 = _AAL_RegisterTimer_12(sub_21105AB0,param_1,100);
    *(int *)((int)param_1 + 0x80) = iVar2;
    _AAL_StartTimer_4(iVar2);
    LOCK();
    DAT_211155e0 = DAT_211155e0 + -1;
    UNLOCK();
    iVar2 = 0;
  }
  return iVar2;
}

