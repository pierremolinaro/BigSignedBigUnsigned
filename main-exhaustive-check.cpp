//
//  main.cpp
//
//  Created by Pierre Molinaro on 30/11/2023.
//
//----------------------------------------------------------------------------------------

#include "BigUnsigned.h"
#include "galgas-random.h"

//----------------------------------------------------------------------------------------

static std::string timeFromStart (const clock_t inStart) {
  const unsigned durationInMilliseconds = unsigned (::clock () - inStart) / (CLOCKS_PER_SEC / 1000) ;
  const unsigned milliseconds = durationInMilliseconds % 1000 ;
  const unsigned durationInSeconds = durationInMilliseconds / 1000 ;
  const unsigned seconds = durationInSeconds % 60 ;
  const unsigned durationInMinutes = durationInSeconds / 60 ;
  const unsigned minutes = durationInMinutes % 60 ;
  const unsigned hours = durationInMinutes / 60 ;
  std::string result ;
  if (hours > 0) {
    result.append (std::to_string (hours)) ;
    result.append (" h ") ;
  }
  if (minutes > 0) {
    result.append (std::to_string (minutes)) ;
    result.append (" min ") ;
  }
  if (seconds > 0) {
    result.append (std::to_string (seconds)) ;
    result.append (" s ") ;
  }
  result.append (std::to_string (milliseconds)) ;
  result.append (" ms") ;
  return result ;
}

//----------------------------------------------------------------------------------------

#ifdef PRAGMA_MARK_ALLOWED
  #pragma mark BigUnsigned, exhaustive check
#endif

//----------------------------------------------------------------------------------------

static void exhaustiveTest_decimalString_xString_BigUnsigned (const std::vector <BigUnsigned> & inBigUnsignedArray) {
  std::cout << "BigUnsigned: exhaustive test [0, "
            << (inBigUnsignedArray.size () - 1)
            << "] decimalString, xString... "
            << std::flush ;
  const clock_t start = ::clock () ;
  for (size_t i = 0 ; i < inBigUnsignedArray.size () ; i++) {
    const std::string s = inBigUnsignedArray [i].decimalString () ;
    const std::string sHex = inBigUnsignedArray [i].xString () ;
    const std::string refString = std::to_string (i) ;
    char str [32] ;
    snprintf (str, 31, "%lX", i) ;
    const std::string refHexString = str ;
    if ((s != refString) || (sHex != refHexString)) {
      std::cout << "error (i=" << i << ")\n" ;
      std::cout << " Reference string '" << refString << "'\n" ;
      std::cout << "    decimalString '" << s << "'\n" ;
      std::cout << "Reference xstring '" << refHexString << "'\n" ;
      std::cout << "          xString '" << sHex << "'\n" ;
      exit (1) ;
    }
  }
  std::cout << "Ok " << timeFromStart (start) << "\n" ;
}

//----------------------------------------------------------------------------------------

static void exhaustiveTest_and_or_complemented_BigUnsigned (const std::vector <BigUnsigned> & inBigUnsignedArray) {
  std::cout << "BigUnsigned: exhaustive test [0, "
            << (inBigUnsignedArray.size () - 1)
            << "] and, or, complement... "
            << std::flush ;
  const clock_t start = ::clock () ;
  for (size_t a = 0 ; a < inBigUnsignedArray.size () ; a++) {
    const BigUnsigned bigA = inBigUnsignedArray [a] ;
    for (size_t b = 0 ; b < inBigUnsignedArray.size () ; b++) {
      const BigUnsigned bigB = inBigUnsignedArray [b] ;
      const size_t maxChunkCount = std::max (bigA.chunkCount(), bigB.chunkCount()) ;
      const BigUnsigned v1 = bigA | bigB ;
      const BigUnsigned v2 = (bigA.complemented (maxChunkCount) & bigB.complemented (maxChunkCount)).complemented (maxChunkCount) ;
      const BigUnsigned v3 = bigA & bigB ;
      const BigUnsigned v4 = (bigA.complemented (maxChunkCount) | bigB.complemented (maxChunkCount)).complemented (maxChunkCount) ;
      if ((v1 != v2) || (v3 != v4)) {
        std::cout << " error\n" ;
        bigA.printHex  ("bigA ") ;
        bigB.printHex  ("bigB ") ;
        v1.printHex    ("v1") ;
        v2.printHex    ("v2") ;
        v3.printHex    ("v3") ;
        v4.printHex    ("v4") ;
        exit (1) ;
      }
    }
  }
  std::cout << "Ok " << timeFromStart (start) << "\n" ;
}

