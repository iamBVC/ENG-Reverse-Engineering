/* sub_21104A10 @ 21104a10   474 bytes */

void __thiscall sub_21104A10(void *this,int param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  
  if ((*(byte *)((int)this + 0xcc) & 0x20) == 0) {
    LOCK();
    DAT_211155e0 = DAT_211155e0 + 1;
    UNLOCK();
    _AAL_UnregisterTimer_4(*(int *)((int)this + 0x80));
    *(undefined4 *)((int)this + 0x80) = 0xffffffff;
    if ((*(byte *)((int)this + 0xcc) & 0x20) == 0) {
      sub_21105500((int)this);
    }
    sub_211053E0((int)this);
    if (param_1 == 0) {
      if ((*(int *)((int)this + 0x7c) != 0) && (iVar3 = 0, 0 < *(int *)((int)this + 0x78))) {
        param_1 = 0;
        do {
          pvVar2 = (void *)(param_1 + *(int *)((int)this + 0x7c));
          *(undefined4 *)((int)pvVar2 + 0x58) = 0;
          *(undefined4 *)((int)pvVar2 + 0xc) = 0;
          *(undefined4 *)((int)pvVar2 + 0x118) = 0;
          *(undefined4 *)((int)pvVar2 + 0x18) = 0;
          sub_2110A200(pvVar2,4,0,0);
          iVar3 = iVar3 + 1;
          param_1 = param_1 + 0x11c;
        } while (iVar3 < *(int *)((int)this + 0x78));
      }
      if (*(LPVOID *)((int)this + 0x60) != (LPVOID)0x0) {
        sub_2110D4F4(*(LPVOID *)((int)this + 0x60));
        *(undefined4 *)((int)this + 0x60) = 0;
      }
      if (*(LPVOID *)((int)this + 0x68) != (LPVOID)0x0) {
        sub_2110D4F4(*(LPVOID *)((int)this + 0x68));
        *(undefined4 *)((int)this + 0x68) = 0;
      }
      if (*(LPVOID *)((int)this + 0x74) != (LPVOID)0x0) {
        sub_2110D4F4(*(LPVOID *)((int)this + 0x74));
        *(undefined4 *)((int)this + 0x74) = 0;
      }
    }
    else {
      if ((*(int *)((int)this + 0x7c) != 0) && (iVar3 = 0, 0 < *(int *)((int)this + 0x78))) {
        param_1 = 0;
        do {
          pvVar2 = (void *)(param_1 + *(int *)((int)this + 0x7c));
          *(undefined4 *)((int)pvVar2 + 0x58) = 0;
          *(undefined4 *)((int)pvVar2 + 0xc) = 0;
          *(undefined4 *)((int)pvVar2 + 0x118) = 0;
          *(undefined4 *)((int)pvVar2 + 0x18) = 0;
          sub_2110A200(pvVar2,4,0,0);
          iVar3 = iVar3 + 1;
          param_1 = param_1 + 0x11c;
        } while (iVar3 < *(int *)((int)this + 0x78));
      }
      iVar3 = *(int *)((int)this + 0x7c);
      if (iVar3 != 0) {
        param_1 = *(int *)(iVar3 + -4);
        piVar4 = (int *)(iVar3 + param_1 * 0x11c);
        if (-1 < param_1 + -1) {
          do {
            piVar5 = piVar4 + -0x47;
            sub_21105570(piVar5);
            sub_21103610(piVar4 + -0x23,0x24,3,&DAT_211050a0);
            if (*piVar5 != 0) {
              *(int *)(*piVar5 + 4) = piVar4[-0x46];
              *(int *)piVar4[-0x46] = *piVar5;
              *piVar5 = 0;
              piVar4[-0x46] = 0;
            }
            param_1 = param_1 + -1;
            piVar4 = piVar5;
          } while (param_1 != 0);
        }
        sub_2110D4F4((LPVOID)(iVar3 + -4));
        *(undefined4 *)((int)this + 0x7c) = 0;
      }
      if (*(int *)((int)this + 0xb0) != 0) {
        sub_2110D4F4((LPVOID)(*(int *)((int)this + 0xb0) + -4));
        *(undefined4 *)((int)this + 0xb0) = 0;
      }
      puVar1 = _AAL_GetDeviceInfo_8(1,*(int *)((int)this + 0x44));
      if (puVar1 != (undefined4 *)0x0) {
        puVar1[5] = 0;
      }
    }
    *(uint *)((int)this + 0xcc) = *(uint *)((int)this + 0xcc) | 0x20;
    LOCK();
    DAT_211155e0 = DAT_211155e0 + -1;
    UNLOCK();
  }
  return;
}

