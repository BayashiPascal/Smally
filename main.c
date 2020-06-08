#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "smally.h"

void UnitTestSmallyLZ77() {

  SmallyLZ77 smally = SmallyLZ77CreateStatic();
  FILE* fpIn =
    fopen(
      "./testSmallyLZ77.txt",
      "r");
  FILE* fpOut =
    fopen(
      "./testSmallyLZ77.sma",
      "w");
  SmallyCompressFile(&smally, fpIn, fpOut);

  fclose(fpIn);
  SmallyFreeStatic(&smally);
  printf("UnitTestSmallyLZ77 OK\n");

}

void UnitTestAll() {

  UnitTestSmallyLZ77();
  printf("UnitTestAll OK\n");

}

int main() {

  UnitTestAll();

  // Return success code
  return 0;

}
