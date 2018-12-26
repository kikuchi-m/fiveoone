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

java_binary(
    name = 'udp_server_java',
    srcs = glob([
        'java/src/main/*.java',
    ]),
    main_class = 'sample.UdpServer',
    deps = [
        'sample_java_proto',
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

java_proto_library(
    name = 'sample_java_proto',
    deps = [
        ':sample_proto',
    ],
)
