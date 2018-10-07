#!/bin/bash

set -e -u -o pipefail

_main() {
	git clone --shared /workspace /build/greenplum-workspace
	cd /build/greenplum-workspace
	./build.bash /build/build
}

_main "$@"
