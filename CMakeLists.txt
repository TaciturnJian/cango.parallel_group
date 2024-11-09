cmake_minimum_required(VERSION 3.21)

project(cango.parallel_group)
add_library(cango_parallel_group INTERFACE)
add_library(cango::parallel_group ALIAS cango_parallel_group)
target_include_directories(cango_parallel_group INTERFACE include)
set_target_properties(cango_parallel_group PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

if (MSVC)
	target_compile_options(cango_parallel_group INTERFACE /utf-8)
endif ()

if (PROJECT_IS_TOP_LEVEL)
	add_executable(cango_parallel_group_grammar_test test/grammar_test.cpp)
	target_link_libraries(cango_parallel_group_grammar_test PRIVATE cango::parallel_group)
	set_target_properties(cango_parallel_group_grammar_test PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
	)
endif ()
