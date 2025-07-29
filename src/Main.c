#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/PerlinNoise.h"


int Octaves = 7;
float Persistance = 900.0f;

void Setup(AlxWindow* w){
    PerlinNoise_Permutations_Init();
    AlxFont_Resize(&window.AlxFont,50,50);
}

void Update(AlxWindow* w){
    if(Stroke(ALX_KEY_UP).PRESSED){
        Octaves++;
    }
    if(Stroke(ALX_KEY_DOWN).PRESSED){
        Octaves--;
    }

    if(Stroke(ALX_KEY_W).PRESSED){
        Persistance *= 1.01f;
    }
    if(Stroke(ALX_KEY_S).PRESSED){
        Persistance *= 0.99f;
    }
    
    Clear(BLACK);

    RGA_Set(Time_Nano());

    PerlinNoise_Offset_Set(Octaves);
    PerlinNoise_Persistance_Set(Persistance);

    for (int x = 0; x < GetWidth(); x++) {
        float px = (float)x;
        float n = PerlinNoise_1D_Get(px);
        
        n += 1.0f;
        n /= 2.0f;
        
        //Draw(x,((1.0f - n) * GetHeight() * 0.8f),WHITE);

        Vec2 s = { x,((1.0f - n) * GetHeight() * 0.8f) };
        Vec2 e = { x,GetHeight() * 0.8f };
        RenderLine(s,e,WHITE,1.0f);
    }
    
    String str = String_Format("O:%d  P:%f",Octaves,Persistance);
    RenderCStrSize(str.Memory,str.size,0.0f,0.0f,RED);
    String_Free(&str);
}

void Delete(AlxWindow* w){
    
}

int main(){
    if(Create("Perlin Noise",200,150,1,1,Setup,Update,Delete))
        Start();
    return 0;
}