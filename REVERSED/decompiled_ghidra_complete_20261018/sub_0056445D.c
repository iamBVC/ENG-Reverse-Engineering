/* __cfltcvt @ 0056445d   81 bytes */

/* Library Function - Single Match
    __cfltcvt
   
   Library: Visual Studio 2003 Release */

errno_t __cdecl
__cfltcvt(double *arg,char *buffer,size_t sizeInBytes,int format,int precision,int caps)

{
  errno_t eVar1;
  
  if ((sizeInBytes == 0x65) || (sizeInBytes == 0x45)) {
    eVar1 = sub_564196(arg,buffer,format,precision);
  }
  else {
    if (sizeInBytes == 0x66) {
      eVar1 = sub_56429A(arg,buffer,format);
      return eVar1;
    }
    eVar1 = sub_564378(arg,buffer,format,precision);
  }
  return eVar1;
}

