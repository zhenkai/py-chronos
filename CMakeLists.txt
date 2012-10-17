project(hello)
cmake_minimum_required(VERSION 2.8.3)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /opt/local/lib)
FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs REQUIRED)
FIND_PACKAGE(Boost COMPONENTS python-mt system-mt REQUIRED)

ENABLE_TESTING()
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
LINK_LIBRARIES(${Boost_LIBRARIES} ${PYTHON_LIBRARIES}) # Deprecated but so convenient!

INCLUDE_DIRECTORIES(/usr/local/include/sync)
LINK_LIBRARIES(-lsync)

PYTHON_ADD_MODULE(chronos chronos.cpp simple-chronos-socket.cpp)
FILE(COPY chronos.py DESTINATION .)
ADD_TEST(. chronos.py)

