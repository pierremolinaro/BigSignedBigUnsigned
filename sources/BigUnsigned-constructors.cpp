//--------------------------------------------------------------------------------------------------

#include "BigUnsigned.h"
#include "galgas-random.h"

//--------------------------------------------------------------------------------------------------

#ifdef PRAGMA_MARK_ALLOWED
  #pragma mark Constructors
#endif

//--------------------------------------------------------------------------------------------------

BigUnsigned BigUnsigned::randomNumber (void) {
  const size_t MAX_BYTE_SIZE = 160 ;
  const size_t randomByteCount = 1 + galgas_random () % MAX_BYTE_SIZE ;
  std::vector <uint8_t> u8BigEndianArray ; ;
  for (size_t i = 0 ; i < randomByteCount ; i ++) {
    u8BigEndianArray.push_back (uint8_t (galgas_random ())) ;
  }
  return BigUnsigned (u8BigEndianArray) ;
}

//--------------------------------------------------------------------------------------------------

BigUnsigned::BigUnsigned (void) :
mSharedArray () {
}

//--------------------------------------------------------------------------------------------------

BigUnsigned BigUnsigned::powerOfTwo (const uint32_t inPowerOfTwo) {
  const size_t wordCount = 1 + inPowerOfTwo / ChunkUIntBitCount ;
  const int32_t bitIndex = inPowerOfTwo % ChunkUIntBitCount ;
  BigUnsigned result ;
  result.mSharedArray.insulateWithChunkCapacity (wordCount) ;
  result.mSharedArray.appendChunks (wordCount - 1, 0 COMMA_HERE) ;
  result.mSharedArray.appendChunk (ChunkUInt (ChunkUInt (1) << bitIndex) COMMA_HERE) ;
  return result ;
}

//--------------------------------------------------------------------------------------------------

BigUnsigned::BigUnsigned (const std::string & inString, const uint8_t inSeparator) :
mSharedArray () {
  size_t idx = 0 ;
  ChunkUInt accumulator = 0 ;
  for (size_t i = 0 ; i < inString.length () ; i++) {
    const char c = inString.c_str () [i] ;
    if ((c >= '0') && (c <= '9')) {
      accumulator *= 10 ;
      accumulator += ChunkUInt (c - '0') ;
      idx += 1 ;
      if (idx == greatestPowerOf10DigitCount) {
        idx = 0 ;
        *this *= greatestPowerOf10 ;
        *this += accumulator ;
        accumulator = 0 ;
      }
    }else if (c != inSeparator) {
      std::cout << "Error " << __FILE__ << ":" << __LINE__ << "\n" ;
      exit (1) ;
    }
  }
  if (idx > 0) {
    ChunkUInt multiplier = 10 ;
    for (size_t i = 1 ; i < idx ; i++) {
      multiplier *= 10 ;
    }
    *this *= multiplier ;
    *this += accumulator ;
  }
}


//--------------------------------------------------------------------------------------------------

BigUnsigned::BigUnsigned (const BigUnsigned & inSource) :
mSharedArray (inSource.mSharedArray) {
}

//--------------------------------------------------------------------------------------------------

BigUnsigned & BigUnsigned::operator = (const BigUnsigned & inSource) {
  mSharedArray = inSource.mSharedArray ;
  return *this ;
}

//--------------------------------------------------------------------------------------------------

