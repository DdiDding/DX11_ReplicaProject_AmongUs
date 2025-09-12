cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
};

cbuffer TransformData2 : register(b1)
{
    //�̼� ����
    //0 - [��� �Ҳ���]
    //1 - [�ʷϺ� ����]
    //2 - [������ ����]
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
    //�˾ƵѰŴ� �̹����� �̹� �ΰ��� �����ִ�
    //�̼� ����
    //0 - [��� �Ҳ���]
    //1 - [�ʷϺ� ����]
    //2 - [������ ����]
    
    float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, input.uv);

    
    if (_status == 0)
    {
        //�ʷ� �� ���� 
        if (textureColor.g >= 0.392 && textureColor.r <= 0.203)
        {
            return textureColor * float4(0.3, 0.3, 0.3, 1);
        }
        
        //���� �� ����
        if (textureColor.r >= 0.321 && textureColor.b <= 0.203)
        {
            return textureColor * float4(0.3, 0.3, 0.3, 1);
        }
    }
    else if (_status == 1)
    {
        //���� �� ����
        if (textureColor.r >= 0.321 && textureColor.b <= 0.203)
        {
            return textureColor * float4(0.3, 0.3, 0.3, 1);
        }
    }
    else if (_status == 2)
    {
        //�ʷ� �� ���� 
        if (textureColor.g >= 0.392 && textureColor.r <= 0.203)
        {
            return textureColor * float4(0.3, 0.3, 0.3, 1);
        }
    }
    
    
    return textureColor;
}

