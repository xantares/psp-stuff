cmake_minimum_required (VERSION 2.8)
project (HelloWorld C)


macro (psp_executable name sources)
  add_executable (${name} ${sources})

  set_target_properties (${name} PROPERTIES SUFFIX ".elf")
  add_custom_command (TARGET ${name} POST_BUILD
    COMMAND psp-fixup-imports ${name}.elf
    COMMAND mksfo "Hello World" PARAM.SFO
    COMMAND psp-strip ${name}.elf -o ${name}_strip.elf
    COMMAND pack-pbp EBOOT.PBP PARAM.SFO NULL NULL NULL NULL NULL ${name}_strip.elf NULL)
endmacro ()

psp_executable (hello_world main.c)