#ifdef PRAGMA_MARK_ALLOWED
  #pragma mark Constructors for 8 bits chunks
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_8_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const uint64_t inValue) :
  mSharedArray (8) {
    uint64_t v = inValue ;
    for (size_t i = 0 ; i < 8 ; i++) {
      mSharedArray.appendChunk (uint8_t (v) COMMA_HERE) ;
      v >>= 8 ;
    }
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_8_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const std::vector <uint8_t> & inBigEndianArray) :
  mSharedArray (inBigEndianArray.size ()) {
    for (auto it = inBigEndianArray.rbegin () ; it != inBigEndianArray.rend () ; it++) {
      mSharedArray.appendChunk (*it COMMA_HERE) ;
    }
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_8_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const std::vector <uint64_t> & inBigEndianArray) :
    mSharedArray (inBigEndianArray.size () * 8) {
    for (auto it = inBigEndianArray.rbegin () ; it != inBigEndianArray.rend () ; it++) {
      uint64_t v = *it ;
      for (size_t j = 0 ; j < 8 ; j++) {
        mSharedArray.appendChunk (uint8_t (v) COMMA_HERE) ;
        v >>= 8 ;
      }
    }
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef PRAGMA_MARK_ALLOWED
  #pragma mark Constructors for 32 bits chunks
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_32_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const uint64_t inValue) :
  mSharedArray (2) {
    mSharedArray.appendChunk (uint32_t (inValue) COMMA_HERE) ;
    mSharedArray.appendChunk (uint32_t (inValue >> 32) COMMA_HERE) ;
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_32_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const std::vector <uint8_t> & inBigEndianArray) :
  mSharedArray ((inBigEndianArray.size () + 3) / 4) {
    uint32_t accumulator = 0 ;
    size_t phase = 0 ;
    for (auto it = inBigEndianArray.rbegin () ; it != inBigEndianArray.rend () ; it++) {
      const uint64_t v = *it ;
      accumulator |= (v << phase) ;
      phase += 8 ;
      if (phase == 32) {
        mSharedArray.appendChunk (accumulator COMMA_HERE) ;
        accumulator = 0 ;
        phase = 0 ;
      }
    }
    if (phase > 0) {
      mSharedArray.appendChunk (accumulator COMMA_HERE) ;
    }
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_32_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const std::vector <uint64_t> & inBigEndianArray) :
    mSharedArray (inBigEndianArray.size () * 2) {
    for (auto it = inBigEndianArray.rbegin () ; it != inBigEndianArray.rend () ; it++) {
      uint64_t v = *it ;
      for (size_t j = 0 ; j < 2 ; j++) {
        mSharedArray.appendChunk (uint32_t (v) COMMA_HERE) ;
        v >>= 32 ;
      }
    }
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef PRAGMA_MARK_ALLOWED
  #pragma mark Constructors for 16 bits chunks
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_16_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const uint64_t inValue) :
  mSharedArray (4) {
    mSharedArray.appendChunk (uint16_t (inValue) COMMA_HERE) ;
    mSharedArray.appendChunk (uint16_t (inValue >> 16) COMMA_HERE) ;
    mSharedArray.appendChunk (uint16_t (inValue >> 32) COMMA_HERE) ;
    mSharedArray.appendChunk (uint16_t (inValue >> 48) COMMA_HERE) ;
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_16_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const std::vector <uint8_t> & inBigEndianArray) :
  mSharedArray ((inBigEndianArray.size () + 1) / 2) {
    uint16_t accumulator = 0 ;
    size_t phase = 0 ;
    for (auto it = inBigEndianArray.rbegin () ; it != inBigEndianArray.rend () ; it++) {
      const uint64_t v = *it ;
      accumulator |= (v << phase) ;
      phase += 8 ;
      if (phase == 16) {
        mSharedArray.appendChunk (accumulator COMMA_HERE) ;
        accumulator = 0 ;
        phase = 0 ;
      }
    }
    if (phase > 0) {
      mSharedArray.appendChunk (accumulator COMMA_HERE) ;
    }
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_16_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const std::vector <uint64_t> & inBigEndianArray) :
    mSharedArray (inBigEndianArray.size () * 4) {
    for (auto it = inBigEndianArray.rbegin () ; it != inBigEndianArray.rend () ; it++) {
      uint64_t v = *it ;
      for (size_t j = 0 ; j < 4 ; j++) {
        mSharedArray.appendChunk (uint16_t (v) COMMA_HERE) ;
        v >>= 16 ;
      }
    }
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef PRAGMA_MARK_ALLOWED
  #pragma mark Constructors for 64 bits chunks
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_64_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const uint64_t inValue) :
  mSharedArray (1) {
    mSharedArray.appendChunk (inValue COMMA_HERE) ;
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_64_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const std::vector <uint8_t> & inBigEndianArray) :
  mSharedArray ((inBigEndianArray.size () + 7) / 8) {
    uint64_t accumulator = 0 ;
    size_t phase = 0 ;
    for (auto it = inBigEndianArray.rbegin () ; it != inBigEndianArray.rend () ; it++) {
      const uint64_t v = *it ;
      accumulator |= (v << phase) ;
      phase += 8 ;
      if (phase == 64) {
        mSharedArray.appendChunk (accumulator COMMA_HERE) ;
        accumulator = 0 ;
        phase = 0 ;
      }
    }
    if (phase > 0) {
      mSharedArray.appendChunk (accumulator COMMA_HERE) ;
    }
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------

#ifdef USE_64_BITS_CHUNKS
  BigUnsigned::BigUnsigned (const std::vector <uint64_t> & inBigEndianArray) :
    mSharedArray (inBigEndianArray.size ()) {
    for (auto it = inBigEndianArray.rbegin () ; it != inBigEndianArray.rend () ; it++) {
      mSharedArray.appendChunk (*it COMMA_HERE) ;
    }
    mSharedArray.removeLeadingZeroChunks (HERE) ;
  }
#endif

//--------------------------------------------------------------------------------------------------
