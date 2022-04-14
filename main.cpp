
#include <vector>
#include <string>


#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定

#include "Input.h"

#include "WinApp.h"
#include "DirectXCommon.h"

#include "Object3d.h"
#include "model.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "DebugText.h"
#include "Audio.h"



using namespace DirectX;
using namespace Microsoft::WRL;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    //ポインタ置き場
    Input* input = nullptr;
    WinApp* winApp = nullptr;
    DirectXCommon* dxCommon = nullptr;
    /*Audio* audio = nullptr;*/

#pragma region WindowsAPI初期化
    winApp = new WinApp();
    winApp->Initialize();
#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理
    // DirectX初期化処理　ここから
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);


    //Object3d静的初期化
    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
    //OBJからモデルデータを読み込む
    model* Model = model::LoadFromOBJ("triangle_mat");
    //3dオブジェクト生成
    Object3d* object3d = Object3d::Create();
    //モデル紐づけ
    object3d->SetModel(Model);

    // スプライト共通部分の初期化
    SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(),dxCommon->GetCommandList(),winApp->window_width,winApp->window_height);

    // デバッグテキスト
    DebugText* debugText = nullptr;
    debugText = new DebugText();

    // デバッグテキスト用のテクスチャ番号を指定
    const int debugTextTexNumber = 2;
    // デバッグテキスト用のテクスチャ読み込み
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // デバッグテキスト初期化
    debugText->Initialize(spriteCommon, debugTextTexNumber);

    //入力の初期化
    input = new Input();
    input->Initialize(winApp);

  // //オーディオの初期化
  //  audio = new Audio();
  //  audio->Initialize();
  //
  ///*  XAudio2VoiceCallback voiceCallback;*/

  //  

  //  // 音声読み込み
  //   audio->LoadWave("Alarm01.wav");

  //  // 音声再生
  //    audio->PlayWave("Alarm01.wav");

    // DirectX初期化処理　ここまで
#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理
  

    //// スプライト共通データ生成
    //spriteCommon = SpriteCommonCreate(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
    // スプライト共通テクスチャ読み込み
    /*spriteCommon->LoadTexture(0, L"Resources/texture.png");
    spriteCommon->LoadTexture(1, L"Resources/house.png");

    std::vector<Sprite*> sprites;*/

   /* Sprite* sprite = Sprite::Create(spriteCommon, 0);*/
    spriteCommon->LoadTexture(1, L"Resources/circle.png");
    spriteCommon->LoadTexture(4, L"Resources/canon.png");

    Sprite* sprite = Sprite::Create(spriteCommon, 1, { 0,0 }, false, false);
    Sprite* sprite2 = Sprite::Create(spriteCommon, 4, { 0,0 }, false, false);
    Sprite* sprite3 = Sprite::Create(spriteCommon, 1, { 0,0 }, false, false);

    sprite->SetPosition({ (float)(600) ,(float)(10) ,0 });
    sprite->SetSize({ (float)(60), (float)(60) });
    sprite->TransferVertexBuffer();

    sprite2->SetPosition({ (float)(0) ,(float)(450) ,0 });
    sprite2->TransferVertexBuffer();
    sprite3->SetPosition({ (float)(100) ,(float)(600) ,0 });
    sprite3->TransferVertexBuffer();

    //// スプライトの生成
    //for (int i = 0; i < 20; i++)
    //{
    //    int texNumber = 0;
    //    Sprite* sprite = Sprite::Create(spriteCommon,texNumber, { 0,0 }, false, false);

    //    // スプライトの座標変更
    //    sprite->SetPosition({ (float)(rand() % 1280) ,(float)(rand() % 720) ,0 });
    //    sprite->SetRotation({ (float)(rand() % 360) });
    //    sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });
    //    //sprites[i].isInvisible = true;
  
    //    // 頂点バッファに反映
    //    sprite->TransferVertexBuffer();

    //    sprites.push_back(sprite);
    //    sprite->SetPosition({ 500,300,0 });
    //}

  
