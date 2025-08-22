[shader("vertex")]
float4 vertexMain(float3 pos : POSITION) : SV_Position
{
    return float4(pos, 1.0);
}

[shader("fragment")]
float4 fragmentMain() : SV_Target
{
    return float4(1.0f, 0.5f, 0.2f, 1.0f);
}