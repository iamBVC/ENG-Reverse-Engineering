/* Recovered from 00419BD0: terminated parse fields and byte-indexed options. */
undefined4 sub_419BD0(int *device)
{
  char name[260];
  char field[5];
  char *payload;
  size_t length;
  unsigned int value;
  int *bindings;
  int *node;
  int index = 0;
  int offset = 0;
  int i;

  if (device == 0) {
    snprintf(name, sizeof name, "InputDevice %.16s", (char *)DAT_00582b50);
    bindings = &DAT_00584758;
  } else {
    snprintf(name, sizeof name, "InputDevice %.80s %.80s",
             (char *)(device + 0x34), (char *)(device + 0x20));
    bindings = (int *)device[0x1c];
    offset = 48;
  }
  payload = (char *)sub_405790(name, 0);
  if (payload == 0) return 0;
  length = strlen(payload);
  if (device != 0) {
    if (length < 48 || sscanf(payload, "X1:%08X Y1:%08X X2:%08X Y2:%08X ",
        device + 0x17, device + 0x18, device + 0x19, device + 0x1a) < 4) return 0;
  }
  for (i = 0; i < 14; ++i) {
    if (length < (size_t)(offset + i * 4 + 4)) return 0;
    memcpy(field, payload + offset + i * 4, 4);
    field[4] = 0;
    if (sscanf(field, "%04X", &value) < 1) return 0;
    bindings[i] = value;
  }
  if (device != 0) {
    index = 1;
    node = (int *)DAT_00582260[0];
    while ((*node != 0 || node[1] == 0) && node != device) {
      ++index;
      node = (int *)*node;
    }
  }
  value = 0x7f;
  if (length >= (size_t)(offset + 58)) {
    memcpy(field, payload + offset + 56, 2);
    field[2] = 0;
    if (sscanf(field, "%02X", &value) < 1) value = 0x7f;
  }
  ((unsigned char *)DAT_005fcf70)[index * 12 + 11] = (unsigned char)value;
  return 1;
}
