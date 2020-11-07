add_executable(exprgen main.cpp)

macro(expr_gen DEF_FILE OUT_FILE)
    add_custom_command(OUTPUT ${OUT_FILE} 
        COMMAND exprgen --def ${DEF_FILE} --out ${OUT_FILE})
endmacro()
