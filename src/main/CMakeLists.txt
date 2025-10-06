create_executable_project(main)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Window SFML::System)

if (WIN32)
    file(GLOB_RECURSE SFML_DLLS "${SFML_ROOT}/bin/*.dll")
    foreach(SFML_DLL ${SFML_DLLS})
        add_custom_command(TARGET main POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL}
            $<TARGET_FILE_DIR:main>
            COMMENT "Копируем DLL-файлы SFML"
        )
    endforeach()
endif()