cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
};

cbuffer TransformData2 : register(b1)
{
    //몇퍼센트인지 int로 받음
    int _percent;
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
 
    if (0 < _percent)
    {
        
        float percent = _percent / 100.0f;
    
        if (input.uv.x < percent)
        {
            return float4(0.274f, 0.913f, 0.447f, 1);
        }
    }
    return textureColor;
}

