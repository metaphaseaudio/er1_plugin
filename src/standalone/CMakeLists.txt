if (WIN32)
	add_executable(VirtualER-1 WIN32 VirtualER1Component.cpp ER1Application.cpp)
else()
    add_executable(VirtualER-1 VirtualER1Component.cpp ER1Application.cpp)
endif()

target_link_libraries(VirtualER-1 er1lib ${ER1_LIBS})