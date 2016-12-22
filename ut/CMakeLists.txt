set(SOURCE_UT fuzzy_search_ut.cpp
              ldistance_ut.cpp
              ring_buffer_ut.cpp
              ut_main.cpp
   )

add_executable(ldistance_ut ${SOURCE_UT})
target_link_libraries(ldistance_ut ldistance)
