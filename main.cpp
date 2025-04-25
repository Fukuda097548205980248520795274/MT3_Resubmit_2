#include <Novice.h>
#include "Struct.h"
#include "Const.h"
#include "./Func/Vector/Vector.h"
#include "./Func/Matrix/Matrix.h"
#include "./Func/Draw/Draw.h"
#include "imgui.h"

const char kWindowTitle[] = "LE2A_11_フクダソウワ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	/*---------------
		変数を作る
	---------------*/

	// カメラの移動・回転
	Vector3 cameraTranslate = { 0.0f , 1.9f , -6.49f };
	Vector3 cameraRotate = { 0.26f , 0.0f , 0.0f };

	// 線分
	Segment segment;
	segment.origin = { -2.0f , -1.0f , 0.0f };
	segment.diff = { 3.0f , 2.0f , 2.0f };

	// 点
	Vector3 point = { -1.5f , 0.6f , 0.6f };


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

		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("point", &point.x, 0.01f);
		ImGui::DragFloat3("segmentOrigin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("segmentDiff", &segment.diff.x, 0.01f);
		ImGui::End();


		// 正射影ベクトル
		Vector3 project = Project(Subtract(point, segment.origin), segment.diff);

		// 最近接点
		Vector3 closestPoint = ClosestPoint(project, segment);


		Sphere pointSphere = { point , 0.01f };
		Sphere closestSphere = { closestPoint , 0.01f };


		/*-------------------
			座標変換の行列
		-------------------*/

		// ビュー行列
		Matrix4x4 viewMatrix = Inverse(MakeAffineMatrix({ 1.0f , 1.0f , 1.0f }, cameraRotate, cameraTranslate));

		// 透視投影行列
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, static_cast<float>(kWindowWidth) / static_cast<float>(kWindowHeight), 0.1f, 100.0f);

		// ビューポート行列
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight), 0.0f, 1.0f);


		Vector3 start = Transform(Transform(segment.origin, Multiply(viewMatrix, projectionMatrix)), viewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), Multiply(viewMatrix, projectionMatrix)), viewportMatrix);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(Multiply(viewMatrix, projectionMatrix), viewportMatrix);

		DrawSphere(pointSphere, Multiply(viewMatrix, projectionMatrix), viewportMatrix, 0xFF0000FF);
		DrawSphere(closestSphere, Multiply(viewMatrix, projectionMatrix), viewportMatrix, 0x000000FF);

		Novice::DrawLine
		(
			static_cast<int>(start.x), static_cast<int>(start.y),
			static_cast<int>(end.x), static_cast<int>(end.y),
			0xFFFFFFFF
		);

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
