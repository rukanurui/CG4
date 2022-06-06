#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "Modelfbx.h"


class FBXobj3d
{
protected: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//setter
	static void SetDevice(ID3D12Device* device) { FBXobj3d::device = device; }
	//static void SetDevice(Camera* camera) { FBXobj3d::camera = camera; }

public://�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����(���W�ϊ�)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;//�r���[�v���W�F�N�V����
		XMMATRIX world;//���[���h�s��
		XMFLOAT3 camerapos;//�J�������W(���[���h���W)
	};

public://�����o�֐�
	//������
	void Initialize();
	//�O���t�B�b�N�X�p�C�v���C���̐���
	static void CreateGraphicsPipeline();
	//���t���[������
	void Update();
	//���f���̃Z�b�g
	void SetModel(FbxModel* model) { this->model = model; }
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);


protected://�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBufferTransform;
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	//���f��
	FbxModel* model = nullptr;

private:
	//�f�o�C�X
	static ID3D12Device* device;
	//�J����

	///�����J�����ɏ���
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;
	///

	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F
	static ComPtr<ID3D12PipelineState> pipelinestate;

	
};

