//자신이 임포스터이며 다른 크루원들을 나타내는 셰이더
cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
    float4 _color_body;
    float4 _color_body_shadow;
};

//int가 하나들어오는데 이게 0이면 그냥 정상 출력하고 1이면 테두리가 나오게 출력하자
cbuffer TransformData : register(b1)
{
    int _isNear;
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
    
    float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, input.uv);
    
    //0.009까지댐 ~ 0.03
    float distance = 0.02;
    
    float2 leftUv = input.uv;    leftUv.x -= distance; 
    float2 rightUv = input.uv;    rightUv.x += distance;
    float2 upUv = input.uv;    upUv.y -= distance;
    float2 downUv = input.uv;    downUv.y += distance;
    
    //현재 픽셀에서 각방향으로 distance만큼 이동한 픽셀의 색
    float4 textureColorL = shaderTexture.Sample(SampleType, leftUv);
    float4 textureColorR = shaderTexture.Sample(SampleType, rightUv);
    float4 textureColorU = shaderTexture.Sample(SampleType, upUv);
    float4 textureColorD = shaderTexture.Sample(SampleType, downUv);
    
    
    if (textureColor.r > 0.4 && textureColor.g > 0.4 && textureColor.b > 0.4)
    {
        return textureColor;
    }
    //붉은계열 처리
    else if (textureColor.r > 0.48)
    {
        return input.color_body;
    }
    //파란계열 처리
    else if (textureColor.b > 0.46)
    {
        return input.color_body_shadow;

    }
    else if (textureColor.g > 0.4)
    {
        return textureColor + float4(0, -0.3, 0.8, 1);
    }
    
    //테두리 부분을 해야하면
    if (_isNear == 1)
    {
        //투명인 부분에
        if (textureColor.a <= 0.8)
        {

        //왼쪽픽셀에 색상이 있어?
        if ((textureColorL.a >= 0.2 || textureColorR.a >= 0.2) &&
            (textureColorU.a >= 0.2 || textureColorD.a >= 0.2))
        {
            return float4(1, 0, 0, 1);
        }
            
            
        }
    }
    
    return textureColor;
}

