cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
    float3 _mouse;
};

struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float2 mouse : TEXCOORD2;
    float4 worldTest : TEXCOORD3;
};


//정점쉐이더의 중요한 역할은 투영공간으로 변환시키는것!
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
    output.worldTest = output.position;
        
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
    output.mouse = _mouse;
    
    output.uv = input.uv;
    
    return output;
}

//이거 이해하기
Texture2D shaderTexture;
SamplerState SampleType;


float4 PS(PixelInput input) : SV_Target
{
    
    float4 textureColor;
    //textureColor = tex2D(sam, input.uv);
    textureColor = shaderTexture.Sample(SampleType, input.uv);
    
    if (input.mouse.x - 100 < input.worldTest.x &&
        input.worldTest.x < input.mouse.x + 100)
    {
        return textureColor * float4(1, 0, 0, 0.6);
    }
 
    if (textureColor.r == 0 && textureColor.g == 1 && textureColor.b == 0 && textureColor.a == 1)
    {
        return float4(1, 0, 0, 0.6);
    }
    else if (textureColor.r == 1 && textureColor.g == 0 && textureColor.b == 1 && textureColor.a == 1)
    {
        return float4(0.5, 0.1, 0.1, 0.6);
    }
    else if (textureColor.r == 1 && textureColor.g == 0 && textureColor.b == 0 && textureColor.a == 1)
    {
        return float4(0.3, 0, 0, 0.8);
    }
    return textureColor;
}

