#!/bin/bash
cd ../Pi/build/test
./KYPHSensors_test
./ProtocolUnwrapper_test
./SQLQuery_test
./SerialDataHandler_test

cd ../../../

lcov -c -d . -o CodeCoverage/Pi/kyph_pi.info

genhtml Pi/kyph_pi.info
