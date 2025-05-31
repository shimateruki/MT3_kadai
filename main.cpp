#include <Novice.h>
#include <cmath>
#include <cassert>
#include <corecrt_math.h>
#include<imgui.h>
#include "MatrixUtility.h"

const char kWindowTitle[] = "LC1C_09_シマ_テルキ_タイトル";



Vector3 Project(const Vector3& v1, const Vector3& v2) {
	float v2LengthSq = v2.x * v2.x + v2.y * v2.y + v2.z * v2.z;
	assert(v2LengthSq != 0.0f); // 0除算防止

	float dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	float scalar = dot / v2LengthSq;

	Vector3 result{
		v2.x * scalar,
		v2.y * scalar,
		v2.z * scalar
	};

	return result;
}

Vector3 ClossetPoint(const Vector3& point, const Segment& segment) {
	Vector3 originToPoint{
		point.x - segment.origin.x,
		point.y - segment.origin.y,
		point.z - segment.origin.z
	};

	Vector3 projected = Project(originToPoint, segment.diff);

	Vector3 closest{
		segment.origin.x + projected.x,
		segment.origin.y + projected.y,
		segment.origin.z + projected.z
	};

	return closest;
}






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


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowsWidth, kWindowsHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	MatrixUtility* matrixUtility = new MatrixUtility();
	//カメラ
	Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };
	Vector3 cameraPosition = { 0.0f, 1.0f, 5.0f };




	Segment segment{ {-2.0f, -1.0f, 0.0f}, {3.0f, 2.0f,2.0f } };

	Vector3 point{ -1.5f, 0.6f, 0.6f };



	//pointを線分に射影したベクトル　今回は正しく計算できているかを確認するた眼だけに使う
	Vector3 project = Project(matrixUtility->Subtract(point, segment.origin), segment.diff);

	//この値が線分上を表す
	Vector3 clossetPoint = ClossetPoint(point, segment);

	Sphere pointShere{ point, 0.01f };//1cmの球を描画
	Sphere closePointSphere{ clossetPoint, 0.01f };


	closePointSphere.center = clossetPoint;

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

			//行列の計算

		Matrix4x4 cameraMatrix = matrixUtility-> MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { cameraRotate }, cameraTranslate);
		Matrix4x4 viewMatrix = matrixUtility->Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = matrixUtility-> MakePerspectiveFovMatrix(0.45f, float(kWindowsWidth) / float(kWindowsHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = matrixUtility-> Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = matrixUtility-> MakeViewportMatrix(0, 0, float(kWindowsWidth), float(kWindowsHeight), 0.0f, 1.0f);



			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///


		//imGit処理
		ImGui::Begin("Window");
		ImGui::InputFloat3("Point", &point.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Sement origin", &segment.origin.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("segment diff", &segment.diff.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		//点の描画
	
		matrixUtility->DrawGrid(viewProjectionMatrix, viewportMatrix);
		matrixUtility->DrawSphere(pointShere, viewProjectionMatrix, viewportMatrix, RED);
		matrixUtility->DrawSphere(closePointSphere, viewProjectionMatrix, viewportMatrix, BLACK);

		// --- 描画処理 ---
	// 線分の始点と終点をスクリーン座標に変換
		Vector3 start = matrixUtility->Transform(segment.origin, viewProjectionMatrix);
		start = matrixUtility->Transform(start, viewportMatrix);

		Vector3 end = matrixUtility->Transform(matrixUtility->Add(segment.origin, segment.diff), viewProjectionMatrix);
		end = matrixUtility->Transform(end, viewportMatrix);

		// スクリーン座標で線分を描画
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);
		///
		/// ↑描画処理ここまで
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