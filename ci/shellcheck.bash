#!/bin/bash

set -e -u -o pipefail

_main() {
	git ls-files '*.bash' -- :!/orca | xargs shellcheck --shell bash
}

_main "$@"
