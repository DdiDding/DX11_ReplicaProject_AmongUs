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


//�������̴��� �߿��� ������ ������������ ��ȯ��Ű�°�!
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

//�̰� �����ϱ�
Texture2D shaderTexture;
SamplerState SampleType;


float4 PS(PixelInput input) : SV_Target
{
    
    //������ ��ü���� ���İ�
    float minAlpha = 0.6f;
    //�ؽ�ó ����
    
    float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, input.uv);
    
    if (minAlpha < textureColor.a)
    {
        textureColor.a = minAlpha;
    }
    
    //�Ͼ� �迭 ó��
    if (textureColor.r > 0.4 && textureColor.g > 0.4 && textureColor.b > 0.4)
    {
        return textureColor;
    }
    //�����迭 ó��
    else if (textureColor.r > 0.48)
    {
        input.color_body.a = minAlpha;
        return input.color_body;
    }
    //�Ķ��迭 ó��
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

