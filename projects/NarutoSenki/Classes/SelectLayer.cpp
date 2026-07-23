#include "SelectLayer.h"
#include "StartMenu.h"
USING_NS_CC_EXT;
using namespace CocosDenshion;
#include<time.h>


SelectLayer::SelectLayer(void)
{
	_heroHalf=NULL;
	_heroName=NULL;
	_selectImg=NULL;
	_selectHero=NULL;
	
	isStart=false;
	_isHardCoreMode=CCUserDefault::sharedUserDefault()->getBoolForKey("isHardCore"); // follow HardCore unlock flag (unlocked by default)

	SaveError=false;
	_playerSelect=NULL;
	selectArray=NULL;


}


SelectLayer::~SelectLayer(void)
{
	CC_SAFE_RELEASE(selectArray);
	
}

bool SelectLayer::init(){

	bool bRet=false;
	do{
		CC_BREAK_IF(!CCLayer::init());

			//¼ÓÔØÐòÁÐ¼¯	
		    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Record.plist");
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Record2.plist");		
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI.plist");
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Report.plist");
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Ougis.plist");
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Ougis2.plist");
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Map.plist");
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Gears.plist");
			
			KTools* tool= KTools::create();

			if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
				if(false && tool->checkMD5()==0){ /* anti-tamper kill-gate disabled (personal port) */
					SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
					CCDirector::sharedDirector()->end();
					return false;
				}
			}
			
			
		char* bg_src="red_bg.png";
		
		CCSprite* bgSprite = CCSprite::create(bg_src);
		bgSprite->setAnchorPoint(ccp(0,0));
		bgSprite->setPosition(ccp(0,0));
		this->addChild(bgSprite, -5);

		//produce groud 


		CCSprite* gold_left=CCSprite::createWithSpriteFrameName("gold_left.png");
		gold_left->setAnchorPoint(ccp(0,0));
		gold_left->setPosition(ccp(0,20));
		this->addChild(gold_left,1);


		CCSprite* gold_right=CCSprite::createWithSpriteFrameName("gold_right.png");
		gold_right->setAnchorPoint(ccp(0,1));
		gold_right->setPosition(ccp(winSize.width-gold_right->getContentSize().width-20,winSize.height-20));
		this->addChild(gold_right,1);


		//produce the cloud
		CCSprite* cloud_left=CCSprite::createWithSpriteFrameName("cloud.png");	
		cloud_left->setPosition(ccp(0,15));
		cloud_left->setFlipX(true);
		cloud_left->setFlipY(true);
		cloud_left->setAnchorPoint(ccp(0,0));
		this->addChild(cloud_left,2);

		CCActionInterval* cmv1=CCMoveBy::create(1,ccp(-15,0));
		CCAction* cseq1=CCRepeatForever::create(CCSequence::create(cmv1,cmv1->reverse(),NULL));
		cloud_left->runAction(cseq1);

		CCSprite* cloud_right=CCSprite::createWithSpriteFrameName("cloud.png");	
		cloud_right->setPosition(ccp(winSize.width-cloud_right->getContentSize().width,15));
		cloud_right->setFlipY(true);
		cloud_right->setAnchorPoint(ccp(0,0));
		this->addChild(cloud_right,2);

		CCActionInterval* cmv2=CCMoveBy::create(1,ccp(15,0));
		CCAction* cseq2=CCRepeatForever::create(CCSequence::create(cmv2,cmv2->reverse(),NULL));
		cloud_right->runAction(cseq2);

		CCSprite* cloud_top=CCSprite::createWithSpriteFrameName("cloud_top.png");
		cloud_top->setPosition(ccp(winSize.width/2,winSize.height-(cloud_top->getContentSize().height+12)));
		cloud_top->setAnchorPoint(ccp(0.5f,0));
		this->addChild(cloud_top,1);

		
		//produce the menu_bar
		CCSprite* menu_bar_b = CCSprite::create("menu_bar2.png");
		menu_bar_b->setAnchorPoint(ccp(0,0));
		this->addChild(menu_bar_b,2);

		


		CCSprite* menu_bar_t = CCSprite::create("menu_bar3.png");
		menu_bar_t->setAnchorPoint(ccp(0,0));
		menu_bar_t->setPosition(ccp(0,winSize.height-menu_bar_t->getContentSize().height));
		this->addChild(menu_bar_t,2);

		
		if(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("select_title.png")){ // title frame is missing in this build's resources; skip if absent to avoid crash
		CCSprite* select_title=CCSprite::createWithSpriteFrameName("select_title.png");
		select_title->setAnchorPoint(ccp(0,0));
		select_title->setPosition(ccp(2,winSize.height-select_title->getContentSize().height-2));
		this->addChild(select_title,3);
		}

		

		if(!SaveError){
			int first_player=NULL;
			selectArray=CCArray::create();
			
			char* selectList[]={"Naruto","Sakura","Sai","Kakashi","None","None","None",
				"Shikamaru","Ino","Choji","Asuma","Kiba","Hinata","Shino",
				"Neji","Tenten","Lee","None","None","None","None",
				"None","Tobirama","Hiruzen","Minato","Jiraiya","Tsunade","Orochimaru",
				"None","Deidara","Kakuzu","Hidan","Tobi","Konan","Pain",
				"Itachi","Kisame","None","None","None","None","None",
				"Sasuke","Karin","Suigetsu","Jugo","None","None","None",
				"Gaara","None","Kankuro","Chiyo","None","None","None",
				"None","None","None","None","None","None","None"
			};

			int num= sizeof(selectList)/sizeof(char*);
			_pageLayer1=CCLayer::create();
			_pageLayer2=CCLayer::create();
			_pageLayer3=CCLayer::create();
			this->addChild(_pageLayer1,2);
			this->addChild(_pageLayer2,2);
			this->addChild(_pageLayer3,2);
			for(int i=0;i<num;i++){
				CCString* path;
				const char* charName;
				
				path=CCString::createWithFormat("%s_select.png",selectList[i]);
				charName=selectList[i];
				
				SelectButton* select_btn=SelectButton::create(path->getCString());
				select_btn->setDelegate1(this);

				select_btn->setCharName(CCString::createWithFormat("%s",charName));
				int Column=i%7;
				int Page=i/21;
				int Row=(i/7)-Page*3;
				select_btn->setPosition(ccp(winSize.width/2-36+(Column-1)*27+Column/4*10,winSize.height-112-(72*Row)));
				if(Page==0){
					_pageLayer1->addChild(select_btn,-Column);
				}else if(Page==1){
					_pageLayer2->addChild(select_btn,-Column);
				}else{
					_pageLayer3->addChild(select_btn,-Column);
				}
				selectArray->addObject(select_btn);

			};
			selectArray->retain();
			_pageBtn1=CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("page1_off.png"),CCSprite::createWithSpriteFrameName("page1_on.png"),this,menu_selector(SelectLayer::onPage1));
			_pageBtn2=CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("page2_off.png"),CCSprite::createWithSpriteFrameName("page2_on.png"),this,menu_selector(SelectLayer::onPage2));
			_pageBtn3=CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("page3_off.png"),CCSprite::createWithSpriteFrameName("page3_on.png"),this,menu_selector(SelectLayer::onPage3));
			CCMenu* page_menu=CCMenu::create(_pageBtn1,_pageBtn2,_pageBtn3,NULL);
			page_menu->alignItemsHorizontallyWithPadding(20);
			page_menu->setPosition(ccp(winSize.width/2+48,42));
			this->addChild(page_menu,10);
			showPage(1);
		
			
			first_player=0;
			

			const char* path=CCString::createWithFormat("%s_half.png",selectList[first_player])->getCString();
			_heroHalf=CCSprite::createWithSpriteFrameName(path);
			_heroHalf->setAnchorPoint(ccp(0,0));
			_heroHalf->setPosition(ccp(10,10));
			this->addChild(_heroHalf,1);
			num2=num;
			const char* namePath=CCString::createWithFormat("%s_font.png",selectList[first_player])->getCString();
			_heroName=CCSprite::createWithSpriteFrameName(namePath);
			_heroName->setAnchorPoint(ccp(0.5f,0));
			_heroName->setPosition(ccp(100,20));
			this->addChild(_heroName,5);


			_selectImg=CCSprite::createWithSpriteFrameName("1p.png");
			_selectImg->setAnchorPoint(ccp(0,0));
			SelectButton* pObject=(SelectButton*) selectArray->objectAtIndex(first_player);
			_selectImg->setPosition(ccp(pObject->getPositionX()-2,pObject->getPositionY()-2));
			_pageLayer1->addChild(_selectImg,500);

			_selectHero=pObject->getCharName()->getCString();

			CCActionInterval* blink=CCBlink::create(0.6f,1);
			_selectImg->runAction(CCRepeatForever::create(blink));


			CCMenuItem* start_bt=CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("start_btn.png"),NULL,NULL,this,menu_selector(SelectLayer::onGameStart));
			CCMenu* menu =CCMenu::create(start_bt,NULL);
			menu->setAnchorPoint(ccp(0,0));
			menu->setPosition(winSize.width-40,36);
			this->addChild(menu,500);



			CCMenuItem* skill_bt=CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("skill_btn.png"),NULL,NULL,this,menu_selector(SelectLayer::onSkillMenu));
			CCMenu* menu2 =CCMenu::create(skill_bt,NULL);
			menu2->setAnchorPoint(ccp(0,0));
			menu2->setPosition(winSize.width-35,96);
			this->addChild(menu2,5);

			

			if(CCUserDefault::sharedUserDefault()->getBoolForKey("isBGM")!=false){
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Audio/Music/select_music.mp3",true);
			}

			this->setKeypadEnabled(true); // was Android-only; enabled on all platforms for PC ESC/F1 back
			
			
		}


		bRet=true;
	}while(0);

	return bRet;

}

