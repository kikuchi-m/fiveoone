package(
    default_visibility = ['//visibility:public'],
)

proto_library(
    name = 'leap_proto',
    srcs = [
        'leap.proto',
    ],
)

cc_proto_library(
    name = 'leap_proto_cc',
    deps = [
        ':leap_proto',
    ],
)

java_proto_library(
    name = 'leap_proto_java',
    deps = [
        ':leap_proto',
    ],
)
