/* __cfltcvt @ 2110de0a   81 bytes */

/* Library Function - Single Match
    __cfltcvt
   
   Library: Visual Studio 2003 Release */

errno_t __cdecl
__cfltcvt(double *arg,char *buffer,size_t sizeInBytes,int format,int precision,int caps)

{
  char *pcVar1;
  undefined1 *puVar2;
  
  if ((sizeInBytes == 0x65) || (sizeInBytes == 0x45)) {
    puVar2 = sub_2110DB43(arg,buffer,format,precision);
  }
  else {
    if (sizeInBytes == 0x66) {
      pcVar1 = sub_2110DC47(arg,buffer,format);
      return (errno_t)pcVar1;
    }
    puVar2 = (undefined1 *)sub_2110DD25(arg,buffer,format,precision);
  }
  return (errno_t)puVar2;
}

