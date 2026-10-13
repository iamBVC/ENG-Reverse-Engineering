/* The original thiscall constructor returns its incoming object in EAX. */
int sub_41BCB0(int object)
{
  *(unsigned int *)(object + 0x20) = 0;
  *(unsigned int *)(object + 0x24) = 0;
  return object;
}
