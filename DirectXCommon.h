#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <cstdlib>
#include "WinApp.h"


#pragma once
//DirectX基盤
class DirectXCommon
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public: //メンバ関数
	//初期化
	void Initialize(WinApp*winApp);

	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapchain();

	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

	void PreDraw();

	void PostDraw();

	ID3D12Device* GetDevice() { return dev.Get(); }

	ID3D12GraphicsCommandList* GetCommandList() { return cmdList.Get(); }

private://メンバ変数
	WinApp* winApp;

	ComPtr<ID3D12Device> dev;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	std::vector<ComPtr<ID3D12Resource>>backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
};

