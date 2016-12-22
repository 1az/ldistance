set(SOURCE_LIB fuzzy_search.cpp
               ldistance.cpp
               ring_buffer.cpp
   )

add_library(ldistance STATIC ${SOURCE_LIB})
target_include_directories(ldistance PUBLIC ${CMAKE_CURRENT_LIST_DIR})
