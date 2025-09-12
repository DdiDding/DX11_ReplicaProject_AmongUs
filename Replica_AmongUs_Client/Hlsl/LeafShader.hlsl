
cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
};

cbuffer TransformData2 : register(b1)
{
    //���ۼ�Ʈ���� int�� ����
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


//�������̴��� �߿��� ������ ������������ ��ȯ��Ű�°�!
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
    output.uv = input.uv;
    
    return output;
}

//�̰� �����ϱ�
Texture2D shaderTexture;
SamplerState SampleType;


float4 PS(PixelInput input) : SV_Target
{
    
    float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, input.uv);
 
    if (input.position.x < 412)
    {
        return float4(0, 0, 0, 0);
    }
 
    return textureColor;
}

