# In The Name Of God
# ========================================
# [] File Name : CMakeLists.txt
#
# [] Creation Date : 08-04-2015
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
add_executable(TBMap.out bitmap.h main.c bitmap.c common.c common.h)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0 -g -std=gnu11 ")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -DDEBUG")
