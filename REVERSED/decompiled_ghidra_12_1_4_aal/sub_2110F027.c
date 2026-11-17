/* sub_2110F027 @ 2110f027   53 bytes */

uint __thiscall sub_2110F027(void *this,uint param_1,uint param_2)

{
  uint uVar1;
  undefined2 in_FPUControlWord;
  undefined4 local_8;
  
  local_8 = CONCAT22((short)((uint)this >> 0x10),in_FPUControlWord);
  uVar1 = sub_2110F072(local_8);
  uVar1 = uVar1 & ~param_2 | param_1 & param_2;
  sub_2110F104(uVar1);
  return uVar1;
}

