#version 400

in vec3 EntryPoint;//Color
in vec4 ExitPointCoord;//gl_Posiction

uniform sampler2D ExitPoints;
uniform sampler3D VolumeTex;
uniform sampler1D TransferFunc;  
uniform float     StepSize;
uniform vec2      ScreenSize;
layout (location = 0) out vec4 FragColor;

void main()
{
    vec2 texc = ((ExitPointCoord.xy/ExitPointCoord.w) + 1.0f)/2.0f;
    vec3 exitPoint = texture(ExitPoints, texc).xyz;
    //vec3 exitPoint = texture(ExitPoints, gl_FragCoord.st/ScreenSize).xyz;
  
    if (EntryPoint == exitPoint)
        discard;
    vec3 dir = exitPoint - EntryPoint;
    float len = length(dir);
    vec3 deltaDir = normalize(dir) * StepSize;
    float deltaDirLen = length(deltaDir);
    vec3 voxelCoord = EntryPoint;
    vec4 colorAcum = vec4(0.0); // The dest color
    float alphaAcum = 0.0; 
    float intensity;
    float lengthAcum = 0.0;
    vec4 colorSample; 
    float alphaSample; 
    vec4 bgColor = vec4(1.0, 1.0, 1.0, 0.0);
 
    for(int i = 0; i < 1600; i++)
    {
        colorSample = texture(VolumeTex, voxelCoord);
        alphaSample = colorSample.a * StepSize;
        colorAcum += (1.0 - alphaAcum) * colorSample*alphaSample*3;
        alphaAcum += alphaSample;
        voxelCoord += deltaDir;
        lengthAcum += deltaDirLen;

        if (lengthAcum >= len )
        {   
            //colorAcum.rgb = colorAcum.rgb * colorAcum.a + (1 - colorAcum.a) * bgColor.rgb;        
            break; 
        }   
        else if (colorAcum.a > 1.0)
        {
            //colorAcum.a = 1.0;
            break;
        }
    }
    FragColor = colorAcum;
    //FragColor = vec4((colorAcum.rgb * 2 + vec3(0.2f,0.2f,0.2f)), colorAcum.a);
    // for test
    //FragColor = vec4(EntryPoint, 1.0);
    //FragColor = vec4(exitPoint, 1.0);
   
}
