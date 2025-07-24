#include <Novice.h>
#include <cmath>
#include <cassert>
#include <corecrt_math.h>
#include<imgui.h>
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

	Plane plane;
	plane.normal = { 0,1.0f,0 };
	plane.distance = 0.5f;


	

	Segment segment{ {-2.0f, -1.0f, 0.0f}, {2.0f, 1.0f,1.0f }, WHITE };

	Triangle triangle = {
		{-0.5f, -0.5f, 1.0f, 0.5f, -0.5f, 1.0f ,   // 頂点2 (手前、右下)
		 0.0f,  0.5f, 0.0f }   // 頂点3 (奥、上)},  // 頂点1 (手前、左下)

	};
	AABB aabb1{
		.min{-0.5f,-0.5f, -0.5f},
		.max{0.0f, 0.0f, 0.0f}
	};
	AABB aabb2
	{
			.min{0.2f, 0.2f, 0.2f},
			.max{1.0f, 1.0f, 1.0f}
	};

	Vector3 controlPoints[3] = {
		{ -0.8f, 0.58f, 1.0f }, // 制御点1
		{ 1.76f, 1.0f, -0.3f }, // 制御点2
		{ 0.94f, -0.7f, 2.3f }  // 制御点3
	};


	

	unsigned int color = BLUE;
	

	

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

			//aabb1の最小値と最大値を更新
		//aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		//aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		//aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		//aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
		//aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
		//aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);

		////aabb2の最小値と最大値を更新
		//aabb2.min.x = (std::min)(aabb2.min.x, aabb2.max.x);
		//aabb2.min.y = (std::min)(aabb2.min.y, aabb2.max.y);
		//aabb2.min.z = (std::min)(aabb2.min.z, aabb2.max.z);
		//aabb2.max.x = (std::max)(aabb2.min.x, aabb2.max.x);
		//aabb2.max.y = (std::max)(aabb2.min.y, aabb2.max.y);
		//aabb2.max.z = (std::max)(aabb2.min.z, aabb2.max.z);

	
	


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
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		

		ImGui::DragFloat3("controlPoints[0]", &controlPoints[0].x, 0.01f);
		ImGui::DragFloat3("controlPoints[1]", &controlPoints[1].x, 0.01f);
		ImGui::DragFloat3("controlPoints[2]", &controlPoints[2].x, 0.01f);


		  
		ImGui::End();


		// --- 描画処理 ---
		matrixUtility ->DrawGrid(viewProjectionMatrix, viewportMatrix);	




		//Vector3 start = matrixUtility->Transform(segment.origin, viewProjectionMatrix);
		//start = matrixUtility->Transform(start, viewportMatrix);

		//Vector3 end = matrixUtility->Transform(matrixUtility->Add(segment.origin, segment.diff), viewProjectionMatrix);
		//end = matrixUtility->Transform(end, viewportMatrix);

		//// スクリーン座標で線分を描画
		//Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), segment.color);
	

		//aabb描画
		/*matrixUtility->DrawAABB(aabb1, viewProjectionMatrix, viewportMatrix, color);*/

		matrixUtility->DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], viewProjectionMatrix, viewportMatrix, color);


	
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