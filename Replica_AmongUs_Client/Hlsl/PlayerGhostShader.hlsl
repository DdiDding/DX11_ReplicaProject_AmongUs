cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
    float4 _color_body;
    float4 _color_body_shadow;
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
    float4 color_body : TEXCOORD1;
    float4 color_body_shadow : TEXCOORD2;
};


//정점쉐이더의 중요한 역할은 투영공간으로 변환시키는것!
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
        
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
    output.uv = input.uv;
 
    output.color_body = _color_body;
    output.color_body_shadow = _color_body_shadow;
    
    return output;
}

//이거 이해하기
Texture2D shaderTexture;
SamplerState SampleType;


float4 PS(PixelInput input) : SV_Target
{
    
    //유령의 전체적인 알파값
    float minAlpha = 0.6f;
    //텍스처 색상
    
    float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, input.uv);
    
    if (minAlpha < textureColor.a)
    {
        textureColor.a = minAlpha;
    }
    
    //하얀 계열 처리
    if (textureColor.r > 0.4 && textureColor.g > 0.4 && textureColor.b > 0.4)
    {
        return textureColor;
    }
    //붉은계열 처리
    else if (textureColor.r > 0.48)
    {
        input.color_body.a = minAlpha;
        return input.color_body;
    }
    //파란계열 처리
    else if (textureColor.b > 0.46)
    {
        input.color_body_shadow.a = minAlpha;
        return input.color_body_shadow;
    }
    else if (textureColor.g > 0.4)
    {
        return float4(0, 0, 0, 0);
        //return textureColor + float4(0, -0.3, 0.8, 0);
    }
    
    return textureColor;
}