void SelectLayer::setSelected(CCObject* sender){
	SelectButton* btn=(SelectButton*) sender;

	 _selectImg->retain();
	 _selectImg->removeFromParentAndCleanup(false);
	 btn->getParent()->addChild(_selectImg,500);
	 _selectImg->release();
	 _selectImg->setPosition(ccp(btn->getPositionX()-2,btn->getPositionY()-2));
	
	 _heroHalf->removeFromParent();
	 const char* path=CCString::createWithFormat("%s_half.png",btn->getCharName()->getCString())->getCString();
	 _heroHalf=CCSprite::createWithSpriteFrameName(path);

	 _heroHalf->setAnchorPoint(ccp(0,0));
	 _heroHalf->setPosition(ccp(10,10));
	 this->addChild(_heroHalf,1);

	 _heroName->removeFromParent();
	 const char* namePath=CCString::createWithFormat("%s_font.png",btn->getCharName()->getCString())->getCString();
	 _heroName=CCSprite::createWithSpriteFrameName(namePath);
	 _heroName->setAnchorPoint(ccp(0.5f,0));
	 _heroName->setPosition(ccp(100,20));
	 this->addChild(_heroName,5);

	_selectHero=btn->getCharName()->getCString();

}


void SelectLayer::onError(CCObject* sender){

	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCDirector::sharedDirector()->end();
	return;

}


