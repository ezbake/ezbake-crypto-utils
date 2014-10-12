#!/bin/bash

#   Copyright (C) 2013-2014 Computer Sciences Corporation
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.


[ -z $REQUIRED_THRIFT_VERSION ] && REQUIRED_THRIFT_VERSION='0.9.1'
[ -z $BUILD_DIR ]               && BUILD_DIR='src/test/thrift/generated-sources'
[ -z $LANGUAGES_TO_GENERATE ]   && LANGUAGES_TO_GENERATE=(java)
[ -z $FINAL_DIR ]               && FINAL_DIR='src/test'


fail() {
  echo $@
  exit 0
}

# Test to see if we have thrift installed
VERSION=$(thrift -version 2>/dev/null | grep -F "${REQUIRED_THRIFT_VERSION}" |  wc -l)
if [ "$VERSION" -ne 1 ] ; then
  # Nope: bail
  echo "****************************************************"
  echo "*** thrift is not available"
  echo "***   expecting 'thrift -version' to return ${REQUIRED_THRIFT_VERSION}"
  echo "*** generated code will not be updated"
  fail "****************************************************"
fi


THRIFT_ARGS=" -I src/test/thrift -o $BUILD_DIR"
mkdir -p $BUILD_DIR
rm -rf $BUILD_DIR/gen-java

for f in src/test/thrift/*.thrift; do
  thrift ${THRIFT_ARGS} --gen java $f || fail unable to generate java thrift classes
  thrift ${THRIFT_ARGS} --gen py $f || fail unable to generate python thrift classes
  thrift ${THRIFT_ARGS} --gen rb $f || fail unable to generate ruby thrift classes
  thrift ${THRIFT_ARGS} --gen cpp $f || fail unable to generate cpp thrift classes
done
