/* sub_5644D3 @ 005644d3   288 bytes */

void * sub_5644D3(LPVOID param_1,uint param_2)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  LPVOID pvVar4;
  uint uVar5;
  
  if (param_1 == (LPVOID)0x0) {
    pvVar1 = _malloc(param_2);
  }
  else {
    if (param_2 == 0) {
      sub_5628BC(param_1);
    }
    else {
      do {
        if (param_2 < 0xffffffe1) {
          iVar2 = sub_565BEB(param_1);
          if (iVar2 == 0) {
            if (param_2 == 0) {
              param_2 = 1;
            }
            param_2 = param_2 + 0xf & 0xfffffff0;
            pvVar4 = HeapReAlloc(DAT_006db91c,0,param_1,param_2);
          }
          else {
            if (param_2 <= DAT_0057ca20) {
              iVar3 = sub_5663F6(iVar2,param_1,param_2);
              pvVar4 = param_1;
              if (iVar3 == 0) {
                pvVar4 = (LPVOID)sub_565F41(param_2);
                if (pvVar4 == (LPVOID)0x0) goto LAB_0056456c;
                uVar5 = *(int *)((int)param_1 + -4) - 1;
                if (param_2 <= uVar5) {
                  uVar5 = param_2;
                }
                sub_566D90(pvVar4,param_1,uVar5);
                sub_565C16(iVar2,param_1);
              }
              if (pvVar4 != (LPVOID)0x0) {
                return pvVar4;
              }
            }
LAB_0056456c:
            if (param_2 == 0) {
              param_2 = 1;
            }
            param_2 = param_2 + 0xf & 0xfffffff0;
            pvVar4 = HeapAlloc(DAT_006db91c,0,param_2);
            if (pvVar4 == (LPVOID)0x0) goto LAB_005645cf;
            uVar5 = *(int *)((int)param_1 + -4) - 1;
            if (param_2 <= uVar5) {
              uVar5 = param_2;
            }
            sub_566D90(pvVar4,param_1,uVar5);
            sub_565C16(iVar2,param_1);
          }
          if (pvVar4 != (LPVOID)0x0) {
            return pvVar4;
          }
        }
LAB_005645cf:
        if (DAT_006da40c == 0) {
          return (void *)0x0;
        }
        iVar2 = sub_5672AD(param_2);
      } while (iVar2 != 0);
    }
    pvVar1 = (void *)0x0;
  }
  return pvVar1;
}

