/* Original search order: executable directory, HDPath, CDPath, CD-ROM drives. */
undefined4 *sub_415690(char *directory, char *filename)
{
  char root[260];
  char *separator;
  const char *base;
  size_t length;
  DWORD copied;
  int attempt;
  int count;

  if (filename == 0) return 0;
  for (attempt = 0; attempt < 29; ++attempt) {
    if (attempt == 0) {
      copied = GetModuleFileNameA(0, root, sizeof root);
      if (copied == 0 || copied >= sizeof root) continue;
      separator = strrchr(root, '\\');
      if (separator == 0) continue;
      separator[1] = 0;
      base = root;
    } else if (attempt < 3) {
      base = (char *)sub_405790(attempt == 1 ? s_HDPath_00571d94 : s_CDPath_00571d8c,
                               groove_default_path);
      if (base == 0) continue;
    } else {
      snprintf(root, sizeof root, "%c:\\", 'A' + attempt - 3);
      if (GetDriveTypeA(root) != DRIVE_CDROM) continue;
      base = root;
    }
    length = strlen(base);
    count = snprintf((char *)DAT_00583748, sizeof DAT_00583748, "%s%s%s%s%s", base,
                     length != 0 && base[length - 1] != '\\' ? "\\" : "",
                     directory != 0 ? directory : "", directory != 0 ? "\\" : "", filename);
    if (count < 0 || count >= sizeof DAT_00583748) continue;
    if (GetFileAttributesA((char *)DAT_00583748) != INVALID_FILE_ATTRIBUTES)
      return (undefined4 *)DAT_00583748;
  }
  return 0;
}
