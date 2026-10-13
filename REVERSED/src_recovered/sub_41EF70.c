/* IAMMultiMediaStream setup at 0041EF70, with original stdcall argument counts. */
HRESULT sub_41EF70(undefined4 filename, undefined4 draw, undefined4 *output)
{
  WCHAR wide_path[260];
  int *stream = 0;
  HRESULT result;
  *output = 0;
  result = CoCreateInstance((IID *)DAT_0056e5ec, 0, 1, (IID *)DAT_0056e5fc, (void **)&stream);
  DAT_005865e0 = stream;
  if (SUCCEEDED(result)) {
    result = (**(groove_com4 **)(*stream + 0x30))((UINT_PTR)stream, 0, 1, 0);
    if (SUCCEEDED(result)) {
      result = (**(groove_com5 **)(*stream + 0x3c))((UINT_PTR)stream, draw, (UINT_PTR)DAT_0056e5cc, 0, 0);
      if (SUCCEEDED(result)) {
        (**(groove_com5 **)(*stream + 0x3c))((UINT_PTR)stream, 0, (UINT_PTR)DAT_0056e5bc, 1, 0);
        if (MultiByteToWideChar(0, 0, (char *)filename, -1, wide_path, 260) == 0)
          result = HRESULT_FROM_WIN32(GetLastError());
        else
          result = (**(groove_com3 **)(*stream + 0x40))((UINT_PTR)stream, (UINT_PTR)wide_path, 0);
        if (SUCCEEDED(result)) {
          *output = (unsigned int)stream;
          (**(groove_com1 **)(*stream + 4))((UINT_PTR)stream);
        }
      }
    }
    (**(groove_com1 **)(*stream + 8))((UINT_PTR)stream);
    DAT_005865e0 = 0;
  }
  fprintf(stderr, "[movie] stream setup hr=%08lx\n", (unsigned long)result);
  fflush(stderr);
  return result;
}
