#!/bin/bash
# This script checks C++ standard coding error
# -> reserved word: <underscore><captal_letter> such as _ABC

find . -type f -name '*.h' -exec grep -H " _[A-Z]" {} \; \
         -or -name '*.cpp' -exec grep -H " _[A-Z]" {} \; | \
    egrep -v '(Macho\.h|Macho\.cpp)' | 
    egrep -v '(_WIN32|_MSC_VER|_MAX_PATH)' | \
    egrep -v '(_GNU_SOURCE|_TRUNCATE)' | \
    egrep -v '(_CORBA_Unbounded_Sequence)'



