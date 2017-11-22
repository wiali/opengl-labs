set (SOURCES
	lighting.cpp
	main.cpp
  )

set (HEADERS
	lighting.h
  )

qt5_wrap_cpp (SOURCES ${HEADERS})

add_executable (lighting-test ${SOURCES})
target_link_libraries (lighting-test ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES})