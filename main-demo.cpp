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

static uint32_t msFromStart (const clock_t inStart) {
  clock_t duration = ::clock () - inStart ;
  duration /= CLOCKS_PER_SEC / 1000 ;
  return uint32_t (duration) ;
}

//----------------------------------------------------------------------------------------

#ifdef PRAGMA_MARK_ALLOWED
  #pragma mark BigUnsigned
#endif

//----------------------------------------------------------------------------------------
// page 191
//----------------------------------------------------------------------------------------

static void pgcdComputing (void) {
  set_galgas_random_seed (0) ;
  std::cout << "BigUnsigned: gcd computing... " ;
  std::cout << "n**17 + 9 and (n+1)**17 + 9...\n" ;
  const clock_t start = ::clock () ;
  const std::string s ("8 424 432 925 592 889 329 288 197 322 308 900 672 459 420 460 792 433") ;
  const BigUnsigned n (s, ' ') ;
  std::cout << " n " << n.spacedDecimalStringWithDigitCount (3).c_str () << "\n" ;
  { const std::string verif = n.spacedDecimalString (3) ;
    if (s != verif) {
      std::cout << "  Error\n" ;
      std::cout << "   s     '" << s.c_str () << "'\n" ;
      std::cout << "   verif '" << verif.c_str () << "'\n" ;
      exit (1) ;
    }
  }
//--- Computing n**17+9
  BigUnsigned nPower17Plus9 = n ;
  for (uint64_t i = 1 ; i < 17 ; i++) {
    nPower17Plus9 *= n ;
  }
  nPower17Plus9 += 9 ;
  std::cout << " n**17 + 9 " << nPower17Plus9.spacedDecimalStringWithDigitCount (3).c_str () << "\n" ;
//--- Computing (n+1)**17+9
  BigUnsigned nPlus1 = n + 1 ;
  BigUnsigned nPlus1Power17Plus9 = nPlus1 ;
  for (uint64_t i = 1 ; i < 17 ; i++) {
    nPlus1Power17Plus9 *= nPlus1 ;
  }
  nPlus1Power17Plus9 += 9 ;
  std::cout << " (n+1)**17 + 9 " << nPlus1Power17Plus9.spacedDecimalStringWithDigitCount (3).c_str () << "\n" ;
//--- Calcul du PGCD
  { BigUnsigned dividend = nPlus1Power17Plus9 ;
    BigUnsigned divisor  = nPower17Plus9 ;
    bool loop = true ;
    while (loop) {
      const BigUnsignedQuotientRemainder r = dividend.divideByBigUnsigned (divisor) ;
      loop = !r.remainder ().isZero () ;
      if (loop) {
        dividend = divisor ;
        divisor = r.remainder () ;
      }else{
        std::cout << "PGCD (n**17 + 9, (n+1)**17 + 9) = " << divisor.spacedDecimalString (3).c_str () << "\n" ;
      }
    }
  }
//--- Computing (n-1)**17+9
  BigUnsigned nMinus1 = n - 1 ;
  BigUnsigned nMinus1Power17Plus9 = nMinus1 ;
  for (uint64_t i = 1 ; i < 17 ; i++) {
    BigUnsigned v = nMinus1Power17Plus9 * nMinus1 ;
    nMinus1Power17Plus9 = v ;
  }
  nMinus1Power17Plus9 += 9 ;
  std::cout << " (n-1)**17 + 9 " << nMinus1Power17Plus9.spacedDecimalStringWithDigitCount (3).c_str () << "\n" ;
//--- Calcul du PGCD
  { BigUnsigned dividend = nPower17Plus9 ;
    BigUnsigned divisor  = nMinus1Power17Plus9 ;
    bool loop = true ;
    while (loop) {
      const BigUnsignedQuotientRemainder r = dividend.divideByBigUnsigned (divisor) ;
      loop = !r.remainder ().isZero () ;
      if (loop) {
        dividend = divisor ;
        divisor = r.remainder () ;
      }else{
        std::cout << "PGCD (n**17 + 9, (n-1)**17 + 9) = " << divisor.spacedDecimalString (3).c_str () << "\n" ;
      }
    }
  }
//---
  std::cout << msFromStart (start) << " ms\n" ;
}

//----------------------------------------------------------------------------------------

static void somePrimeNumbers (void) {
  set_galgas_random_seed (0) ;
  std::cout << "BigUnsigned: some prime numbers...\n" ;
  const clock_t start = ::clock () ;
  { BigUnsigned n = BigUnsigned (1) ;
    n <<= 127 ;
    n -= 1 ;
    const std::string s = n.spacedDecimalString (3) ;
    std::cout << "  2**127 - 1 = " << s.c_str () << "\n" ;
  }
  { BigUnsigned n = BigUnsigned (1) ;
    n <<= 148 ;
    n += 1 ;
    const BigUnsignedQuotientU64Remainder r = n.dividingByChunkUInt (17) ;
    n = r.quotient () ;
    const std::string s = n.spacedDecimalString (3) ;
    std::cout << "  (2**148 + 1) / 17 = " << s.c_str () << "\n" ;
  }
  { BigUnsigned n = BigUnsigned (1) ;
    n <<= 607 ;
    n -= 1 ;
    const std::string s = n.spacedDecimalString (3) ;
    std::cout << "  2**607 - 1 = " << s.c_str () << "\n" ;
  }
  { BigUnsigned n = BigUnsigned (1) ;
    n <<= 4423 ;
    n -= 1 ;
    const std::string s = n.spacedDecimalString (3) ;
    std::cout << "  2**4423 - 1 = " << s.c_str () << "\n" ;
  }
  { BigUnsigned n = BigUnsigned (1) ;
    n <<= 44497 ;
    n -= 1 ;
    const std::string s = n.spacedDecimalString (3) ;
    std::cout << "  2**44497 - 1 = " << s.c_str () << "\n" ;
  }
  std::cout << msFromStart (start) << " ms\n" ;
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
  somePrimeNumbers () ;
  pgcdComputing () ;
//---
  std::cout << "ChunkSharedArray Allocation Count: "
            << ChunkSharedArray::chunkSharedArrayAllocationCount () << "\n" ;
  std::cout << "ChunkSharedArray Currently Allocated Count: "
            << ChunkSharedArray::chunkSharedArrayCurrentlyAllocatedCount () << "\n" ;
//---
  std::cout << "Demo done in " << msFromStart (start) << " ms\n" ;
  return 0;
}

//----------------------------------------------------------------------------------------
