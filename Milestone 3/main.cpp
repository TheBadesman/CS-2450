// Dear ImGui: standalone example application for Windows API + DirectX 11

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <string>
#include <imgui_stdlib.h>
#include "UVSim.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring> // Added for strncpy

// Data
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static bool                     g_SwapChainOccluded = false;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{

    UVSim Simulator{};
    bool Stopped = false;
    bool Running = false;
    static float timer = 0.0f;
    std::string readInput = "";
    bool waitingForRead = false;
    bool openFile = false;

    constexpr int memory_size = 250
    constexpr int max_index = memory_size - 1;
    
    for (size_t i = 0; i < memory_size; i++)
    {
        Simulator.memory[i] = "x0000";
    }
    

    // Make process DPI aware and obtain main monitor scale
    ImGui_ImplWin32_EnableDpiAwareness();
    float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));

    // Create application window
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"UVSIM", WS_OVERLAPPEDWINDOW, 100, 100, (int)(1280 * main_scale), (int)(800 * main_scale), nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.0f);

    //changes the window title bar to be the same color with RGB of (78, 93, 109)
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.31f, 0.36f, 0.43f, 1.0f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.31f, 0.36f, 0.43f, 1.0f);

    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    bool showLines = true;
   
    std::string consoleInput = "";
    //isBackgroundGreen keeps track if the background is green or not
    bool isBackgroundGreen = true;

    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window being minimized or screen locked
        if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
        {
            ::Sleep(10);
            continue;
        }
        g_SwapChainOccluded = false;

        // Handle window resize
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        timer += io.DeltaTime;

        if (Running && !Stopped && !waitingForRead)
        {
            
            if (timer > 0.5f)
            {
                bool result = true;

                try {
                    result = Simulator.Execute();
                }
                catch (const std::exception& e) {
                    Simulator.AppendOutput(e.what());
                    Running = false;
                    Stopped = true;
                    result = false;
                }

                if (!result)
                {
                    std::string cmd = Simulator.memory[Simulator.address].substr(1,2);

                    if (cmd == "10")
                    {
                        waitingForRead = true;
                        Running = false;
                    }
                    else if (cmd == "43")
                    {
                        Stopped = true;
                        Running = false;
                    }
                }

                timer = 0;
            }
        }

        

        //The start of the Memory Window
        ImVec2 halfSize(io.DisplaySize.x * 0.4f, io.DisplaySize.y * 0.9f);
        ImVec2 leftSection(io.DisplaySize.x * 0.05f, io.DisplaySize.y * 0.05f);
        ImGui::SetNextWindowSize(halfSize, ImGuiCond_Always);
        ImGui::SetNextWindowPos(leftSection, ImGuiCond_Always);
        ImGui::Begin("Memory", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        
        // Static variables for clipboard and context menu error state
        static std::string copiedInstruction = "x0000";
        static std::string memoryErrorMsg = "";

        // Lambda to shift memory elements down (Insert)
        auto shiftDown = [&](int index) -> bool {
            // Check if the last memory address is already occupied by a valid instruction
            if (Simulator.memory[max_index] != "x0000" && Simulator.memory[max_index] != "+0000" && Simulator.memory[max_index] != "") {
                return false; // Memory is full
            }
            for (int i = max_index - 1; i >= index; i--) {
                Simulator.memory[i + 1] = Simulator.memory[i];
            }
            Simulator.memory[index] = "x0000";
            return true;
        };

        // Lambda to shift memory elements up (Delete)
        auto shiftUp = [&](int index) {
            for (int i = index; i < max_index; i++) {
                Simulator.memory[i] = Simulator.memory[i + 1];
            }
            Simulator.memory[max_index] = "x0000";
        };

        if (!memoryErrorMsg.empty()) {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", memoryErrorMsg.c_str());
            ImGui::SameLine();
            if (ImGui::Button("Dismiss")) { memoryErrorMsg = ""; }
        }

        ImGui::TextDisabled("Right-click any address for editing options (Insert/Delete/Copy...)");
        ImGui::Separator();

        // Start scrollable region for memory locations
        ImGui::BeginChild("MemoryScrollRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        // Disable modifications if the simulation is currently running
        ImGui::BeginDisabled(Running);

        for (int x = 0; x < memory_size; x++) {
            ImGui::PushID(x);

            // Display line number
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Line %02d = ", x);
            ImGui::SameLine();

            // Text input for direct manual changes
            char buf[16];
            strncpy(buf, Simulator.memory[x].c_str(), sizeof(buf));
            buf[sizeof(buf) - 1] = '\0';

            ImGui::SetNextItemWidth(120.0f);
            if (ImGui::InputText("##memInput", buf, sizeof(buf))) {
                Simulator.memory[x] = buf;
            }

            // Context menu for cut, copy, paste, insert, delete
            if (ImGui::BeginPopupContextItem("MemContextMenu")) {
                // 1. Insert Above
                if (ImGui::MenuItem("Insert Above")) {
                    if (!shiftDown(x)) {
                        memoryErrorMsg = "Cannot insert: Memory is full (address " + std::to_string(max_index) + " is occupied).";
                    }
                }
            
                // 2. Insert Below
                if (ImGui::MenuItem("Insert Below")) {
                    // Check if we are already at the very last possible index
                    if (x >= max_index || !shiftDown(x + 1)) {
                        memoryErrorMsg = "Cannot insert: Memory is full (address " + std::to_string(max_index) + " is occupied).";
                    }
                }
            
                if (ImGui::MenuItem("Delete")) {
                    shiftUp(x);
                }
            
                ImGui::Separator();
            
                if (ImGui::MenuItem("Cut")) {
                    copiedInstruction = Simulator.memory[x];
                    shiftUp(x);
                }
            
                if (ImGui::MenuItem("Copy")) {
                    copiedInstruction = Simulator.memory[x];
                }
            
                // 3. Paste (Insert)
                if (ImGui::MenuItem("Paste (Insert)")) {
                    if (shiftDown(x)) {
                        Simulator.memory[x] = copiedInstruction;
                    } else {
                        memoryErrorMsg = "Cannot paste: Memory is full (address " + std::to_string(max_index) + " is occupied).";
                    }
                }
            
                if (ImGui::MenuItem("Paste (Overwrite)")) {
                    Simulator.memory[x] = copiedInstruction;
                }
            
                ImGui::EndPopup();
            }

            ImGui::PopID();
        }

        ImGui::EndDisabled();
        ImGui::EndChild();

        //End of Memory window
        ImGui::End();

        // ----- Memory layout values -----
        ImVec2 memorySize(io.DisplaySize.x * 0.4f, io.DisplaySize.y * 0.9f);
        ImVec2 memoryPos(io.DisplaySize.x * 0.05f, io.DisplaySize.y * 0.05f);
        float memoryBottom = memoryPos.y + memorySize.y;

        // ----- Status window layout -----
        ImVec2 statusSize(350.0f, 180.0f);
        ImVec2 statusPos(io.DisplaySize.x * 0.7f, io.DisplaySize.y * 0.05f);

        ImGui::SetNextWindowSize(statusSize, ImGuiCond_Always);
        ImGui::SetNextWindowPos(statusPos, ImGuiCond_Always);

        ImGui::Begin("Status", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        ImGui::Text("Accumulator = %d", Simulator.accumulator);
        ImGui::Text("Current Address = %d", Simulator.address);

        if (Stopped)
            ImGui::Text("Stopped = True");
        else
            ImGui::Text("Stopped = False");

        if (ImGui::Button("Step")) {
            if (!Stopped){

                bool result = Simulator.Execute();

                if (!result)
                {
                    std::string cmd = Simulator.memory[Simulator.address].substr(1,2);

                    if (cmd == "10")
                    {
                        waitingForRead = true;
                    }
                    else if (cmd == "43")
                    {
                        Stopped = true;
                    }
                }
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Run")) {
            Running = true;
            Stopped = false;
        }

        ImGui::SameLine();
        if (ImGui::Button("Stop")) {
            Running = false;
            Stopped = true;
        }

        ImGui::SameLine();
        if (ImGui::Button("Continue")) {
            Stopped = false;
        }

        ImGui::SameLine();
        if (ImGui::Button("Clear")) {
            for (size_t i = 0; i < memory_size; i++){
                Simulator.memory[i] = "x0000"; //resets all memory loactions to zero
            }
            //Stops the function for running and sets the address to 0
            Running = false;
            Stopped = true;
            Simulator.address = 0;
            Simulator.accumulator = 0;
            waitingForRead = false;
            Simulator.ClearOutput();
            openFile = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Color")) {
            //switches the color from green to white or white to green
            isBackgroundGreen = !isBackgroundGreen;
        }

        ImGui::End();


        // ----- Console window layout -----
        float consoleTopY = statusPos.y + statusSize.y;
        float consoleHeight = memoryBottom - consoleTopY;

        ImVec2 consoleSize(statusSize.x, consoleHeight);
        ImVec2 consolePos(statusPos.x, consoleTopY);

        ImGui::SetNextWindowPos(consolePos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(consoleSize, ImGuiCond_Always);

        // ----- Console window -----

        ImGui::Begin("Console",
            NULL,
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize);

        static std::string fileError = "";

        if (!openFile){
            ImGui::Text("Enter file path:");
            ImGui::InputText("##fileinput", &consoleInput);

            if (ImGui::Button("Load File")){
                std::string fullPath = consoleInput;

                std::ifstream file(fullPath);

                if (!file.is_open())
                {
                    fileError = "Error: Could not open file.";
                }
                else
                {
                    fileError = "";
                    Simulator.address = 0;
                    for (int i = 0; i < memory_size; i++){Simulator.memory[i] = "x0000";}

                    std::string line;

                    while (file >> line)
                    {
                        if (Simulator.address >= memory_size)
                        {
                            fileError = "Error: Program too large for memory.";
                            break;
                        }

                        Simulator.memory[Simulator.address++] = line;
                    }

                    Simulator.address = 0;
                    file.close();
                    openFile = true;

                    Simulator.AppendOutput("File loaded Successfully");
                }
            }
        }

        if(openFile){
            static std::string savePath = "";
            ImGui::InputText("Save Path", &savePath);

            if (ImGui::Button("Save File")) {
                std::ofstream outFile(savePath);

                if (!outFile.is_open())
                {
                    fileError = "Error: Could not save file.";
                }
                else
                {
                    for (int i = 0; i < memory_size; i++) {
                        outFile << Simulator.memory[i] << "\n";
                    }
                    outFile.close();
                    fileError = "";
                    Simulator.AppendOutput("File saved successfully");
                    openFile = false;
                }
            }
        }

        if (waitingForRead)
        {
            ImGui::Separator();
            ImGui::Text("READ Instruction Input:");
            ImGui::InputText("##readinput", &readInput);

            if (ImGui::Button("Submit Input"))
            {
                Simulator.READ(readInput);
                waitingForRead = false;
                readInput.clear();
                Simulator.address++; 
            }
        }

        ImGui::Separator();
        ImGui::Text("Program Output:");
        ImGui::BeginChild("ConsoleOutput", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);

        ImGui::TextWrapped("%s", Simulator.consoleLog.c_str());

        // Auto-scroll to bottom
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();

        if (!fileError.empty())
        {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", fileError.c_str());
        }

        ImGui::End();

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        

        //uvuGreen is the green with RGB values (76,114,29)
        const float uvuGreen[4] = { 0.298f, 0.447f, 0.114f, 1.0f };
        // offColor is RGB values (255,255,255)
        const float offColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

        //this if statement makes the background green if isBackgroundGreen is true, and white if false
        if (isBackgroundGreen) {
            g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
            g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, uvuGreen);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }
        else {
            g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
            g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, offColor);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }

        // Present
        HRESULT hr = g_pSwapChain->Present(1, 0);   // Present with vsync
        //HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
        g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    // This is a basic setup. Optimally could use e.g. DXGI_SWAP_EFFECT_FLIP_DISCARD and handle fullscreen mode differently. See #8979 for suggestions.
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
