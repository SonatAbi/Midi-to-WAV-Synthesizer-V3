
add_executable(compare compare.cpp)
INSTALL(TARGETS compare DESTINATION bin)

if(WIN32)
  set(EXE_NAME qinstrument.exe)
  set(COMPARE_EXE_NAME compare.exe)
else()
  set(EXE_NAME qinstrument)
  set(COMPARE_EXE_NAME compare)
endif()

# these tests should pass

add_test(NAME test1
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test1-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test00.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test2
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test2-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test00_harmonic1.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test3
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test3-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test00_harmonic2.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test4
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test4-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test00_harmonicboth.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test5
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test5-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test01.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
	add_test(NAME test6
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test6-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test01_harmonic1.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test7
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test7-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test01_harmonic2.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test8
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test8-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test01_harmonicboth.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test9
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test9-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test02.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test10
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test10-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test02_harmonic1.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test11
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test11-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test02_harmonic2.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test12
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test12-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test02_harmonicboth.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test13
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test13-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test03.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test14
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test14-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test03_harmonic1.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test15
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test15-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test03_harmonic2.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test16
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test16-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test03_harmonicboth.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test17
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test17-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test04.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test18
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test18-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test04_harmonic1.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test19
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test19-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test04_harmonic2.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test20
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test20-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test04_harmonicboth.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test21
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test21-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test04_longer.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
add_test(NAME test22
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}

    -DOUTPUT_FILE=${CMAKE_SOURCE_DIR}/tests/test22-0.wav
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test04_velocity.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
	
	