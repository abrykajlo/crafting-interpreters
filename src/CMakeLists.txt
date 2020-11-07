add_executable(lox main.cpp)
set_target_properties(lox PROPERTIES CXX_STANDARD 17)

target_include_directories(lox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

expr_gen(${CMAKE_CURRENT_SOURCE_DIR}/Expr.def Expr.h)

set(LOX_HEADERS Lox.h Scanner.h Token.h TokenType.h Expr.h)
set(LOX_SRC Lox.cpp Scanner.cpp Token.cpp)
target_sources(lox PRIVATE ${LOX_HEADERS} ${LOX_SRC} ${CMAKE_CURRENT_BINARY_DIR})