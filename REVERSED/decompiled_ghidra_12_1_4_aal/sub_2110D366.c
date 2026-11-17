/* sub_2110D366 @ 2110d366   147 bytes */

void sub_2110D366(undefined8 *param_1,int *param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  
  if (param_3 != 0) {
    piVar3 = (int *)(param_3 + (int)param_2);
    if (DAT_21114890 != 0) {
      for (uVar1 = param_3 >> 4; uVar1 != 0; uVar1 = uVar1 - 1) {
        uVar5 = packssdw(CONCAT44((int)((longlong)*(undefined8 *)param_2 >> 0x2b),
                                  (int)*(undefined8 *)param_2 >> 0xb),
                         CONCAT44((int)((longlong)*(undefined8 *)(param_2 + 2) >> 0x2b),
                                  (int)*(undefined8 *)(param_2 + 2) >> 0xb));
        *param_1 = uVar5;
        param_1 = param_1 + 1;
        param_2 = param_2 + 4;
      }
    }
    while (puVar4 = param_1, param_2 < piVar3) {
      while( true ) {
        param_1 = (undefined8 *)((int)puVar4 + 2);
        iVar2 = *param_2 >> 0xb;
        param_2 = param_2 + 1;
        if (0x7fff < iVar2) break;
        if (iVar2 < -0x8000) {
          *(undefined2 *)puVar4 = 0x8000;
        }
        else {
          *(short *)puVar4 = (short)iVar2;
        }
        puVar4 = param_1;
        if (piVar3 <= param_2) {
          return;
        }
      }
      *(undefined2 *)puVar4 = 0x7fff;
    }
  }
  return;
}

