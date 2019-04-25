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
    //vec3 exitPoint = texture(ExitPoints, gl_FragCoord.st/ScreenSize).xyz;
    vec3 exitPoint = texture(ExitPoints, gl_FragCoord.st/vec2(800.0f,800.0f)).xyz;
  
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
        colorSample.a = 1.0 - pow(1.0 - colorSample.a, StepSize * 200.0f);
        if( colorSample.x <= 0){
            break;
        }
        if(colorSample.x > 135){
            colorSample.a = 1.0;
        }
        else if(colorSample.x > 35 && colorSample.x <= 135){
            colorSample.a  = (colorSample.x - 35) / 100;
        }
        else if(colorSample.x < 35){
            //colorSample.a = colorSample.x * StepSize;
            colorSample.a = 0;
        }
        colorAcum.rgb += (1.0 - colorAcum.a) * colorSample.rgb * colorSample.a * 3 ;
        colorAcum.a += (1.0 - colorAcum.a) * colorSample.a;
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
    // for test
    //FragColor = vec4(EntryPoint, 1.0);
    //FragColor = vec4(exitPoint, 1.0);
   
}