//----------------------------------------------------------------------------------------

static void exhaustiveTest_xor_complemented_BigUnsigned (const std::vector <BigUnsigned> & inBigUnsignedArray) {
  std::cout << "BigUnsigned: exhaustive test [0, "
            << (inBigUnsignedArray.size () - 1)
            << "] xor... "
            << std::flush ;
  const clock_t start = ::clock () ;
  for (size_t a = 0 ; a < inBigUnsignedArray.size () ; a++) {
    const BigUnsigned bigA = inBigUnsignedArray [a] ;
    for (size_t b = 0 ; b < inBigUnsignedArray.size () ; b++) {
      const BigUnsigned bigB = inBigUnsignedArray [b] ;
      const size_t maxChunkCount = std::max (bigA.chunkCount(), bigB.chunkCount()) ;
      const BigUnsigned v1 = bigA ^ bigB ;
      const BigUnsigned v2 = (bigA & bigB.complemented (maxChunkCount)) | (bigA.complemented (maxChunkCount) & bigB) ;
      const BigUnsigned v3 = ((bigA.complemented (maxChunkCount) & bigB.complemented (maxChunkCount)) | (bigA & bigB)).complemented (maxChunkCount) ;
      if ((v1 != v2) || (v1 != v3)) {
        std::cout << " error\n" ;
        bigA.printHex  ("bigA ") ;
        bigB.printHex  ("bigB ") ;
        v1.printHex    ("v1") ;
        v2.printHex    ("v2") ;
        v3.printHex    ("v3") ;
        exit (1) ;
      }
    }
  }
  std::cout << "Ok " << timeFromStart (start) << "\n" ;
}

//----------------------------------------------------------------------------------------

static void exhaustiveTest_MultiplyingDividing_BigUnsigned (const std::vector <BigUnsigned> & inBigUnsignedArray) {
  std::cout << "BigUnsigned: exhaustive test [0, "
            << (inBigUnsignedArray.size () - 1)
            << "] multiplying, dividing... "
            << std::flush ;
  const clock_t start = ::clock () ;
  for (size_t dividendIdx = 0 ; dividendIdx < inBigUnsignedArray.size () ; dividendIdx++) {
    const BigUnsigned dividend = inBigUnsignedArray [dividendIdx] ;
    for (size_t divisorIdx = 1 ; divisorIdx < inBigUnsignedArray.size () ; divisorIdx++) {
      const BigUnsigned divisor = inBigUnsignedArray [divisorIdx] ;
      const BigUnsignedQuotientRemainder r = dividend.divideByBigUnsigned (divisor) ;
      BigUnsigned verif = divisor ;
      verif *= r.quotient () ;
      verif += r.remainder () ;
      if ((dividend != verif) || (r.remainder () >= divisor)) {
        std::cout << " error" ;
        if (dividend != verif) {
          std::cout << " dividend != verif !!!" ;
        }
        if (r.remainder () >= divisor) {
          std::cout << " Remainder > divisor !!!" ;
        }
        std::cout << "\n" ;
        verif.printHex     ("Verif    ") ;
        dividend.printHex  ("Dividend ") ;
        divisor.printHex   ("Divisor  ") ;
        r.quotient ().printHex  ("Quotient ") ;
        r.remainder ().printHex ("remainder") ;
        std::cout << "With naive division\n" ;
        const BigUnsignedQuotientRemainder rr = dividend.naiveDivideByBigUnsigned (divisor) ;
        rr.quotient ().printHex  ("Quotient ") ;
        rr.remainder ().printHex ("Remainder") ;
        if (rr.remainder () >= divisor) {
          std::cout << "  Remainder > divisor !!!\n" ;
        }
        exit (1) ;
      }
    }
  }
  std::cout << "Ok " << timeFromStart (start) << "\n" ;
}

//----------------------------------------------------------------------------------------

