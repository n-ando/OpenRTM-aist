#!/bin/bash
# This script checks C++ standard coding error
# -> reserved word: <underscore><letter> of global variable such as _abc

find . -type f -name '*.h' -exec grep -H " _[a-zA-Z]" {} \; \
         -or -name '*.cpp' -exec grep -H " _[a-zA-Z]" {} \; | \
    egrep -v '(Macho\.h|Macho\.cpp)' | 
    egrep -v '(_WIN32|_MSC_VER|_MAX_PATH|_WINSTATIC)' | \
    egrep -v '(_GNU_SOURCE|_TRUNCATE)' | \
    egrep -v '(_CORBA_Unbounded_Sequence)' | \
    egrep -v '(_var|_ptr|_default_POA|_narrow|_nil|_this)' | \
    egrep -v '(_tscopy|_popen|_pclose)'
    




