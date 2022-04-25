#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include "Modelfbx.h"


class FbxLoader
{
public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

	void Initialize(ID3D12Device* device);

	void Finalize();


private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;
	//std::を省略
	using string = std::string;

	ID3D12Device* device = nullptr;
	FbxManager* fbxManager = nullptr;
	FbxImporter* fbxImporter = nullptr;
	
public:
	//モデル格納ルートパス
	static const string baseDirectory;
	//ファイルからFBXモデル読み込み
	void LoadModelFromFile(const string& modelName);
	//再帰的にノード構成を解析
	void ParseNodeRecursive(Model* model, FbxNode* fbxNode);
};