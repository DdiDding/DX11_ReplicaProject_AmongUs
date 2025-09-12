cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
};

cbuffer TransformData2 : register(b1)
{
    //미션 상태
    //0 - [모두 불꺼짐]
    //1 - [초록불 켜짐]
    //2 - [빨간불 켜짐]
    int _status;
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
    //알아둘거는 이미지에 이미 두개다 켜져있다
    //미션 상태
    //0 - [모두 불꺼짐]
    //1 - [초록불 켜짐]
    //2 - [빨간불 켜짐]
    
    float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, input.uv);

    
    if (_status == 0)
    {
        //초록 불 끄기 
        if (textureColor.g >= 0.392 && textureColor.r <= 0.203)
        {
            return textureColor * float4(0.3, 0.3, 0.3, 1);
        }
        
        //빨간 불 끄기
        if (textureColor.r >= 0.321 && textureColor.b <= 0.203)
        {
            return textureColor * float4(0.3, 0.3, 0.3, 1);
        }
    }
    else if (_status == 1)
    {
        //빨간 불 끄기
        if (textureColor.r >= 0.321 && textureColor.b <= 0.203)
        {
            return textureColor * float4(0.3, 0.3, 0.3, 1);
        }
    }
    else if (_status == 2)
    {
        //초록 불 끄기 
        if (textureColor.g >= 0.392 && textureColor.r <= 0.203)
        {
            return textureColor * float4(0.3, 0.3, 0.3, 1);
        }
    }
    
    
    return textureColor;
}

