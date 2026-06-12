# Game Engine CMake

file(GLOB_RECURSE ENGINE_SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Engine/*.cpp)
file(GLOB_RECURSE ENGINE_HEADER_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Engine/*.h)

#message("Engine source files: ${ENGINE_SOURCE_FILES}")
#message("Engine header files: ${ENGINE_HEADER_FILES}")

add_library(GameEngineLib STATIC)

target_sources(GameEngineLib
    PRIVATE 
        ${ENGINE_SOURCE_FILES} 
        
    PUBLIC
        FILE_SET gameEngineHeaders
        TYPE HEADERS
        FILES
            ${ENGINE_HEADER_FILES}
)

target_compile_features(GameEngineLib PUBLIC cxx_std_20) # enable c++20 features

target_include_directories(GameEngineLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${VLD_INCLUDE_DIR}
)

target_link_libraries(GameEngineLib PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    glm::glm
    miniaudio
    ${VLD_LIBRARIES}
    nlohmann_json::nlohmann_json
)

if (WIN32 AND Steamworks_FOUND)
    target_link_libraries(GameEngineLib PUBLIC Steamworks::Steamworks)
    target_compile_definitions(GameEngineLib PRIVATE USE_STEAMWORKS)
endif()

if(MSVC)
    # compile at warning level 4 + treat warnings as errors
    target_compile_options(GameEngineLib PRIVATE /W4 /WX)
else()
    target_compile_options(GameEngineLib PRIVATE -Wall -Wextra -Werror)
endif()


if(EMSCRIPTEN)
  set(EMSCRIPTEN_COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS} -fexperimental-library -g -fexceptions")
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1 -g -sALLOW_MEMORY_GROWTH -fexceptions")

  # Additional settings for Emscripten build
  set_target_properties(GameEngineLib PROPERTIES
      COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS}"
      LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}"
  )
endif()