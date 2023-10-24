# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/APCS/CS202 - Programming Systems/Solo Project - CS202/Chess-CS202/build/_deps/sfml-src"
  "E:/APCS/CS202 - Programming Systems/Solo Project - CS202/Chess-CS202/build/_deps/sfml-build"
  "E:/APCS/CS202 - Programming Systems/Solo Project - CS202/Chess-CS202/build/_deps/sfml-subbuild/sfml-populate-prefix"
  "E:/APCS/CS202 - Programming Systems/Solo Project - CS202/Chess-CS202/build/_deps/sfml-subbuild/sfml-populate-prefix/tmp"
  "E:/APCS/CS202 - Programming Systems/Solo Project - CS202/Chess-CS202/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
  "E:/APCS/CS202 - Programming Systems/Solo Project - CS202/Chess-CS202/build/_deps/sfml-subbuild/sfml-populate-prefix/src"
  "E:/APCS/CS202 - Programming Systems/Solo Project - CS202/Chess-CS202/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/APCS/CS202 - Programming Systems/Solo Project - CS202/Chess-CS202/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/APCS/CS202 - Programming Systems/Solo Project - CS202/Chess-CS202/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
