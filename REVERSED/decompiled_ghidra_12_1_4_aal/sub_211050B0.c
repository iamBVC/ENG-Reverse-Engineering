/* sub_211050B0 @ 211050b0   809 bytes */

undefined4 __fastcall sub_211050B0(int param_1)

{
  LPVOID *ppv;
  ushort uVar1;
  HRESULT HVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  short sVar6;
  int unaff_EDI;
  undefined4 *puVar7;
  uint *puVar8;
  int iVar9;
  int local_a4;
  uint local_a0;
  int *local_9c;
  undefined4 uStack_98;
  int iStack_94;
  undefined4 uStack_90;
  short sStack_8c;
  undefined4 uStack_8a;
  uint uStack_6c;
  undefined4 auStack_68 [26];
  
  if ((*(uint *)(param_1 + 0xcc) & 0x10000) == 0) {
    local_a0 = 0;
    local_a4 = 1;
  }
  else {
    local_a0 = ~*(uint *)(param_1 + 0xcc) & 1;
    local_a4 = 4;
  }
  piVar5 = (int *)(param_1 + 0xb4);
  local_9c = piVar5;
  while( true ) {
    if ((int *)*piVar5 != (int *)0x0) {
      (**(code **)(*(int *)*piVar5 + 8))();
      *piVar5 = 0;
    }
    ppv = (LPVOID *)(param_1 + 0xb8);
    if (*(int **)(param_1 + 0xb8) != (int *)0x0) {
      (**(code **)(**(int **)(param_1 + 0xb8) + 8))();
      *ppv = (LPVOID)0x0;
    }
    HVar2 = CoCreateInstance((IID *)(param_1 + 0xbc),(LPUNKNOWN)0x0,1,(IID *)&DAT_21112278,ppv);
    if (HVar2 < 0) {
      AAL_SetError(s_DirectSoundCreate___handler_fail_21114498);
      return 0;
    }
    iVar3 = (**(code **)(*(int *)*ppv + 0x28))();
    if (iVar3 < 0) {
      AAL_SetError(s_DirectSoundInitialise___failed__21114478);
      return 0;
    }
    *(uint *)(param_1 + 0xcc) = *(uint *)(param_1 + 0xcc) & 0xfffdffff;
    puVar7 = auStack_68;
    for (iVar3 = 0x18; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    auStack_68[0] = 0x60;
    iVar3 = (**(code **)(*(int *)*ppv + 0x10))();
    if (iVar3 == 0) {
      *(uint *)(param_1 + 0xcc) = *(uint *)(param_1 + 0xcc) | (uStack_6c & 0x20) << 0xc;
    }
    if (((*(uint *)(param_1 + 0xcc) & 0x20000) != 0) && (unaff_EDI == 4)) {
      unaff_EDI = 2;
    }
    iVar3 = *(int *)*ppv;
    iVar9 = unaff_EDI;
    iVar4 = sub_21101310();
    iVar3 = (**(code **)(iVar3 + 0x18))(*ppv,iVar4,iVar9);
    if (iVar3 < 0) break;
    puVar8 = &local_a0;
    for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar8 = 0;
      puVar8 = puVar8 + 1;
    }
    local_a0 = 0x24;
    local_9c = (int *)0x1;
    if ((*(uint *)(param_1 + 0xcc) & 0x40000) != 0) {
      local_9c = (int *)0x11;
    }
    uStack_98 = 0;
    uStack_90 = 0;
    iVar3 = (**(code **)(*(int *)*ppv + 0xc))(*ppv,&local_a0,piVar5,0);
    if (iVar3 < 0) {
      AAL_SetError(s_CreateSoundBuffer___failed_on_pr_21114428);
      return 0;
    }
    if (iVar4 != 0) {
      *(undefined2 *)(param_1 + 0x20) = 1;
      *(uint *)(param_1 + 0x28) = (uint)*(ushort *)(param_1 + 0x2c) * *(int *)(param_1 + 0x24);
      iVar3 = (**(code **)(*(int *)*piVar5 + 0x38))((int *)*piVar5,(undefined2 *)(param_1 + 0x20));
      if (iVar3 < 0) {
        AAL_SetError(s_SetFormat___failed_on_primary_bu_21114400);
        return 0;
      }
    }
    (**(code **)(*(int *)*piVar5 + 0x14))((int *)*piVar5,&stack0xffffff3c,0x12,0);
    sVar6 = (short)uStack_8a;
    if (((((uStack_98._2_2_ == *(short *)(param_1 + 0x22)) &&
          (iStack_94 == *(int *)(param_1 + 0x24))) &&
         (piVar5 = local_9c, sStack_8c == *(short *)(param_1 + 0x2c))) &&
        ((sVar6 == *(short *)(param_1 + 0x2e) && ((short)uStack_98 == *(short *)(param_1 + 0x20)))))
       || (((*(uint *)(param_1 + 0xcc) & 1) != 0 || (local_a0 != 0)))) {
      *(short *)(param_1 + 0x20) = (short)uStack_98;
      *(short *)(param_1 + 0x2e) = sVar6;
      *(short *)(param_1 + 0x22) = uStack_98._2_2_;
      *(int *)(param_1 + 0x24) = iStack_94;
      uVar1 = ((sVar6 == 0x10) + 1) * ((uStack_98._2_2_ == 2) + 1);
      *(ushort *)(param_1 + 0x2c) = uVar1;
      *(uint *)(param_1 + 0x28) = (uint)uVar1 * iStack_94;
      if (local_a4 == 4) {
        sub_21105590((int *)*piVar5);
      }
      iVar3 = (**(code **)(*(int *)*piVar5 + 0x30))();
      if (iVar3 != 0) {
        OutputDebugStringA(s_Failed_to_play_the_primary_buffe_211143dc);
      }
      return 1;
    }
    local_a0 = 1;
    local_a4 = 2;
  }
  AAL_SetError(s_SetCooperativeLevel___failed__21114458);
  return 0;
}

