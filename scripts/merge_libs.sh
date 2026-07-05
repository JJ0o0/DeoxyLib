#!/bin/bash

mkdir -p temp_merge
cd temp_merge

ar -x ../build/Deoxy/libDeoxy.a
ar -x ../build/Vendor/libimgui.a
ar -x ../build/Vendor/spdlog/libspdlog.a

ar -rcs libDeoxy_Full.a *.o

mv libDeoxy_Full.a ../dist/lib/libDeoxy.a

cd ..
rm -rf temp_merge

echo "'Fat' (Deoxy + Dependencies) created in dist/lib/libDeoxy.a"