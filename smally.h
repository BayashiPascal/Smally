// *************** CRYPTIC.H ***************
#ifndef CRYPTIC_H
#define CRYPTIC_H

// ================= Include ==================
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pberr.h"
#include "gset.h"

// ================= Define ==================

#define SMALLY_DEFAULT_OP_MODE SmallyOpMode_LZ77

// ================= Data structures ===================

// Operating mode
typedef enum SmallyOpMode {

  SmallyOpMode_LZ77

} SmallyOpMode;

// Structure for the Feistel cipher
typedef struct Smally {

  // Operating mode
  SmallyOpMode mode;

} Smally;

// ================ Functions declaration ====================

// Static constructor for a Feistel cipher,
// 'keys' is a GSet of null terminated strings, all the same size
// 'fun' is the ciphering function of the form
// void (*fun)(char* src, char* dest, char* key, unsigned long len)
// 'src', 'dest' have same length 'len'
// 'key' may be of any length
#if BUILDMODE != 0
static inline
#endif
Smally SmallyCreateStatic(void);

// Function to free the memory used by the static Smally
void SmallyFreeStatic(Smally* that);

// Get the operating mode of the Smally 'that'
#if BUILDMODE != 0
static inline
#endif
SmallyOpMode SmallyGetOpMode(const Smally* const that);

// Set the operating mode of the Smally 'that' to 'mode'
#if BUILDMODE != 0
static inline
#endif
void SmallySetOpMode(
  Smally* const that,
   SmallyOpMode mode);

// Function to compress a file 'fpIn' with the Smally 'that'
// Save the result in the file 'fpOut'.
void SmallyCompressFile(
      Smally* that,
  FILE* const fpIn,
  FILE* const fpOut);

// Function to decompress a file 'fpIn' with the Smally 'that'
// Save the result in the file 'fpOut'.
void SmallyDecompressFile(
      Smally* that,
  FILE* const fpIn,
  FILE* const fpOut);

// ================ inliner ====================

#if BUILDMODE != 0
#include "smally-inline.c"
#endif

#endif
