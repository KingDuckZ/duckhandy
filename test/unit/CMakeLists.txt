project(dhandy_unit_test CXX)

add_executable(${PROJECT_NAME}
	main.cpp
	lexical_cast_test.cpp
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${DUCKHANDY_SOURCE_DIR}/lib/Catch/single_include
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE duckhandy
)

add_test(
	NAME DuckHandyTest
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND ${PROJECT_NAME}
)
