#!/bin/bash

set -e -u -o pipefail

_main() {
	# testing for unset variable
	if [[ "${DEBUG+x}" = "x" ]]; then
		set -x
	fi

	local image_id
	readonly image_id=sha256:8238603319080c773ab2eea3bb198c0a7e6a9eb9568122c8f54f6344bd167c0f

	create_container "${image_id}"
}

create_container() {
	local image_id
	image_id=$1
	local workspace
	readonly workspace=~/src/d/greenplum-workspace
	docker run --rm -ti \
		--init \
		--cap-add SYS_PTRACE \
		--volume gpdbccache:/ccache \
		--volume "${workspace}":/workspace:ro \
		--env CCACHE_DIR=/ccache \
		"${image_id}" \
		/workspace/clone-and-build.bash
}

_main "$@"
