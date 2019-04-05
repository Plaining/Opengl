
#version 330 core
out vec4 FragColor;

in vec4 Pos;
in vec3 color;

uniform vec2 ScreenSize;
uniform sampler2D textureColorbuffer;
uniform float StepSize;
uniform sampler3D texture3dID;
uniform sampler1D texture1dID;

void main() {
    vec3 exitPoint = texture(textureColorbuffer,gl_FragCoord.st/ScreenSize).xyz;
    if(color == exitPoint){
    discard;
    }
    vec3 dir = exitPoint - color;
    float len = length(dir);
    vec3 deltaDir = normalize(dir) * StepSize;
    float deltaDirLen = length(deltaDir);
    vec3 voxelCoord = color;
    vec4 colorAcum = vec4(0.0);
    float alphaAcum = 0.0;
    float intensity;
    float lengthAcum = 0.0;
    vec4 colorSample;
    float alphaSample;
    vec4 bgColor = vec4(1.0,1.0,1.0,1.0);

    for(int i=0;i<1600;i++){
    	intensity = texture(texture3dID, voxelCoord).x;
    	colorSample = texture(texture1dID, intensity);
    	if(colorSample.a>0.0){
    		colorSample.a = 1.0 - pow(1.0 - colorSample.a,StepSize*200.0f);
    		colorAcum.rgb += (1.0 - colorAcum.a)*colorSample.rgb*colorSample.a;
    		colorAcum.a +=(1.0 - colorAcum.a)*colorSample.a;
    	}
    	voxelCoord += deltaDir;
    	lengthAcum += deltaDirLen;
    	if(lengthAcum >= len){
    		colorAcum.rgb = colorAcum.rgb*colorAcum.a+(1-colorAcum.a)*bgColor.rgb;
    	}else if(colorAcum.a>1.0){
    		colorAcum.a = 1.0;
    		break;
    	}
    }
    FragColor = colorAcum;
    //FragColor = vec4(exitPoint,1.0f);
    //FragColor = vec4(color,1.0);
}