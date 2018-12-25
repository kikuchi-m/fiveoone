cc_binary(
    name = 'udp_server',
    srcs = [
        'udp_server.cc',
    ],
    deps = [
        'sample_cc_proto',
        '@boost//:lib-boost-asio',
    ],
)

cc_binary(
    name = 'udp_client',
    srcs = [
        'udp_client.cc',
    ],
    deps = [
        'sample_cc_proto',
        '@boost//:lib-boost-asio',
    ],
)

proto_library(
    name = 'sample_proto',
    srcs = [
        'sample.proto',
    ],
)

cc_proto_library(
    name = 'sample_cc_proto',
    deps = [
        ':sample_proto',
    ],
)
