# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Espressif/frameworks/esp-idf-v5.1.2/components/bootloader/subproject"
  "C:/Users/user/workspace/esp32/scan/230400/bootloader"
  "C:/Users/user/workspace/esp32/scan/230400/bootloader-prefix"
  "C:/Users/user/workspace/esp32/scan/230400/bootloader-prefix/tmp"
  "C:/Users/user/workspace/esp32/scan/230400/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/user/workspace/esp32/scan/230400/bootloader-prefix/src"
  "C:/Users/user/workspace/esp32/scan/230400/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/user/workspace/esp32/scan/230400/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/user/workspace/esp32/scan/230400/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
