//This is the header to set up the Graphics class.
#pragma once

//This is mainly code from "https://docs.microsoft.com/en-us/windows/win32/direct3d12/creating-a-basic-direct3d-12-component" but it is changed to be better suited for the engine.

#define _WARP  //If define, creates a WARP adapter instead of a hardware adapter. Allowing for more advanced rendering features.

//Please undefine the macros below this comment, instead of deleting them.

//#undef _DEBUG
//#undef _WARP

//Includes header and libraries necessary in order to debug.
#if defined(_DEBUG)
#pragma comment (lib,"dxguid.lib")  
#include <dxgidebug.h>
#endif

#include "SimpleCamera.h"
#include "StepTimer.h"

// This code is basically the example code available on windows documentation but instead of WRL, winrt is used.

  /***********************************************************/
  /*                                                         */
  /*   In order to read the comments correctly have in mind  */
  /*   that the code to the right of a variable or function  */
  /*   means it only applies to it. In other words there is  */
  /*   no newline in code which is written with the "//" me- */
  /*   thod.                                                 */
  /*                                                         */
  /***********************************************************/

using namespace winrt;

class Graphics
{
protected:  //This should only be accessible to the Window class, as it  wouldn't make too much sense to start rendering in for example an AI behaviour class or similar.

    Graphics(UINT width, UINT height);  //Constructor of Graphics.

    void Init();  //Initializes the D3D12 pipeline and initializes commands.
    void Update();  //Updates the content of the frames
    void Render();  //Populates the command list and displays the current object on the window.
    void Destroy(); //Terminates the fence event, thus it stops frame update.

private:
#if defined(_DEBUG)

    com_ptr<IDXGIDebug> debug;  //The pointer used in the DebugInterface function in order to create a IDXGI debug layer.
    HMODULE debug_module;  //The imported module that is used in order to load the necessary functions from the debug IDXGI .DLL file.

    void CreateDebugInterface();  //Creates the debug interface for DXGI objects and allows to track live objects and ref counts of them.

#endif

    /*******************************************************************/
    /**                                                               **/
    /**   This is by far the most confusing aspect of using D3D12     **/
    /**   and I should investigate this further                       **/
    /**                                                               **/
    /*******************************************************************/

    struct Vertex  //The structure which would be used to display a 3D object. This is composed of DirectXMath objects as there is no way I know algebra high enough yet.
    {
        DirectX::XMFLOAT3 position;  //This is a 3D vector which is used to determine the position of the vertex. (x,y and z)
        DirectX::XMFLOAT4 color;  //This is a 4D vector which contains four float variables, and because of that we use it for the color pattern of the figure instead of it's intended purpose.
    };

