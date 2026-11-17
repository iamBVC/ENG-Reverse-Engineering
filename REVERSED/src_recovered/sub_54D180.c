/* The original uses two opcode tables: 69 handlers with an immediate argument,
   followed by 365 handlers that receive only the actor. */
#include <stdio.h>

void sub_54D180(int *param_1)
{
  uint instruction, opcode;
  static unsigned int target_write_trace_count;
  uint history_instruction[16] = {0};
  uint history_top[16] = {0};
  uint history_depth[16] = {0};
  uint history_value[16] = {0};
  unsigned int history_next = 0;
  unsigned int history_count = 0;
  while ((*(byte *)(param_1 + 0x3a) & 0x12) == 0) {
    int before_x = DAT_006d9d80;
    int before_y = DAT_006d9d84;
    int before_z = DAT_006d9d88;
    instruction = *(uint *)*param_1;
    *param_1 += 4;
    opcode = instruction & 0xffff;
    if (opcode == 64 && (instruction >> 16) >= 0x3a &&
        (instruction >> 16) <= 0x3c) {
      unsigned char *actor_bytes = (unsigned char *)param_1;
      uint stack_top = *(uint *)(actor_bytes + 0x104);
      uint stack_depth = *(uint *)(actor_bytes + 0x108);
      fprintf(stderr,
              "[camera-script-arg] actor=%p key=%u ip=%p stack-top=%08x depth=%u peek=%08x\n",
              (void *)param_1, instruction >> 16,
              (void *)(uintptr_t)(*param_1 - 4), stack_top, stack_depth,
              *(uint *)(stack_top - 4));
      {
        uint *script_words = (uint *)(uintptr_t)(*param_1 - 4);
        int word_index;
        for (word_index = -12; word_index <= 0; ++word_index) {
          fprintf(stderr, "[camera-script-word] key=%u offset=%d value=%08x\n",
                  instruction >> 16, word_index * 4,
                  script_words[word_index]);
        }
      }
      fflush(stderr);
    }
    if (opcode < 69)
      (*PTR_sub_426500_005796bc_storage[opcode])(param_1, (int)(short)(instruction >> 16));
    else
      (*DAT_00579108_storage[opcode - 69])(param_1);
    {
      unsigned char *actor_bytes = (unsigned char *)param_1;
      uint stack_top = *(uint *)(actor_bytes + 0x104);
      history_instruction[history_next] = instruction;
      history_top[history_next] = stack_top;
      history_depth[history_next] = *(uint *)(actor_bytes + 0x108);
      history_value[history_next] = stack_top >= 4 ? *(uint *)(stack_top - 4) : 0;
      history_next = (history_next + 1) & 15;
      if (history_count < 16) ++history_count;
      if (opcode == 64 && (instruction >> 16) == 0x3b) {
        unsigned int history_i;
        for (history_i = 0; history_i < history_count; ++history_i) {
          unsigned int slot = (history_next - history_count + history_i) & 15;
          fprintf(stderr,
                  "[camera-script-history] actor=%p i=%u ins=%08x top=%08x depth=%u next=%08x\n",
                  (void *)param_1, history_i, history_instruction[slot],
                  history_top[slot], history_depth[slot], history_value[slot]);
        }
        fflush(stderr);
      }
    }
    if ((before_x != DAT_006d9d80 || before_y != DAT_006d9d84 ||
         before_z != DAT_006d9d88) && target_write_trace_count++ < 16) {
      fprintf(stderr,
              "[camera-script-write] actor=%p opcode=%u instruction=%08x handler=%p before=%d/%d/%d after=%d/%d/%d\n",
              (void *)param_1, opcode, instruction,
              opcode < 69 ? (void *)PTR_sub_426500_005796bc_storage[opcode] :
                            (void *)DAT_00579108_storage[opcode - 69],
              before_x, before_y, before_z,
              DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
      fflush(stderr);
    }
  }
}
