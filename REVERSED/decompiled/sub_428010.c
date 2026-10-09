/* sub_428010 @ 00428010   170 bytes */

void sub_428010(int param_1)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  byte bVar5;
  char cVar6;
  uint uVar7;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  uVar1 = *(uint *)(param_1 + 0x38);
  bVar2 = (byte)(uVar1 >> 0x18) & 0x7f;
  local_c = (uint)bVar2;
  uVar7 = 0x80 - local_c;
  bVar5 = (byte)(uVar1 >> 8);
  local_8 = (uint)bVar5;
  bVar3 = (byte)(uVar1 >> 0x10);
  local_4 = (uint)bVar3;
  if ((uVar1 & 0xff) < uVar7) {
    local_c = (uint)(byte)((char)uVar1 + bVar2);
  }
  else {
    local_c = 0x80;
  }
  if (local_8 < uVar7) {
    cVar6 = bVar5 + bVar2;
  }
  else {
    cVar6 = -0x80;
  }
  if (local_4 < uVar7) {
    cVar4 = bVar3 + bVar2;
  }
  else {
    cVar4 = -0x80;
  }
  *(uint *)(param_1 + 0x38) = (uint)CONCAT11(cVar4,cVar6) << 8 | local_c | uVar1 & 0xff000000;
  return;
}

