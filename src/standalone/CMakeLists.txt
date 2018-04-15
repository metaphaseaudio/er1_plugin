add_executable(VirtualER-1 VirtualER1Component.cpp ER1Application.cpp)
target_link_libraries(VirtualER-1 er1lib ${ER1_LIBS})