/* The original uses two opcode tables: 69 handlers with an immediate argument,
   followed by 365 handlers that receive only the actor. */

void sub_54D180(int *param_1)
{
  uint instruction, opcode;
  while ((*(byte *)(param_1 + 0x3a) & 0x12) == 0) {
    instruction = *(uint *)*param_1;
    *param_1 += 4;
    opcode = instruction & 0xffff;
    if (opcode < 69)
      (*PTR_sub_426500_005796bc_storage[opcode])(param_1, (int)(short)(instruction >> 16));
    else
      (*DAT_00579108_storage[opcode - 69])(param_1);
  }
}
