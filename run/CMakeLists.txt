file(GLOB_RECURSE RUN_FILES *.cpp)

add_executable(run ${RUN_FILES})
target_link_libraries(run PRIVATE ${ProjectName})
