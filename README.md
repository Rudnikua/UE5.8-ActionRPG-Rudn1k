# Third-Person Action RPG Prototype (Unreal Engine 5 / C++)

![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.8-black?logo=unrealengine)
![C++](https://img.shields.io/badge/Language-C%2B%2B20-00599C?logo=cplusplus)
![Input](https://img.shields.io/badge/System-Enhanced%20Input-blue)
![Audio](https://img.shields.io/badge/Audio-MetaSounds-purple)

A third-person Action RPG / Hack-and-Slash prototype built in **Unreal Engine 5** with a focus on clean, modular **C++ gameplay architecture**, vector-math combat mechanics, custom animation notifies, and state-machine-driven Enemy AI.

> **Course Project Acknowledgment:** This prototype was developed as part of the *Unreal Engine 5 C++: The Ultimate Game Developer Course* by **Stephen Ulibarri**, extended with custom combat polish, audio notify states, and enemy death physics.

---

## 🎥 Gameplay Showcase
> https://github.com/user-attachments/assets/4b49b795-320c-4316-8d86-32f991d5f3d0

---

## ⚙️ Core C++ Architecture & Technical Highlights

### 1. Character Hierarchy & Decoupled Combat
* **Inheritance Structure:** Built around a shared `ABaseCharacter` base class that encapsulates common combat attributes, montage playback, and damage handling, extended by `AMainCharacter` (player input and movement) and `AEnemy` (AI behavior).
* **Frame-Accurate Melee Hit Detection:** Instead of relying on overlap events on fast-moving meshes, weapon collisions are evaluated via per-frame `BoxTraceSingle` sweeps between `BoxTraceStart` and `BoxTraceEnd` sockets along the blade.
* **Interface-Based Hit Resolution:** Damageable actors implement `IHitInterface` (`GetHit_Implementation`), decoupling weapon trace logic from target-specific reactions (enemies, destructible props, etc.).

### 2. Vector-Math Directional Hit Reactions
* Calculates the exact angle of incoming strikes relative to the victim's forward vector using **Dot Product** and **Cross Product** (`DirectionalHitReact`).
* Maps the resulting angle to select and play the corresponding directional hit-react animation montage section (`FromFront`, `FromBack`, `FromLeft`, `FromRight`).

### 3. C++ Enemy AI (Finite State Machine)
* **Custom State Machine (`EEnemyState`):** Manages transitions across `Patrolling`, `Chasing`, `Attacking`, `Engaged`, and `Dead` states directly in C++.
* **Perception & Delegate Binding:** Uses `UPawnSensingComponent` bound dynamically via `OnSeePawn.AddDynamic` to detect player targets within sight radius and cone angle.
* **Natural Combat Pacing:** Implements randomized patrol wait timers and attack window timers (`AttackMinTime` – `AttackMaxTime`), attack interruption on incoming hits, and dynamic death handling (AnimGraph death poses for armored knights vs. full skeletal mesh **Ragdoll** simulation for insect enemies).

### 4. Custom Audio & Animation Notifies
* **MetaSounds Integration:** Created a custom C++ `UNotifyState_SlideSound` (`UAnimNotifyState`) to dynamically control audio fade-out durations during player dodge/slide animations.
* **Combat Flow:** Randomized attack montage section selection and state-guarded Enhanced Input triggers (`Started`) to prevent animation clipping or accidental weapon disarming.

### 5. Attributes, Stamina & Economy Loop
* Custom `UAttributeComponent` tracking Health, Stamina (with continuous regeneration and dodge cost), Gold, and Souls.
* Defeated enemies spawn collectible `ASoul` actors with Niagara VFX, updating the player's HUD (`MainOverlay`) and floating enemy health bars in real time.

---

## 🕹️ Controls (Enhanced Input)

| Key / Input | Action |
| :--- | :--- |
| **W A S D** | Move character (camera-relative) |
| **Mouse** | Orbit camera (`SpringArm`) |
| **Space** | Jump (when unoccupied) |
| **Left Mouse Button** | Melee Attack (combo chain) |
| **Ctrl** | Dodge / Slide (consumes Stamina) |
| **E** | Contextual Interact (Pick up weapon / Equip & Disarm) |

---

## 📂 Repository Structure

To comply with GitHub LFS storage limits and Fab / Unreal Marketplace asset licensing rules, heavy third-party visual asset packs are excluded via `.gitignore`. All **C++ source code**, **configuration files**, **custom Blueprints**, and **core maps** are included for code review.

```text
├── Config/                 # Engine, Input Mapping Contexts, and Collision profiles
├── Content/
│   ├── Blueprints/         # Player, Enemy, Weapon, and UI Widget Blueprints
│   ├── Effects/            # Niagara particle systems & custom materials
│   └── Maps/               # Playable test arena & level data
├── Source/                 # Complete C++ source code (.h, .cpp, .Build.cs)
├── .gitattributes          # Git LFS tracking rules for .uasset and .umap
├── .gitignore              # Excludes Binaries, Intermediate, Saved, and third-party packs
└── BP_UdemyCPP.uproject    # Unreal Engine project manifest
