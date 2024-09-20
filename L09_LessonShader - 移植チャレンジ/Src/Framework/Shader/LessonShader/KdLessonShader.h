#pragma once

class KdLessonShader
{
public:

	// 定数バッファ(オブジェクト単位更新)
	struct cbObject
	{
		// UV操作
		Math::Vector2	UVOffset = { 0.0f, 0.0f };
		Math::Vector2	UVTiling = { 1.0f, 1.0f };

		// フォグ有効
		int				FogEnable = 1;

		// エミッシブのみの描画
		int				OnlyEmissie = 0;

		// スキンメッシュオブジェクトかどうか(スキンメッシュ対応)
		int				IsSkinMeshObj = 0;

		// ディゾルブ関連
		float			DissolveThreshold = 0.0f;	// 0 ～ 1
		float			DissolveEdgeRange = 0.03f;	// 0 ～ 1

		Math::Vector3	DissolveEmissive = { 0.0f, 1.0f, 1.0f };
	};

	// 定数バッファ (メッシュ単位更新)
	struct cbMesh
	{
		Math::Matrix	mW;
	};

	// 定数バッファ (マテリアル単位更新)
	struct cbMaterial
	{
		Math::Vector4	BaseColor	= { 1.0f, 1.0f, 1.0f, 1.0f };

		Math::Vector3	Emissive	= { 1.0f, 1.0f, 1.0f };
		float			Metallic	= 0.0f;

		float			Roughness	= 0.0f;

		float			_blank[3]	= { 0.0f, 0.0f, 0.0f };
	};

	//================================================
	// 設定・取得
	//================================================

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

	// フォグ有効/無効
	void SetFogEnable(bool enable)
	{
		m_cb0_Obj.Work().FogEnable = enable;

		m_dirtyCBObj = true;
	}

	// ディゾルブ設定
	void SetDissolve(float threshold, const float* range = nullptr, const Math::Vector3* edgeColor = nullptr)
	{
		auto& cbObj = m_cb0_Obj.Work();

		cbObj.DissolveThreshold = threshold;

		if (range)
		{
			cbObj.DissolveEdgeRange = *range;
		}

		if (edgeColor)
		{
			cbObj.DissolveEmissive = *edgeColor;
		}

		m_dirtyCBObj = true;
	}

	// ディゾルブテクスチャ設定
	void SetDissolveTexture(KdTexture& dissolveMask)
	{
		KdDirect3D::Instance().WorkDevContext()->PSSetShaderResources(11, 1, dissolveMask.WorkSRViewAddress());
	}

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

private:

	// マテリアルのセット
	void WriteMaterial(const KdMaterial& material, const Math::Vector4& colRate, const Math::Vector3& emiRate);

    ID3D11VertexShader* m_VS            = nullptr;  // 頂点シェーダー
    ID3D11PixelShader*  m_PS            = nullptr;  // ピクセルシェーダー

    ID3D11InputLayout*  m_inputLayout   = nullptr;  // 頂点入力レイアウト

	KdConstantBuffer<cbObject>		m_cb0_Obj;			// オブジェクト単位で更新
	KdConstantBuffer<cbMesh>		m_cb1_Mesh;			// メッシュ毎に更新
	KdConstantBuffer<cbMaterial>	m_cb2_Material;		// マテリアル毎に更新

	KdRenderTargetPack	m_depthMapFromLightRTPack;
	KdRenderTargetChanger m_depthMapFromLightRTChanger;

	bool m_dirtyCBObj : 1 = false;	// 定数バッファに変更があったかどうか 
};
