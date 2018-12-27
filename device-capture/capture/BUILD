package(
    default_visibility = ['//visibility:public'],
)

cc_library(
    name = 'leap_capture',
    srcs = [
        'frame_sender.cc',
        'udp_client.cc',
    ],
    hdrs = [
        'export.h',
        'frame_sender.h',
        'udp_client.h',
    ],
    deps = [
        '//protocol:leap_proto_cc',
    ],
)
