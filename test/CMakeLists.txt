file(GLOB SOURCE_FILES *.h *.cpp ../C1.h ../C1.cpp)
add_executable(MyAppTests ${SOURCE_FILES})



target_include_directories(MyAppTests PUBLIC "catch/")
