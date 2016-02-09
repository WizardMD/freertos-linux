#   Copyright 2016 sean93.park@gmail.com
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

# compile flags
set(FLAGS_COMMON
      "-fno-builtin"
      "-march=i686"
      "-m32"
      )

set(FLAGS_CXXONLY
      "-fpermissive"
      "-fno-exceptions"
      "-fno-rtti"
      )

set(CMAKE_C_FLAGS_DEBUG
      "-O0"
      "-g"
      "-DDEBUG"
      )
set(CMAKE_CXX_FLAGS_DEBUG
      "-O0"
      "-g"
      "-DDEBUG"
      )
set(CMAKE_C_FLAGS_RELEASE
      "-O2"
      "-DNDEBUG"
      )
set(CMAKE_CXX_FLAGS_RELEASE
      "-O2"
      "-DNDEBUG"
      )

# link
set(EXE_LINK_LIBS "pthread")

# file folders
set(FREERTOS_ROOT     "${CMAKE_SOURCE_DIR}/freertos/FreeRTOS")
set(FREERTOS_SOURCE   "${FREERTOS_ROOT}/Source")
set(FREERTOS_INCLUDE  "${FREERTOS_ROOT}/Source/include")

set(PATH_ROOT         "${CMAKE_SOURCE_DIR}")
set(PATH_SOURCE       "${PATH_ROOT}/source")
set(PATH_INCLUDE      "${PATH_ROOT}/include")
set(PATH_PORTABLE     "${PATH_ROOT}/portable")

set(BUILD_ROOT        "${CMAKE_BINARY_DIR}")
set(BUILD_LIB         "${BUILD_ROOT}/../lib")
set(BUILD_BIN         "${BUILD_ROOT}/../bin")


# set options
foreach(FLAG ${FLAGS_COMMON})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG}")
endforeach()

foreach(FLAG ${FLAGS_CXXONLY})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG}")
endforeach()


