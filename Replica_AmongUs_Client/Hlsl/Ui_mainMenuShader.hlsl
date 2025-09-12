cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
};

cbuffer TransformData2 : register(b1)
{
    //마우스가 올라갔는가?? 올라갔으면 1, 안올라갔으면 0
    int _isMouseIn;
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

    
    if (_isMouseIn == 1)
    {
    
    //검은색이면
        if (textureColor.r == 0 && textureColor.g == 0 && textureColor.b == 0){
            
            return textureColor; //검은색 렌더링
        }
    
        //검은색이 아니면
        else{
            
            return textureColor * float4(0, 1, 0, 1);
        }
    }
    
    return textureColor;
}

