#pragma once
#include <string>
#include <DirectXMath.h>
#include<vector>
#include <DirectXTex.h>
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>

struct Node
{
	//名前
	std::string name;
	//ローカルスケール
	DirectX::XMVECTOR scaling = { 1,1,1,0 };
	//ローカル回転角
	DirectX::XMVECTOR rotation = { 0,0,0,0 };
	//ローカル移動
	DirectX::XMVECTOR translation = { 0,0,0,1 };
	//ローカル変形行列
	DirectX::XMMATRIX transform;
	//グローバル変形行列
	DirectX::XMMATRIX globalTransform;
	//親ノード
	Node* parent = nullptr;
};

class FbxModel
{
public:
	friend class FbxLoader;

	struct VertexPosNormalUV
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
	};

	//アンビエント影響度
	DirectX::XMFLOAT3 ambient={1,1,1};
	//ディフューズ影響度
	DirectX::XMFLOAT3 diffuse = { 1,1,1 };
	//テクスチャメタデータ
	DirectX::TexMetadata meteadeta = {};
	//スクラッチイメージ
	DirectX::ScratchImage scratchImg = {};

	//メッシュを持つノード
	Node* meshNode = nullptr;
	//頂点データ配列
	std::vector<VertexPosNormalUV> vertices;
	//頂点インデックス配列
	std::vector<unsigned short> indices;

private:
	std::string name;
	//ノード配列
	std::vector<Node> nodes;
};
