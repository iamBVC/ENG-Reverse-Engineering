/* The original leaves the allocator's pointer in EAX for its caller. */
int sub_41EE40(int param_1)
{
  return (int)sub_41AE20((int)(param_1 + 3 + (param_1 + 3 >> 0x1f & 3U)) >> 2);
}
