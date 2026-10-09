/* gr_map.c - helpers extracted from the MAP loader `sub_42AC50`.
 *
 * These are behavioural ports, not 1:1 counterparts: in the original the logic
 * is inlined into the loader, so there is no separate function to match byte
 * for byte.  They exist so the loader can be rebuilt in readable pieces and
 * tested against the Python reference implementation (eng_wad/).
 */
#include "groove.h"

/* sub_42AC50, spatial-hash insertion for one tile (asm lines 62115-62127):
 *
 *     fld  [pos_z]        ; u32[2] of the record, which is the NEGATED z
 *     fadd flt_56E158     ; +0.5
 *     __ftol              ; (int)(pos_z + 0.5)
 *     imul grid_width
 *     fld  [pos_x]        ; u32[0]
 *     fsub flt_56E158     ; -0.5
 *     __ftol              ; (int)(pos_x - 0.5)
 *     sub                 ; (int)(pos_x - 0.5) - grid_width * (int)(pos_z + 0.5)
 *
 * `pos_z` is passed exactly as stored in the file, i.e. already negated.
 */
int groove_tile_cell_index(float pos_x, float pos_z, int grid_width)
{
    return (int)(pos_x - 0.5f) - grid_width * (int)(pos_z + 0.5f);
}