void SelectLayer::onSkillMenu(CCObject* sender){

	CCScene* pscene =CCScene::create();
	SkillLayer* skillLayer=SkillLayer::create();
	skillLayer->setDelegate(this);
	skillLayer->initInterface();
	pscene->addChild(skillLayer);

	CCDirector::sharedDirector()->pushScene(pscene);

}



void SelectLayer::onGameStart(CCObject* sender){

	

	if (!isStart){

		KTools* tool= KTools::create();

		

		isStart=true;
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");


		CCDictionary* dic=CCDictionary::create();

		CCString* tmpChar;


		char* heroList[]={"Konan","Sakura","Naruto","Sai","Deidara",
			"Kakashi","Itachi","Tenten","Jiraiya","Suigetsu",
			"Tsunade","Tobirama","Neji","Ino","Asuma","Gaara",
			"Karin","Sasuke","Hidan","Choji","Kankuro",
			"Shino","Minato","Tobi","Kakuzu","Hinata",
			"Hiruzen","Kiba","Jugo","Lee"
		};


		int num= sizeof(heroList)/sizeof(char*);

		
		tmpChar=CCString::create(_selectHero);
		
		srand((int)time(0));
		int zhenying=1;
		



		CCString* tmpRole=CCString::create("Player");
		CCString* tmpGroup=CCString::create("Konoha");

		dic->setObject(tmpChar,"character");
		dic->setObject(tmpRole,"role");
		dic->setObject(tmpGroup,"group");

		CCArray* tempHeros=CCArray::createWithObject(dic);

		

		CCArray* realHero=CCArray::create();
		
		for(int i=0;i<num;i++){
			if(strcmp(tmpChar->getCString(),heroList[i])==0){
				continue;
			}		
			CCString* hero=CCString::create(heroList[i]);
			realHero->addObject(hero);
		
		}


		for(int i=0;i<5;i++){
			CCString* hero;
			if(i<2){

				
				int length=realHero->count();
				srand((int)time(0));
				int index=random(length);
				if(index==(int)realHero->count()){
					index=realHero->count()-1;
				}

				CCObject* tempObject=realHero->objectAtIndex(index);
				hero=(CCString*) tempObject;
				realHero->removeObjectAtIndex(index);
				
				dic=CCDictionary::create();
				tmpChar=CCString::create(hero->getCString());
				tmpRole=CCString::create("Com");
				
				tmpGroup=CCString::create("Konoha");
				
				dic->setObject(tmpChar,"character");
				dic->setObject(tmpRole,"role");
				dic->setObject(tmpGroup,"group");

				tempHeros->addObject(dic);
				

			}else{
				int length=realHero->count();
				srand((int)time(0));
				int index=random(length);
				if(index==(int)realHero->count()){
					index=realHero->count()-1;
				}

				CCObject* tempObject=realHero->objectAtIndex(index);
				CCString* hero=(CCString*) tempObject;

				dic=CCDictionary::create();
				tmpChar=CCString::create(hero->getCString());
				tmpRole=CCString::create("Com");
				
				tmpGroup=CCString::create("Akatsuki");
				
				dic->setObject(tmpChar,"character");
				dic->setObject(tmpRole,"role");
				dic->setObject(tmpGroup,"group");

				tempHeros->addObject(dic);
				realHero->removeObjectAtIndex(index);

			} 

		}



		CCScene* loadScene=CCScene::create();
		LoadLayer* loadLayer=LoadLayer::create();
		loadLayer->tempHeros=tempHeros;
		loadScene->addChild(loadLayer);
		
		loadLayer->_isHardCoreMode=_isHardCoreMode;
		loadLayer->preloadAudio();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,loadScene));
	

	}
}


