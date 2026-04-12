cMake_minimum_required(VERSION 3.20)
project(UVSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- ImGui Directory ----
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)

# ---- ImGui Core Files ----
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

# ---- Backend Files ----
set(IMGUI_BACKENDS
    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
)

# ---- Misc C++ helpers (for imgui_stdlib) ----
set(IMGUI_MISC
    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
)

add_executable(UVSim
    main.cpp
    UVSim.cpp
    ${IMGUI_SOURCES}
    ${IMGUI_BACKENDS}
    ${IMGUI_MISC}
)

# ---- Include directories ----
target_include_directories(UVSim PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${IMGUI_DIR}/misc/cpp
)

# ---- Link Windows + DirectX ----
target_link_libraries(UVSim PRIVATE
    d3d11
    dxgi
    d3dcompiler
    user32
    gdi32
    dwmapi #jacen added this, my console said i needed it
)
