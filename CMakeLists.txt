cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(duckhandy)
list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

include(shared_git_project)
include(CTest)

set(DUCKHANDY_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(${PROJECT_NAME} INTERFACE)

target_compile_features(${PROJECT_NAME}
	INTERFACE cxx_nullptr
	INTERFACE cxx_range_for
	INTERFACE cxx_lambdas
	INTERFACE cxx_decltype_auto
	INTERFACE cxx_defaulted_functions
	INTERFACE cxx_deleted_functions
	INTERFACE cxx_auto_type
	INTERFACE cxx_decltype_incomplete_return_types
	INTERFACE cxx_noexcept
	INTERFACE cxx_rvalue_references
)

target_include_directories(${PROJECT_NAME}
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/sprout
)
target_compile_definitions(${PROJECT_NAME}
	INTERFACE SPROUT_NO_CXX11_NUMERIC_LIMITS
	INTERFACE SPROUT_USE_TEMPLATE_ALIASES
)

if (BUILD_TESTING)
	add_subdirectory(test/unit)
endif()
