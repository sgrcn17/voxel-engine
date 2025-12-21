# TODO - Voxel Engine

## Główne zadania

### 2. Poprawa kamery/main.cpp
- [ ] Przenieść logikę kamery z `main.cpp` do osobnego modułu/klasy
- [ ] Uporządkować ścieżki do shaderów/textur (relatywne zamiast absolutnych)
- [ ] Dodać konfigurację przez plik/argumenty zamiast hardcodowanych wartości
- [ ] Poprawić zarządzanie czasem (deltaTime) i FPS limiting
- [ ] Dodać obsługę zmiany rozdzielczości okna


### 5. Dodanie technik graficznych
- [ ] Frustum culling - renderowanie tylko widocznych chunków
- [ ] Occlusion culling - pomijanie chunków zasłoniętych przez inne
- [ ] Face culling - już częściowo (tylko widoczne ściany bloków)
- [ ] Level of Detail (LOD) - różne poziomy szczegółowości dla odległych chunków
- [ ] Fog/Distance fog - zanikanie odległych chunków
- [ ] Ambient occlusion - cieniowanie narożników bloków
- [ ] Lighting system - podstawowe oświetlenie (directional/sunlight)

### 7. Poprawienie danych podawanych do OpenGL
- [ ] Zmienić `vertices` z `std::vector<float>` na bardziej efektywny format (np. `std::vector<short>` dla pozycji)
- [ ] Rozważyć użycie `GL_UNSIGNED_BYTE` dla UV coordinates zamiast `float`
- [ ] Dodać vertex buffer interleaving optimization
- [ ] Rozważyć użycie `GL_DYNAMIC_DRAW` zamiast `GL_STATIC_DRAW` dla często zmienianych chunków
- [ ] Dodać vertex buffer streaming dla dużych ilości danych
- [ ] Zoptymalizować format vertex attributes (packing)

### 8. Zintegrowanie z typami bloków istniejącego kodu, dopisanie do data.hpp
- [ ] Rozszerzyć `enum class BlockType` o wszystkie typy bloków (Grass, Dirt, Stone, Sand, etc.)
- [ ] Dodać `struct BlockProperties { bool solid; bool transparent; glm::vec2 topUV, sideUV, bottomUV; }`
- [ ] Utworzyć lookup table `BlockProperties blockProperties[BlockType::SIZE]`
- [ ] Zaktualizować `GenerateChunkBlocks` aby używała `BlockType` enum
- [ ] Dodać funkcję `GetBlockTextureUV(BlockType type, FaceDirection face)` do `data.hpp`
- [ ] Zaktualizować `AddQuadVertices` aby używała `BlockType` do wyboru tekstury
- [ ] Dodać `constexpr` mapy/metafunkcje dla właściwości bloków

### 9. Zapisywanie informacji o blokach w pliku
- [ ] Zaimplementować `Region` class (32x32 chunki per region)
- [ ] Dodać kompresję zlib dla danych chunków
- [ ] Utworzyć format pliku regionu (header + chunk table + compressed data)
- [ ] Dodać `World::SaveChunk()` i `World::LoadChunk()` methods
- [ ] Dodać `World::SaveAllChunks()` i `World::LoadRegion()` methods
- [ ] Dodać cache regionów w pamięci (lazy loading)
- [ ] Dodać dirty flag dla chunków wymagających zapisu
- [ ] Dodać automatyczne zapisywanie co X sekund lub przy wyjściu

### 10. Dodanie wielowątkowości/multi processingu
- [ ] Utworzyć thread pool dla generowania chunków
- [ ] Przenieść `GenerateChunkBlocks` do osobnego wątku
- [ ] Przenieść `UpdateMesh()` do osobnego wątku (z synchronizacją OpenGL)
- [ ] Dodać queue dla chunków do generowania (`std::queue` + mutex)
- [ ] Dodać queue dla chunków do mesh update (`std::queue` + mutex)
- [ ] Zaimplementować async chunk loading z plików
- [ ] Dodać `std::atomic` flags dla thread-safe chunk state
- [ ] Rozważyć użycie `std::async` lub `std::thread` dla prostszych operacji
- [ ] Dodać worker threads dla terrain generation (fractal noise calculations)

---

## Multitaskowe zadania

### Dodatkowe optymalizacje
- [ ] Spatial hashing dla szybkiego lookup chunków
- [ ] Chunk preloading - generowanie chunków przed wejściem gracza
- [ ] Chunk unloading - usuwanie odległych chunków z pamięci
- [ ] Memory pooling - reuse vertex/index buffers zamiast alokacji
- [ ] SIMD optimizations dla generowania chunków (jeśli kompilator nie optymalizuje)
  - **Uwaga:** SIMD (Single Instruction, Multiple Data) - równoległe przetwarzanie wielu wartości jedną instrukcją (SSE/AVX). Kompilatory często automatycznie wektoryzują pętle, więc ręczne użycie SIMD ma sens tylko w wąskich gardłach.

### HUD + niszczenie i stawianie bloków
- [ ] Dodać system raycasting (sprawdzanie który blok gracz patrzy)
- [ ] Dodać obsługę kliknięcia myszy (lewy = niszczenie, prawy = stawianie)
- [ ] Dodać inventory system (przechowywanie bloków do stawiania)
- [ ] Dodać HUD (crosshair, inventory, FPS counter)

### Polepszony generator świata
- [ ] Ulepszyć generowanie terenu - różne wysokości gór i pagórków
- [ ] Dodać woda (opcjonalnie)
- [ ] Poprawić noise algorithm dla bardziej naturalnego wyglądu terenu