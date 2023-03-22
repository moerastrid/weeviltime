#!/bin/sh

maps=$(find ./cub_maps/invalid -type f -name '*.cub')

for map in $maps; do
echo "Testing: <$map>"
./cub3D $map
echo
done