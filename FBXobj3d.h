#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "Modelfbx.h"


class FBXobj3d
{
protected: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//setter
	static void SetDevice(ID3D12Device* device) { FBXobj3d::device = device; }
	//static void SetDevice(Camera* camera) { FBXobj3d::camera = camera; }

public://サブクラス
	//定数バッファ用データ構造体(座標変換)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;//ビュープロジェクション
		XMMATRIX world;//ワールド行列
		XMFLOAT3 camerapos;//カメラ座標(ワールド座標)
	};

public://メンバ関数
	//初期化
	void Initialize();
	//グラフィックスパイプラインの生成
	static void CreateGraphicsPipeline();
	//舞フレーム処理
	void Update();
	//モデルのセット
	void SetModel(FbxModel* model) { this->model = model; }
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);


protected://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBufferTransform;
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	//モデル
	FbxModel* model = nullptr;

private:
	//デバイス
	static ID3D12Device* device;
	//カメラ

	///多分カメラに書く
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView;
	///

	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステートオブジェ
	static ComPtr<ID3D12PipelineState> pipelinestate;

	
};

