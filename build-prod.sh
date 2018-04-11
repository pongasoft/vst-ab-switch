#!/usr/bin/env bash

# from http://stackoverflow.com/questions/59895/can-a-bash-script-tell-what-directory-its-stored-in
SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do
  DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE"
done
BASEDIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

mkdir -p build/Release
cd build/Release

if [ -z "${VST3_SDK_ROOT}" ]; then
  VST3_SDK_ROOT="/Applications/VST_SDK.369/VST3_SDK"
fi

cmake -DVST3_SDK_ROOT=${VST3_SDK_ROOT} -DCMAKE_BUILD_TYPE=Release ${BASEDIR}
cmake --build . --target archive
