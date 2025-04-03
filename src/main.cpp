#include "Geode/binding/AchievementManager.hpp"
#include "Geode/binding/GameManager.hpp"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
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

        auto fireShard = StatsDisplayAPI::getNewItem("fire-shards"_spr, CCSprite::createWithSpriteFrameName("fireShardBig_001.png"), GameStatsManager::sharedState()->getStat("18"), 0.35);
        auto iceShard = StatsDisplayAPI::getNewItem("ice-shards"_spr, CCSprite::createWithSpriteFrameName("iceShardBig_001.png"), GameStatsManager::sharedState()->getStat("19"), 0.35);
        auto poisonShard = StatsDisplayAPI::getNewItem("poison-shards"_spr, CCSprite::createWithSpriteFrameName("poisonShardBig_001.png"), GameStatsManager::sharedState()->getStat("17"), 0.35);
        auto shadowShard = StatsDisplayAPI::getNewItem("shadow-shards"_spr, CCSprite::createWithSpriteFrameName("shadowShardBig_001.png"), GameStatsManager::sharedState()->getStat("16"), 0.35);
        auto lavaShard = StatsDisplayAPI::getNewItem("lava-shards"_spr, CCSprite::createWithSpriteFrameName("lavaShardBig_001.png"), GameStatsManager::sharedState()->getStat("20"), 0.35);
        // auto bonusShard1 = StatsDisplayAPI::getNewItem("bonus-shards-one"_spr, CCSprite::createWithSpriteFrameName("bonusShardSmall_001.png"), GameStatsManager::sharedState()->getStat("23"), 0.5);

        auto earthShard = StatsDisplayAPI::getNewItem("earth-shards"_spr, CCSprite::createWithSpriteFrameName("shard0201ShardBig_001.png"), GameStatsManager::sharedState()->getStat("23"), 0.35);
        auto bloodShard = StatsDisplayAPI::getNewItem("blood-shards"_spr, CCSprite::createWithSpriteFrameName("shard0202ShardBig_001.png"), GameStatsManager::sharedState()->getStat("24"), 0.35);
        auto metalShard = StatsDisplayAPI::getNewItem("metal-shards"_spr, CCSprite::createWithSpriteFrameName("shard0203ShardBig_001.png"), GameStatsManager::sharedState()->getStat("25"), 0.35);
        auto lightShard = StatsDisplayAPI::getNewItem("light-shards"_spr, CCSprite::createWithSpriteFrameName("shard0204ShardBig_001.png"), GameStatsManager::sharedState()->getStat("26"), 0.35);
        auto soulShard = StatsDisplayAPI::getNewItem("soul-shards"_spr, CCSprite::createWithSpriteFrameName("shard0205ShardBig_001.png"), GameStatsManager::sharedState()->getStat("27"), 0.35);
        // auto bonusShard2 = StatsDisplayAPI::getNewItem("bonus-shards-two"_spr, CCSprite::createWithSpriteFrameName("bonusShard2Small_001.png"), GameStatsManager::sharedState()->getStat("28"), 0.5);

        // Get achievement percentage and set it on the label
        // CCLabelBMFont* achLabel = typeinfo_cast<CCLabelBMFont*>(achievements->getChildByID("achievements-label"_spr));
        // if (achLabel) {
        //     achLabel->setString(fmt::format("{}%", this->getAllAchievementsPercent()).c_str());  // Set the achievements percentage
        // }

        if (statMenu) {
            if (Mod::get()->getSettingValue<bool>("demons")) statMenu->addChild(demons);
            if (Mod::get()->getSettingValue<bool>("demonKeys")) {
                // if (Mod::get()->getSettingValue<bool>("complete-demon-keys")) {
                //     CCLabelBMFont* demonKeyText = typeinfo_cast<CCLabelBMFont*>(demonKeys->getChildByID("demon-keys-label"_spr));
                //     demonKeyText->setString((std::to_string(GameStatsManager::sharedState()->getStat("21")) + "/" + "i give up lol").c_str()); // GS_20
                // }
                statMenu->addChild(demonKeys);
            };
            if (Mod::get()->getSettingValue<bool>("goldKeys")) statMenu->addChild(goldKeys);
            // if (Mod::get()->getSettingValue<bool>("achievements")) statMenu->addChild(achievements);
            if (Mod::get()->getSettingValue<bool>("show-shards")) {
                if (Mod::get()->getSettingValue<bool>("show-shards-completed")) {
                    statMenu->addChild(fireShard);
                    statMenu->addChild(iceShard);
                    statMenu->addChild(poisonShard);
                    statMenu->addChild(shadowShard);
                    statMenu->addChild(lavaShard);
                    // statMenu->addChild(bonusShard1);
                    statMenu->addChild(earthShard);
                    statMenu->addChild(bloodShard);
                    statMenu->addChild(metalShard);
                    statMenu->addChild(lightShard);
                    statMenu->addChild(soulShard);
                    // statMenu->addChild(bonusShard2);

                    if (auto label = typeinfo_cast<CCLabelBMFont*>(fireShard->getChildByID("fire-shards-label"_spr)))
                        if (GameStatsManager::sharedState()->getStat("18") == 100) label->setColor(ccc3(0, 255, 0));
                    if (auto label = typeinfo_cast<CCLabelBMFont*>(iceShard->getChildByID("ice-shards-label"_spr)))
                        if (GameStatsManager::sharedState()->getStat("19") == 100) label->setColor(ccc3(0, 255, 0));
                    if (auto label = typeinfo_cast<CCLabelBMFont*>(poisonShard->getChildByID("poison-shards-label"_spr)))
                        if (GameStatsManager::sharedState()->getStat("17") == 100) label->setColor(ccc3(0, 255, 0));
                    if (auto label = typeinfo_cast<CCLabelBMFont*>(shadowShard->getChildByID("shadow-shards-label"_spr)))
                        if (GameStatsManager::sharedState()->getStat("16") == 100) label->setColor(ccc3(0, 255, 0));
                    if (auto label = typeinfo_cast<CCLabelBMFont*>(lavaShard->getChildByID("lava-shards-label"_spr)))
                        if (GameStatsManager::sharedState()->getStat("20") == 100) label->setColor(ccc3(0, 255, 0));
                    if (auto label = typeinfo_cast<CCLabelBMFont*>(earthShard->getChildByID("earth-shards-label"_spr)))
                        if (GameStatsManager::sharedState()->getStat("23") == 100) label->setColor(ccc3(0, 255, 0));
                    if (auto label = typeinfo_cast<CCLabelBMFont*>(bloodShard->getChildByID("blood-shards-label"_spr)))
                        if (GameStatsManager::sharedState()->getStat("24") == 100) label->setColor(ccc3(0, 255, 0));
                    if (auto label = typeinfo_cast<CCLabelBMFont*>(metalShard->getChildByID("metal-shards-label"_spr)))
                        if (GameStatsManager::sharedState()->getStat("25") == 100) label->setColor(ccc3(0, 255, 0));
                    if (auto label = typeinfo_cast<CCLabelBMFont*>(lightShard->getChildByID("light-shards-label"_spr)))
                        if (GameStatsManager::sharedState()->getStat("26") == 100) label->setColor(ccc3(0, 255, 0));
                    if (auto label = typeinfo_cast<CCLabelBMFont*>(soulShard->getChildByID("soul-shards-label"_spr)))
                        if (GameStatsManager::sharedState()->getStat("27") == 100) label->setColor(ccc3(0, 255, 0));
                } else {
                    if (GameStatsManager::sharedState()->getStat("18") != 100) statMenu->addChild(fireShard);
                    if (GameStatsManager::sharedState()->getStat("19") != 100) statMenu->addChild(iceShard);
                    if (GameStatsManager::sharedState()->getStat("17") != 100) statMenu->addChild(poisonShard);
                    if (GameStatsManager::sharedState()->getStat("16") != 100) statMenu->addChild(shadowShard);
                    if (GameStatsManager::sharedState()->getStat("20") != 100) statMenu->addChild(lavaShard);
                    // statMenu->addChild(bonusShard1);
                    if (GameStatsManager::sharedState()->getStat("23") != 100) statMenu->addChild(earthShard);
                    if (GameStatsManager::sharedState()->getStat("24") != 100) statMenu->addChild(bloodShard);
                    if (GameStatsManager::sharedState()->getStat("25") != 100) statMenu->addChild(metalShard);
                    if (GameStatsManager::sharedState()->getStat("26") != 100) statMenu->addChild(lightShard);
                    if (GameStatsManager::sharedState()->getStat("27") != 100) statMenu->addChild(soulShard);
                    // statMenu->addChild(bonusShard2);
                }
            }
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
