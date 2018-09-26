cmake_minimum_required(VERSION 3.3)
project(gpdb_everything C CXX)

# XXX: this is a hack to rig the find_package in orca
set(XERCES_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/xerces/lib/libxerces-c.so)
set(XERCES_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/xerces/include)

include(ProcessorCount)
ProcessorCount(NCPU)
math(EXPR NJOBS "${NCPU} * 3 / 2")
include(ExternalProject)
ExternalProject_Add(xerces
	SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/xerces
	CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/xerces/configure --disable-network --prefix ${CMAKE_CURRENT_BINARY_DIR}/xerces "CC=ccache ${CMAKE_C_COMPILER}" "CXX=ccache ${CMAKE_CXX_COMPILER}"
	BUILD_COMMAND make install -j${NJOBS} -l${NCPU}
	BUILD_BYPRODUCTS ${XERCES_LIBRARY}
	)

add_subdirectory(orca)

add_dependencies(naucrates xerces)
