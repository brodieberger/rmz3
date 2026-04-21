export type GraphicProp = '4bpp' | '8bpp' | 'lz77' | 'no_pal' | 'chunked';

// e.g. sprites/dynamic/anubis/header.json の data の要素
export type GraphicHeader = {
  name: string; // ".png" | ".4bpp" | ".lz"
  ofs: number; // VRAMのどこに転送されるか
  chunkSize: number;
  props: GraphicProp[];
  palette?: {
    color: number;
    id: number;
  };
  files?: string[]; // そのグラフィックが依存しているファイル (e.g. グラフィックデータやパレットデータ). 自分で書いてあげる必要がある
  hdrOnly?: boolean;
};

export type Nullable<T> = T | null | undefined;
