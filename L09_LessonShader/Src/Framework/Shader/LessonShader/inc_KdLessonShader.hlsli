// 定数バッファ (オブジェクト単位)
cbuffer cbObject : register(b0)
{
	float2 g_UVOffset;
	float2 g_UVTiling;
}

// 定数バッファ (メッシュ単位)
cbuffer cbMesh : register(b1)
{
	// オブジェクト情報
	row_major float4x4 g_mWorld;	// ワールド変換行列
}
