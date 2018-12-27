java_binary(
    name = 'fiveoone',
    srcs = glob([
        'src/main/java/**/*.java',
    ]),
    main_class = 'jp.co.atware.fiveoone.Application',
    javacopts = [
        '-Xlint:deprecation',
        '-Xlint:unchecked',
    ],
    deps = [
        '//protocol:leap_proto_java',
    ],
)

