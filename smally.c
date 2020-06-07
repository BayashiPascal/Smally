// *************** CRYPTIC.C ***************

// ================= Include ==================
#include "smally.h"
#if BUILDMODE == 0
#include "smally-inline.c"
#endif

// ================ Functions implementation ==================

// Function to free the memory used by the static Smally
void _SmallyFreeStatic(Smally* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

}

// Function to free the memory used by the static SmallyLZ77
void SmallyLZ77FreeStatic(SmallyLZ77* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  // Free the parent
  SmallyFreeStatic((Smally*)that);

}

// Function to compress a file 'fpIn' with the Smally 'that'
// Save the result in the file 'fpOut'.
void _SmallyLZ77CompressFile(
  const SmallyLZ77* const that,
              FILE* const fpIn,
              FILE* const fpOut) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

  if (fpIn == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'fpIn' is null");
    PBErrCatch(SmallyErr);

  }

  if (fpOut == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'fpOut' is null");
    PBErrCatch(SmallyErr);

  }

#endif

}

// Function to decompress a file 'fpIn' with the SmallyLZ77 'that'
// Save the result in the file 'fpOut'.
void _SmallyLZ77DecompressFile(
  const SmallyLZ77* const that,
              FILE* const fpIn,
              FILE* const fpOut) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

  if (fpIn == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'fpIn' is null");
    PBErrCatch(SmallyErr);

  }

  if (fpOut == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'fpOut' is null");
    PBErrCatch(SmallyErr);

  }

#endif

}
