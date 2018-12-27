java_binary(
    name = 'five_o_one_server',
    srcs = glob([
        'src/main/java/**/*.java',
    ]),
    main_class = 'jp.co.atware.five_o_one.Application',
    javacopts = [
        '-Xlint:deprecation',
        '-Xlint:unchecked',
    ],
    deps = [
        '//protocol:leap_proto_java',
    ],
)

