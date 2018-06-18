/* ---------------------------------------------------------------------
This file is for Extractor class.

create: 2018/06/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "extractor.h"

/* ------------------------------------------------------------------ */

void Extractor::reserve() {

  reservation_count += 1;

}

/* ------------------------------------------------------------------ */

void Extractor::cancel() {

  reservation_count -= 1;

}

/* ------------------------------------------------------------------ */

bool Extractor::del_data() {

  if (0 < reservation_count) {
    return false;
  } else {
    delete data;
    is_extracted = false;
    return true;
  }

}

/* ------------------------------------------------------------------ */

Data *Extractor::get_data() {

  if (!is_extracted) {
    create();
    extract();
    is_extracted = true;
  }

  reservation_count -= 1;

  return data;

}

/* ------------------------------------------------------------------ */

const Data *Extractor::get_data_() {

  if (!is_extracted) {
    create();
    extract();
    is_extracted = true;
  }

  return data;

}