static void exhaustiveTest_AddingSubtractingBigUnsigned (const std::vector <BigUnsigned> & inBigUnsignedArray) {
  std::cout << "BigUnsigned: exhaustive test [0, "
            << (inBigUnsignedArray.size () - 1)
            << "] adding, subtracting... "
            << std::flush ;
  const clock_t start = ::clock () ;
  for (size_t a = 0 ; a < inBigUnsignedArray.size () ; a++) {
    const BigUnsigned bigA = inBigUnsignedArray [a] ;
    for (size_t b = 0 ; b <= a ; b++) {
      const BigUnsigned bigB = inBigUnsignedArray [b] ;
      BigUnsigned verif = bigA ;
      verif += bigB ;
      verif -= bigB ;
      if (bigA.compare (verif) != 0) {
        std::cout << " error\n" ;
        verif.printHex ("verif") ;
        bigA.printHex  ("bigA ") ;
        bigB.printHex  ("bigB ") ;
        exit (1) ;
      }
    }
  }
  std::cout << "Ok " << timeFromStart (start) << "\n" ;
}

//----------------------------------------------------------------------------------------

static void exhaustiveCheckUpTo (const uint64_t inUpperBound) {
  std::cout << "BigUnsigned: exhaustive test [0, "
            << (inUpperBound - 1) << "] ...\n"
            << std::flush ;
  const clock_t start = ::clock () ;
  std::vector <BigUnsigned> bigUnsignedArray ;
  for (uint64_t i = 0 ; i < inUpperBound ; i++) {
    bigUnsignedArray.push_back (BigUnsigned (i)) ;
  }
  exhaustiveTest_decimalString_xString_BigUnsigned (bigUnsignedArray) ;
  exhaustiveTest_AddingSubtractingBigUnsigned (bigUnsignedArray) ;
  exhaustiveTest_MultiplyingDividing_BigUnsigned (bigUnsignedArray) ;
  exhaustiveTest_and_or_complemented_BigUnsigned (bigUnsignedArray) ;
  exhaustiveTest_xor_complemented_BigUnsigned (bigUnsignedArray) ;
  std::cout << "BigUnsigned: exhautive test [0, " << (inUpperBound - 1)
            << "] done in " << timeFromStart (start) << "\n" ;
}

//----------------------------------------------------------------------------------------

#ifdef PRAGMA_MARK_ALLOWED
  #pragma mark Main
#endif

//----------------------------------------------------------------------------------------

int main (int /* argc */ , const char * /* argv */[]) {
  const clock_t start = ::clock () ;
  #ifndef DO_NOT_GENERATE_CHECKINGS
    std::cout << "Debug mode: DO_NOT_GENERATE_CHECKINGS is not defined\n" ;
  #else
    std::cout << "Release mode: DO_NOT_GENERATE_CHECKINGS is defined\n" ;
  #endif
  std::cout << "Chunk size: " << ChunkUIntBitCount << " bits\n" ;
//--- Check ctl (count leading zeros) function
  const ChunkUInt testValue = ChunkUInt (0x10) ;
  const uint32_t computedCTL = countLeadingZeros (testValue) ;
  uint32_t requiredCTL = 0 ;
  { ChunkUInt v = testValue ;
    while ((v & (ChunkUInt (1) << (ChunkUIntBitCount - 1))) == 0) {
      v <<= 1 ;
      requiredCTL += 1 ;
    }
  }
  std::cout << "countLeadingZeros function: " ;
  if (computedCTL == requiredCTL) {
    std::cout << "ok\n" ;
  }else{
    std::cout << "error, computed " << computedCTL << ", required " << requiredCTL << "\n" ;
    exit (1) ;
  }
//--- BigUnsigned
  exhaustiveCheckUpTo (1 << 17) ;
//---
  std::cout << "ChunkSharedArray Allocation Count: "
            << ChunkSharedArray::chunkSharedArrayAllocationCount () << "\n" ;
  std::cout << "ChunkSharedArray Currently Allocated Count: "
            << ChunkSharedArray::chunkSharedArrayCurrentlyAllocatedCount () << "\n" ;
//---
  std::cout << "Done in " << timeFromStart (start) << "\n" ;
  return 0;
}

//----------------------------------------------------------------------------------------
