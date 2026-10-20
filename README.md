# Unlock All (Geometry Dash / Geode mod)

A [Geode](https://geode-sdk.org) mod for Geometry Dash 2.2081 that unlocks:

- every **icon** (cubes, ships, balls, UFOs, waves, robots, spiders, swings, jetpacks, death effects, trails, ship fire)
- every **color** (primary, secondary, glow)
- every **main level** (removes the secret coin requirement on Clubstep, Theory of Everything 2, Deadlocked, ...)

Each unlock has its own toggle in the mod settings. The mod does not edit your save file; disable it and everything is locked again.

## Install

1. Install [Geode](https://geode-sdk.org/install) for Geometry Dash.
2. Download `cheese123113.unlock-all.geode` from the [latest release](https://github.com/cheese123113/gd-unlock-all/releases/latest).
3. Put it in your Geode mods folder (in game: Geode menu → settings icon → *Open Mods Folder*), then restart the game.

## Build

Every push is built for Windows, macOS, iOS and Android by GitHub Actions; the combined `.geode` file is uploaded as the **Build Output** artifact of the workflow run.

To build locally, install the [Geode SDK and CLI](https://docs.geode-sdk.org/getting-started/), then:

```sh
geode build
```

## How it works

- `GameManager::isIconUnlocked` and `GameManager::isColorUnlocked` are hooked to return `true`.
- `LevelPage::updateDynamicPage` and `LevelPage::onPlay` temporarily set the level's required coin count to 0 while the page is drawn or played.
