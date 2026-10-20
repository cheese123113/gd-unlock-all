#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/LevelPage.hpp>

using namespace geode::prelude;

static bool isEnabled(std::string_view key) {
    return Mod::get()->getSettingValue<bool>(key);
}

// Icons and colors: the icon kit asks GameManager whether each item is unlocked.
class $modify(UnlockAllGameManager, GameManager) {
    bool isIconUnlocked(int id, IconType type) {
        if (isEnabled("unlock-icons")) return true;
        return GameManager::isIconUnlocked(id, type);
    }

    bool isColorUnlocked(int id, UnlockType type) {
        if (isEnabled("unlock-colors")) return true;
        return GameManager::isColorUnlocked(id, type);
    }
};

// Main levels are locked behind a secret coin requirement. Zero it only while
// the level page is drawn or played, so turning the setting off restores the lock.
class CoinRequirementOverride {
    GJGameLevel* m_level = nullptr;
    int m_saved = 0;

public:
    explicit CoinRequirementOverride(GJGameLevel* level) {
        if (level && isEnabled("unlock-levels")) {
            m_level = level;
            m_saved = level->m_requiredCoins;
            level->m_requiredCoins = 0;
        }
    }

    ~CoinRequirementOverride() {
        if (m_level) m_level->m_requiredCoins = m_saved;
    }

    CoinRequirementOverride(CoinRequirementOverride const&) = delete;
    CoinRequirementOverride& operator=(CoinRequirementOverride const&) = delete;
};

class $modify(UnlockAllLevelPage, LevelPage) {
    void updateDynamicPage(GJGameLevel* level) {
        CoinRequirementOverride override(level);
        LevelPage::updateDynamicPage(level);
    }

    void onPlay(CCObject* sender) {
        CoinRequirementOverride override(m_level);
        LevelPage::onPlay(sender);
    }
};
