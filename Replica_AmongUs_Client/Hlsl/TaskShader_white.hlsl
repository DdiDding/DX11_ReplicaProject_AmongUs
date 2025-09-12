cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
};

cbuffer TransformData2 : register(b1)
{
    //플레이어와 테스크간의 거리상태를 받음
    int _near;
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
};


//정점쉐이더의 중요한 역할은 투영공간으로 변환시키는것!
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
        
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
    output.uv = input.uv;
    
    return output;
}

//이거 이해하기
Texture2D shaderTexture;
SamplerState SampleType;


float4 PS(PixelInput input) : SV_Target
{
    
    float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, input.uv);
    
    if (_near == 1)
    {
        if (textureColor.a > 0.1)
            textureColor += float4(0.4, 0.4, 0.4, 1);
        return textureColor;
    }
    else if (_near == 2)
    {
        return textureColor;
    }
    else if (_near == 3)
    {
        if (textureColor.r == 1 && textureColor.g == 1 && textureColor.b == 1)
            return float4(0, 0, 0, 0);
    }
    
    return textureColor;
}

