#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "LC1C_09_シマ_テルキ_タイトル";



struct Matrix4x4
{
	float m[4][4];
};

struct Vector3
{
	float x;
	float y;
	float z;

};

//X軸回転行列
Matrix4x4 MakeRotateXMatix(float radian)
{

}

//Y軸回転行列

Matrix4x4 MakeRotateYMatix(float radian)
{

}
//Z軸回転行列
Matrix4x4 MakeRotateZMatix(float radian)
{

}





// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	Vector3 rotate = { 0.4f, 1.43f, -0.8f };
	Matrix4x4 rotateXMatrix = MakeRotateXMatix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatix(rotate.y);
	Matrix4x4 rotateYMatrix = MakeRotateYMatix(rotate.z);

	


	


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

	
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
