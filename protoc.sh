#!/bin/bash
set -e

pushd "$(cd "$(dirname $0)" && pwd)"
device-capture/bazel-device-capture/bazel-out/host/bin/external/com_google_protobuf/protoc \
  --java_out=server/src/main/java/generated \
  device-capture/protocol/leap.proto
