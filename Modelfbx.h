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
	//���O
	std::string name;
	//���[�J���X�P�[��
	DirectX::XMVECTOR scaling = { 1,1,1,0 };
	//���[�J����]�p
	DirectX::XMVECTOR rotation = { 0,0,0,0 };
	//���[�J���ړ�
	DirectX::XMVECTOR translation = { 0,0,0,1 };
	//���[�J���ό`�s��
	DirectX::XMMATRIX transform;
	//�O���[�o���ό`�s��
	DirectX::XMMATRIX globalTransform;
	//�e�m�[�h
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

	//�A���r�G���g�e���x
	DirectX::XMFLOAT3 ambient={1,1,1};
	//�f�B�t���[�Y�e���x
	DirectX::XMFLOAT3 diffuse = { 1,1,1 };
	//�e�N�X�`�����^�f�[�^
	DirectX::TexMetadata meteadeta = {};
	//�X�N���b�`�C���[�W
	DirectX::ScratchImage scratchImg = {};

	//���b�V�������m�[�h
	Node* meshNode = nullptr;
	//���_�f�[�^�z��
	std::vector<VertexPosNormalUV> vertices;
	//���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;

private:
	std::string name;
	//�m�[�h�z��
	std::vector<Node> nodes;
};
