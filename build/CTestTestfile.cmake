# CMake generated Testfile for 
# Source directory: C:/Users/User/Desktop/Lab_Second
# Build directory: C:/Users/User/Desktop/Lab_Second/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(MyTests "C:/Users/User/Desktop/Lab_Second/build/Debug/runTests.exe")
  set_tests_properties(MyTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/Desktop/Lab_Second/CMakeLists.txt;41;add_test;C:/Users/User/Desktop/Lab_Second/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(MyTests "C:/Users/User/Desktop/Lab_Second/build/Release/runTests.exe")
  set_tests_properties(MyTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/Desktop/Lab_Second/CMakeLists.txt;41;add_test;C:/Users/User/Desktop/Lab_Second/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(MyTests "C:/Users/User/Desktop/Lab_Second/build/MinSizeRel/runTests.exe")
  set_tests_properties(MyTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/Desktop/Lab_Second/CMakeLists.txt;41;add_test;C:/Users/User/Desktop/Lab_Second/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(MyTests "C:/Users/User/Desktop/Lab_Second/build/RelWithDebInfo/runTests.exe")
  set_tests_properties(MyTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/Desktop/Lab_Second/CMakeLists.txt;41;add_test;C:/Users/User/Desktop/Lab_Second/CMakeLists.txt;0;")
else()
  add_test(MyTests NOT_AVAILABLE)
endif()
subdirs("googletest")
