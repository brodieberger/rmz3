include songs.mk
include stage_rules.mk
include sprite_rules.mk
include graphics_file_rules.mk

ASSETS := $(SONG_ASMS) $(STAGE_HDR) $(SPRITES) $(ALL_GRAPHICS)

.PHONY: assets
assets: $(ASSETS)

.PHONY: clean-assets
clean-assets: clean-stage clean-midi clean-sprite clean-graphics clean-graphic-headers
