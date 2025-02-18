#include "Geode/binding/AchievementManager.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <capeling.garage-stats-menu/include/StatsDisplayAPI.h>

using namespace geode::prelude;

class $modify(MyGJGarageLayer, GJGarageLayer) {
public:
    struct Fields {
        ProfilePage* m_profilePopup = ProfilePage::create(GJAccountManager::sharedState()->m_accountID, true);
    };

    bool init() {
        if (!GJGarageLayer::init()) {
            return false;
        }

        auto statMenu = this->getChildByID("capeling.garage-stats-menu/stats-menu");
        auto demons = StatsDisplayAPI::getNewItem("demons"_spr, CCSprite::createWithSpriteFrameName("GJ_demonIcon_001.png"), GameStatsManager::sharedState()->getStat("5"));
        auto demonKeys = StatsDisplayAPI::getNewItem("demon-keys"_spr, CCSprite::createWithSpriteFrameName("GJ_bigKey_001.png"), GameStatsManager::sharedState()->getStat("21"), 0.375);
        auto goldKeys = StatsDisplayAPI::getNewItem("gold-keys"_spr, CCSprite::createWithSpriteFrameName("GJ_bigGoldKey_001.png"), GameStatsManager::sharedState()->getStat("43"), 0.375);
        auto achievements = StatsDisplayAPI::getNewItem("achievements"_spr, CCSprite::createWithSpriteFrameName("rankIcon_top10_001.png"), 0, 0.5);

        // Get achievement percentage and set it on the label
        // CCLabelBMFont* achLabel = typeinfo_cast<CCLabelBMFont*>(achievements->getChildByID("achievements-label"_spr));
        // if (achLabel) {
        //     achLabel->setString(fmt::format("{}%", this->getAllAchievementsPercent()).c_str());  // Set the achievements percentage
        // }

        if (statMenu) {
            statMenu->addChild(demons);
            statMenu->addChild(demonKeys);
            statMenu->addChild(goldKeys);
            // statMenu->addChild(achievements);
            statMenu->updateLayout();
        }

        return true;
    }

    void onStars(CCObject*) {
        auto popup = static_cast<MyGJGarageLayer*>(this)->m_fields->m_profilePopup;
        auto layer = popup->getChildByType<CCLayer*>(0);
        CCMenuItemSpriteExtra* starsBtn = typeinfo_cast<CCMenuItemSpriteExtra*>(layer->getChildByID("stats-menu")->getChildByID("stars-icon"));
        starsBtn->activate();
    }

private:
    float getAllAchievementsPercent() {
        float achievementPercent = 0.f;
        int totalEarned = 0;
        int totalAchievements = AchievementManager::sharedState()->m_allAchievements->count();

		for (int i = 0; i < AchievementManager::sharedState()->m_allAchievements->count(); ++i) {
			auto achievement = static_cast<cocos2d::CCDictionary*>(AchievementManager::sharedState()->m_allAchievements->objectAtIndex(i));

			auto achievementID = achievement->valueForKey("id")->getCString();

			if (AchievementManager::sharedState()->isAchievementEarned(achievementID)) {
				totalEarned++;
			}
		}

        if (totalAchievements > 0) {
            achievementPercent = (static_cast<float>(AchievementManager::sharedState()->m_achievementUnlocks->count()) / static_cast<float>(totalAchievements)) * 100;
        }

        return achievementPercent;
    }
};