#pragma endregion 描画初期化処理

    int counter = 0; // アニメーションの経過時間カウンター

    //ゲーム用変数
    float x = 600;
    float y = 10;

    float bulx = 130;
    float buly = 540;
   

    float Gvel = 9.8f/60;//重力加速度
    float G = 0;

    float vel = 15.0f;
    float Fvely = -10.0;





    while (true)  // ゲームループ
    {
#pragma region ウィンドウメッセージ処理
        if (winApp->ProcessMessage())
        {
            break;
        }

#pragma endregion ウィンドウメッセージ処理

#pragma region DirectX毎フレーム処理
        // DirectX毎フレーム処理　ここから

        //入力の更新
        input->Update();

        //object3d更新
       /* object3d->Update();*/

        ////スプライト更新
        //for (auto& sprite : sprites) {
        //    sprite->Update();
        //}
        sprite->Update();
        sprite2->Update();
        sprite3->Update();

        G += Gvel;


        bulx += vel;

        y += G;

        buly += Fvely+G;

        sprite->SetPosition({ x,y,1 });
        sprite3->SetPosition({ bulx,buly,1 });

        const int cycle = 540; // 繰り返しの周期
        counter++;
        counter %= cycle; // 周期を超えたら0に戻る
        float scale = (float)counter / cycle; // [0,1]の数値

        scale *= 360.0f;


        if (input->TriggerKey(DIK_0)) // 数字の0キーが押されていたら
        {
            OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
        }

        float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

        if (input->TriggerKey(DIK_SPACE))     // スペースキーが押されていたら
        {
            // 画面クリアカラーの数値を書き換える
            clearColor[1] = 1.0f;
        }

        
        // 各オブジェクトの半径
        const float radius1 = 3.0f;
        const float radisu2 = 3.0f;
        // X座標,Y座標を指定して表示
        debugText->Print("Hello,DirectX!!", 200, 100);
        // X座標,Y座標,縮尺を指定して表示
        debugText->Print("Nihon Kogakuin", 200, 200, 2.0f);

        //sprite.rotation = 45;
        //sprite.position = {1280/2, 720/2, 0};
        //sprite.color = {0, 0, 1, 1};


        // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

        //描画前処理
        dxCommon->PreDraw();

        //3dオブジェクト描画前処理
        Object3d::PreDraw(dxCommon->GetCommandList());

        //3dオブジェクトの描画
        /*object3d->Draw();*/

        ///<summary>
        ///ここに3dオブジェクトの描画処理を追加できる
        /// </summary>

        //3dオブジェクトの描画後処理
        Object3d::PostDraw();

        // ４．描画コマンドここから
       

        // スプライト共通コマンド
        spriteCommon->PreDraw();

        // スプライト描画

        /*for (auto& sprite : sprites) {
            sprite->Draw();
        }*/

        sprite->Draw();
        
        sprite3->Draw();
        sprite2->Draw();

        // デバッグテキスト描画
        debugText->DrawAll();

        // ４．描画コマンドここまで
         //描画後処理
        dxCommon->PostDraw();

    }
        //解放処理
        delete input;
        delete dxCommon;

        //3dオブジェクト解放
        /*delete object3d;*/
        //3dモデル解放
        delete Model;

        //デバッグテキスト解放
        debugText->Finalize();
        delete debugText;

        ////スプライト解放
        //for (auto& sprite : sprites) {
        //    delete sprite;
        //}
        //sprites.clear();
        delete sprite;
        delete sprite2;
        delete sprite3;
        delete spriteCommon;


        //オーディオ解放
   /*     audio->Finalize();
        delete audio;*/


        winApp->Finalize();
        delete winApp;
        winApp = nullptr;
#pragma endregion WindowsAPI後始末

        return 0;
 }