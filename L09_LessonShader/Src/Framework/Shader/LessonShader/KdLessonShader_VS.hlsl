// カメラやライトのデータが使えるようになる
#include "../inc_KdCommon.hlsli"
#include "inc_KdLessonShader.hlsli"

// 頂点シェーダーから出力するデータ
struct VSOutput
{
	float4 Pos : SV_Position;
	float2 UV : TEXCOORD0;
};

VSOutput main(
	float4 pos : POSITION,
	float2 uv : TEXCOORD0
)
{
	VSOutput Out;

	// ここ大事！ (座標変換)
	Out.Pos = mul(pos,		g_mWorld);	// ローカル座標系		-> ワールド座標系
	Out.Pos = mul(Out.Pos,	g_mView);	// ワールド座標系		-> ビュー座標系へ変換
	Out.Pos = mul(Out.Pos,	g_mProj);	// ビュー座標系		-> 射影座標系へ変換

	Out.UV = uv * g_UVTiling + g_UVOffset;
	
	return Out;
}
