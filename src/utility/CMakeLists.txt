# Source files
file(GLOB SOURCES "*.c")

# Register the component
idf_component_register(SRCS ${SOURCES} INCLUDE_DIRS "." REQUIRES driver)