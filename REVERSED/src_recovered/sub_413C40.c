/* Hand reconstruction of 0x00413C40: give the string-like object in ECX a buffer
   that can hold param_2 bytes.  The capacity is rounded up to the next 0x1F
   boundary, and when that allocation fails the original retries from its
   catch(...) with the exact size, so the fallback is written as a plain test on
   the returned pointer.  Ghidra stopped at the try boundary and turned the
   interior label loc_413CC0 into a separate function. */

void __thiscall sub_413C40(int param_1,uint param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  byte *buffer;
  byte *old_buffer;
  uint capacity;
  uint old_length;
  uint keep;
  uint allocation;
  uint uVar1;
  char cVar2;

  puStack_c = &LAB_0056d850;
  local_10 = ExceptionList;
  capacity = param_2 | 0x1f;
  if (0xfffffffd < capacity) {
    capacity = param_2;
  }
  allocation = capacity + 2;
  if ((int)allocation < 0) {
    allocation = 0;
  }
  buffer = (byte *)operator_new(allocation);
  if (buffer == (byte *)0x0) {
    capacity = param_2;
    allocation = capacity + 2;
    if ((int)allocation < 0) {
      allocation = 0;
    }
    buffer = (byte *)operator_new(allocation);
  }
  old_length = *(uint *)(param_1 + 8);
  if (old_length != 0) {
    keep = capacity < old_length ? capacity : old_length;
    old_buffer = *(byte **)(param_1 + 4);
    for (uVar1 = 0; uVar1 < keep; uVar1 = uVar1 + 1) {
      buffer[uVar1 + 1] = old_buffer[uVar1];
    }
  }
  old_buffer = *(byte **)(param_1 + 4);
  if (old_buffer != (byte *)0x0) {
    cVar2 = old_buffer[-1];
    if ((cVar2 != '\0') && (cVar2 != -1)) {
      old_buffer[-1] = cVar2 + -1;
    }
    else {
      sub_562941((int)(old_buffer + -1));
    }
  }
  *(uint *)(param_1 + 8) = 0;
  buffer = buffer + 1;
  *(byte **)(param_1 + 4) = buffer;
  buffer[-1] = 0;
  *(uint *)(param_1 + 0xc) = capacity;
  keep = capacity < old_length ? capacity : old_length;
  *(uint *)(param_1 + 8) = keep;
  buffer[keep] = 0;
  ExceptionList = local_10;
  return;
}
