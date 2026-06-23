cbuffer ConstantBuffer : register(b0)
{
    matrix wvpMat;
}

struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VSOutput
{
    float4 position : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VSOutput main(VSInput IN)
{
    VSOutput OUT;
    OUT.position = mul(float4(IN.position, 1.0f), wvpMat);
    OUT.color = IN.color;
    OUT.uv = IN.uv;
    return OUT;
}