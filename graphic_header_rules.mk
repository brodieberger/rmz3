GFX_JSON_CONVERTER := ./tools/dev/graphic_header.ts

GFX_JSON := $(shell find sprites -type f -name 'header.json')

# e.g. sprites/dynamic/zero/idle/sheet/header.json -> build/rmz3/sprites/dynamic/zero/idle/sheet/header.s
GFX_ASM := $(addprefix $(BUILD_DIR)/, $(GFX_JSON:.json=.s))

# オフセットの計算にグラフィックデータのサイズが必要なので、すべてのグラフィックデータを依存関係に含める
$(GFX_ASM): $(BUILD_DIR)/%.s: %.json $(ALL_GRAPHICS)
	$(GFX_JSON_CONVERTER) $< > $@

# e.g. build/rmz3/sprites/dynamic/zero/idle/sheet/header.o
GFX_HDR := $(GFX_ASM:.s=.o)

# $(warning GFX_HDR = $(GFX_HDR))

.PHONY: graphic-headers
graphic-headers: $(GFX_HDR)

.PHONY: clean-graphic-headers
clean-graphic-headers:
	@rm -f $(GFX_HDR) $(GFX_ASM)
