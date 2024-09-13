#pragma once

class KdLessonShader
{
public:

	// 定数バッファ (オブジェクト単位)
	struct cbObject
	{
		// UV操作
		Math::Vector2	UVOffset = { 0.0f, 0.0f };
		Math::Vector2	UVTiling = { 1.0f, 1.0f };
	};

	// 定数バッファ (メッシュ単位更新)
	struct cbMesh
	{
		Math::Matrix	mW;
	};

    //================================================
    // 初期化・解放
    //================================================

    // 初期化
    bool Init();
    // 解放
    void Release();

    // デストラクタで自動で解放するようにする
    ~KdLessonShader() { Release(); }

    //================================================
    // 描画準備
    //================================================
    // 陰影をつけるオブジェクト等を描画する前後に行う
    void Begin();
    void End();

    //================================================
    // 描画関数
    //================================================
    // メッシュ描画
    void DrawMesh(const KdMesh* mesh, const Math::Matrix& mWorld, const std::vector<KdMaterial>& materials,
        const Math::Vector4& col, const Math::Vector3& emissive);

    // モデルデータ描画：アニメーションに非対応
    void DrawModel(const KdModelData& rModel, const Math::Matrix& mWorld = Math::Matrix::Identity,
        const Math::Color& colRate = kWhiteColor, const Math::Vector3& emissive = Math::Vector3::Zero);

	// UVタイリング設定
	void SetUVTiling(const Math::Vector2& tiling)
	{
		m_cb0_Obj.Work().UVTiling = tiling;

		m_dirtyCBObj = true;
	}

	// UVオフセット設定
	void SetUVOffset(const Math::Vector2& offset)
	{
		m_cb0_Obj.Work().UVOffset = offset;

		m_dirtyCBObj = true;
	}

private:

	// マテリアルのセット
	void WriteMaterial(const KdMaterial& material, const Math::Vector4& colRate, const Math::Vector3& emiRate);

    ID3D11VertexShader* m_VS            = nullptr;  // 頂点シェーダー
    ID3D11PixelShader*  m_PS            = nullptr;  // ピクセルシェーダー

    ID3D11InputLayout*  m_inputLayout   = nullptr;  // 頂点入力レイアウト

	KdConstantBuffer<cbObject>		m_cb0_Obj;			// オブジェクト単位で更新
	KdConstantBuffer<cbMesh>		m_cb1_Mesh;			// メッシュ毎に更新

	bool m_dirtyCBObj : 1 = false;	// 定数バッファに変更があったかどうか 
};
