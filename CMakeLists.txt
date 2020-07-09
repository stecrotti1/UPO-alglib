cmake_minimum_required(VERSION 3.14)
project(alg_workspace C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(include/upo)
include_directories(src)

add_executable(alg_workspace
        apps/use_timer.c
        include/upo/error.h
        include/upo/hires_timer.h
        include/upo/io.h
        include/upo/macro.h
        include/upo/random.h
        include/upo/timer.h
        include/upo/utility.h
        include/upo/stack.h
        include/upo/hashtable.h
        src/hires_timer.c
        src/hires_timer_private.h
        src/io.c
        src/random.c
        src/timer.c
        src/timer_private.h
        src/utility.c
        src/stack.c
        src/stack_private.h
        src/hashtable.c
        src/hashtable_private.h
        test/test_hires_timer.c
        test/test_timer.c
        test/test_stack.c
        test/test_bst.c
        test/test_bst_more.c
        test/test_hashtable_linprob.c
        test/test_hashtable_linprob_more.c
        test/test_hashtable_sepchain.c
        test/test_hashtable_sepchain_more.c)
