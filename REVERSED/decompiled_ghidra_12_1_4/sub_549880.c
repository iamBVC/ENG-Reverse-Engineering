/* sub_549880 @ 00549880   49 bytes */

undefined4 * sub_549880(int param_1,int param_2,char param_3,char param_4)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 0x74);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    if (((puVar1[3] == param_2) && (*(char *)(puVar1 + 0x1f) == param_3)) &&
       (*(char *)((int)puVar1 + 0x7d) == param_4)) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}

