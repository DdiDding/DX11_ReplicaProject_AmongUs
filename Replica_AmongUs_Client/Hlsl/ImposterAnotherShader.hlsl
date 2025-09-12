//�ڽ��� ���������̸� �ٸ� ũ������� ��Ÿ���� ���̴�
cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
    float4 _color_body;
    float4 _color_body_shadow;
};

//int�� �ϳ������µ� �̰� 0�̸� �׳� ���� ����ϰ� 1�̸� �׵θ��� ������ �������
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
    
    float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, input.uv);
    
    //0.009������ ~ 0.03
    float distance = 0.02;
    
    float2 leftUv = input.uv;    leftUv.x -= distance; 
    float2 rightUv = input.uv;    rightUv.x += distance;
    float2 upUv = input.uv;    upUv.y -= distance;
    float2 downUv = input.uv;    downUv.y += distance;
    
    //���� �ȼ����� ���������� distance��ŭ �̵��� �ȼ��� ��
    float4 textureColorL = shaderTexture.Sample(SampleType, leftUv);
    float4 textureColorR = shaderTexture.Sample(SampleType, rightUv);
    float4 textureColorU = shaderTexture.Sample(SampleType, upUv);
    float4 textureColorD = shaderTexture.Sample(SampleType, downUv);
    
    
    if (textureColor.r > 0.4 && textureColor.g > 0.4 && textureColor.b > 0.4)
    {
        return textureColor;
    }
    //�����迭 ó��
    else if (textureColor.r > 0.48)
    {
        return input.color_body;
    }
    //�Ķ��迭 ó��
    else if (textureColor.b > 0.46)
    {
        return input.color_body_shadow;

    }
    else if (textureColor.g > 0.4)
    {
        return textureColor + float4(0, -0.3, 0.8, 1);
    }
    
    //�׵θ� �κ��� �ؾ��ϸ�
    if (_isNear == 1)
    {
        //������ �κп�
        if (textureColor.a <= 0.8)
        {

        //�����ȼ��� ������ �־�?
        if ((textureColorL.a >= 0.2 || textureColorR.a >= 0.2) &&
            (textureColorU.a >= 0.2 || textureColorD.a >= 0.2))
        {
            return float4(1, 0, 0, 1);
        }
            
            
        }
    }
    
    return textureColor;
}

