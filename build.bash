#!/bin/bash

set -e -u -o pipefail

_main() {
	local build_dir
	readonly build_dir=$1
	env LDFLAGS='-fuse-ld=gold -Wl,--threads' cmake -GNinja -H. -B"${build_dir}"
	ninja -C "${build_dir}"
}

_main "$@"
