cmake_minimum_required(VERSION 3.10)
project(mydenetlib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(TRANSPORT_LAYER_SOURCES
    ../src/TransportLayer/Socket/ASocket.cpp
    ../src/TransportLayer/Socket/UDPSocket.cpp
    ../src/TransportLayer/Socket/TCPSocket.cpp
    src/TCPSocketTest.cpp
    main.cpp
)

add_executable(mydnet ${TRANSPORT_LAYER_SOURCES})

if(WIN32)
    target_link_libraries(mydnet ws2_32)
    set_target_properties(mydnet PROPERTIES SUFFIX ".exe")

    if(MINGW)
        target_link_libraries(mydnet -static-libgcc -static-libstdc++ -static)
    endif()
endif()

target_include_directories(mydnet PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)