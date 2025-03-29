# Platform

Man.

Examples:

## Input

```c
if (st_is_key_just_pressed(ST_KEY_J)) {
	st_log("J");
}
```

## Keymaps

```c
st_add_keymap("j?", ST_KEY_J);
st_add_keymap("j?", ST_KEY_H);
if (st_is_keymap_just_pressed("j?")) {
	st_log("J?");
}
```

## Textures

```c
// textures are only loaded once
StTexture* texture = StTexture_new("assets/bob.png");
st_draw_texture(texture, (StVec2){69, 420}, 8528974);
```

## Models

```c
// models are only loaded once
// you could use .obj but it doesn't load the materials for some reason
StModel* bob = StModel_new("assets/bob.glb");
st_draw_object_3d((StObject3D){
	.model = bob,
	.position = (StVec3){0, 0, 0},
	.rotation = 0,
	.scale = (StVec3){2, 1, 1},
	.tint = st_rgb(255, 255, 255),
});
```
