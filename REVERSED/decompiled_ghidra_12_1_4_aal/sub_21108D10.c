/* sub_21108D10 @ 21108d10   311 bytes */

void __fastcall sub_21108D10(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  
  sub_21109360(param_1,0,(LPCSTR)0x0,(int *)0x0,0);
  sub_21108FF0(param_1,0);
  puVar1 = (undefined4 *)param_1[1];
  if (puVar1 != (undefined4 *)0x0) {
    if (puVar1[0x203] != 0) {
      piVar2 = (int *)puVar1[1];
      while (piVar2 != (int *)0x0) {
        if (piVar2[2] != 0) {
          *(int *)(piVar2[2] + 0xc) = piVar2[3];
        }
        if (piVar2[3] != 0) {
          *(int *)(piVar2[3] + 8) = piVar2[2];
        }
        piVar2[5] = -1;
        if (*piVar2 != 0) {
          *(int *)(*piVar2 + 4) = piVar2[1];
        }
        if ((int *)piVar2[1] != (int *)0x0) {
          *(int *)piVar2[1] = *piVar2;
        }
        if ((int *)puVar1[1] == piVar2) {
          puVar1[1] = *piVar2;
        }
        if ((int *)puVar1[piVar2[4] + 3] == piVar2) {
          puVar1[piVar2[4] + 3] = piVar2[2];
        }
        *piVar2 = puVar1[2];
        piVar2[1] = 0;
        if (puVar1[2] != 0) {
          *(int **)(puVar1[2] + 4) = piVar2;
        }
        puVar1[2] = piVar2;
        piVar2 = (int *)puVar1[1];
      }
      *puVar1 = 0;
      sub_2110D4F4((LPVOID)puVar1[0x203]);
      puVar1[0x203] = 0;
    }
    sub_2110D4F4(puVar1);
    param_1[1] = 0;
  }
  puVar1 = (undefined4 *)*param_1;
  if (puVar1 != (undefined4 *)0x0) {
    if (puVar1[3] != 0) {
      piVar2 = (int *)puVar1[1];
      while (piVar2 != (int *)0x0) {
        piVar2[2] = -1;
        if (*piVar2 != 0) {
          *(int *)(*piVar2 + 4) = piVar2[1];
        }
        if ((int *)piVar2[1] != (int *)0x0) {
          *(int *)piVar2[1] = *piVar2;
        }
        if ((int *)puVar1[1] == piVar2) {
          puVar1[1] = *piVar2;
        }
        *piVar2 = puVar1[2];
        piVar2[1] = 0;
        if (puVar1[2] != 0) {
          *(int **)(puVar1[2] + 4) = piVar2;
        }
        puVar1[2] = piVar2;
        piVar2 = (int *)puVar1[1];
      }
      *puVar1 = 0;
      sub_2110D4F4((LPVOID)puVar1[3]);
    }
    sub_2110D4F4(puVar1);
    *param_1 = 0;
  }
  return;
}

