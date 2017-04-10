
find_package( OpenCV REQUIRED )

file(GLOB_RECURSE CCV_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable (ccv ${CCV_SRC} ConvolveMatrix.cpp ../include/ConvolveMatrix.h)

target_link_libraries(ccv ${OpenCV_LIBS})


