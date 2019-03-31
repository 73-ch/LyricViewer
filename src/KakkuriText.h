#include "ofMain.h"

using namespace glm;

enum KakkuriIndexMode {
    KAKKURI_NO_INDEX,
    KAKKURI_INDEX_LINE,
    KAKKURI_INDEX_TRIANGLE,
    KAKKURI_INDEX_CUSTOM
};

class KakkuriText {
    void calcOffset();
    
    ofTrueTypeFont& font;
    vec3 offset;
    ofMesh mesh;
    string current_text;
    float current_roughness = 5;
    
    vector<ofIndexType> line_indices;
    vector<ofIndexType> triangle_indices;
    vector<unsigned int> num_verts;
    ofPrimitiveMode current_mode;
public:
    KakkuriText(ofTrueTypeFont& font_);
    KakkuriText& operator=(const KakkuriText&) {return *this; };
    KakkuriText& operator=(KakkuriText&&) = default;
    
    void setText(const string text, const float roughness);
    void setFont(ofTrueTypeFont& font_);
    void setPrimitiveMode(const ofPrimitiveMode mode, const bool auto_index = false);
    void setIndexMode(const KakkuriIndexMode mode, vector<ofIndexType> indices = vector<ofIndexType>{});
    void draw();
    
    
};
