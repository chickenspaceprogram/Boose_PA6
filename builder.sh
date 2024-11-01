if [ "$1" = "--help" ] || [ "$1" = "-h" ]
then
  printf "\nbuilder v1.0.0 - Created by Athena Boose <pestpestthechicken@yahoo.com>\n\n"
  printf "usage: builder <path> <name>\n\n"
  printf "builder is a script that automatically builds and cleans up CMake projects.\n\n"
  printf "Argument description:\npath: the place where you want the new directory to be\nname: the name of the new directory and the .tex file\n\n"
  exit 0
fi

if [ "$1" = "--version" ] || [ "$1" = "-v" ]
then
  printf "\nbuilder v1.0.0 - Created by Athena Boose <pestpestthechicken@yahoo.com>\n"
  printf "Enter --help for help.\n\n"
  exit 0
fi

if [ "$1" = "clean" ]
then
  rm -r CMakeFiles
  rm cmake_install.cmake
  rm CMakeCache.txt
  rm Makefile
fi

if [ "$1" = "pkg" ]
then
  mkdir Boose_PA6_zip
  cp -R src Boose_PA6_zip
  cp CMakeLists.txt Boose_PA6_zip
  zip -r Boose_PA6.zip Boose_PA6_zip
  rm -r Boose_PA6_zip
fi