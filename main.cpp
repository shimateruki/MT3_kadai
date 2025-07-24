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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowsWidth, kWindowsHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	MatrixUtility* matrixUtility = new MatrixUtility();

	// カメラ
	Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };

	// スライドの例に沿った変数の定義
	Vector3 a{ 0.2f, 1.0f, 0.0f };
	Vector3 b{ 2.4f, 3.1f, 1.2f };
	Vector3 c{};
	Vector3 d{};
	Vector3 e{};

	Vector3 rotate{ 0.4f, 1.43f, -0.8f };
	Matrix4x4 rotateXMatrix{};
	Matrix4x4 rotateYMatrix{};
	Matrix4x4 rotateZMatrix{};
	Matrix4x4 rotateMatrix{};

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



		c = a + b;
		d = a - b;
		e = a * 2.4f;

		rotateXMatrix = matrixUtility->MakeRotateXMatrix(rotate.x);
		rotateYMatrix = matrixUtility->MakeRotateYMatrix(rotate.y);
		rotateZMatrix = matrixUtility->MakeRotateZMatrix(rotate.z);
		rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;

		// ImGuiの表示
		ImGui::Begin("Window");
		ImGui::Text("c:%.2f, %.2f, %.2f", c.x, c.y, c.z);
		ImGui::Text("d:%.2f, %.2f, %.2f", d.x, d.y, d.z);
		ImGui::Text("e:%.2f, %.2f, %.2f", e.x, e.y, e.z);

		ImGui::Text("matrix:%f, %f, %f,%f,\n %f, %f %f,%f \n, %f,%f,%f,%f\n,%f,%f,%f, %f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
			rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3],
			rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);
		ImGui::End();
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