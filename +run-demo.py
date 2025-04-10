#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
#------------------------------------------------------------------------------
# https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
#------------------------------------------------------------------------------

import os
import sys
import subprocess

#------------------------------------------------------------------------------
#   FOR PRINTING IN COLOR
#-----------------------------------------------------------------------------------------

def RED () :
  return '\033[31m'

#··············································································

def BLUE () :
  return '\033[34m'

#··············································································

def ENDC () :
  return '\033[0m'

#··············································································

def BOLD () :
  return '\033[1m'

#··············································································

def BOLD_BLUE () :
  return BOLD () + BLUE ()

#··············································································

def BOLD_RED () :
  return BOLD () + RED ()

#------------------------------------------------------------------------------

def runCommand (command) :
  s = "+"
  for cmd in command:
    s += " " + cmd
  print (BOLD_BLUE () + s + ENDC ())
  childProcess = subprocess.Popen (command)
  childProcess.wait ()
  if childProcess.returncode != 0 :
    print (BOLD_RED () + "**** Error Code " + str (childProcess.returncode) + ENDC ())
    sys.exit (childProcess.returncode)

#------------------------------------------------------------------------------

def invocationList () :
  result = ["g++", "-std=c++14", "-g"]
  result.append ("-Isources")
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
  "main-demo.cpp",
  "-fsanitize=undefined",
  "-fsanitize=address",
  "-DUSE_8_BITS_CHUNKS",
  "-o", "z-main-demo-8-bits-chunks-debug"
])
print ("", flush=True)
runCommand (["./z-main-demo-8-bits-chunks-debug"])

print (BOLD_BLUE () + "8 bits chunk, release mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-demo.cpp",
  "-DDO_NOT_GENERATE_CHECKINGS",
  "-o", "z-main-demo-8-bits-chunks-release"
])
print ("", flush=True)
runCommand (["./z-main-demo-8-bits-chunks-release"])

#--- Build and run (16 bits chunks)
print (BOLD_BLUE () + "16 bits chunk, debug mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-demo.cpp",
  "-fsanitize=undefined",
  "-fsanitize=address",
  "-DUSE_16_BITS_CHUNKS",
  "-o", "z-main-demo-16-bits-chunks-debug"
])
print ("", flush=True)
runCommand (["./z-main-demo-16-bits-chunks-debug"])

print (BOLD_BLUE () + "16 bits chunk, release mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-demo.cpp",
  "-DUSE_16_BITS_CHUNKS",
  "-DDO_NOT_GENERATE_CHECKINGS",
  "-o", "z-main-demo-16-bits-chunks-release"
])
print ("", flush=True)
runCommand (["./z-main-demo-16-bits-chunks-release"])

#--- Build and run (32 bits chunks)
print (BOLD_BLUE () + "32 bits chunk, debug mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-demo.cpp",
  "-fsanitize=undefined",
  "-fsanitize=address",
  "-DUSE_32_BITS_CHUNKS",
  "-o", "z-main-demo-32-bits-chunks-debug"
])
print ("", flush=True)
runCommand (["./z-main-demo-32-bits-chunks-debug"])

print (BOLD_BLUE () + "32 bits chunk, release mode" + ENDC ())
print ("Compiling...") ;
runCommand (invocationList () + [
  "main-demo.cpp",
  "-DUSE_32_BITS_CHUNKS",
  "-DDO_NOT_GENERATE_CHECKINGS",
  "-o", "z-main-demo-32-bits-chunks-release"
])
print ("", flush=True)
runCommand (["./z-main-demo-32-bits-chunks-release"])

#--- Build and run (64 bits chunks)
print (BOLD_BLUE () + "64 bits chunk, debug mode" + ENDC ())

print ("Compiling...") ;
runCommand (invocationList () + [
  "main-demo.cpp",
  "-fsanitize=undefined",
  "-fsanitize=address",
  "-o", "z-main-demo-64-bits-chunks-debug"
])
print ("", flush=True)
runCommand (["./z-main-demo-64-bits-chunks-debug"])
print (BOLD_BLUE () + "64 bits chunk, release mode" + ENDC ())

print ("Compiling...") ;
runCommand (invocationList () + [
  "main-demo.cpp",
  "-DDO_NOT_GENERATE_CHECKINGS",
  "-o", "z-main-demo-64-bits-chunks-release"
])
print ("", flush=True)
runCommand (["./z-main-demo-64-bits-chunks-release"])

#------------------------------------------------------------------------------
