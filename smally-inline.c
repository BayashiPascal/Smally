// *************** CRYPTIC-INLINE.C ***************

// ================ Functions implementation ====================

// Static constructor for a Feistel cipher,
// 'keys' is a GSet of null terminated strings, all the same size
// 'fun' is the ciphering function of the form
// void (*fun)(char* src, char* dest, char* key, unsigned long len)
// 'src', 'dest' have same length 'len'
// 'key' may be of any length
#if BUILDMODE != 0
static inline
#endif
Smally SmallyCreateStatic(void) {

  // Declare a Smally and set the properties
  Smally c = {

    .mode = SMALLY_DEFAULT_OP_MODE

  };

  // Return the Smally
  return c;

}

// Get the operating mode of the Smally 'that'
#if BUILDMODE != 0
static inline
#endif
SmallyOpMode SmallyGetOpMode(
  const Smally* const that) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  // Return the operating mode
  return that->mode;

}

// Set the operating mode of the Smally 'that' to 'mode'
#if BUILDMODE != 0
static inline
#endif
void SmallySetOpMode(
  Smally* const that,
   SmallyOpMode mode) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  // Set the operating mode
  that->mode = mode;

}
