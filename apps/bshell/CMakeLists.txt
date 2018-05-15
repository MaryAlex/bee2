include_directories(commands)
include_directories(utils)

add_executable(bshell
        constants.h
        commands/commandsImpl/bpace_alice_start.c
        commands/commandsImpl/bpace_bob_start.c
        commands/commandsImpl/command.c
        commands/commandsImpl/help.c
        commands/bpace_alice_start.h
        commands/bpace_bob_start.h
        commands/command.h
        commands/help.h
        utils/utilsImpl/bpace_util.c
        utils/utilsImpl/string_util.c
        utils/utilsImpl/file_util.c
        utils/string_util.h
        utils/bpace_util.h
        utils/file_util.h
        bshell.c commands/commandsImpl/bpace_bob_second.c commands/bpace_bob_second.h commands/commandsImpl/bpace_alice_second.c commands/bpace_alice_second.h)

configure_file(demo.sh demo.sh COPYONLY)

target_link_libraries(bshell bee2_static)