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

	// 階層構造ノードの定義と初期値設定
	Node shoulder = {
		.translate = {0.2f, 1.0f, 0.0f},
		.rotate = {0.0f, 0.0f, -6.0f},
		.scale = {1.0f, 1.0f, 1.0f}
	};
	Node elbow = {
		.translate = {0.4f, 0.0f, 0.0f},
		.rotate = {0.0f, 0.0f, -1.4f},
		.scale = {1.0f, 1.0f, 1.0f}
	};
	Node hand = {
		.translate = {0.3f, 0.0f, 0.0f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.scale = {1.0f, 1.0f, 1.0f}
	};

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

		// ノードのワールド行列を計算
		Matrix4x4 worldMatrix_shoulder = matrixUtility->MakeAffineMatrix(shoulder.scale, shoulder.rotate, shoulder.translate);
		Matrix4x4 worldMatrix_elbow = matrixUtility->Multiply(matrixUtility->MakeAffineMatrix(elbow.scale, elbow.rotate, elbow.translate), worldMatrix_shoulder);
		Matrix4x4 worldMatrix_hand = matrixUtility->Multiply(matrixUtility->MakeAffineMatrix(hand.scale, hand.rotate, hand.translate), worldMatrix_elbow);

		// 描画用の球と線分のワールド座標を計算
		Sphere sphere_shoulder = { matrixUtility->Transform({0.0f, 0.0f, 0.0f}, worldMatrix_shoulder), 0.1f };
		Sphere sphere_elbow = { matrixUtility->Transform({0.0f, 0.0f, 0.0f}, worldMatrix_elbow), 0.1f };
		Sphere sphere_hand = { matrixUtility->Transform({0.0f, 0.0f, 0.0f}, worldMatrix_hand), 0.1f };

		// 線分は親ノードの位置から子ノードの位置まで
		Segment segment_shoulder_elbow = {
			.origin = sphere_shoulder.center,
			.diff = matrixUtility->Subtract(sphere_elbow.center, sphere_shoulder.center)
		};
		Segment segment_elbow_hand = {
			.origin = sphere_elbow.center,
			.diff = matrixUtility->Subtract(sphere_hand.center, sphere_elbow.center)
		};

		// カメラ行列
		Matrix4x4 cameraMatrix = matrixUtility->MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { cameraRotate }, cameraTranslate);
		Matrix4x4 viewMatrix = matrixUtility->Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = matrixUtility->MakePerspectiveFovMatrix(0.45f, float(kWindowsWidth) / float(kWindowsHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = matrixUtility->Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = matrixUtility->MakeViewportMatrix(0, 0, float(kWindowsWidth), float(kWindowsHeight), 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("shoulder translate", &shoulder.translate.x, 0.01f);
		ImGui::DragFloat3("shoulder rotate", &shoulder.rotate.x, 0.01f);
		ImGui::DragFloat3("elbow translate", &elbow.translate.x, 0.01f);
		ImGui::DragFloat3("elbow rotate", &elbow.rotate.x, 0.01f);
		ImGui::DragFloat3("hand translate", &hand.translate.x, 0.01f);
		ImGui::DragFloat3("hand rotate", &hand.rotate.x, 0.01f);
		ImGui::End();

		// グリッド描画
		matrixUtility->DrawGrid(viewProjectionMatrix, viewportMatrix);

		// 球と線分を描画
		matrixUtility->DrawSphere(sphere_shoulder, viewProjectionMatrix, viewportMatrix, RED);
		matrixUtility->DrawSphere(sphere_elbow, viewProjectionMatrix, viewportMatrix, GREEN);
		matrixUtility->DrawSphere(sphere_hand, viewProjectionMatrix, viewportMatrix, BLUE);

		// 線分はワールド座標で描画
		Vector3 screenShoulder = matrixUtility->Transform(matrixUtility->Transform(segment_shoulder_elbow.origin, viewProjectionMatrix), viewportMatrix);
		Vector3 screenElbow = matrixUtility->Transform(matrixUtility->Transform(matrixUtility->Add(segment_shoulder_elbow.origin, segment_shoulder_elbow.diff), viewProjectionMatrix), viewportMatrix);
		Novice::DrawLine(static_cast<int>(screenShoulder.x), static_cast<int>(screenShoulder.y), static_cast<int>(screenElbow.x), static_cast<int>(screenElbow.y), WHITE);

		Vector3 screenHand = matrixUtility->Transform(matrixUtility->Transform(matrixUtility->Add(segment_elbow_hand.origin, segment_elbow_hand.diff), viewProjectionMatrix), viewportMatrix);
		Novice::DrawLine(static_cast<int>(screenElbow.x), static_cast<int>(screenElbow.y), static_cast<int>(screenHand.x), static_cast<int>(screenHand.y), WHITE);

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