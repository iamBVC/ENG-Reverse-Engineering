/* sub_549710 @ 00549710   70 bytes */

void sub_549710(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 0x7c);
  if (puVar1 != (undefined4 *)0x0) {
    *(undefined4 *)(param_1 + 0x7c) = *puVar1;
    *puVar1 = 0;
    if (*(int *)(param_1 + 0x74) == 0) {
      *(undefined4 **)(param_1 + 0x74) = puVar1;
    }
    else {
      **(undefined4 **)(param_1 + 0x78) = puVar1;
    }
    *(undefined4 **)(param_1 + 0x78) = puVar1;
    *(undefined1 *)(puVar1 + 0x1f) = param_2;
    *(undefined1 *)((int)puVar1 + 0x7d) = param_4;
    *(undefined1 *)((int)puVar1 + 0x7a) = param_3;
    puVar1[0x23] = puVar1;
  }
  return;
}

