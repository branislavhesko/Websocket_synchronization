cmake_minimum_required(VERSION 3.15)
project(websockets_communication)

set(CMAKE_CXX_STANDARD 17)

add_executable(websockets_server server.cpp save_synchronization.cpp save_synchronization.h timer.h)
add_executable(websockets_client client.cpp save_synchronization.cpp save_synchronization.h timer.h websocket_client.cpp websocket_client.hpp)
add_executable(websockets_core_client websocket_core_client.cpp json.hpp request_handler.hpp)
add_executable(websockets_core_server websockets_core_server.cpp json.hpp request_handler.hpp)
find_package(ZLIB REQUIRED)


target_link_libraries(websockets_server libixwebsocket.a pthread ${ZLIB_LIBRARIES})
target_link_libraries(websockets_client libixwebsocket.a pthread ${ZLIB_LIBRARIES})
target_link_libraries(websockets_core_client libixwebsocket.a pthread ${ZLIB_LIBRARIES})
target_link_libraries(websockets_core_server libixwebsocket.a pthread ${ZLIB_LIBRARIES})