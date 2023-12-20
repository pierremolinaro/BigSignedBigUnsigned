#!/usr/bin/python3
# -*- coding: utf-8 -*-

#------------------------------------------------------------------------------

import os
import sys
import subprocess

#------------------------------------------------------------------------------
#   FOR PRINTING IN COLOR
#··············································································

def BLUE () :
  return '\033[94m'

#··············································································

def ENDC () :
  return '\033[0m'

#··············································································

def BOLD () :
  return '\033[1m'

#··············································································

def BOLD_BLUE () :
  return BOLD () + BLUE ()

#------------------------------------------------------------------------------

def runCommand (command) :
  childProcess = subprocess.Popen (command)
  childProcess.wait ()
  if childProcess.returncode != 0 :
    print (BOLD_RED () + "**** Error Code " + str (childProcess.returncode) + ENDC ())
    sys.exit (childProcess.returncode)

#------------------------------------------------------------------------------

def invocationList () :
  result = ["g++", "-std=c++14", "-O2"]
  result.append ("-Isources")
  result.append ("sources/BigSigned-add.cpp")
  result.append ("sources/BigSigned-bit.cpp")
  result.append ("sources/BigSigned-chunk-operations.cpp")
  result.append ("sources/BigSigned-constructors.cpp")
  result.append ("sources/BigSigned-conversions.cpp")
  result.append ("sources/BigSigned-divide.cpp")
  result.append ("sources/BigSigned-logic-operations.cpp")
  result.append ("sources/BigSigned-multiply.cpp")
  result.append ("sources/BigSigned-print.cpp")
  result.append ("sources/BigSigned-shifts.cpp")
  result.append ("sources/BigSigned-subtract.cpp")
  result.append ("sources/BigSigned-utilities.cpp")
  result.append ("sources/BigSigned.cpp")
  result.append ("sources/BigUnsigned-add.cpp")
  result.append ("sources/BigUnsigned-bit.cpp")
  result.append ("sources/BigUnsigned-chunk-operations.cpp")
  result.append ("sources/BigUnsigned-constructors.cpp")
  result.append ("sources/BigUnsigned-conversions.cpp")
  result.append ("sources/BigUnsigned-divide-naive.cpp")
  result.append ("sources/BigUnsigned-divide.cpp")
  result.append ("sources/BigUnsigned-logic-operations.cpp")
  result.append ("sources/BigUnsigned-multiply.cpp")
  result.append ("sources/BigUnsigned-print.cpp")
  result.append ("sources/BigUnsigned-shifts.cpp")
  result.append ("sources/BigUnsigned-subtract.cpp")
  result.append ("sources/BigUnsigned-utilities.cpp")
  result.append ("sources/ChunkSharedArray.cpp")
  result.append ("sources/macroAssert.cpp")
  result.append ("sources/galgas-random.cpp")
  return result

#------------------------------------------------------------------------------

#--- Get script absolute path
scriptDir = os.path.dirname (os.path.abspath (sys.argv [0]))
os.chdir (scriptDir)
#--- Build and run (8 bits chunks)
print (BOLD_BLUE () + "8 bits chunk, debug mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-quick-check.cpp",
  "-DUSE_8_BITS_CHUNKS",
  "-o", "main-quick-check-8-bits-chunks-debug"
])
runCommand (["./main-quick-check-8-bits-chunks-debug"])
print (BOLD_BLUE () + "8 bits chunk, release mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-quick-check.cpp",
  "-DUSE_8_BITS_CHUNKS",
  "-DDO_NOT_GENERATE_CHECKINGS",
  "-o", "main-quick-check-8-bits-chunks-release"
])
runCommand (["./main-quick-check-8-bits-chunks-release"])

#--- Build and run (16 bits chunks)
print (BOLD_BLUE () + "16 bits chunk, debug mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-quick-check.cpp",
  "-DUSE_16_BITS_CHUNKS",
  "-o", "main-quick-check-16-bits-chunks-debug"
])
runCommand (["./main-quick-check-16-bits-chunks-debug"])
print (BOLD_BLUE () + "16 bits chunk, release mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-quick-check.cpp",
  "-DUSE_16_BITS_CHUNKS",
  "-DDO_NOT_GENERATE_CHECKINGS",
  "-o", "main-quick-check-16-bits-chunks-release"
])
runCommand (["./main-quick-check-16-bits-chunks-release"])

#--- Build and run (32 bits chunks)
print (BOLD_BLUE () + "32 bits chunk, debug mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-quick-check.cpp",
  "-DUSE_32_BITS_CHUNKS",
  "-o", "main-quick-check-32-bits-chunks-debug"
])
runCommand (["./main-quick-check-32-bits-chunks-debug"])
print (BOLD_BLUE () + "32 bits chunk, release mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-quick-check.cpp",
  "-DUSE_32_BITS_CHUNKS",
  "-DDO_NOT_GENERATE_CHECKINGS",
  "-o", "main-quick-check-32-bits-chunks-release"
])
runCommand (["./main-quick-check-32-bits-chunks-release"])

#--- Build and run (64 bits chunks)
print (BOLD_BLUE () + "64 bits chunk, debug mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-quick-check.cpp",
  "-o", "main-quick-check-64-bits-chunks-debug"
])
runCommand (["./main-quick-check-64-bits-chunks-debug"])
print (BOLD_BLUE () + "64 bits chunk, release mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-quick-check.cpp",
  "-DDO_NOT_GENERATE_CHECKINGS",
  "-o", "main-quick-check-64-bits-chunks-release"
])
runCommand (["./main-quick-check-64-bits-chunks-release"])

#------------------------------------------------------------------------------
