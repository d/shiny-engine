#!/bin/bash

set -e -u -o pipefail

_main() {
	git clone --shared /workspace /build/greenplum-workspace
	cd /build/greenplum-workspace
	cmake -GNinja -H. -B/build/build
	ninja -C /build/build
}

_main "$@"
