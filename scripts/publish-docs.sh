#!/usr/bin/env bash

# For GitHub Actions CI

set -euxo pipefail

SCRIPT_DIR=$(dirname "$0")

THIS_BRANCH="${GITHUB_REF##*/}"
EDIT_BRANCH=master # Name of branch on which edits are made
DOCS_BRANCH=docs # Name of branch on which HTML docs are published
CURRENT_COMMIT="$(git rev-parse HEAD)"

# Directoy on which we run ./configure
cd "${SCRIPT_DIR}/.."

./configure

# Create HTML pages in doc/g2hecdoc.html/
make html

# Copy generated documentation files to docs/
mkdir -p docs
cp -r doc/g2hecdoc.html/* docs/

# Force add gitignored docs/ directory. It makes it easy to publish docs
# to the docs branch. We do not push this to origin.
git add -f docs

git config --global user.name "libg2hec GHA CI"
git config --global user.email "syncom@users.noreply.github.com"
git commit -m \
  "Libg2hec documentation built on $(date) from ${CURRENT_COMMIT}"

NEW_COMMIT="$(git rev-parse HEAD)"

# Debugging info
git show --stat
git fetch --all
git remote -v
git branch -a
# End debugging info

# Cherry pick docs update into docs branch
git checkout "${DOCS_BRANCH}" --
git pull --ff-only
git cherry-pick --strategy-option theirs --keep-redundant-commits \
  "${NEW_COMMIT}"

# Update new commit SHA
NEW_COMMIT="$(git rev-parse HEAD)"

# For debugging
git show --stat

# Only publish docs if we are on master
if [ "${THIS_BRANCH}" != "${EDIT_BRANCH}" ]; then
  echo "${THIS_BRANCH} is not ${EDIT_BRANCH}. Skip publication."
  exit 0
else
  echo "Publishing documentation to refs/heads/${DOCS_BRANCH}"
  #git push -f "${NEW_COMMIT}:refs/heads/${DOCS_BRANCH}"
fi



