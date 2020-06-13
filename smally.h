// *************** CRYPTIC.H ***************
#ifndef CRYPTIC_H
#define CRYPTIC_H

// ================= Include ==================
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pberr.h"
#include "pbmath.h"
#include "gset.h"
#include "respublish.h"

// ================= Define ==================

#define SMALLYLZ77_DEFAULT_SIZELEN 12   // bits
#define SMALLYLZ77_DEFAULT_SIZEPOS 4    // bits

// ================= Data structures ===================

// Operating mode
typedef enum SmallyType {

  SmallyType_LZ77

} SmallyType;

// Structure for the Smally
typedef struct Smally {

  // Type
  SmallyType type;

  // Verbose mode
  bool verbose;

} Smally;

// https://towardsdatascience.com/how-data-compression-works-
// exploring-lz77-3a2c2e06c097

// Structure for the SmallyLZ77
typedef struct SmallyLZ77 {

  // Parent
  Smally parent;

  // Size in bits of the search buffer
  unsigned int nbBitSearchBuffer;

  // Size in bits of the lookahead buffer
  unsigned int nbBitLookAheadBuffer;

  // Size in of the search buffer
  unsigned int sizeSearchBuffer;

  // Size in of the lookahead buffer
  unsigned int sizeLookAheadBuffer;

} SmallyLZ77;

// ================ Functions declaration ====================

// Static constructor for a Smally of type 'type'
#if BUILDMODE != 0
static inline
#endif
Smally SmallyCreateStatic(SmallyType type);

// Function to free the memory used by the static Smally
void _SmallyFreeStatic(Smally* that);

// Get the type of the Smally 'that'
#if BUILDMODE != 0
static inline
#endif
SmallyType _SmallyGetType(const Smally* const that);

// Get the verbose mode of the Smally 'that'
#if BUILDMODE != 0
static inline
#endif
bool _SmallyGetVerbose(const Smally* const that);

// Set the verbose mode of the Smally 'that'
#if BUILDMODE != 0
static inline
#endif
void _SmallySetVerbose(
  Smally* const that,
     const bool verbose);

// Static constructor for a SmallyLZ77
#if BUILDMODE != 0
static inline
#endif
SmallyLZ77 SmallyLZ77CreateStatic(void);

// Function to free the memory used by the static SmallyLZ77
void SmallyLZ77FreeStatic(SmallyLZ77* that);

// Get the nb of bits for the search buffer of the SmallyLZ77 'that'
#if BUILDMODE != 0
static inline
#endif
unsigned int SmallyGetNbBitSearchBuffer(const SmallyLZ77* const that);

// Get the nb of bits for the look ahead buffer of the SmallyLZ77 'that'
#if BUILDMODE != 0
static inline
#endif
unsigned int SmallyGetNbBitLookAheadBuffer(const SmallyLZ77* const that);

// Get the size of the search buffer of the SmallyLZ77 'that'
#if BUILDMODE != 0
static inline
#endif
unsigned int SmallyGetSizeSearchBuffer(const SmallyLZ77* const that);

// Get the size of the look ahead buffer of the SmallyLZ77 'that'
#if BUILDMODE != 0
static inline
#endif
unsigned int SmallyGetSizeLookAheadBuffer(const SmallyLZ77* const that);

// Function to compress a file 'fpIn' with the SmallyLZ77 'that'
// Save the result in the file 'fpOut'.
void _SmallyLZ77CompressFile(
  const SmallyLZ77* const that,
              FILE* const fpIn,
              FILE* const fpOut);

// Function to decompress a file 'fpIn' with the SmallyLZ77 'that'
// Save the result in the file 'fpOut'.
void _SmallyLZ77DecompressFile(
  const SmallyLZ77* const that,
              FILE* const fpIn,
              FILE* const fpOut);

// ================ inliner ====================

#if BUILDMODE != 0
#include "smally-inline.c"
#endif

#endif

// ================= Generic functions ==================

#define SmallyGetType(S) _Generic(S, \
  Smally*: _SmallyGetType, \
  SmallyLZ77*: _SmallyGetType, \
  const Smally*: _SmallyGetType, \
  const SmallyLZ77*: _SmallyGetType, \
  default: PBErrInvalidPolymorphism)((const Smally*)S)

#define SmallyGetVerbose(S) _Generic(S, \
  Smally*: _SmallyGetVerbose, \
  SmallyLZ77*: _SmallyGetVerbose, \
  const Smally*: _SmallyGetVerbose, \
  const SmallyLZ77*: _SmallyGetVerbose, \
  default: PBErrInvalidPolymorphism)((const Smally*)S)

#define SmallySetVerbose(S, V) _Generic(S, \
  Smally*: _SmallySetVerbose, \
  SmallyLZ77*: _SmallySetVerbose, \
  default: PBErrInvalidPolymorphism)((Smally*)S, V)

#define SmallyFreeStatic(S) _Generic(S, \
  Smally*: _SmallyFreeStatic, \
  SmallyLZ77*: SmallyLZ77FreeStatic, \
  default: PBErrInvalidPolymorphism)(S)

#define SmallyCompressFile(S, I, O) _Generic(S, \
  SmallyLZ77*: _SmallyLZ77CompressFile, \
  const SmallyLZ77*: _SmallyLZ77CompressFile, \
  default: PBErrInvalidPolymorphism)(S, I, O)

#define SmallyDecompressFile(S, I, O) _Generic(S, \
  SmallyLZ77*: _SmallyLZ77DecompressFile, \
  const SmallyLZ77*: _SmallyLZ77DecompressFile, \
  default: PBErrInvalidPolymorphism)(S, I, O)
