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
    vec3 nvoxel = vec3(0.0,0.0,0.0);


    vec3 lightColor = vec3(1.0,1.0,1.0);
    vec3 lightPos = vec3(3.0f, 1.0f, 2.0f);
    vec3 viewPos  = vec3(0.0,0.0,3.0);
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    for(int i = 0; i < 1600; i++)
    {
        colorSample = texture(VolumeTex, voxelCoord);
        nvoxel = colorSample.rgb;
        //colorSample.a = 1.0 - pow(1.0 - colorSample.a, StepSize * 200.0f);
        /*if( colorSample.x <= 0){
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
        }*/

        colorSample.rgb = vec3(colorSample.a,colorSample.a,colorSample.a);
        colorSample.a = colorSample.a * StepSize;
        //colorSample.a = 1.0 - pow(1.0 - colorSample.a, StepSize * 200.0f);
        /*
        Bank BRDF
        */
        vec3 FragPos = colorSample.rgb;
        vec3 norm = normalize(nvoxel);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        float specularStrength = 0.5;
        vec3 V = normalize(viewPos - FragPos);
        vec3 H = normalize(lightDir + V);
        vec3 specular = vec3(0.0,0.0,0.0);
        if(dot(V,norm)>0&&(dot(lightDir,norm)>0)){
            vec3 T = normalize(cross(norm,V));
            float a = dot(lightDir,T);
            float b = dot(V,T);
            float c = sqrt(1-pow(a,2.0))*sqrt(1-pow(b,2.0))-a*b;
            float brdf = specularStrength * pow(c,32);
            specular = brdf * lightColor * diff;
        }
        /*
        Cook-Torrance
        */
        /*vec3 FragPos = colorSample.rgb;
        vec3 norm = normalize(nvoxel);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        float specularStrength = 0.5;
        vec3 V = normalize(viewPos - FragPos);
        vec3 H = normalize(lightDir + V);
        vec3 specular = vec3(0.0,0.0,0.0);

        float m = 0.5;
        float f = 0.5;
        float nv = dot(norm,V);
        float nl = max(dot(norm, lightDir),0);
        if(nv>0 && nl>0){
            float nh = dot(norm,H);
            float temp = (nh*nh-1)/(m*m*nh*nh);
            float roughness = (exp(temp))/(pow(m,2)*pow(nh,4.0));
            
            float vh = dot(V,H);
            float a = (2*nh*nv)/vh;
            float b = (2*nh*nl)/vh;
            float geometric = min(a,b);
            geometric = min(1,geometric);

            float fc = f+(1-f)*pow(1-vh,5.0);
            float rs = (fc*geometric*roughness)/(nv*nl);
            specular = rs * nl * specularStrength *lightColor;
        }
        */
        /*
        Blinn-phong
        */
        /*vec3 FragPos = colorSample.rgb;
        // diffuse 
        vec3 norm = normalize(nvoxel);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        //above is ambert
        // specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightColor;  
        //above is Blinn-phong
        */
       
        colorAcum.rgb += (1.0 - colorAcum.a) * colorSample.rgb * colorSample.a * 3 * (ambient + diffuse + specular);
        colorAcum.a += (1.0 - colorAcum.a) * colorSample.a;
        voxelCoord += deltaDir;
        lengthAcum += deltaDirLen;
            
        if (lengthAcum >= len )
        {       
            break; 
        }   
        else if (colorAcum.a > 1.0)
        {
            break;
        }
    }

    FragColor = colorAcum;
    // for test
    //FragColor = vec4(EntryPoint, 1.0);
    //FragColor = vec4(exitPoint, 1.0);
   
}
