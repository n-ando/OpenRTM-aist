cmake_minimum_required (VERSION 2.6)


project (docs)

set(ENABLED_SECTIONS jp)
set(OUTPUT_LANGUAGE Japanese)
set(OUTPUT_DIRECTORY IDLReference)


configure_file(doxygen_idlref.conf.cmake.in ${PROJECT_SOURCE_DIR}/doxygen_idlref.conf @ONLY)

set(OUTPUT_DIRECTORY ClassReference)
configure_file(doxygen_classref.conf.cmake.in ${PROJECT_SOURCE_DIR}/doxygen_classref.conf @ONLY)

add_custom_command(
	OUTPUT IDLReference/html/index.html
	COMMAND doxygen ${PROJECT_SOURCE_DIR}/doxygen_idlref.conf
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
add_custom_target(IDLReference DEPENDS IDLReference/html/index.html)



add_custom_command(
	OUTPUT ClassReference/html/index.html
	COMMAND doxygen ${PROJECT_SOURCE_DIR}/doxygen_idlref.conf
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
add_custom_target(ClassReference DEPENDS ClassReference/html/index.html)





set(ENABLED_SECTIONS )
set(OUTPUT_LANGUAGE English)
set(OUTPUT_DIRECTORY IDLReference-en)


configure_file(doxygen_idlref.conf.cmake.in ${PROJECT_SOURCE_DIR}/doxygen_idlref-en.conf @ONLY)


set(OUTPUT_DIRECTORY ClassReference-en)

configure_file(doxygen_classref.conf.cmake.in ${PROJECT_SOURCE_DIR}/doxygen_classref-en.conf @ONLY)



add_custom_command(
	OUTPUT IDLReference-en/html/index.html
	COMMAND doxygen ${PROJECT_SOURCE_DIR}/doxygen_idlref-en.conf
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
add_custom_target(IDLReference-en DEPENDS IDLReference-en/html/index.html)



add_custom_command(
	OUTPUT ClassReference-en/html/index.html
	COMMAND doxygen ${PROJECT_SOURCE_DIR}/doxygen_idlref-en.conf
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
add_custom_target(ClassReference-en DEPENDS ClassReference-en/html/index.html)



install(DIRECTORY IDLReference DESTINATION docs)
install(DIRECTORY ClassReference DESTINATION docs)
install(DIRECTORY IDLReference-en DESTINATION docs)
install(DIRECTORY ClassReference-en DESTINATION docs)
 


