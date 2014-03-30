cmake_minimum_required ( VERSION 2.8 )
project ( HelloWorld C )

add_executable(hello_world main.c)
target_link_libraries(hello_world pspdebug pspdisplay pspge pspctrl pspsdk c pspnet pspnet_inet pspnet_apctl pspnet_resolver psputility pspuser pspkernel)