void SelectLayer::keyBackClicked(){
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/cancel.ogg");	
	CCScene* menuScene =CCScene::create();
	CCLayer* menuLayer=StartMenu::create();
	menuScene->addChild(menuLayer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,menuScene));

}

void SelectLayer::showPage(int p){
	_pageLayer1->setVisible(p==1); _pageLayer1->setPositionY(p==1?0:2000);
	_pageLayer2->setVisible(p==2); _pageLayer2->setPositionY(p==2?0:2000);
	_pageLayer3->setVisible(p==3); _pageLayer3->setPositionY(p==3?0:2000);
	_pageBtn1->setNormalImage(CCSprite::createWithSpriteFrameName(p==1?"page1_on.png":"page1_off.png"));
	_pageBtn2->setNormalImage(CCSprite::createWithSpriteFrameName(p==2?"page2_on.png":"page2_off.png"));
	_pageBtn3->setNormalImage(CCSprite::createWithSpriteFrameName(p==3?"page3_on.png":"page3_off.png"));
}
void SelectLayer::onPage1(CCObject* sender){ showPage(1); }
void SelectLayer::onPage2(CCObject* sender){ showPage(2); }
void SelectLayer::onPage3(CCObject* sender){ showPage(3); }


SelectLayer* SelectLayer::create(){

	SelectLayer* sl=new SelectLayer();
	if (sl && sl->init())
	{
		sl->autorelease();
		return sl;
	}
	else
	{
		delete sl;
		return NULL;
	}
}
