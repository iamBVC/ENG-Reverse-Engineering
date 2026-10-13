/* The original allocates one contiguous 0x14-byte file header on the stack.
   Independent decompiler locals cannot be used as a fread buffer. */
undefined4 sub_40D3B0(undefined4 param_1,undefined4 param_2)
{
  uint header[5];
  void *file;
  void *packed;

  file = (void *)sub_562AEE(param_1, &DAT_00570350);
  if (file != 0) {
    sub_5629E6(header, sizeof header, 1, file);
    if (header[0] == 0x89af9817 && header[1] == 0x12d142fe) {
      packed = _malloc(header[4]);
      if (packed != 0) {
        sub_5629E6(packed, header[4], 1, file);
        sub_40D300(packed, param_2, header[3]);
        sub_5628BC(packed);
        return header[3];
      }
    }
    sub_5628EB(file);
  }
  return 0;
}
