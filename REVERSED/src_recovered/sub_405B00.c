/* Registry numeric preferences at 00405B00: DWORD or textual float values. */
undefined4 sub_405B00(float *output, undefined4 root, DWORD path, LPCSTR name)
{
  unsigned char data[2049];
  DWORD size = 2048;
  DWORD type;
  DWORD number;
  HKEY key;
  LSTATUS status;
  undefined4 result = 0;

  key = (HKEY)sub_405960(root, path, 1);
  if (key == 0) return 0;
  status = RegQueryValueExA(key, name, 0, &type, data, &size);
  if (status == ERROR_SUCCESS && size <= 2048) {
    if (type == REG_DWORD) {
      if (size == sizeof number) {
        memcpy(&number, data, sizeof number);
        *output = (float)number;
        result = 1;
      }
    } else {
      /* Win32 does not guarantee that a queried string includes a terminator. */
      data[size] = 0;
      *output = (float)strtod((char *)data, 0);
      result = 1;
    }
  }
  RegCloseKey(key);
  return result;
}
