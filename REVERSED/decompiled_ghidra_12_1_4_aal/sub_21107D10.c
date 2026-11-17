/* sub_21107D10 @ 21107d10   890 bytes */

undefined4 * __thiscall sub_21107D10(void *this,int *param_1,uint param_2,undefined4 *param_3)

{
  bool bVar1;
  HGLOBAL pvVar2;
  int *pMem;
  undefined3 extraout_var;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  int *piVar9;
  undefined4 *puStack_10;
  undefined4 *puStack_c;
  uint uStack_8;
  undefined4 *puStack_4;
  
  pMem = (int *)0x0;
  if ((*(int *)((int)this + 0x34) == 0) || (*(int *)((int)this + 0x2c) == 0)) goto LAB_21108067;
  puVar6 = param_3;
  if ((int)param_3 < 1) {
    puVar6 = (undefined4 *)0x1;
  }
  pvVar2 = GlobalAlloc(0x40,(int)puVar6 * 0x10 + 0x14);
  pMem = GlobalLock(pvVar2);
  piVar9 = param_1;
  param_3 = pMem;
  if (pMem == (int *)0x0) goto LAB_21108067;
  piVar5 = pMem + 5;
  iVar4 = 0;
  *pMem = (int)puVar6;
  pMem[1] = 0x10;
  pMem[3] = (int)param_1;
  pMem[4] = (int)piVar5;
  if (0 < (int)puVar6) {
    do {
      *piVar5 = iVar4;
      piVar5[1] = 0;
      piVar5[2] = 0;
      piVar5[3] = 0;
      iVar4 = iVar4 + 1;
      piVar5 = piVar5 + 4;
    } while (iVar4 < (int)puVar6);
  }
  _AAL_Lock_0();
  iVar4 = (**(code **)(*piVar9 + 0xc))(piVar9,param_2,pMem[4] + 4,0);
  if (iVar4 < 0) {
LAB_2110803b:
    pvVar2 = GlobalHandle(pMem);
    GlobalUnlock(pvVar2);
    GlobalFree(pvVar2);
    param_3 = (undefined4 *)0x0;
    piVar9 = (int *)0x0;
  }
  else {
    switch(*(undefined4 *)((int)this + 0x30)) {
    case 1:
      iVar4 = *(int *)((int)this + 0x2c);
      break;
    case 2:
      iVar4 = (uint)*(ushort *)(*(int *)((int)this + 0x18) + 2) * *(int *)((int)this + 0x40) * 0x40;
      break;
    default:
      iVar4 = 0;
      break;
    case 0xc:
    case 0x15:
      iVar4 = (*(uint *)((int)this + 0x2c) >> 4) * 0x38;
    }
    bVar1 = sub_21107B90(*(int **)(pMem[4] + 4),0,iVar4,&puStack_c,(int *)&param_2,&puStack_10,
                         (int *)&uStack_8);
    if (CONCAT31(extraout_var,bVar1) == 0) goto LAB_2110803b;
    piVar5 = (int *)0x0;
    if (*(int *)((int)this + 0x30) == 1) {
      puVar6 = *(undefined4 **)((int)this + 0x34);
      puVar8 = puStack_c;
      for (uVar7 = param_2 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *puVar8 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar7 = param_2 & 3; pMem = param_3, uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar6;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
    }
    else {
      piVar5 = operator_new(0x11c);
      if (piVar5 == (int *)0x0) {
        piVar5 = (int *)0x0;
      }
      else {
        *piVar5 = 0;
        piVar5[1] = 0;
        piVar9 = piVar5 + 0x24;
        iVar4 = 3;
        do {
          *piVar9 = 0;
          piVar9[1] = 0;
          piVar9 = piVar9 + 9;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        piVar5[0x16] = 0;
        piVar5[2] = 0;
        piVar5[3] = 0;
      }
      sub_2110A040(piVar5,(int)this);
      uVar7 = param_2;
      puStack_4 = puStack_c;
      param_1 = (int *)0x0;
      if (piVar5[0x24] != 0) {
        (*(code *)piVar5[0x29])(piVar5[0x2b],2,&param_1);
        do {
          pMem = param_3;
          if (uVar7 == 0) break;
          iVar4 = (*(code *)piVar5[0x28])
                            (piVar5[0x2b],(undefined1 *)((int)param_1 + (int)puStack_4),uVar7);
          iVar3 = (*(code *)piVar5[0x2a])(piVar5[0x2b],piVar5[0x2c]);
          piVar5[piVar5[0x16] + 0x10] = iVar3;
          param_1 = (int *)((int)param_1 + iVar4);
          uVar7 = uVar7 - iVar4;
          pMem = param_3;
        } while (iVar4 != 0);
      }
    }
    uVar7 = uStack_8;
    piVar9 = pMem;
    if (uStack_8 != 0) {
      if (*(int *)((int)this + 0x30) == 1) {
        puVar6 = (undefined4 *)(param_2 + *(int *)((int)this + 0x34));
        puVar8 = puStack_10;
        for (uVar7 = uStack_8 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar8 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar8 = puVar8 + 1;
        }
        for (uVar7 = uStack_8 & 3; piVar9 = param_3, uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined1 *)puVar8 = *(undefined1 *)puVar6;
          puVar6 = (undefined4 *)((int)puVar6 + 1);
          puVar8 = (undefined4 *)((int)puVar8 + 1);
        }
      }
      else {
        puStack_4 = puStack_10;
        param_1 = (int *)0x0;
        if (piVar5[0x24] != 0) {
          (*(code *)piVar5[0x29])(piVar5[0x2b],2,&param_1);
          do {
            piVar9 = param_3;
            if (uVar7 == 0) break;
            iVar4 = (*(code *)piVar5[0x28])
                              (piVar5[0x2b],(undefined1 *)((int)param_1 + (int)puStack_4),uVar7);
            iVar3 = (*(code *)piVar5[0x2a])(piVar5[0x2b],piVar5[0x2c]);
            piVar5[piVar5[0x16] + 0x10] = iVar3;
            param_1 = (int *)((int)param_1 + iVar4);
            uVar7 = uVar7 - iVar4;
            piVar9 = param_3;
          } while (iVar4 != 0);
        }
      }
    }
    if (piVar5 != (int *)0x0) {
      piVar5[0x16] = 0;
      piVar5[3] = 0;
      piVar5[0x46] = 0;
      piVar5[6] = 0;
      sub_2110A200(piVar5,4,0,0);
      if (*piVar5 != 0) {
        *(int *)(*piVar5 + 4) = piVar5[1];
        *(int *)piVar5[1] = *piVar5;
        *piVar5 = 0;
        piVar5[1] = 0;
      }
      sub_2110D4F4(piVar5);
    }
    sub_21107C10(*(int **)(piVar9[4] + 4),puStack_c,param_2,puStack_10,uStack_8);
  }
  _AAL_Unlock_0();
  pMem = param_3;
  if (piVar9 != (int *)0x0) {
    return param_3;
  }
LAB_21108067:
  AAL_SetError(s_Could_not_create_sound_object_2111458c);
  return pMem;
}

