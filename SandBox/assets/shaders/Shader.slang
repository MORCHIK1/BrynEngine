// shader.slang

struct F {
    float a;
    int b;
};

// layout qualifier is good practice for OpenGL/Vulkan
layout(binding = 0, std140) 
ConstantBuffer<F> buf;

[shader("vertex")]
float4 vertexMain(float3 pos : POSITION) : SV_Position
{
    // --- THIS IS THE FIX ---
    // Use 'buf' for anything, even something trivial.
    // This forces the compiler to keep 'buf' as a global parameter.
    pos.x += buf.a * 0.00001f; // Multiply by small number to avoid visible change if not desired

    return float4(pos, 1.0);
}

[shader("fragment")]
float4 fragmentMain() : SV_Target
{
    // Use float(buf.b) to cast int to float for the color channels
    return float4(buf.a, float(buf.b), float(buf.b), 1.0f);
}