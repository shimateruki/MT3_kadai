#include <Novice.h>
#include <cmath>
#include <cassert>
#include <corecrt_math.h>
#include <imgui.h>
#include "MatrixUtility.h"

const char kWindowTitle[] = "LC1C_09_シマ_テルキ_タイトル";

static const int kRowHeight = 30;
static const int kColuWidth = 80;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColuWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColuWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColuWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	Novice::ScreenPrintf(x, y + 20, "%s", label);
	for (int row = 0; row < 4; ++row)
	{
		for (int colum = 0; colum < 4; ++colum)
		{
			Novice::ScreenPrintf(x + colum * kColuWidth, y + 40 + row * kRowHeight, "%6.02f", matrix.m[row][colum]);
		}
	}
}

int kWindowsWidth = 1280;
int kWindowsHeight = 720;

struct Node {
	Vector3 translate;
	Vector3 rotate;
	Vector3 scale;
};

struct  Spring
{
	//アンカー　固定された端の位置
	Vector3 anchor;
	float naturalLength;
	float stiffness; //ばね定数
	float damping; //減衰係数

};

struct  Ball
{
	Vector3 position; //位置
	Vector3 velocity; //速度
	Vector3 cceleration; //加速度
	float mass; //質量
	float radius; //半径
	unsigned int color; //色
};


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowsWidth, kWindowsHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	MatrixUtility* matrixUtility = new MatrixUtility();

	Spring spring;
	spring.anchor = { 0.0f, 0.0f, 0.0f };
	spring.naturalLength = 1.0f; // 自然長
	spring.stiffness = 100.0f; // ばね定数
	spring.damping = 2.0f; // 減衰係数

	Ball ball{};
	ball.position = { 1.2f, 0.0f, 0.0f };
	ball.mass = 2.0f; // 質量
	ball.radius = 0.95f; // 半径
	ball.color = BLUE;


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

		Vector3 diff = ball.position - spring.anchor; // ボールの位置とアンカーの差分
		float length = matrixUtility->Length(diff); // 差分の長さ
		if (length != 0.0f)
		{
			Vector3 direction = matrixUtility->Normalize(diff);
			Vector3 restPosition = spring.anchor + direction * spring.naturalLength; // 自然長に基づく位置
			Vector3 displacement = length * (ball.position - restPosition);

		}
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