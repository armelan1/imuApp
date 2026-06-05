#!/bin/bash
set -e

PORT=${1:-/dev/ttyACM0}

echo "Building..."
idf.py build

echo "Flashing to $PORT..."
idf.py -p "$PORT" flash monitor
