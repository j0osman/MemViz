# Memory Efficiency Analyzer (C++20)

A small C++ program that inspects **heap allocation spacing** to estimate allocator overhead and memory efficiency for different data types.

It allocates two objects of the same type using `new`, measures the address distance between them, and compares:

- **Logical size** → `sizeof(T)`
- **Physical spacing** → Address difference between allocations
- **Waste** → Extra bytes introduced by allocator alignment/metadata
- **Efficiency** → `logical_size / physical_size`

---

## 🔍 What This Program Shows

When you allocate objects on the heap, the allocator does **not** simply place them back-to-back.

There may be:

- Alignment padding  
- Allocator metadata  
- Size rounding to bucket classes  
- Internal fragmentation  

This program gives a quick, practical look at how much space is actually consumed per allocation.

---

## 📦 Example Output

```text
DATA TYPE: Integer
 Address A: 0x55c8c4c8eeb0
 Address B: 0x55c8c4c8eed0
 Logical Size: 4
 Physical Size: 32
 Waste: 28
 Efficiency: 12.50%

---------------------------------------------------
```

Actual values will vary depending on:

- Compiler
- Standard library implementation
- Operating system
- Heap allocator (glibc, jemalloc, mimalloc, etc.)

---

## 🧠 How It Works

Core idea:

```cpp
T* p1 = new T();
T* p2 = new T();

uintptr_t addr1 = reinterpret_cast<uintptr_t>(p1);
uintptr_t addr2 = reinterpret_cast<uintptr_t>(p2);

size_t physical_size = std::abs(addr1 - addr2);
size_t logical_size = sizeof(T);
```

We treat the distance between two sequential allocations as an approximation of the real per-object heap cost.

---

## 🛠 Requirements

- C++20 (or newer)
- `<print>` support (C++23 for `std::println`)
- A compiler that supports `std::print`  
  - GCC 13+
  - Clang 16+ (with libc++)
  - MSVC recent versions

---

## ▶️ Build & Run

### GCC

```bash
g++ -std=c++23 main.cpp -o mem_analyzer
./mem_analyzer
```

### Clang

```bash
clang++ -std=c++23 main.cpp -o mem_analyzer
./mem_analyzer
```

---

## 📊 Tested Types

The program currently analyzes:

- `int`
- `long long`
- `double`
- `long double`
- `char`
- `std::string`

You can add more by calling:

```cpp
analyze_mem<YourType>("Your Type Name");
```

---

## ⚠️ Important Notes

- This is **not** an exact allocator profiler.
- It assumes allocations occur near each other (which is usually true in simple runs).
- Modern allocators use size classes, so spacing may not match `sizeof(T)` directly.
- Small objects are often rounded up to minimum block sizes (e.g., 16 or 32 bytes).

---

## 🎯 Why This Is Useful

This is helpful if you're:

- Studying allocator behavior
- Exploring fragmentation
- Designing custom allocators
- Thinking about memory efficiency in high-performance systems
- Curious about how expensive small heap allocations really are

---

## 🚀 Possible Extensions

- Run multiple allocations and compute averages
- Compare `new` vs `malloc`
- Test with custom allocators
- Measure cache-line alignment effects
- Benchmark allocation latency

---

## 📄 License

Use freely for experimentation and learning.
