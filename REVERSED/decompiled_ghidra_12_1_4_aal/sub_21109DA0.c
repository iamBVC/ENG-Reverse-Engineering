/* sub_21109DA0 @ 21109da0   353 bytes */

undefined4 sub_21109DA0(int *param_1)

{
  int *piVar1;
  int *piVar2;
  HANDLE hProcess;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined8 uVar8;
  DWORD DVar9;
  
  piVar2 = param_1;
  DVar9 = 0x80;
  hProcess = GetCurrentProcess();
  SetPriorityClass(hProcess,DVar9);
  DVar9 = WaitForSingleObject((HANDLE)param_1[2],8);
  while (DVar9 == 0x102) {
    DVar9 = SuspendThread(DAT_211155bc);
    iVar5 = DAT_211155e8;
    if (DVar9 != 0xffffffff) {
      LOCK();
      DAT_211155e8 = DAT_211155e8 + 1;
      UNLOCK();
      iVar7 = 0;
      if ((DAT_211155c8 == 0) && (DAT_211155e8 == 1)) {
        LOCK();
        DAT_211155cc = DAT_211155cc + 1;
        UNLOCK();
        uVar8 = sub_211010C0(1);
        if (piVar2[3] == 0) {
          uVar6 = 5000;
        }
        else {
          uVar6 = (int)uVar8 * 1000 + piVar2[3] * -1000;
          if (100000 < uVar6) {
            uVar6 = 100000;
          }
        }
        piVar2[3] = (int)uVar8;
        param_1 = (int *)0x0;
        if (0 < piVar2[1]) {
          do {
            if (*(int *)(*piVar2 + iVar7) != 0) {
              piVar1 = (int *)(*piVar2 + iVar7 + 4);
              *piVar1 = *piVar1 + uVar6;
              iVar5 = iVar7 + *piVar2;
              uVar3 = *(uint *)(iVar5 + 4);
              uVar4 = *(uint *)(iVar5 + 8);
              if (uVar4 <= uVar3) {
                do {
                  *(uint *)(iVar5 + 4) = uVar3 - uVar4;
                  (**(code **)(iVar7 + *piVar2 + 0x10))(*(undefined4 *)(iVar7 + 0xc + *piVar2));
                  iVar5 = *piVar2 + iVar7;
                  uVar3 = *(uint *)(iVar5 + 4);
                  uVar4 = *(uint *)(iVar5 + 8);
                } while (uVar4 <= uVar3);
              }
            }
            param_1 = (int *)((int)param_1 + 1);
            iVar7 = iVar7 + 0x14;
          } while ((int)param_1 < piVar2[1]);
        }
        LOCK();
        DAT_211155cc = DAT_211155cc + -1;
        UNLOCK();
        LOCK();
        DAT_211155e8 = DAT_211155e8 + -1;
        UNLOCK();
      }
      else {
        LOCK();
        UNLOCK();
        DAT_211155e8 = iVar5;
      }
      ResumeThread(DAT_211155bc);
    }
    DVar9 = WaitForSingleObject((HANDLE)piVar2[2],8);
  }
  OutputDebugStringA(s_Timer_Thread_Terminating_21114664);
  return 0;
}