    struct Model  //Structure which holds a 3D model.
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT4 color;
    };


    void LoadPipeline();  //Creates and loads the Direct3D12 pipeline. This is where adapters, buffers and memory resources are initialized.

    void EnumerateAdapters();  //Enumartes the IDXGI Adapters.
    void CreateCommandQueue();  //Creates the command queue.
    void CreateSwapChain();  //Creates the swap chain.
    void CreateDescriptorHeap();  //Creates the descriptor heap.
    void CreateFrameResources();  //Creates the frame resources.
    void CheckTearingSupport();  //Checks and creates tearing support for G-Sync (and etc.) displays.


    void LoadAssets();  //Creates and loads the assets which will be used by the Direct3D12 pipeline. This is where variables for the command list(s) are initialized.

    void CreateRootSignatures();  //Creates root signatures. (The two functions below)
    void CreatePipelineState();  //Creates the pipeline state.
    void CreateVertexBuffers();  //Creates the vertex buffer.
    void CreateSyncObjects();  //Creates the sync obejects.

    void PopulateCommandList();  //Defines the command list using the assets and then gives the command list to the command queue.
    void WaitForPreviousFrame();  //Asserts that the frame is rendered and signals the fence.

    static const UINT FrameCount = 2;  //The amount of back buffers the swap chain has. It must not be less than two if flip presentation is used.

    static const UINT ThreadCount = 1;
    static const float ParticleSpread;
    static const UINT ParticleCount = 10000;        // The number of particles in the n-body simulation.

    // Pipeline objects.
    CD3DX12_VIEWPORT m_viewport;
    CD3DX12_RECT m_scissorRect;

    com_ptr<IDXGISwapChain3> m_swapChain;  //It is the object responsible for presenting the rendered objects.
    com_ptr<ID3D12Device> m_device;  //The D3D12 device which is used in order to initialize assets and command queues.
    com_ptr<ID3D12Resource> m_renderTargets[FrameCount];  //Array which contains the pointer to back buffer resources.
    com_ptr<ID3D12CommandAllocator> m_commandAllocator;  //Backing memory for recording GPU commands into a commands list. It's an array because there must be a command allocator for each frame "in-flight"
    com_ptr<ID3D12CommandQueue> m_commandQueue;  //The command queue uses the command list to exectue the commands in it and then display them if no errors are present.
    com_ptr<ID3D12RootSignature> m_rootSignature;
    com_ptr<ID3D12RootSignature> m_computeRootSignature;
    com_ptr<ID3D12DescriptorHeap> m_rtvHeap;  //Describes location of texture resource in GPU memory, dimensions and format of it. It is used the clear the back buffers of the render target
    com_ptr<ID3D12DescriptorHeap> m_srvUavHeap;
    com_ptr<ID3D12PipelineState> m_pipelineState;
    com_ptr<ID3D12PipelineState> m_computeState;
    com_ptr<ID3D12GraphicsCommandList> m_commandList;  //It's a pointer which allows for the rendering of 3D objects. It is used by the command queue.
    com_ptr<IDXGIFactory4> factory;  //The object which enumerates adapters.

    UINT m_rtvDescriptorSize;  //The size of the RTV descriptor, this value contains the size of the render targets and passes them unto the RTV descriptor.
    UINT m_srvUavDescriptorSize;  //The size of the UAV descriptor, this value contains the size of the render targets and passes them unto the UAV descriptr.

    // App resources.

    com_ptr<ID3D12Resource> m_vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;


    // Compute objects.
    com_ptr<ID3D12CommandAllocator> m_computeAllocator[ThreadCount];
    com_ptr<ID3D12CommandQueue> m_computeCommandQueue[ThreadCount];
    com_ptr<ID3D12GraphicsCommandList> m_computeCommandList[ThreadCount];

    UINT m_srvIndex[ThreadCount];        // Denotes which of the particle buffer resource views is the SRV (0 or 1). The UAV is 1 - srvIndex.
    UINT m_heightInstances;
    UINT m_widthInstances;
    SimpleCamera m_camera;
    StepTimer m_timer;


    // Synchronization objects.

    UINT m_frameIndex;  //Variable used to store the index of the current frame.
    HANDLE m_fenceEvent;  //A handle which will tell when to change the contents of the fence.
    com_ptr<ID3D12Fence> m_renderContextFence;  //The fence is used in order to synchronize commands in the Command Queue.
    UINT64 m_renderContextFenceValue;
    HANDLE m_renderContextFenceEvent;  
    UINT64 m_frameFenceValues[FrameCount];  //The value that the fence contains.

    com_ptr<ID3D12Fence> m_threadFences[ThreadCount];
    volatile HANDLE m_threadFenceEvents[ThreadCount];


    std::wstring m_assetsPath;  //The path to the shaders.
    float m_aspectRatio;  //The aspect ratio of the screen.

    const UINT WindowWidth;  //The width of the window.
    const UINT WindowHeight;  //The height of the window.

    //Boolean values.

    bool m_VSync = false;  //Boolean value for allowing v-sync.
    bool m_Tearing = false;  //Boolean value for allowing tearing, mainly used by G-Sync displays, among others which require it.
    bool m_Fullscreen = false;  //Boolean value for signifying that fullscren is active.

    //Additional functions.

    std::wstring GetAssetFullPath(LPCWSTR assetName) { return m_assetsPath + assetName; };  //Gets the full asset path to shaders and assets (of course).
    void GetHardwareAdapter(_In_ IDXGIFactory2* pFactory, _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter);  //Enumerates the hardware adapters that are present until one is valid.

};
