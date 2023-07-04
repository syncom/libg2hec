#!/usr/bin/env bash
#
# bear and clang-check (included in LLVM tools) needs to be installed
# for static analysis

set -euxo pipefail

echo "Static analysis through clang static analyzer"
PROJECT_ROOT=$(cd "$(dirname "$0")"; pwd -P)/..

"${PROJECT_ROOT}"/scripts/build.sh

COMPILE_DB_DIR="${PROJECT_ROOT}"
COMPILE_DB="${COMPILE_DB_DIR}/compile_commands.json"
if [ ! -f "${COMPILE_DB}" ]; then
    exit 1
fi

# For debugging
bear --version
BEAR_VERSION_MAJOR="$(bear --version | cut -f2 -d' ' | cut -f1 -d'.')"
if (( BEAR_VERSION_MAJOR > 2 )); then
  FILE_PATHS="$(grep file "${COMPILE_DB}" | \
    awk '{print $2;}' | \
    sed 's/\"//g' | \
    sed 's/,/\//g')"
else
  FILE_PATHS="$(grep -B1 --no-group-separator file "${COMPILE_DB}" | \
    awk '{print $2;}' | \
    sed 's/\"//g' | \
    sed 'N;s/\n//g' | \
    sed 's/,/\//g')"
fi
while read -r FILE; do
  cd "$(dirname "${FILE}")"
  output=$(clang-check -analyze \
    -extra-arg -Xanalyzer \
    -extra-arg -analyzer-disable-checker=unix \
    -extra-arg -Xanalyzer \
    -extra-arg -analyzer-checker=core,deadcode,security,cplusplus,nullability \
    -extra-arg -Xanalyzer \
    -extra-arg -analyzer-disable-checker=security.insecureAPI.DeprecatedOrUnsafeBufferHandling \
    -extra-arg -Xanalyzer \
    -extra-arg -analyzer-output=text \
    -p "${COMPILE_DB_DIR}" \
    "$(basename "${FILE}")" 2>&1)
  if grep -q "warning:" <<< "${output}"; then
    >&2 echo "${output}"
    exit 1
  fi
done <<< "$FILE_PATHS"
echo "Static analysis returns clean result"