/* Recovered from 00419A60: one contiguous settings payload, not split locals. */
undefined4 sub_419A60(int *device)
{
  char name[260];
  char payload[112] = {0};
  int *bindings;
  int *node;
  unsigned int option;
  int index = 0;
  int offset = 0;
  int i;

  if (device == 0) {
    snprintf(name, sizeof name, "InputDevice %.16s", (char *)DAT_00582b50);
    bindings = &DAT_00584758;
  } else {
    snprintf(name, sizeof name, "InputDevice %.80s %.80s",
             (char *)(device + 0x34), (char *)(device + 0x20));
    snprintf(payload, sizeof payload, "X1:%08X Y1:%08X X2:%08X Y2:%08X ",
             device[0x17], device[0x18], device[0x19], device[0x1a]);
    offset = 48;
    bindings = (int *)device[0x1c];
    index = 1;
    node = (int *)DAT_00582260[0];
    while ((*node != 0 || node[1] == 0) && node != device) {
      ++index;
      node = (int *)*node;
    }
  }
  for (i = 0; i < 14; ++i) {
    if (device != 0 && bindings[i] > 0xffff) return 0;
    snprintf(payload + offset + i * 4, sizeof payload - offset - i * 4,
             "%04X", (unsigned int)bindings[i]);
  }
  /* hMem is a pointer to DWORDs in the export; the assembly uses BYTE offsets. */
  option = ((unsigned char *)DAT_005fcf70)[index * 12 + 11];
  snprintf(payload + offset + 56, sizeof payload - offset - 56, "%02X", option);
  sub_405800(name, payload);
  return 1;
}
