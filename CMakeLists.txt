project(chronos)
cmake_minimum_required(VERSION 2.8.3)
FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs REQUIRED)
FIND_PACKAGE(Boost COMPONENTS python-mt REQUIRED)

ENABLE_TESTING()
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
LINK_LIBRARIES(${Boost_LIBRARIES} ${PYTHON_LIBRARIES}) # Deprecated but so convenient!

INCLUDE_DIRECTORIES(/usr/local/include/sync)
LINK_LIBRARIES(/usr/local/lib)

PYTHON_ADD_MODULE(chronos chronos.cpp)
FILE(COPY chronos.py DESTINATION .)
ADD_TEST(. chronos.py)

