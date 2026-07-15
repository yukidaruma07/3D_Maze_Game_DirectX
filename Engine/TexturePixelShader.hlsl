Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

cbuffer ConstantBuffer : register(b0)
{
    matrix wvpMat;
    float4 diffUse;
    float4 ambient;
    float4 speculer;
    int isTexture;
    int isGray;
}

struct PSInput {
    float4 position : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

float4 main(PSInput IN) : SV_Target
{
    float4 diffUse_ = { 1.0, 0.0, 0.0, 1.0};
    if (isTexture)
    {
        diffUse_ = texture0.Sample(sampler0, IN.uv);

    }
    else
    {
        diffUse_ = diffUse;
    }
    
    if (isGray)
    {
        float r = 0.299 * diffUse_.r;
        float g = 0.587 * diffUse_.g;
        float b = 0.114 * diffUse_.b;
        diffUse_ = r + g + b;
    }
    
    return diffUse_ + diffUse_ * ambient + speculer;
}