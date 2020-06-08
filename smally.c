// *************** CRYPTIC.C ***************

// ================= Include ==================
#include "smally.h"
#if BUILDMODE == 0
#include "smally-inline.c"
#endif

// ================= Data structures ===================

typedef struct SmallyLZ77Token {
  unsigned int offset;
  unsigned int length;
  char breakChar;
} SmallyLZ77Token;

// ================ Functions declaration ====================

// Function to search a token for the LZ77 algorithm
SmallyLZ77Token SmallyLZ77SearchToken(
  const SmallyLZ77* const that,
  const GSet* const searchSet,
  const GSet* const lookAheadSet);

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

  // Create a dictionary of all possible values to be used as data
  // of the GSet
  unsigned char vals[256];
  for (
    int i = 256;
    i--;) {

    vals[i] = i;

  }

  // Declare the search and look ahead buffers
  GSet searchSet = GSetCreateStatic();
  GSet lookAheadSet = GSetCreateStatic();

  // Loop until the look ahead buffer is not empty or the file is not
  // completely processed
  do {

    // Refill the look ahead buffer
    while (!feof(fpIn) &&
      GSetNbElem(&lookAheadSet) < SmallyGetSizeLookAheadBuffer(that)) {

      char c;
      size_t ret =
        fread(
          &c,
          1,
          1,
          fpIn);
      if (ret == 1) {

        GSetAppend(
          &lookAheadSet,
          vals + c);

      } else if (!feof(fpIn)) {

        SmallyErr->_type = PBErrTypeIOError;
        sprintf(
          SmallyErr->_msg,
          "I/O error %d",
          ferror(fpIn));
        PBErrCatch(SmallyErr);

      }

    }

    // Search the longest token in the dictionnary
    SmallyLZ77Token token;
    if (GSetNbElem(&searchSet) > 0) {

      token =
        SmallyLZ77SearchToken(
          that,
          &searchSet,
          &lookAheadSet);

    } else {

      token = (SmallyLZ77Token){
        .length = 0,
        .offset = 0,
        .breakChar = *(char*)GSetHead(&lookAheadSet)
      };

    }

    // Write the token (l, o, c) to the output file
    char buffer[3];
    buffer[2] = token.breakChar;
    buffer[1] = ((char*)(&(token.offset)))[sizeof(token.offset) - 1];
    buffer[0] = ((char*)(&(token.offset)))[sizeof(token.offset) - 2];
    buffer[0] |=
      ((char*)(&(token.offset)))[sizeof(token.length) - 1] <<
      (8 - SmallyGetNbBitLookAheadBuffer(that));
    size_t ret =
      fwrite(
        buffer,
        1,
        3,
        fpOut);
    if (
      ret != 3 &&
      !feof(fpOut)) {

      SmallyErr->_type = PBErrTypeIOError;
      sprintf(
        SmallyErr->_msg,
        "I/O error %d",
        ferror(fpOut));
      PBErrCatch(SmallyErr);

    }

//printf("%d, %d, %c\n",token.offset,token.length,token.breakChar);

    // Slide the window
    // First, move the bytes from the look ahead buffer ot the search
    // buffer
    for (
      unsigned int i = token.length + 1;
      i--;) {

      GSetAppend(
        &searchSet,
        GSetPop(&lookAheadSet));

    }

    // Second, pop from the search buffer as long as it exceeds its maximum
    // size
    while (GSetNbElem(&searchSet) > SmallyGetSizeSearchBuffer(that)) {

      (void)GSetPop(&searchSet);

    }

  } while (
    !feof(fpIn) ||
    GSetNbElem(&lookAheadSet) > 0);

  // Free memory
  GSetFlush(&searchSet);
  GSetFlush(&lookAheadSet);

}

// Function to search a token for the LZ77 algorithm
SmallyLZ77Token SmallyLZ77SearchToken(
  const SmallyLZ77* const that,
  const GSet* const searchSet,
  const GSet* const lookAheadSet) {

#if BUILDMODE == 0

  if (that == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'that' is null");
    PBErrCatch(SmallyErr);

  }

  if (searchSet == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'searchSet' is null");
    PBErrCatch(SmallyErr);

  }

  if (lookAheadSet == NULL) {

    SmallyErr->_type = PBErrTypeNullPointer;
    sprintf(
      SmallyErr->_msg,
      "'lookAheadSet' is null");
    PBErrCatch(SmallyErr);

  }

#endif

  // Create the result token
  SmallyLZ77Token bestToken = {
    .length = 0,
    .offset = 0,
    .breakChar = *(char*)GSetHead(lookAheadSet)
  };

  // Create an iterator for the look ahead buffer
  GSetIterForward iterLookAhead =
    GSetIterForwardCreateStatic(lookAheadSet);

  // Create an iterator for the start in search buffer
  GSetIterBackward iterStartSearch =
    GSetIterBackwardCreateStatic(searchSet);

  // Create an iterator to scan the search buffer
  GSetIterForward iterSearch =
    GSetIterForwardCreateStatic(searchSet);

  // Declare a variable to memorize the offset
  unsigned int offset = 1;

  // Loop until we have scanned the whole dictionary
  do {

    // Create a temporary token
    SmallyLZ77Token token = {
      .length = 0,
      .offset = offset,
      .breakChar = *(char*)GSetHead(lookAheadSet)
    };

    // Reset the iterator of the look ahead buffer
    GSetIterReset(&iterLookAhead);

    // Reset the iterator of the scan in the dictionnary
    iterSearch = *(GSetIterForward*)(&iterStartSearch);

    // Scan the look ahead and dictionnary buffers until
    // we found a different byte
    bool flagEqual = false;

    do {

      // If the current byte in the look ahead buffer and search buffer
      // are equals
      flagEqual =
        (GSetIterGet(&iterSearch) == GSetIterGet(&iterLookAhead));
      if (flagEqual) {

        // Increase the length of the token
        ++(token.length);

      // Else, if we have found the breaking byte
      } else {

        token.breakChar = *(char*)GSetIterGet(&iterLookAhead);

      }

    } while (
      flagEqual &&
      GSetIterStep(&iterLookAhead) &&
      GSetIterStep(&iterSearch));

    // If the bytes were equals up to the end of the search of look
    // ahead buffer
    if (flagEqual) {

      // The breaking byte is set to the current byte in the
      // look ahead buffer
      token.breakChar = *(char*)GSetIterGet(&iterLookAhead);

    }

    // If the token is longer than the current best one
    if (bestToken.length < token.length) {

      // Update the best token
      bestToken = token;

    }

    // Increment the offset
    ++offset;

  } while (GSetIterStep(&iterStartSearch));

  // Return the result token
  return bestToken;

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
