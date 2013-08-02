########################################################################
#
# Compiler-linker config
#
# this must be macro, because we may use this option outside of this file
macro (set_default_compiler_linker_config)
  if (MSVC11)
      # ref: http://msdn.microsoft.com/en-us/library/fwkeyyhe.aspx
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nologo") # Suppresses display of sign-on banner
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -EHsc") # enable C++ exception
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zc:wchar_t") # treat wchar_t as builtin type
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -GR-") # disable RTTI
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Gd") # default calling convention: __cdecl
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W3") # level 3 warning, Wall is disastrous
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Oy-") # don't omit frame pointers
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWIN32 -DUNICODE -D_UNICODE -D_WINDOWS") # Windows/Unicode etc.
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_VARIADIC_MAX=10") # make varidic elments(tupple/bind/etc.) wide support
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}")
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -MTd") # link to multi thread static library
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -RTC1") # enable runtime check
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Od") # disable optimize
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Gm") # enable minimal rebuild
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -GS") # check for buffer overruns
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ZI") # edit and continue
      set(common_cxx_release_flag "${common_cxx_release_flag} -DNDEBUG") # some macro only in release
      set(common_cxx_release_flag "${common_cxx_release_flag} -MT") # link to multi thread static library
      set(common_cxx_release_flag "${common_cxx_release_flag} -GF") # string pooling
      set(common_cxx_release_flag "${common_cxx_release_flag} -Oy") # omit frame pointers
      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} ${common_cxx_release_flag}")
      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -Ox") # full optimization
      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -GS-") # disable buffer security check
      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -Zi") # Program Database, for debug info
      set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}") # we use same option with RELWITHDEBINFO
      set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}") # we use same option with RELWITHDEBINFO
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -NOLOGO") # Suppresses display of sign-on banner
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -DEBUG") # generate debug info(i.e. pdb info)
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -SUBSYSTEM:CONSOLE") # console application
      set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
      set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /INCREMENTAL") #enable incremental link
      set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SAFESEH:NO") #disable safeseh
      set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS}")
      set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} /INCREMENTAL:NO") #no incremental link
      set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}") # we use same option with RELWITHDEBINFO
      set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}") # we use same option with RELWITHDEBINFO
  elseif (UNIX)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # turns on debugging information
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") # strictest warning policy
      if (APPLE)
          # c++11/c++0x support
          set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
          set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
          set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
          set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
      else()
          # c++11/c++0x support
          set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
      endif()
  endif()
endmacro()
