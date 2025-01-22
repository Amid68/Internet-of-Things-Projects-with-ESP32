idf_component_register(
    SRCS 
        "blinking.c"
        "components/led_controller/led_controller.c"
        "components/blinking_sequence/blinking_sequence.c"
    
    INCLUDE_DIRS 
        "."
        "components/led_controller"
        "components/blinking_sequence"
)