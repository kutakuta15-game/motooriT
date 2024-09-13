#include "../inc_KdCommon.hlsli"

// モデル描画用テクスチャ
Texture2D g_baseTex : register(t0); // ベースカラーテクスチャ

// サンプラ
SamplerState g_ss : register(s0); // 通常のテクスチャ描画用

struct VSOutput
{
	float4 Pos : SV_Position;
	float2 UV : TEXCOORD1;
};

float4 main(VSOutput In) : SV_TARGET
{
	float4 baseColor = g_baseTex.Sample(g_ss, In.UV);
	return baseColor;
}
