#!/bin/bash
# Check test suite with valgrind
# Note: CppuTest memcheck should be disabled
# Note: Consider using ctest -T memcheck instead

AMICI_PATH="`dirname \"$0\"`"
AMICI_PATH="`( cd \"$AMICI_PATH/..\" && pwd )`"

# read environment variables put there by build script
if [ -f ${AMICI_PATH}/scripts/env.sh ]; then
    . ${AMICI_PATH}/scripts/env.sh
fi

set -e 

# run tests
cd ${AMICI_PATH}/tests/cpputest/build

VALGRIND_OPTS="--leak-check=full --error-exitcode=1 --trace-children=yes"

for MODEL in `ctest -N | grep "Test #" | sed -E 's/ *Test #[0-9]+: (.*)/\1/'`
    do cd ${AMICI_PATH}/tests/cpputest/build/${MODEL}/ && valgrind ${VALGRIND_OPTS} ./model_${MODEL}_test
done
