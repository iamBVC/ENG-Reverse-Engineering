/* sub_41F0C0 @ 0041f0c0   1231 bytes */

/* WARNING: Removing unreachable block (ram,0x0041f56e) */

int sub_41F0C0(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *unaff_EBX;
  int *unaff_ESI;
  undefined4 *puVar3;
  int *unaff_EDI;
  undefined4 *puVar4;
  int *piVar5;
  int **ppiStack_238;
  int *piStack_230;
  undefined *puStack_22c;
  int *piStack_228;
  int *piStack_224;
  int *piStack_220;
  int local_204 [5];
  HCURSOR local_1f0;
  int local_1ec;
  int local_1e8;
  int local_1e4;
  int *piStack_1dc;
  uint uStack_1d8;
  undefined4 local_1c8;
  undefined4 local_1c4 [8];
  undefined4 auStack_1a4 [7];
  int iStack_188;
  undefined1 auStack_180 [16];
  undefined4 auStack_170 [5];
  undefined4 uStack_15c;
  undefined4 auStack_138 [12];
  undefined4 uStack_108;
  undefined1 auStack_104 [16];
  undefined4 auStack_f4 [20];
  undefined4 uStack_a4;
  int local_7c [15];
  int *piStack_40;
  int *piStack_1c;
  int *piStack_10;
  int **ppiStack_8;
  
  local_1c8 = 0x6c;
  puVar3 = local_1c4;
  for (iVar1 = 0x1a; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  local_204[2] = 0;
  local_204[3] = 0;
  local_204[4] = 0;
  local_204[0] = 0;
  local_204[1] = 0;
  DAT_005865e4 = 1;
  local_1f0 = (HCURSOR)0x0;
  local_1ec = 0;
  local_1e8 = DAT_00583374;
  local_1e4 = DAT_00583378;
  if (0x140 < DAT_00583374) {
    local_1f0 = (HCURSOR)((int)(DAT_00583374 + (DAT_00583374 >> 0x1f & 7U)) >> 3);
    local_1e8 = DAT_00583374 - (int)local_1f0;
    local_1ec = (int)(DAT_00583378 + (DAT_00583378 >> 0x1f & 7U)) >> 3;
    local_1e4 = DAT_00583378 - local_1ec;
  }
  piStack_220 = local_7c;
  piVar5 = local_7c;
  for (iVar1 = 0x1f; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar5 = 0;
    piVar5 = piVar5 + 1;
  }
  piStack_224 = param_2;
  local_7c[0] = 0x7c;
  piStack_228 = (int *)0x41f186;
  (**(code **)(*param_2 + 0x58))();
  piStack_228 = local_204;
  puStack_22c = &DAT_0056e5cc;
  piStack_230 = param_1;
  iVar1 = (**(code **)(*param_1 + 0x10))();
  if (iVar1 < 0) {
    ppiStack_238 = (int **)s_pMMStream_>GetMediaStream_MSPID__00572a54;
    sub_414600();
    goto LAB_0041f53c;
  }
  ppiStack_238 = (int **)&DAT_0056e5dc;
  iVar1 = (**(code **)*unaff_EBX)(unaff_EBX);
  if (iVar1 < 0) {
    ppiStack_238 = (int **)s_pPrimaryVidStream_>QueryInterfac_005729e0;
    sub_414600();
    goto LAB_0041f53c;
  }
  ppiStack_238 = (int **)0x0;
  (**(code **)(*unaff_EDI + 0x24))(unaff_EDI,&piStack_1dc,local_204 + 4);
  iVar1 = (**(code **)(*piStack_230 + 0x34))(piStack_230,0,0,0,&puStack_22c);
  if (iVar1 != 0) {
    if (iStack_188 == 0x18) {
      uStack_1d8 = uStack_1d8 | 0x1000;
      ppiStack_238 = &piStack_1dc;
      iStack_188 = 0x20;
      (**(code **)(*unaff_EDI + 0x28))(unaff_EDI);
    }
    ppiStack_238 = (int **)0x0;
    iVar1 = (**(code **)(*unaff_EDI + 0x34))(unaff_EDI,0,0);
    if (iVar1 < 0) {
      ppiStack_238 = (int **)s_pDDStream_>CreateSample_NULL__NU_00572990;
      sub_414600();
      goto LAB_0041f53c;
    }
  }
  puVar3 = auStack_170;
  for (iVar1 = 0x1f; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar3 = auStack_f4;
  for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  auStack_170[0] = 0x7c;
  ppiStack_238 = &piStack_220;
  uStack_108 = 0x4080;
  auStack_170[1] = 0x1007;
  uStack_15c = 0;
  auStack_170[3] = 0x140;
  auStack_170[2] = 0xf0;
  auStack_f4[0] = 100;
  uStack_a4 = 0;
  iVar1 = (**(code **)(*piStack_10 + 0x18))(piStack_10,auStack_170);
  if (iVar1 == 0) {
LAB_0041f334:
    piVar5 = (int *)0x0;
    (**(code **)(*piStack_230 + 0x14))(piStack_230,0,0,0,0x1000400,auStack_104);
    (**(code **)(*piStack_10 + 0x58))(piStack_10,1,0);
    iVar1 = (**(code **)(*piVar5 + 0x84))(piVar5,0,piStack_40,&ppiStack_238,0x4000,0);
    piVar5 = piStack_40;
    if ((iVar1 != 0) && (piStack_224 = (int *)0x1, piStack_230 != (int *)0x0)) {
      (**(code **)(*piStack_230 + 8))(piStack_230);
    }
  }
  else {
    iVar1 = *piStack_10;
    puVar3 = auStack_1a4;
    puVar4 = auStack_138;
    for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    iVar1 = (**(code **)(iVar1 + 0x18))(piStack_10,auStack_180,&piStack_230,0);
    if (iVar1 == 0) goto LAB_0041f334;
    piStack_224 = (int *)0x1;
    piVar5 = piStack_1c;
  }
  local_204[2] = 0;
  local_204[3] = 0;
  local_204[4] = 0x140;
  local_1f0 = (HCURSOR)0xf0;
  iVar1 = (**(code **)(*piStack_228 + 0x20))(piStack_228,&stack0xfffffde4,local_204 + 2);
  if (iVar1 < 0) {
    ppiStack_238 = (int **)s_pSample_>GetSurface__pSurface____00572948;
    sub_414600();
  }
  else {
    ppiStack_238 = (int **)&DAT_0056e60c;
    iVar1 = (*(code *)*puRam00000000)(0);
    if (iVar1 < 0) {
      ppiStack_238 = (int **)s_pSurface_>QueryInterface_IID_IDi_005728e0;
      sub_414600();
    }
    else {
      ppiStack_238 = ppiStack_8;
      iVar1 = (*(code *)(*ppiStack_8)[7])();
      if (iVar1 < 0) {
        ppiStack_238 = (int **)s_pMMStream_>SetState_STREAMSTATE__0057289c;
        sub_414600();
      }
      else {
        ppiStack_238 = (int **)0x41f432;
        local_1f0 = SetCursor((HCURSOR)0x0);
        ppiStack_238 = (int **)0x1000400;
        (**(code **)(*piVar5 + 0x14))(piVar5,0,0,0);
        DAT_005865e8 = 0;
        do {
          iVar2 = (**(code **)(*piStack_230 + 0x18))(piStack_230,2,0,0,0);
          if (iVar2 != 0) {
            if (iVar1 != 0) goto LAB_0041f4de;
            goto LAB_0041f4d8;
          }
          if (puStack_22c == (undefined *)0x0) {
            iVar1 = (*(code *)(*ppiStack_238)[5])(ppiStack_238,0,piStack_220,0,0x1000000,0);
          }
          else {
            iVar1 = (**(code **)(*piVar5 + 0x14))
                              (piVar5,&stack0xfffffde4,piStack_220,local_204,0x1000000,0);
          }
          if (iVar1 != 0) goto LAB_0041f4de;
          sub_40F060(PTR_DAT_005724dc + 0x18,PTR_DAT_005724dc + 0x118);
          iVar1 = 0;
        } while ((PTR_DAT_005724dc[0x19] & 0x80) == 0);
        DAT_005865e8 = 1;
LAB_0041f4d8:
        DAT_005865e4 = 0;
LAB_0041f4de:
        if (puStack_22c == (undefined *)0x0) {
          (*(code *)(*ppiStack_238)[0x21])(ppiStack_238,0,piVar5,&stack0xfffffde4,0x200,0);
        }
        iVar1 = (*(code *)(*ppiStack_8)[7])(ppiStack_8,0);
        if (iVar1 < 0) {
          ppiStack_238 = (int **)s_pMMStream_>SetState_STREAMSTATE__00572854;
          sub_414600();
        }
        else {
          ppiStack_238 = (int **)0x1000400;
          (**(code **)(*piVar5 + 0x14))(piVar5,0,0,0);
          ppiStack_238 = (int **)0x41f53c;
          SetCursor(local_1f0);
        }
      }
    }
  }
LAB_0041f53c:
  if (unaff_EBX != (int *)0x0) {
    ppiStack_238 = (int **)0x41f54a;
    (**(code **)(*unaff_EBX + 8))();
  }
  if (unaff_EDI != (int *)0x0) {
    ppiStack_238 = (int **)0x41f558;
    (**(code **)(*unaff_EDI + 8))();
  }
  if (unaff_ESI != (int *)0x0) {
    ppiStack_238 = (int **)0x41f566;
    (**(code **)(*unaff_ESI + 8))();
  }
  if (piStack_220 != (int *)0x0) {
    ppiStack_238 = (int **)0x41f582;
    (**(code **)(*piStack_220 + 8))();
  }
  return iVar1;
}

