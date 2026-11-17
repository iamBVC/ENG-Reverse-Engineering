/* sub_548A20 @ 00548a20   314 bytes */

int sub_548A20(int *param_1,int param_2)

{
  undefined1 uVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined1 local_10 [8];
  char local_8;
  byte local_6;
  char local_5;
  char local_4;
  
  sub_548C90(param_1);
  *(undefined1 *)((int)param_1 + 0x4a) = 0;
  *(undefined2 *)(param_1 + 0x12) = 0;
  param_1[0x11] = 0;
  *(undefined1 *)((int)param_1 + 0x4b) = 0;
  param_1[0xd] = param_2 + 2;
  uVar1 = *(undefined1 *)(param_2 + 2);
  param_1[0xd] = param_2 + 3;
  param_1[0x10] = (int)CONCAT11(uVar1,*(undefined1 *)(param_2 + 3));
  param_1[0xd] = param_2 + 9;
  bVar2 = *(byte *)(param_2 + 9);
  param_1[0xd] = param_2 + 10;
  bVar3 = *(byte *)(param_2 + 10);
  param_1[0xd] = param_2 + 0xb;
  bVar4 = *(byte *)(param_2 + 0xb);
  param_1[0xd] = param_2 + 0xc;
  bVar5 = *(byte *)(param_2 + 0xc);
  param_1[3] = 0;
  param_2 = param_2 + 0xd;
  param_1[0xd] = param_2;
  param_1[0xf] = (uint)bVar2 << 0x18 | (uint)bVar3 << 0x10 | (uint)bVar4 << 8 | (uint)bVar5;
  *param_1 = param_2;
  param_1[1] = param_2;
  *(undefined2 *)(param_1 + 4) = 0;
  param_1[2] = 0;
  param_1[5] = param_2;
  *(short *)(param_1 + 8) = (short)param_1[0x12];
  param_1[6] = param_1[0x11];
  param_1[7] = 0;
  do {
    iVar6 = param_1[0xd];
    iVar7 = param_1[0x12];
    iVar8 = param_1[0x11];
    sub_548B60(param_1,local_10);
    if (local_8 == '\x10') {
      if (local_6 == 0x2f) {
        iVar8 = 0x7fffffff;
        param_1[0x11] = 0x7fffffff;
      }
    }
    else if (((local_6 & 0xf0) == 0xb0) && (local_5 == 'c')) {
      if (local_4 == '\x14') {
        param_1[5] = param_1[0xd];
        *(short *)(param_1 + 8) = (short)param_1[0x12];
        param_1[6] = param_1[0x11];
      }
      else if (local_4 == '\x1e') {
        param_1[0x11] = 0x7fffffff;
      }
    }
  } while (param_1[0x11] < 0x7fffffff);
  param_1[9] = iVar6;
  *(short *)(param_1 + 0xc) = (short)iVar7;
  param_1[10] = iVar8;
  param_1[0xb] = iVar8;
  param_1[0xd] = param_1[1];
  *(short *)(param_1 + 0x12) = (short)param_1[4];
  param_1[0x11] = param_1[2];
  return param_1[1] + param_1[0xf];
}

