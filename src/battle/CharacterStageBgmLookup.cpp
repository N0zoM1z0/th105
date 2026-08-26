namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo();

struct CharacterByteMapNode {
    CharacterByteMapNode *left_00;
    CharacterByteMapNode *parent_04;
    CharacterByteMapNode *right_08;
    int key_0c;
    unsigned char value_10;
    unsigned char unknown_11[4];
    unsigned char is_end_15;
    unsigned char unknown_16[2];
};

struct CharacterByteMapTree;
struct CharacterByteMapIterator {
    CharacterByteMapTree *owner_00;
    CharacterByteMapNode *node_04;
};

struct CharacterByteMapTree {
    unsigned unknown_00;
    CharacterByteMapNode *end_node_04;

    CharacterByteMapIterator *lower_bound(
        CharacterByteMapIterator *result, const int *key);
};

extern CharacterByteMapTree g_stage_for_character_map;
extern CharacterByteMapTree g_bgm_for_character_map;

unsigned char __cdecl get_stage_for_character(int character_key)
{
    CharacterByteMapIterator found;
    CharacterByteMapIterator *result =
        g_stage_for_character_map.lower_bound(&found, &character_key);
    if (result->owner_00 == 0)
        _invalid_parameter_noinfo();
    if (result->node_04 == result->owner_00->end_node_04)
        _invalid_parameter_noinfo();
    return result->node_04->value_10;
}

unsigned char __cdecl get_bgm_for_character(int character_key)
{
    CharacterByteMapIterator found;
    CharacterByteMapIterator *result =
        g_bgm_for_character_map.lower_bound(&found, &character_key);
    if (result->owner_00 == 0)
        _invalid_parameter_noinfo();
    if (result->node_04 == result->owner_00->end_node_04)
        _invalid_parameter_noinfo();
    return result->node_04->value_10;
}

} // namespace th105
