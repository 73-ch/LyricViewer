#pragma once

#include "ofMain.h"

using namespace glm;

class TextMesh {
    void calcOffset();
    
    ofTrueTypeFont& font;
    vec3 offset;
    ofMesh mesh;
    string current_text;
    float current_thickness;
    
    public:
    TextMesh(ofTrueTypeFont& font_);
    TextMesh& operator=(const TextMesh&) {return *this; };
    TextMesh& operator=(TextMesh&&) = default;
    
    void setText(const string text, const float thickness);
    void setFont(ofTrueTypeFont& font_);
    void draw(ofPolyRenderMode render_type = OF_MESH_FILL);
};
