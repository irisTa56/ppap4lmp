/* ---------------------------------------------------------------------
This file is for Extractor class.

create: 2018/06/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "extractor.h"

/* ------------------------------------------------------------------ */

template <typename DATA>
void Extractor<DATA>::reserve() {

  reservation_count += 1;

}

/* ------------------------------------------------------------------ */

template <typename DATA>
bool Extractor<DATA>::del_data() {

  if (0 < reservation_count) {
    return false;
  } else {
    delete data;
    return true;
  }

}

/* ------------------------------------------------------------------ */

template <typename DATA>
DATA *Extractor<DATA>::get_data() {

  if (!is_extracted) {
    extract();
    is_extracted = true;
  }

  reservation_count -= 1;

  return data;

}
