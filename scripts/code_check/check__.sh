#!/bin/bash
# This script checks C++ standard coding error
# -> double underscore is illeagal such as __ABC

grep "__" -r . | \
    egrep "\.(cpp|h):" | \
    egrep -v "(doil|tests)" | \
    egrep -v "(__QNX|__RTP|__NT|__WIN32|__GNU|__gnu|__clang__|__linux|__declspec|__powerpc|__arm|__pragma|__attribute|_____)" | \
    egrep -v "(__widget__|__type__|__constraints__)" | \
    egrep -v "(__rosidl)" | \
    egrep -v "(__restrict)" | \
    egrep -v "(__this())"

