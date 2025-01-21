# LED Controller Component Configuration

idf_component_register(
    SRCS 
        "led_controller.c"
        "main.c"
    INCLUDE_DIRS 
        "."
    REQUIRES 
        led_strip
    EMBED_FILES 
        Kconfig.projbuild
)