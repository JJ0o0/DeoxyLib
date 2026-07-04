#!/bin/bash

set -e

rm -rf build/docs
mkdir -p build/docs

echo "Running Doxygen (API Reference)..."
doxygen Doxyfile

echo "Running MkDocs..."
./.venv/bin/mkdocs build

echo "Documentation generated at build/docs/"