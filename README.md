# LRUCache — High-Efficiency C++ LRU Cache

A lightweight, **generic** Least Recently Used (LRU) cache implementation in C++ using templates, optimized with:

* **O(1) average complexity** for both `get()` and `put()` operations (via `std::unordered_map` + `std::list`).
* **Generic key and value types** via templates.
* **Bazel build system** for reproducibility and speed.
* **Google Test** for unit testing.

---

## 🚀 Features

* **Generic** — works with any key/value types.
* **Automatic eviction** — when capacity is reached, least recently used entries are removed.
* **Efficient** — operations run in O(1) time.
* **Easy integration** — header-only design (`.h` + `.tpp`) makes it simple to reuse in other projects.
* **Debugging helpers** — includes `printCacheEntries()` utility.

---

## 🛠️ Build Instructions

This project uses **Bazel** as the build system.

### Build main program

```bash
bazel build //src:mainProg
```

### Run main program

```bash
./bazel-bin/src/mainProg
```

---

## ✅ Running Tests

Tests are written using **Google Test** and integrated with Bazel:

```bash
bazel test test --test_output=all
```

This runs all unit tests and prints failures directly.

---

## 🖥️ Example Usage

See src/main.cpp or test/test.cpp.

---

## ⚡ CI/CD with GitHub Actions

This repo includes a **GitHub Actions workflow** (`.github/workflows/ci.yml`) that:

* Builds the project with Bazel.
* Runs all Google Tests.
* Uses Bazel caching (`disk-cache`, `repository-cache`, etc.) for fast runs.

---

## 📜 License

MIT License © 2025