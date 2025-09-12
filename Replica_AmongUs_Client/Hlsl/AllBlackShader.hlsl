struct VertexInput
{
    float4 position : POSITION0;
    float4 color : COLOR0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;
    float4 color : COLOR0;
};

cbuffer TransformData : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
};

cbuffer TransformData : register(b1)
{
    float _alpha;
};


PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
    
    output.color = input.color;
    return output;
}

float4 PS(PixelInput input) : SV_Target
{
    
    input.color.a = _alpha;
    return input.color;
}