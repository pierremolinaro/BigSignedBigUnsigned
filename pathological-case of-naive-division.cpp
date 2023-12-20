//
//  main.cpp
//
//  Created by Pierre Molinaro on 30/11/2023.
//
//----------------------------------------------------------------------------------------

#include "BigSigned.h"
#include "galgas-random.h"

//----------------------------------------------------------------------------------------

static int CHECK_COUNT = 1'000'000 ;

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

int main (int /* argc */ , const char * /* argv */[]) {
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
//---
//   { const clock_t start = ::clock () ;
//     const BigUnsigned dividend (0x0'FFFF) ;
//     const BigUnsigned divisor  (0x0'01FF) ;
//     dividend      .printHex ("  dividend ") ;
//     divisor       .printHex ("  divisor  ") ;
//     const BigUnsignedQuotientRemainder r = dividend.naiveDivideByBigUnsigned (divisor) ;
//     r.quotient  ().printHex ("  quotient ") ;
//     r.remainder ().printHex ("  remainder") ;
//     std::cout << "Done in " << timeFromStart (start) << "\n" ;
//   }
//---
//   { const clock_t start = ::clock () ;
//     const BigUnsigned dividend (0x0'FFFF'FFFF) ;
//     const BigUnsigned divisor  (0x0'0001'FFFF) ;
//     dividend      .printHex ("  dividend ") ;
//     divisor       .printHex ("  divisor  ") ;
//     const BigUnsignedQuotientRemainder r = dividend.naiveDivideByBigUnsigned (divisor) ;
//     r.quotient  ().printHex ("  quotient ") ;
//     r.remainder ().printHex ("  remainder") ;
//     std::cout << "Done in " << timeFromStart (start) << "\n" ;
//   }
//---
  { const clock_t start = ::clock () ;
    const BigUnsigned dividend (0x0'FFFF'FFFF'0000'0000) ;
    const BigUnsigned divisor  (0x0'0000'0001'FFFF'FFFF) ;
    dividend      .printHex ("  dividend ") ;
    divisor       .printHex ("  divisor  ") ;
    const BigUnsignedQuotientRemainder r = dividend.naiveDivideByBigUnsigned (divisor) ;
    r.quotient  ().printHex ("  quotient ") ;
    r.remainder ().printHex ("  remainder") ;
    std::cout << "Done in " << timeFromStart (start) << "\n" ;
  }
//---
  { const clock_t start = ::clock () ;
    const uint64_t dividendArray [2] = {0x0'FFFF'FFFF'FFFF'FFFF, 0} ;
    const BigUnsigned dividend (2, dividendArray) ;
    const uint64_t divisorArray [2] = {1, 0x0'FFFF'FFFF'FFFF'FFFF} ;
    const BigUnsigned divisor  (2, divisorArray) ;
    dividend      .printHex ("  dividend ") ;
    divisor       .printHex ("  divisor  ") ;
    const BigUnsignedQuotientRemainder r = dividend.naiveDivideByBigUnsigned (divisor) ;
    r.quotient  ().printHex ("  quotient ") ;
    r.remainder ().printHex ("  remainder") ;
    std::cout << "Done in " << timeFromStart (start) << "\n" ;
  }
//---
  std::cout << "ChunkSharedArray Allocation Count: "
            << ChunkSharedArray::chunkSharedArrayAllocationCount () << "\n" ;
  std::cout << "ChunkSharedArray Currently Allocated Count: "
            << ChunkSharedArray::chunkSharedArrayCurrentlyAllocatedCount () << "\n" ;
//---
  return 0;
}

//----------------------------------------------------------------------------------------
