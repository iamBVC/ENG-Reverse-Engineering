/* MSVC 6 atof entry at 0056286F; use the linked CRT's parser and workspace. */
float10 sub_56286F(byte *text)
{
  return (float10)strtod((char *)text, 0);
}
