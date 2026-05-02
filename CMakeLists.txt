cmake_minimum_required(VERSION 3.20)
project(ghg LANGUAGES C CXX)

add_executable(ghg source/game.c source/vol.cpp source/say.cpp)

target_link_libraries(ghg cjson)

if(NOT WIN32)
 set(CROSS_LIB_DIR ~/cross/${ARCH_CODE}/usr/lib/${ARCH_CODE})
 target_link_directories(ghg PUBLIC ${CROSS_LIB_DIR} PUBLIC ${CROSS_LIB_DIR}/pulseaudio)
 target_link_libraries(ghg asound espeak)
endif()

# sometimes I forget about /usr/games...

install(TARGETS ghg
 RUNTIME DESTINATION games)

install(FILES ghg.6 DESTINATION share/man/man6)
install(DIRECTORY AtypicalAdventure DESTINATION ../var/games/ghg/examples)
