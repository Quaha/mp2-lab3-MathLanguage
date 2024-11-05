file(GLOB_RECURSE SOURCE_FILES *.cpp)

add_library(${ProjectName} ${SOURCE_FILES})
target_include_directories(${ProjectName} PUBLIC ${CMAKE_SOURCE_DIR}/include)
