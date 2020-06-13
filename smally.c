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
  unsigned char breakChar;

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

  (void)that;

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

  // Create a progress bar
  ProgBarTxt progBar = ProgBarTxtCreateStatic();

  // Declare a variable to memorize the number of byte read
  unsigned long nbByteRead = 0;

  // Declare a variable to memorize the number of byte written
  unsigned long nbByteWritten = 0;

  // Get the size of the input file
  fseek(
    fpIn,
    0,
    SEEK_END);
  unsigned long sizeFile = ftell(fpIn);
  fseek(
    fpIn,
    0,
    0);

  // Declare the search and look ahead buffers
  GSet searchSet = GSetCreateStatic();
  GSet lookAheadSet = GSetCreateStatic();

  // Loop until the look ahead buffer is not empty or the file is not
  // completely processed
  do {

    // Refill the look ahead buffer
    while (
      !feof(fpIn) &&
      GSetNbElem(&lookAheadSet) < SmallyGetSizeLookAheadBuffer(that) - 1) {

      unsigned char c;
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
      ++nbByteRead;

    }

    // If we are in verbose mode
    if (SmallyGetVerbose(that)) {

      // Update and display the progress bar
      ProgBarTxtSet(
        &progBar,
        (float)nbByteRead / (float)sizeFile);
      printf(
        "Compressing... %s\r",
        ProgBarTxtGet(&progBar));
      fflush(stdout);

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

      token = (SmallyLZ77Token) {

        .length = 0,
        .offset = 0,
        .breakChar = *(unsigned char*)GSetHead(&lookAheadSet)

      };

    }

    // Write the token (l, o, c) to the output file

    unsigned char buffer[3];
    buffer[2] = token.breakChar;
    buffer[1] = token.offset & 0xFF;
    buffer[0] = (token.offset & 0xFF00) >> 8;
    buffer[0] |= token.length << (8 - SmallyGetNbBitLookAheadBuffer(that));

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
    nbByteWritten += 3;

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
    while (GSetNbElem(&searchSet) >= SmallyGetSizeSearchBuffer(that)) {

      (void)GSetPop(&searchSet);

    }

  } while (
    !feof(fpIn) ||
    GSetNbElem(&lookAheadSet) > 0);

  // If we are in verbose mode
  if (SmallyGetVerbose(that)) {

      // Update and display the progress bar
      ProgBarTxtSet(
        &progBar,
        (float)nbByteRead / (float)sizeFile);
      printf(
        "Compressing... %s\n",
        ProgBarTxtGet(&progBar));
      fflush(stdout);
    printf(
      "Compressed file relative size: %.2f%%\n",
      (float)nbByteWritten / (float)sizeFile * 100.0);

  }

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

  (void)that;

  // Create the result token
  SmallyLZ77Token bestToken = {

    .length = 0,
    .offset = 0,
    .breakChar = *(unsigned char*)GSetHead(lookAheadSet)

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
      .offset = offset - 1,
      .breakChar = *(unsigned char*)GSetHead(lookAheadSet)

    };

    // Reset the iterator of the look ahead buffer
    GSetIterReset(&iterLookAhead);

    // Reset the iterator of the scan in the dictionnary
    memcpy(
      &iterSearch,
      &iterStartSearch,
      sizeof(GSetIterForward));

    // Scan the look ahead and dictionnary buffers until
    // we found a different byte
    bool flagEqual = false;

    do {

      // If the current byte in the look ahead buffer and search buffer
      // are equals
      flagEqual =
        (GSetIterGet(&iterSearch) == GSetIterGet(&iterLookAhead));
      if (
        flagEqual &&
        !GSetIterIsLast(&iterLookAhead)) {

        // Increase the length of the token
        ++(token.length);

      // Else, if we have found the breaking byte
      } else {

        token.breakChar = *(unsigned char*)GSetIterGet(&iterLookAhead);

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
      token.breakChar = *(unsigned char*)GSetIterGet(&iterLookAhead);

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

  // Create a dictionary of all possible values to be used as data
  // of the GSet
  unsigned char vals[256];
  for (
    int i = 256;
    i--;) {

    vals[i] = i;

  }

  // Create a progress bar
  ProgBarTxt progBar = ProgBarTxtCreateStatic();

  // Declare a variable to memorize the number of byte read
  unsigned long nbByteRead = 0;

  // Get the size of the input file
  fseek(
    fpIn,
    0,
    SEEK_END);
  unsigned long sizeFile = ftell(fpIn);
  fseek(
    fpIn,
    0,
    0);

  // Declare the search and look ahead buffers
  GSet searchSet = GSetCreateStatic();

  // Read the first token (l, o, c) from the input file
  unsigned char buffer[3];
  size_t ret =
    fread(
      buffer,
      1,
      3,
      fpIn);
  if (
    ret != 3 &&
    !feof(fpIn)) {

    SmallyErr->_type = PBErrTypeIOError;
    sprintf(
      SmallyErr->_msg,
      "I/O error %d",
      ferror(fpIn));
    PBErrCatch(SmallyErr);

  }
  nbByteRead += 3;

  // Loop on the file
  do {

    // If we are in verbose mode
    if (SmallyGetVerbose(that)) {

      // Update and display the progress bar
      ProgBarTxtSet(
        &progBar,
        (float)nbByteRead / (float)sizeFile);
      printf(
        "Decompressing... %s\r",
        ProgBarTxtGet(&progBar));
      fflush(stdout);

    }

    SmallyLZ77Token token;
    token.breakChar = buffer[2];
    token.offset = (unsigned int)buffer[1];
    int shift = (8 - SmallyGetNbBitLookAheadBuffer(that));
    token.length = (unsigned int)(buffer[0] >> shift);
    buffer[0] = buffer[0] << SmallyGetNbBitLookAheadBuffer(that);
    token.offset += 256 * (unsigned int)
      (buffer[0] >> SmallyGetNbBitLookAheadBuffer(that));

    // Decode the token
    GSetIterBackward iterOffset = GSetIterBackwardCreateStatic(&searchSet);
    for (
      unsigned int i = token.offset;
      i--;) {

        GSetIterStep(&iterOffset);

    }

    GSetIterForward iterLength;
    memcpy(
      &iterLength,
      &iterOffset,
      sizeof(GSetIterForward));
    for (
      unsigned int i = token.length;
      i--;) {

        unsigned char c = *(unsigned char*)GSetIterGet(&iterLength);
        ret =
          fwrite(
            &c,
            1,
            1,
            fpOut);
        if (
          ret != 1 &&
          !feof(fpOut)) {

          SmallyErr->_type = PBErrTypeIOError;
          sprintf(
            SmallyErr->_msg,
            "I/O error %d",
            ferror(fpOut));
          PBErrCatch(SmallyErr);

        }

        GSetAppend(
          &searchSet,
          vals + c);
        GSetIterStep(&iterLength);

    }

    // Output the breaking byte
    ret =
      fwrite(
        &(token.breakChar),
        1,
        1,
        fpOut);
    if (
      ret != 1 &&
      !feof(fpOut)) {

      SmallyErr->_type = PBErrTypeIOError;
      sprintf(
        SmallyErr->_msg,
        "I/O error %d",
        ferror(fpOut));
      PBErrCatch(SmallyErr);

    }

    GSetAppend(
      &searchSet,
      vals + token.breakChar);

    // Pop from the search buffer as long as it exceeds its maximum
    // size
    while (GSetNbElem(&searchSet) >= SmallyGetSizeSearchBuffer(that)) {

      (void)GSetPop(&searchSet);

    }

    // Read the next token
    ret =
      fread(
        buffer,
        1,
        3,
        fpIn);
    if (
      ret != 3 &&
      !feof(fpIn)) {

      SmallyErr->_type = PBErrTypeIOError;
      sprintf(
        SmallyErr->_msg,
        "I/O error %d",
        ferror(fpIn));
      PBErrCatch(SmallyErr);

    }
    nbByteRead += 3;

  } while (!feof(fpIn));

  // If we are in verbose mode
  if (SmallyGetVerbose(that)) {

      // Update and display the progress bar
      ProgBarTxtSet(
        &progBar,
        (float)nbByteRead / (float)sizeFile);
      printf(
        "Decompressing... %s\n",
        ProgBarTxtGet(&progBar));
      fflush(stdout);

  }

  // Free memory
  GSetFlush(&searchSet);

}
