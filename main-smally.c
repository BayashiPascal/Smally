#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "smally.h"

int main(
     int argc,
  char** argv) {

  // Declare variables to process arguments
  FILE* fpOut = NULL;
  FILE* fpIn = NULL;
  SmallyType opMode = SmallyType_LZ77;
  bool verbose = false;

  // Loop on arguments
  for (
    int iArg = 1;
    iArg < argc;
    ++iArg) {

    int retStrCmp =
      strcmp(
        argv[iArg],
        "-help");
    if (retStrCmp == 0) {

      printf("smally\n");
      printf("[-help] : print the help message\n");
      printf("[-out <path>] : Save the result to the file at <path>\n");
      printf("                If not specified uses stdout\n");
      printf("[-compress <path>] : Encode the file at <path>\n");
      printf("[-decompress <path>] : Decode the file at <path>\n");
      printf("[-lz77] : Use LZ77 compression\n");
      printf("[-verbose] : Display information message\n");
      printf("\n");

    // Else
    } else {

      // If the argument is -out
      unsigned int retStrCmp =
        strcmp(
          argv[iArg],
          "-out");
      if (retStrCmp == 0) {

        // If the output file is opened
        if (fpOut != NULL) {

          // Close it
          fclose(fpOut);

        }

        // Open the file
        fpOut =
          fopen(
            argv[iArg + 1],
            "w");

      }

      // If the argument is -compress
      retStrCmp =
        strcmp(
          argv[iArg],
          "-compress");
      if (retStrCmp == 0) {

        // If the input file is opened
        if (fpIn != NULL) {

          // Close it
          fclose(fpIn);

        }

        // Open the file
        fpIn =
          fopen(
            argv[iArg + 1],
            "r");

        // If the path is incorrect
        if (fpIn == NULL) {

          printf(
            "The path [%s] is incorrect\n",
            argv[iArg + 1]);
          return 1;

        }

        // If the output file is not specified
        if (fpOut == NULL) {

          fpOut =
            fopen(
              "/dev/stdout",
              "w");

        }

        if (opMode == SmallyType_LZ77) {

          // Create the Smally
          SmallyLZ77 smally = SmallyLZ77CreateStatic();

          // Set the verbose mode
          SmallySetVerbose(
            &smally,
            verbose);

          if (verbose) {

            printf(
              " - %s - \n",
              argv[iArg + 1]);

          }

          // Compress the file
          SmallyCompressFile(
            &smally,
            fpIn,
            fpOut);

          // Free memory
          SmallyFreeStatic(&smally);

        }

      }

      // If the argument is -decompress
      retStrCmp =
        strcmp(
          argv[iArg],
          "-decompress");
      if (retStrCmp == 0) {

        // If the input file is opened
        if (fpIn != NULL) {

          // Close it
          fclose(fpIn);

        }

        // Open the file
        fpIn =
          fopen(
            argv[iArg + 1],
            "r");

        // If the path is incorrect
        if (fpIn == NULL) {

          printf(
            "The path [%s] is incorrect\n",
            argv[iArg + 1]);
          return 1;

        }

        // If the output file is not specified
        if (fpOut == NULL) {

          fpOut =
            fopen(
              "/dev/stdout",
              "w");

        }

        if (opMode == SmallyType_LZ77) {

          // Create the Smally
          SmallyLZ77 smally = SmallyLZ77CreateStatic();

          // Set the verbose mode
          SmallySetVerbose(
            &smally,
            verbose);

          if (verbose) {

            printf(
              " - %s - \n",
              argv[iArg + 1]);

          }

          // Decompress the file
          SmallyDecompressFile(
            &smally,
            fpIn,
            fpOut);

          // Free memory
          SmallyFreeStatic(&smally);

        }

      }

      // If the argument is -lz77
      retStrCmp =
        strcmp(
          argv[iArg],
          "-lz77");
      if (retStrCmp == 0) {

        // Memorize the operation mode
        opMode = SmallyType_LZ77;

      }

      // If the argument is -verbose
      retStrCmp =
        strcmp(
          argv[iArg],
          "-verbose");
      if (retStrCmp == 0) {

        // Memorize the verbose mode
        verbose = true;

      }

    }

  }

  // If the input file is opened
  if (fpIn != NULL) {

    // Close it
    fclose(fpIn);

  }

  // If the output file is opened
  if (fpOut != NULL) {

    // Close it
    fclose(fpOut);

  }

  // Return success code
  return 0;

}
