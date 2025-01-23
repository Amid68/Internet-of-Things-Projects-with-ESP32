idf_component_register(
    SRCS "dhtdemo.c"
    INCLUDE_DIRS "."
    REQUIRES dht
    PRIV_REQUIRES freertos driver
)