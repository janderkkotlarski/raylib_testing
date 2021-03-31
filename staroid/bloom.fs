#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

const vec2 size = vec2(800, 800);   // render size
const float samples = 8.0;          // pixels per axis; higher = bigger glow, worse performance
const float quality = 5.0; 	        // lower = smaller glow, better quality

void main()
{
    vec4 sum = vec4(0);
    vec2 sizeFactor = vec2(1)/size*quality;

    // Texel color fetching from texture sampler
    vec4 source = texture(texture0, fragTexCoord);

    const float range = 1.0;            // should be = (samples - 1)/2;

    const float step = 0.25;

    for (float x = -range; x <= range; x += step)
    {
        for (float y = -range; y <= range; y += step)
        {
            sum += texture(texture0, fragTexCoord + vec2(x, y)*sizeFactor);
        }
    }

    // Calculate final fragment color
    finalColor = ((sum/(samples*samples)) + source)*colDiffuse;
}