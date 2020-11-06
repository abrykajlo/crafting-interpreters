add_executable(exprgen main.cpp)

set(OUPUT_DIR ./output)
set(INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(OUTPUT ${OUTPUT_DIR}/Expr.h
    COMMAND exprgen --def ${INPUT_DIR}/Expr.def --out ${OUTPUT_DIR}/Expr.h
    USES_TERMINAL)
add_custom_target(gen DEPENDS ${OUTPUT_DIR}/Expr.h)