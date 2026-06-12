# Q*Bert CMake

file(GLOB_RECURSE GAME_SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
file(GLOB_RECURSE GAME_HEADER_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h)

#message("Game source files: ${GAME_SOURCE_FILES}")
#message("Game header files: ${GAME_HEADER_FILES}")

add_executable(${TARGET_NAME} ${TARGET_PARAM})

target_sources(${TARGET_NAME} PUBLIC ${GAME_SOURCE_FILES} ${GAME_HEADER_FILES})

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20) # enable c++20 features

target_include_directories("${TARGET_NAME}" PRIVATE
  ${VLD_INCLUDE_DIR}
  "${CMAKE_CURRENT_SOURCE_DIR}/Source"
)

target_link_libraries("${TARGET_NAME}" PRIVATE
  GameEngineLib
  SDL3::SDL3
  SDL3_ttf::SDL3_ttf
  glm::glm
  ${LIBS}
  ${VLD_LIBRARIES}
  nlohmann_json::nlohmann_json
)

if(MSVC)
  # compile at warning level 4 + treat warnings as errors
  target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

if(EMSCRIPTEN)
  set(EMSCRIPTEN_COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS} -fexperimental-library -g -fexceptions")

    # Additional settings for Emscripten build
  set_target_properties(${TARGET_NAME} PROPERTIES
      COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS}"
      #LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}"
  )

  target_link_options(
    ${TARGET_NAME} PRIVATE
    ${EMSCRIPTEN_LINK_FLAGS}
    -sUSE_FREETYPE=1
    -sUSE_HARFBUZZ=1
    -sALLOW_MEMORY_GROWTH
    -fexceptions
    --preload-file "${CMAKE_CURRENT_SOURCE_DIR}/Data@/"
  )

  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/web" "$<TARGET_FILE_DIR:${TARGET_NAME}>/"
  )

  # Have emscripten generate a html page too.
  set(CMAKE_EXECUTABLE_SUFFIX ".html")

elseif(WIN32)
  # Set minigin as the default startup project
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})

  # Set working directory to output folder and debug console window
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>")
  else()
    set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>")
  endif()

  # Copy SDL dlls to output folder
  set(SDL_RUNTIME_DLLS
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
  )

  foreach(dllTarget IN LISTS SDL_RUNTIME_DLLS)
    add_custom_command(
      TARGET ${TARGET_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "$<TARGET_FILE:${dllTarget}>"
          "$<TARGET_FILE_DIR:${TARGET_NAME}>"
      VERBATIM
    )
  endforeach()

  if(Steamworks_FOUND)
    target_link_libraries("${TARGET_NAME}" PUBLIC Steamworks::Steamworks)
    target_compile_definitions(${TARGET_NAME} PRIVATE USE_STEAMWORKS)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${Steamworks_RUNTIME_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>")
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E echo "480" > "$<TARGET_FILE_DIR:${TARGET_NAME}>/steam_appid.txt"
      COMMENT "Generating steam_appid.txt"
    )
  endif()

  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:${TARGET_NAME}>/Data"
  )
elseif(APPLE)
  set_target_properties(${TARGET_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    INSTALL_RPATH "@executable_path/../Frameworks"
    BUILD_WITH_INSTALL_RPATH TRUE
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "$<TARGET_BUNDLE_DIR:${TARGET_NAME}>/Contents/Frameworks"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3-shared>" "$<TARGET_BUNDLE_DIR:${TARGET_NAME}>/Contents/Frameworks/"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3_ttf::SDL3_ttf-shared>" "$<TARGET_BUNDLE_DIR:${TARGET_NAME}>/Contents/Frameworks/"
    COMMAND install_name_tool -change "@rpath/libSDL3_ttf.0.dylib" "@executable_path/../Frameworks/libSDL3_ttf.0.2.2.dylib" "$<TARGET_FILE:${TARGET_NAME}>"
    COMMAND install_name_tool -change "@rpath/libSDL3.0.dylib" "@executable_path/../Frameworks/libSDL3.0.dylib" "$<TARGET_FILE:${TARGET_NAME}>"
  )

  if(Steamworks_FOUND)
    target_link_libraries("${TARGET_NAME}" PUBLIC Steamworks::Steamworks)
    target_compile_definitions(${TARGET_NAME} PRIVATE USE_STEAMWORKS)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${Steamworks_LIBRARIES}" "$<TARGET_BUNDLE_DIR:${TARGET_NAME}>/Contents/Frameworks/"
    )
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E echo "480" > "$<TARGET_FILE_DIR:${TARGET_NAME}>/steam_appid.txt"
      COMMENT "Generating steam_appid.txt"
    )
  endif()

  # Copy Data folder to output directory after build
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:${TARGET_NAME}>/Data"
  )
else()
 if(Steamworks_FOUND)
    target_link_libraries("${TARGET_NAME}" PUBLIC Steamworks::Steamworks)
    target_compile_definitions(${TARGET_NAME} PRIVATE USE_STEAMWORKS)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${Steamworks_LIBRARIES}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
    )
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E echo "480" > "$<TARGET_FILE_DIR:${TARGET_NAME}>/steam_appid.txt"
      COMMENT "Generating steam_appid.txt"
    )
  endif()

  # Copy Data folder to output directory after build
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:${TARGET_NAME}>/Data"
  )
endif()
