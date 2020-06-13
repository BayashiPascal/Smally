// *************** CRYPTIC-INLINE.C ***************

// ================ Functions implementation ====================

// Static constructor for a Smally of type 'type'
#if BUILDMODE != 0
static inline
#endif
Smally SmallyCreateStatic(SmallyType type) {

  // Declare a Smally and set the properties
  Smally s = {

    .type = type,
    .verbose = false

  };

  // Return the Smally
  return s;

}

// Get the type of the Smally 'that'
#if BUILDMODE != 0
static inline
#endif
SmallyType _SmallyGetType(const Smally* const that) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  // Return the type
  return that->type;

}

// Get the verbose mode of the Smally 'that'
#if BUILDMODE != 0
static inline
#endif
bool _SmallyGetVerbose(const Smally* const that) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  // Return the verbose mode
  return that->verbose;

}

// Set the verbose mode of the Smally 'that'
#if BUILDMODE != 0
static inline
#endif
void _SmallySetVerbose(
  Smally* const that,
     const bool verbose) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  // Set the verbose mode
  that->verbose = verbose;

}

// Static constructor for a SmallyLZ77
#if BUILDMODE != 0
static inline
#endif
SmallyLZ77 SmallyLZ77CreateStatic(void) {

  // Declare a Smally and set the properties
  SmallyLZ77 s = {

    .nbBitSearchBuffer = SMALLYLZ77_DEFAULT_SIZELEN,
    .nbBitLookAheadBuffer = SMALLYLZ77_DEFAULT_SIZEPOS

  };

  s.parent = SmallyCreateStatic(SmallyType_LZ77);
  s.sizeSearchBuffer =
    powi(
      2,
      s.nbBitSearchBuffer);
  s.sizeLookAheadBuffer =
    powi(
      2,
      s.nbBitLookAheadBuffer);

  // Return the Smally
  return s;

}

// Get the nb of bits for the search buffer of the SmallyLZ77 'that'
#if BUILDMODE != 0
static inline
#endif
unsigned int SmallyGetNbBitSearchBuffer(const SmallyLZ77* const that) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  return that->nbBitSearchBuffer;

}

// Get the nb of bits for the look ahead buffer of the SmallyLZ77 'that'
#if BUILDMODE != 0
static inline
#endif
unsigned int SmallyGetNbBitLookAheadBuffer(const SmallyLZ77* const that) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  return that->nbBitLookAheadBuffer;

}

// Get the size of the search buffer of the SmallyLZ77 'that'
#if BUILDMODE != 0
static inline
#endif
unsigned int SmallyGetSizeSearchBuffer(const SmallyLZ77* const that) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  return that->sizeSearchBuffer;

}

// Get the size of the look ahead buffer of the SmallyLZ77 'that'
#if BUILDMODE != 0
static inline
#endif
unsigned int SmallyGetSizeLookAheadBuffer(const SmallyLZ77* const that) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  return that->sizeLookAheadBuffer;

}
