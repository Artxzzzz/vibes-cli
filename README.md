<p align="center">
  <img src="https://github.com/user-attachments/assets/9737af79-b767-44cd-a2da-4ba5e60d4d41" width="200" height="200" alt="vibes logo">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/language-C-blue??cacheSeconds=300" alt="C">
  <a href="LICENSE">
    <img src="https://img.shields.io/github/license/Artxzzzz/vibes-cli?cacheSeconds=300" alt="License">
  </a>
  <img src="https://img.shields.io/github/stars/Artxzzzz/vibes-cli?cacheSeconds=300" alt="GitHub stars">
  <a href="https://github.com/Artxzzzz/vibes-cli/releases/latest">
    <img src="https://img.shields.io/github/v/release/Artxzzzz/vibes-cli?cacheSeconds=300" alt="Latest release">
  </a>
</p>

<br><br>

## 📝 Description

**vibes** is a CLI music player written in **C** for `Windows` and `Linux`, designed for those who are tired of heavy `GUI` players or ad-filled music programs.

## ⚙️ Requirements

* **GCC** or **Clang**
* Operating System: **Windows** and **Linux** (I don't know if it works on macOS yet)

**⚠️ Note:** if you are on Linux, make sure you have `libsdl2-dev` & `libsdl2-mixer-dev`. You can install them using:
``` bash
sudo apt install libsdl2-dev libsdl2-mixer-dev
```

<br>

## 💻 How to compile

```bash
# Clone the repository
git clone https://github.com/Artxzzzz/vibes-cli.git
cd vibes-cli
```

<br>

```bash
# Using make (recommended)
make

> If compiling manually, ensure your SDL2 paths are correctly set in your compiler flags.

# Or, if you want to compile manually with GCC (Windows PowerShell)
gcc (Get-ChildItem -Recurse src/*.c | ForEach-Object { $_.FullName }) -o vibes -IC:/SDL2/include -LC:/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -Wall -g
Or (Linux or Git Bash)
shopt -s globstar && gcc src/**/*.c -o vibes -lSDL2 -lSDL2_mixer -Wall -g
```

<br>

## ▶️ How to use

```bash
# After compiling, run with (Windows)
./vibes.exe <music/directory>
or (Linux)
./vibes <music/directory>

For more details help, use the flag -h or --help
```

<br>

## ✍️ How to contribute

* Fork or clone the repository:

  ```bash
  git clone https://github.com/Artxzzzz/vibes-cli.git
  ```
* Create a branch for your changes:

  ```bash
  git checkout -b my-feature
  ```
* Make your changes, commit, and push:

  ```bash
  git add .
  git commit -m "description of your changes"
  git push origin my-feature
  ```

- Now just open a **Pull Request**.

<br><br>

## 📂 Project structure

#### 📂 vibes/

* `src/`
  * `main.c`                - Program entry point and orchestration.
  * `config/`               - Versioning and global definitions.
  * `help/`                 - Command-line flags and user guidance.
  * `play/`                 - Core playback logic and stream flow.
    * `utils/`              - Path resolution, inputs, and progress bars.
  * `playDirectory/`        - Folder scanning and audio file validation.
  * `player/`               - Audio engine management and lifecycle.
  * `sleep/`                - Controlled delays and timing.
* `.gitignore`              - Keeping the workspace clean and focused.
* `Makefile`                - Automated build system.
* `LICENSE`
* `README.md`

<br>
