/* Original groove.exe 0041F0C0-0041F58F: present an intro movie stream.
 * The Ghidra export loses the third argument and several COM object locals.
 * Offsets, argument order, descriptor fields and exit paths follow the IDA
 * listing of the original routine. All COM methods use stdcall on Win32.
 */
int sub_41F0C0(int *draw, int *target, int *stream)
{
  static const GUID surface4_iid =
      {0x0b2b8630, 0xad35, 0x11d0, {0x8e, 0xa6, 0, 0x60, 0x97, 0x97, 0xea, 0x5b}};
  int *video_stream = 0;
  int *dd_stream = 0;
  int *sample = 0;
  int *surface = 0;
  int *surface4 = 0;
  int *offscreen = 0;
  DWORD format[27] = {0};           /* 0x6c-byte DDSURFACEDESC */
  DWORD target_desc[31] = {0};      /* 0x7c-byte DDSURFACEDESC2 */
  DWORD offscreen_desc[31] = {0};   /* 0x7c-byte DDSURFACEDESC2 */
  DWORD blt_fx[25] = {0};           /* 0x64-byte DDBLTFX */
  DWORD format_flags;
  RECT dest_rect;
  RECT source_rect = {0, 0, 320, 240};
  HCURSOR previous_cursor;
  int use_target = 0;
  int result;

  DAT_005865e4 = 1;
  dest_rect.left = 0;
  dest_rect.top = 0;
  dest_rect.right = DAT_00583374;
  dest_rect.bottom = DAT_00583378;
  if (DAT_00583374 > 320) {
    dest_rect.left = DAT_00583374 / 8;
    dest_rect.right -= dest_rect.left;
    dest_rect.top = DAT_00583378 / 8;
    dest_rect.bottom -= dest_rect.top;
  }

  target_desc[0] = sizeof target_desc;
  (**(groove_com2 **)(*target + 0x58))((UINT_PTR)target, (UINT_PTR)target_desc);

  result = (**(groove_com3 **)(*stream + 0x10))
      ((UINT_PTR)stream, (UINT_PTR)DAT_0056e5cc, (UINT_PTR)&video_stream);
  if (result < 0) {
    sub_414600(s_pMMStream__GetMediaStream_MSPID__00572a54, result);
    goto cleanup;
  }

  result = (**(groove_com3 **)(*video_stream))
      ((UINT_PTR)video_stream, (UINT_PTR)DAT_0056e5dc, (UINT_PTR)&dd_stream);
  if (result < 0) {
    sub_414600(s_pPrimaryVidStream__QueryInterfac_005729e0, result);
    goto cleanup;
  }

  format[0] = sizeof format;
  (**(groove_com5 **)(*dd_stream + 0x24))
      ((UINT_PTR)dd_stream, (UINT_PTR)format, (UINT_PTR)&format_flags, 0, 0);
  result = (**(groove_com5 **)(*dd_stream + 0x34))
      ((UINT_PTR)dd_stream, 0, 0, 0, (UINT_PTR)&sample);
  if (result != 0) {
    if (format[21] == 24) {
      format[1] |= 0x1000;
      format[21] = 32;
      (**(groove_com3 **)(*dd_stream + 0x28))
          ((UINT_PTR)dd_stream, (UINT_PTR)format, (UINT_PTR)format_flags);
    }
    result = (**(groove_com5 **)(*dd_stream + 0x34))
        ((UINT_PTR)dd_stream, 0, 0, 0, (UINT_PTR)&sample);
    if (result < 0) {
      sub_414600(s_pDDStream__CreateSample_NULL__NU_00572990, result);
      goto cleanup;
    }
  }

  offscreen_desc[0] = sizeof offscreen_desc;
  offscreen_desc[1] = 0x1007;
  offscreen_desc[2] = 240;
  offscreen_desc[3] = 320;
  offscreen_desc[26] = 0x4080;
  blt_fx[0] = sizeof blt_fx;
  result = (**(groove_com4 **)(*draw + 0x18))
      ((UINT_PTR)draw, (UINT_PTR)offscreen_desc, (UINT_PTR)&offscreen, 0);
  if (result != 0) {
    memcpy((char *)offscreen_desc + 0x48, (char *)format + 0x48, 0x20);
    result = (**(groove_com4 **)(*draw + 0x18))
        ((UINT_PTR)draw, (UINT_PTR)offscreen_desc, (UINT_PTR)&offscreen, 0);
    if (result != 0) {
      use_target = 1;
    }
  }
  if (!use_target) {
    (**(groove_com6 **)(*offscreen + 0x14))
        ((UINT_PTR)offscreen, 0, 0, 0, 0x1000400, (UINT_PTR)blt_fx);
    (**(groove_com3 **)(*draw + 0x58))((UINT_PTR)draw, 1, 0);
    result = (**(groove_com6 **)(*offscreen + 0x84))
        ((UINT_PTR)offscreen, 0, (UINT_PTR)target, (UINT_PTR)&dest_rect, 0x4000, 0);
    if (result != 0) {
      use_target = 1;
      if (offscreen) {
        (**(groove_com1 **)(*offscreen + 8))((UINT_PTR)offscreen);
      }
    }
  }

  result = (**(groove_com3 **)(*sample + 0x20))
      ((UINT_PTR)sample, (UINT_PTR)&surface, (UINT_PTR)&source_rect);
  if (result < 0) {
    sub_414600(s_pSample__GetSurface__pSurface____00572948, result);
    goto cleanup;
  }

  result = (**(groove_com3 **)(*surface))
      ((UINT_PTR)surface, (UINT_PTR)&surface4_iid, (UINT_PTR)&surface4);
  if (result < 0) {
    sub_414600(s_pSurface__QueryInterface_IID_IDi_005728e0, result);
    goto cleanup;
  }

  result = (**(groove_com2 **)(*stream + 0x1c))((UINT_PTR)stream, 1);
  if (result < 0) {
    sub_414600(s_pMMStream__SetState_STREAMSTATE__0057289c, result);
    goto cleanup;
  }

  previous_cursor = SetCursor(0);
  (**(groove_com6 **)(*target + 0x14))
      ((UINT_PTR)target, 0, 0, 0, 0x1000400, (UINT_PTR)blt_fx);
  DAT_005865e8 = 0;
  for (;;) {
    int update_result = (**(groove_com5 **)(*sample + 0x18))
        ((UINT_PTR)sample, 2, 0, 0, 0);
    if (update_result != 0) {
      if (result == 0) DAT_005865e4 = 0;
      break;
    }
    if (use_target) {
      result = (**(groove_com6 **)(*target + 0x14))
          ((UINT_PTR)target, (UINT_PTR)&dest_rect, (UINT_PTR)surface4,
           (UINT_PTR)&source_rect, 0x1000000, 0);
    } else {
      result = (**(groove_com6 **)(*offscreen + 0x14))
          ((UINT_PTR)offscreen, 0, (UINT_PTR)surface4, 0, 0x1000000, 0);
    }
    if (result != 0) break;
    sub_40F060(PTR_DAT_005724dc + 0x18, PTR_DAT_005724dc + 0x118);
    if (PTR_DAT_005724dc[0x19] & 0x80) {
      DAT_005865e8 = 1;
      DAT_005865e4 = 0;
      break;
    }
  }

  if (!use_target) {
    (**(groove_com6 **)(*offscreen + 0x84))
        ((UINT_PTR)offscreen, 0, (UINT_PTR)target, (UINT_PTR)&dest_rect, 0x200, 0);
  }
  result = (**(groove_com2 **)(*stream + 0x1c))((UINT_PTR)stream, 0);
  if (result < 0) {
    sub_414600(s_pMMStream__SetState_STREAMSTATE__00572854, result);
    goto cleanup;
  }
  (**(groove_com6 **)(*target + 0x14))
      ((UINT_PTR)target, 0, 0, 0, 0x1000400, (UINT_PTR)blt_fx);
  SetCursor(previous_cursor);

cleanup:
  if (video_stream) (**(groove_com1 **)(*video_stream + 8))((UINT_PTR)video_stream);
  if (dd_stream) (**(groove_com1 **)(*dd_stream + 8))((UINT_PTR)dd_stream);
  if (sample) (**(groove_com1 **)(*sample + 8))((UINT_PTR)sample);
  if (surface) (**(groove_com1 **)(*surface + 8))((UINT_PTR)surface);
  if (offscreen) (**(groove_com1 **)(*offscreen + 8))((UINT_PTR)offscreen);
  return result;
}
