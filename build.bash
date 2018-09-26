#!/bin/bash

set -e -u -o pipefail

_main() {
	git clone --shared /workspace /build/greenplum-workspace
	cd /build/greenplum-workspace
	env LDFLAGS='-fuse-ld=gold -Wl,--threads' cmake -GNinja -H. -B/build/build
	ninja -C /build/build
}

_main "$@"
